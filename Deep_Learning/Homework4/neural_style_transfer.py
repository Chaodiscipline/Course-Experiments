import torch
import torch.nn as nn
from torch.autograd import Variable
import torchvision
from torchvision import transforms, models
from PIL import Image
import argparse
import numpy as np

#定义加载图像函数，并将PIL image转化为Tensor
use_gpu = torch.cuda.is_available() #查看gpu是否可用
dtype = torch.cuda.FloatTensor if use_gpu else torch.FloatTensor  # 根据是否用gpu选取tensor类型

def load_image(image_path, transforms=None, max_size=None, shape=None):
    image = Image.open(image_path)
    image_size = image.size  # w*h

    if max_size is not None:  #对content图像做以下处理resize
        #获取图像size，为sequence #sequence分为list和tuple，这里是tuple
        image_size = image.size
        #转化为float的array
        size = np.array(image_size).astype(float)  # astype 强制类型转换为float 
        size = max_size / size * size;  # max_size为一个标量，max_size/size*size 即对应相除再相乘，结果size的每个元素都为max_size
        image = image.resize(size.astype(int), Image.ANTIALIAS)  # antialias平滑

    if shape is not None:  #对style图像做以下处理resize
        image = image.resize(shape, Image.LANCZOS) # lanczos 一种插值滤波方法

    #必须提供transform.ToTensor，转化为4D Tensor
    if transforms is not None:
        image = transforms(image).unsqueeze(0)   # 将resize后的image做totensor normalization 的transform
                                                 # unsqueeze 解缩， 即升维操作，第0维的大小为1

    #是否拷贝到GPU
    return image.type(dtype)   # 即image


# 定义VGG模型，前向时抽取0,5,10,19,28层卷积特征。 按层结构排序的第1,6,11,20,29层卷积特征
class VGGNet(nn.Module):
    ######################################
    def __init__(self):
        super(VGGNet, self).__init__()  # super子类调用父类，父类多次调用时只执行一次
        self.select = ['0', '5', '10', '19', '28']
        self.vgg19 = models.vgg19(pretrained = True).features

    def forward(self, x):
        features = []
        #name类型为str，x为Variable
        for name, layer in self.vgg19._modules.items():
            x = layer(x)
            if name in self.select:
                features.append(x)
        return features
    ######################################


 #定义主函数
def main(config):
    #定义图像变换操作，必须定义.ToTensor()。（可做）
    transform = transforms.Compose(   #transforms是torchvision中的模块,这里的compose跟多个transform构成的list，将多个transform组合起来使用
        [transforms.ToTensor(),   #将image转换为tensor，并归一化至0~1（除以255）
        transforms.Normalize((0.485, 0.456, 0.406),   #mean
                             (0.229, 0.224, 0.225))   #std
        ])                                            #对数据按通道进行标准化，即先减均值，再除以标准差

    #content和style图像，style图像resize成同样大小
    content = load_image(config.content, transform, max_size = config.max_size)
    #print("content", content)
    style = load_image(config.style, transform, shape = [content.size(2), content.size(3)]) # shape为conten的后两个维度的大小，行和列

    #将content复制一份作为target，并需要计算梯度，作为最终的输出
    target = Variable(content.clone(), requires_grad = True)
    optimizer = torch.optim.Adam([target], lr = config.lr, betas=[0.5, 0.999])

    vgg = VGGNet()
    if use_gpu:
        vgg = vgg.cuda()

    for step in range(config.total_step):
        #分别计算target、content、style的特征图
        target_features = vgg(target)
        content_features = vgg(Variable(content))
        style_features = vgg(Variable(style))

        content_loss = 0.0
        style_loss = 0.0

        for f1, f2, f3 in zip(target_features, content_features, style_features):
            #计算content_loss
            ######################################
            content_loss += torch.mean((f1 - f2)**2)

            n, c, h, w = f1.size()
            ######################################

            #将特征reshape成二维矩阵相乘，求gram矩阵
            ######################################
            f1 = f1.view(c, h * w)
            f3 = f3.view(c, h * w)  # reshape

            f1 = torch.mm(f1, f1.t())
            f3 = torch.mm(f3, f3.t())  
            ######################################

            #计算style_loss
            ######################################
            style_loss += torch.mean((f1 - f3)**2) / (c * h * w)
            ######################################

        #计算总的loss
        ######################################
        loss = content_loss + style_loss * config.style_weight
        ######################################

        #反向求导与优化
        ######################################
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        ######################################

        if (step+1) % config.log_step == 0:
            print ('Step [%d/%d], Content Loss: %.4f, Style Loss: %.4f'
                   %(step+1, config.total_step, content_loss.data, style_loss.data))

        if (step+1) % config.sample_step == 0:
            # Save the generated image
            denorm = transforms.Normalize((-2.12, -2.04, -1.80), (4.37, 4.46, 4.44))
            img = target.clone().cpu().squeeze()
            img = denorm(img.data).clamp_(0, 1)
            torchvision.utils.save_image(img, 'output-%d.png' %(step+1))
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--content', type=str, default='./content.jpg')
    parser.add_argument('--style', type=str, default='./style.jpg')
    parser.add_argument('--max_size', type=int, default=400)
    parser.add_argument('--total_step', type=int, default=1400)
    parser.add_argument('--log_step', type=int, default=10)
    parser.add_argument('--sample_step', type=int, default=100)
    parser.add_argument('--style_weight', type=float, default=100)
    parser.add_argument('--lr', type=float, default=0.003)
    config = parser.parse_args()
    print(config)
    main(config)