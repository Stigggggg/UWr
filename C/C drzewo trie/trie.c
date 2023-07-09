#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "trie.h"

trienode *createnode()
{
    trienode *newnode=(trienode *)malloc(sizeof(trienode));
    for(int i=0; i<alfabet; i++)
    {
        newnode->children[i]=NULL;
    }
    newnode->occur=0;
    return newnode;
}

void lowercase(char *c)
{
    if(*c>='A' && *c<='Z')
    {
        *c=*c-'A'+'a';
    }
}

void insertnode(trienode **root, char *text)
{
    if(*root==NULL)
    {
        *root=createnode();
    }
    trienode *tmp=*root;
    int length=strlen(text);
    for(int i=0; i<length; i++)
    {
        char c=text[i];
        lowercase(&c);
        if(c>'z' || c<'a')
        {
            fprintf(stderr,"Slowo nie spelnia wymogow\n");
            return;
        }
        if(tmp->children[c-'a']==NULL)
        {
            tmp->children[c-'a']=createnode();
        }
        tmp=tmp->children[c-'a'];
    }
    tmp->occur++;
}

int searchnode(trienode *root, char *text)
{
    trienode *tmp=root;
    int length=strlen(text);
    for(int i=0; i<length; i++)
    {
        lowercase(&text[i]);
        if(tmp->children[text[i]-'a']==NULL)
        {
            return 0;
        }
        tmp=tmp->children[text[i]-'a'];
    }
    if(tmp->occur==0)
    {
        return 0;
    }
    else tmp->occur;
}

void freetrie(trienode *root)
{
    for(int i=0; i<alfabet; i++)
    {
        if(root->children[i]!=NULL)
        {
            freetrie(root->children[i]);
        }
    }
    free(root);
}

bool isleaf(trienode *root)
{
    return root->occur!=0;
}

void printtrie(trienode *root, char str[], int level)
{
    if(isleaf(root)) //jesli jest lisciem, nastepuje koniec stringa i wypisujemy
    {
        str[level]='\0';
        printf("%s %d\n",str, root->occur);
    }
    for(int i=0; i<alfabet; i++) //jesli nie jest, wywolujemy rekurencyjnie, az dojdziemy do liscia
    {
        if(root->children[i])
        {
            str[level]=i+'a'; //dodajemy rodzica do str i idziemy dalej
            printtrie(root->children[i],str,level+1);
        }
    }
}


