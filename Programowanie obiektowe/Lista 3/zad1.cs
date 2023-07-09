// Mikolaj Drozd
// Zad 1 z listy 3
// komendy kompilacji:
// mcs -t:library -out:zad1.dll zad1.cs 
// mcs -r:zad1.dll -out:main1.exe main1.cs
// srodowisko: VS Code, kompilator: Mono

using System;

namespace Lista1
{
    public class Lista<T> 
    {
        private class Element<T>
        {
            public T val;
            public Element<T> prev;
            public Element<T> next;
        } 
        private Element<T> first;
        private Element<T> last;  
        public void push_front(T elem)
        {
            var nowy=new Element<T>();
            nowy.val=elem;
            if(first==null)
            {
                first=nowy;
                last=nowy;
            }
            else
            {
                nowy.next=first;
                first.prev=nowy;
                first=nowy;
            }
        }
        public void push_back(T elem)
        {
            var nowy=new Element<T>();
            nowy.val=elem;
            if(last==null)
            {
                first=nowy;
                last=nowy;
            }
            else
            {
                nowy.prev=last;
                last.next=nowy;
                last=nowy;
            }
        }
        public T pop_front()
        {
            if(first==null)
            {
                throw new InvalidOperationException("Lista jest pusta");
            }
            var wartosc=first.val;
            if(first==last)
            {
                first=null;
                last=null;
            }
            else
            {
                first=first.next;
                first.prev=null;
            }
            return wartosc;
        }
        public T pop_back()
        {
            if(last==null)
            {
                throw new InvalidOperationException("Lista jest pusta");
            }
            var wartosc=last.val;
            if(first==last)
            {
                first=null;
                last=null;
            }
            else
            {
                last=last.prev;
                last.next=null;
            }
            return wartosc;
        }
        public bool is_empty()
        {
            if(first==null)
            {
                return true;
            }
            else return false;
        }
    }
}
