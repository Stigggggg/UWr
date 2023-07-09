// Mikolaj Drozd
// Zad 2 z listy 3
// komendy kompilacji:
// mcs -t:library -out:zad2.dll zad2.cs 
// mcs -r:zad1.dll -out:main2.exe main2.cs
// srodowisko: VS Code, kompilator: Mono

using System;
using System.Collections.Generic; //uzyte jedynie w celu uzyskania komendy KeyNotFoundException

namespace Slownik
{
    public class MyDictionary<K,V>
    {
        public class Para
        {
            public K Key;
            public V Value;
            public Para(K key, V value)
            {
                Key=key;
                Value=value;
            }
        }
        public Para[] dict;
        public MyDictionary()
        {
            dict=new Para[0];
        }
        public void add(K key, V value)
        {
            Para[] new_dict=new Para[dict.Length + 1];
            for (int i=0; i<dict.Length; i++)
            {
                if(dict[i].Key.Equals(key))
                {
                    throw new ArgumentException("Element o podanym kluczu juz wystapil");
                }
                new_dict[i]=dict[i];
            }
            new_dict[dict.Length]=new Para(key, value);
            dict=new_dict;
        }
        public V search(K key)
        {
            for (int i=0; i<dict.Length; i++)
            {
                if (dict[i].Key.Equals(key))
                {
                    return dict[i].Value;
                }
            }
            Console.WriteLine("Nie ma takiego elementu");
            throw new ArgumentException();
        }
        public void remove(K key)
        {
            for (int i=0; i<dict.Length; i++)
            {
                if(dict[i].Key.Equals(key))
                {
                    Para[] new_dict = new Para[dict.Length-1];
                    for (int j=0; j<i; j++)
                    {
                        new_dict[j]=dict[j];
                    }
                    for (int j=i+1; j<dict.Length; j++)
                    {
                        new_dict[j-1]=dict[j];
                    }
                    dict=new_dict;
                }
            }
            Console.WriteLine("Nie ma takiego elementu");
            throw new KeyNotFoundException();
        }
    }
}
