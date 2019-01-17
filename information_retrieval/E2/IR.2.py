#训练数据与测试数据的划分
from sklearn.datasets import fetch_20newsgroups
from sklearn.model_selection import train_test_split

newsgroups = fetch_20newsgroups()
X_train,X_test,y_train,y_test= train_test_split(newsgroups.data,newsgroups.target,test_size=0.2,random_state=1)

#X_train 是由长度为训练集文档数目的列表，其中每个元素为单个文档组成的字符串，y_train为训练集文档对应的标签，用索引表示

print(type(X_test))
print(type(X_test[0]))
print(len(X_train), len(X_test))

#Tfidf向量化处理
from sklearn.feature_extraction.text import TfidfVectorizer

vectorizer = TfidfVectorizer(stop_words='english', lowercase=True)
#以X_train建立字典并向量化
train_vector = vectorizer.fit_transform(X_train)
print(train_vector.shape)

test_vector = vectorizer.transform(X_test)
print(test_vector.shape)

#多项式模型分类

from sklearn.naive_bayes import MultinomialNB
#训练 拉普拉斯平滑参数alpha设为0.01
mnb_clf = MultinomialNB(alpha=0.01, fit_prior=False)
mnb_clf.fit(train_vector, y_train)

# 预测
pred = mnb_clf.predict(test_vector)
print(len(pred))

# 采用Micro-F1评分
from sklearn import metrics

print(metrics.f1_score(y_test, pred, average='micro'))
print(metrics.classification_report(y_test, pred))

