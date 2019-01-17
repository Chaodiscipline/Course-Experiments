import nltk
nltk.download('punkt')
nltk.download('stopwords')
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import nltk.stem
import math
from math import log
import json

# #读取
# tweets = []
# path = 'C:\\Users\\19843\\Desktop\\IR实验\\tweets.txt'
# with open(path, 'rb') as file:
#     lines = file.readlines()
#     for line in lines:
#         line = line.decode("ascii")
#         tweets.append(line)
#
# #截取正文
# def substring(str1):
#     count = 0
#     str = ""
#     for s in str1:
#         if s == '"':
#             count = count + 1
#         elif count == 9:
#             str = str + s
#     return str


tweets_text = []    #tweets_text中的元素为原每个tweet的正文
label = []    #tweets_text中的元素为原每个tweet的id
with open('tweets.txt', encoding='utf-8') as file:
    for line in file:
        tweet = json.loads(line)
        tweets_text.append(tweet['text'])
        label.append(tweet['tweetId'])


# 分词等预处理
def filter(text):
    # tokenization
    #text1 = text.replace('-', ' ')
    filtered1 = word_tokenize(text)
    #print(filtered1)

    # 去标点
    punctuation = [',', '<', '>', '.', "'s", '`', '~', '!', '@', '#', '$', '%', '^',
                   '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', '{', '}', '\\', '|',
                   ':', ';', "\'", '/', '?',"\"","“","''","``"]
    filtered2 = [i for i in filtered1 if i not in punctuation]
    #print(filtered2)

    # Normalization

    # Stemming
    filtered3 = []
    s = nltk.stem.SnowballStemmer('english')
    for i in filtered2:
        # 大写都变为小写
        i.lower()
        filtered3.append(s.stem(i))
    #print(filtered3)

    # 去stopwords
    filtered4 = [w for w in filtered3 if w not in stopwords.words('english')]
    #print(filtered4)
    return(filtered4)


textword = []
for text in tweets_text:
    textword.append(filter(text))



# 计算文档平均长度
M = len(textword)   #总文档数
sum_length = 0
for text in textword:
    sum_length = sum_length + len(text)  # len(textword[i])就是某一文档的长度
avdl = sum_length/M
print('avdl = ', avdl)

#建立inverted index
dict1 = {}
label_num = 0
for word_list in textword:
    for word in word_list:
        if word not in dict1:
            dict1[word] = []
            dict1[word].append([label_num, word_list.count(word)])
        elif label != dict1[word][-1][0]:
            dict1[word].append([label_num, word_list.count(word)])
    label_num = label_num + 1

b = 0.5
k = 2
#检索、打分
while True:
    print("begin")
    query = input()
    if query == '':
        break
    if 'PLNVSM:' in query:
        query_word = filter(query[7:])  # 注意query也需要进行预处理
    if 'BM25:' in query:
        query_word = filter(query[5:])
    print('query预处理: ', query_word)
    score_list = []
    for word in query_word:
        for d in dict1[word]:
            if 'PLNVSM:' in query:
                sim = query_word.count(word) * log(1 + log(1+d[1], math.e), math.e) / \
                        (1 - b + b * len(textword[d[0]])/avdl) * log((M+1)/len(dict1[word]), 2)
            if 'BM25:' in query:
                sim = query_word.count(word) * (k+1)*d[1]/(d[1]+k*(1-b+b*len(textword[d[0]])/avdl)) \
                        * log((M+1)/len(dict1[word]), 2)
            judge = True
            for i in score_list:
                if i[0] == d[0]:
                    judge = False
                    i[1] = i[1] + sim
            if judge:
                score_list.append([d[0], sim])
    # 排序输出
    s = []
    for i in score_list:
        s.append(i[1])
    s.sort()
    s.reverse()
    print('文档评分: ', s)
    c = []
    for n in range(len(score_list)):
        for j in score_list:
            if s[n] == j[1]:
                c.append(j[0])
    print('对应doc_id: ', c)
    #文档查询
    while True:
        print('enter a doc_id to browse:')
        doc_id = int(input())
        if doc_id == -1:
            break
        print(tweets_text[doc_id])




