import requests
from bs4 import BeautifulSoup
import re
import threading

def print_thread(thread_name, action):
    print(f"Thread {thread_name} {action}")
def get_text(url):
    page=requests.get(url)
    if page.status_code==200:
        return page.text
    else:
        return None

def parse(response,out,lock,url):
    soup=BeautifulSoup(response,'html.parser')
    text=soup.get_text()
    words=re.findall(r'\w+',text.lower())
    with lock:
        for i in words:
            if i in out:
                out[i].append(url)
            else:
                out[i]=[url]
    return words

def make_index(list):
    wynik={}
    lock=threading.Lock()
    threads=[]
    for url in list:
        text=get_text(url)
        if text is not None:
           thread=threading.Thread(target=parse,args=(text,wynik,lock,url))
           threads.append(thread)
           print_thread(thread.name,"started")
           thread.start()
    for i in threads:
        i.join()
        print_thread(i.name,"ended")
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
#print(index)
sl="python"
wynik=most_popular(index, sl)
print(wynik)