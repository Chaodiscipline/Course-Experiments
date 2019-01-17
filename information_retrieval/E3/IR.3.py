import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import nltk.stem

#读取
tweets = []
path = 'C:\\Users\\hp\\Desktop\\IR实验\\tweets.txt'
with open(path, 'rb') as file:
    lines = file.readlines()
    for line in lines:
        line = line.decode("ascii")
        tweets.append(line)

# print(tweets)  # 列表 其每一个元素对应一个tweet
# print(tweets[0])  # 字符串 第一个tweet
# print(len(tweets))  # 列表长度30548

#截取正文
def substring(str1):
    count = 0
    str = ""
    for s in str1:
        if s == '"':
            count = count + 1
        elif count == 9:
            str = str + s
    return str


tweets_text = []    #tweets_text中的元素为原每个tweet的正文
for tweet in tweets:
    tweets_text.append(substring(tweet))


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

print(len(textword))

#建立inverted index
dict1 = {}
label = 0
for word_list in textword:
    for word in word_list:
        if word not in dict1:
            dict1[word] = set()
        dict1[word].add(label)
    label = label + 1

#print(dict1.keys())
#print(dict1.items())
#print(dict1["quiet"])




#对检索结果转化为字符串有序输出
def print_answer(answer_set):
    empty_set = set()
    if empty_set == answer_set:
        print('None')
    else:
        answer_list = list(answer_set)
        answer_list.sort()
        print(', '.join(map(str, answer_list)))


while True:
    print("begin")
    query = input()
    if query == '':
        break
    answer_set = set()
    if 'OR:' in query:
        query_word = filter(query[3:])  #注意query也需要进行预处理
        print(query_word)
        for word in query_word:
            if (word != '')and(word in dict1):
                answer_set = dict1[word] | answer_set
        #print_answer(answer_set)
    if 'AND:' in query:
        query_word = filter(query[4:])
        print(query_word)
        if query_word != []:      #第一次要跟所有文档标签做与操作，因此这里集合内容需初始化
            for i in range(30548):
                answer_set.add(i)
            for word in query_word:
                if word != '':
                    if word in dict1:
                        answer_set = dict1[word] & answer_set
                    else:
                        answer_set = set()
        else:
            print('None')
    if 'NOT:' in query:
        query_word = filter(query[4:])
        print(query_word)
        for i in range(30548):
            answer_set.add(i)
        for word in query_word:
            if word != '':
                if word in dict1:
                    print(list(dict1[word]))  #输出含有该单词的文档
                    for i in dict1[word]:
                        answer_set.discard(i)
                    #answer_set.difference(dict1[word])
    print_answer(answer_set)