import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import nltk.stem
import os
import chardet

# 分词等预处理
def filter(text):
    # tokenization
    text1 = text.replace('-', ' ')
    filtered1 = word_tokenize(text1)
    # print(filtered1)

    # 去标点
    punctuation = [',', '<', '>', '.', "'s", '`', '~', '!', '@', '#', '$', '%', '^',
                   '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', '\\', '|',
                   ':', ';', "\'", '/', '?',"\"","“","''","``"]
    filtered2 = [i for i in filtered1 if i not in punctuation]
    # print(filtered2)

    # Normalization

    # Stemming
    filtered3 = []
    s = nltk.stem.SnowballStemmer('english')
    for i in filtered2:
        # 大写都变为小写
        i.lower()
        filtered3.append(s.stem(i))
    # print(filtered3)

    # 去stopwords
    filtered4 = [w for w in filtered3 if w not in stopwords.words('english')]
    # print(filtered4)
    return(filtered4)

# 二进制方式读取，获取字节数据，检测类型
def get_encoding(file):
    with open(file, 'rb') as f:
        return chardet.detect(f.read())['encoding']

# 将每个文档作为一个字符串读入列表sumData
sumData = []
data = []
path = 'C:\\Users\\hp\\PycharmProjects\\20news-18828\\'
files = os.listdir(path)
for i in files:
    files1 = os.listdir(path + i+"\\")
    for p in files1:
        with open(path + i + "\\" + p, "rb") as file:
            decoding = get_encoding(path + i + "\\" + p)
            if decoding != None:
                lines = file.readlines()
                for line in lines:
                    line = line.decode(decoding)
                    data.append(line)
                data = [" ".join(data)]
        if data != []:
            str1 = " ".join(filter(data[0]))
        sumData.append(str1)
        data = []

# 验证
print(sumData)
print(type(sumData))
print(type(sumData[0]))


# 对每个文档统计词频

from sklearn.feature_extraction.text import CountVectorizer
vectorizer = CountVectorizer()
# 建立词典
vectorizer.fit(sumData)
print(vectorizer.vocabulary_)

lenth = len(sumData)
for i in range(lenth):
    vector = vectorizer.transform([sumData[i]])
    # 输出编码后的向量信息
    # print(vector.shape)
    # print(type(vector))
    print(vector)
# 对每个文档用tf-idf统计词频
from sklearn.feature_extraction.text import TfidfVectorizer
vectorizer1 = TfidfVectorizer()
# 建立词汇表
vectorizer1.fit(sumData)
print(vectorizer.idf_)

lenth = len(sumData)
for i in range(lenth):
    vector1 = vectorizer1.transform([sumData[i]])
    # 输出编码后的向量信息
    # print(vector1.shape)
    # print(type(vector1))
    print(vector1)
