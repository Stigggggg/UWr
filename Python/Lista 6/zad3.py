import requests
from bs4 import BeautifulSoup
import re

def get_text(url):
    page=requests.get(url)
    if page.status_code==200:
        return page.text
    else:
        return None

def parse(response):
    soup=BeautifulSoup(response,'html.parser')
    text=soup.get_text()
    words=re.findall(r'\w+',text.lower())
    return words

def make_index(list):
    wynik={}
    for url in list:
        text=get_text(url)
        if text is not None:
            words=parse(text)
            for word in words:
                if word in wynik:
                    wynik[word].append(url)
                else:
                    wynik[word]=[url]
    return wynik

def most_popular(i, slowo):
    if slowo in i:
        strony=i[slowo]
        max_i=max(strony,key=strony.count)
        return max_i
    else:
        return None

urls=["https://www.w3schools.com/python/python_intro.asp", "https://www.geeksforgeeks.org/python-programming-language/", "https://www.geeksforgeeks.org/python-programming-language/learn-python-tutorial/"]
index=make_index(urls)
print(index)
sl="python"
wynik=most_popular(index, sl)
print(wynik)