#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

int max(int a, int b) //funkcja pomocnicza wyznaczajaca maksimum
{
    if(a>b)
        return a;
    else return b;
}

int height(avlnode *node) //funkcja pomocnicza wyznaczajaca wysokosc drzewa, przydatna w balansie
{
    if(node==NULL)
    {
        return 0;
    }
    return node->h;
}

avlnode *newnode(int key) //funkcja tworzaca nowy wezel
{
    avlnode *new=(avlnode *)malloc(sizeof(avlnode)); //alokacja pamieci
    new->val=key; //argument funkcji wartoscia nowego wezla
    new->left=NULL; //zarowno lewe i prawe dziecko ustawiamy domyslnie na NULL
    new->right=NULL;
    new->h=1; //wysokosc przy nowym wezle ustawiamy domyslnie na 1
    return new;
}

avlnode *rightrotate(avlnode *y) //funkcja wykonujaca prawa rotacje drzewa AVL
{
    //odpowiednio przyporzadkowujemy dane do wskaznikow
    avlnode *x=y->left;
    avlnode *T2=x->right;
    //wykonujemy rotacje
    x->right=y;
    y->left=T2;
    //trzeba jeszcze aktualizowac wysokosci drzew
    y->h=max(height(y->left),height(y->right))+1;
    x->h=max(height(x->left),height(x->right))+1;
    return x; //x jest teraz na gorze, wiec to jego zwracamy jako "root"
}

avlnode *leftrotate(avlnode *x) //analogiczna funkcja wykonujaca lewa rotacje
{
    //odpowiednio przyporzadkowujemy dane do wskaznikow
    avlnode *y=x->right;
    avlnode *T2=y->left;
    //wykonujemy rotacje
    y->left=x;
    x->right=T2;
    //trzeba jeszcze aktualizowac wysokosci drzew
    x->h=max(height(x->left),height(x->right))+1;
    y->h=max(height(y->left),height(y->right))+1;
    return y; //tym razem y jest na gorze, wiec to jego zwracamy
}

//Drzewo jest AVL, jesli roznica wysokosci prawego i lewego poddrzewa nie przekracza 1

int getbalance(avlnode *node)
{
    if(node==NULL)
    {
        return 0;
    }
    return height(node->left)-height(node->right);
}

avlnode *searchnode(avlnode *node, int key) 
{
    if(node==NULL || node->val==key) //jesli drzewo jest puste, albo w korzeniu jest poszukiwana wartosc, zwracamy ja
    {
        return node;
    }
    if(node->val<key) //jesli nie, szukamy jej w glab drzewa
    {
        return searchnode(node->right,key);
    }
    else
    {
        return searchnode(node->left,key);
    }
}

avlnode *insertnode(avlnode *node, int key) 
{
    //1. Standardowe dodawanie wezla do BST
    if(node==NULL) //jesli drzewo puste, dodajemy wezel jako "root"
    {
        return newnode(key);
    }
    if(key<node->val) //jesli key mniejszy od korzenia, dodajemy do lewego poddrzewa
    {
        node->left=insertnode(node->left,key);
    }
    else if(key>node->val) //jesli wiekszy, do prawego
    {
        node->right=insertnode(node->right,key);
    }
    else //nie moze byc drugi taki sam
    {
        return node;
    }
    //2. Aktualizacja wysokosci
    node->h=max(height(node->left),height(node->right))+1;
    //3. Sprawdzenie balansu drzewa
    int balance=getbalance(node);
    //Jesli drzewo bedzie niezbalansowane, mamy do rozpatrzenia 4 przypadki:
    //a) wymagana prawa rotacja
    if(balance>1 && key<node->left->val)
    {
        return rightrotate(node);
    }
    //b) wymagana lewa rotacja
    if(balance<-1 && key>node->right->val)
    {
        return leftrotate(node);
    }
    //c) wymagana najpierw lewa, potem prawa
    if(balance>1 && key>node->left->val)
    {
        node->left=leftrotate(node->left);
        return rightrotate(node);
    }
    //d) wymagana najpierw prawa, potem lewa
    if(balance<-1 && key<node->right->val)
    {
        node->right=rightrotate(node->right);
        return leftrotate(node);
    }
    return node;
}

avlnode *minvaluenode(avlnode *node) //pomocnicza funkcja znajdujaca minimum
{
    avlnode *curr=node;
    while(curr->left!=NULL)
    {
        curr=curr->left;
    }
    return curr;
}

avlnode *deletenode(avlnode *node, int key) //funkcja usuwajaca wezel z drzewa
{
    if(node==NULL) //standardowe usuwanie dla drzewa BST
    {
        return node;
    }
    if(key<node->val) //jesli element mniejszy niz root, szukamy w lewym poddrzewie
    {
        node->left=deletenode(node->left,key);
    }
    else if(key>node->val) //jesli wiekszy, to w prawym
    {
        node->right=deletenode(node->right,key);
    }
    else //jesli znalezlismy, patrzymy ile ma dzieci
    {
        if(node->left==NULL || node->right==NULL)
        {
            avlnode *temp;
            if(node->left!=NULL)
            {
                temp=node->left;
            }
            else
            {
                temp=node->right;
            }
            if(temp==NULL) //przypadek dla 0 dzieci
            {
                temp=node;
                node=NULL;
            }
            else //przypadek dla 1 dziecka
            {
                *node=*temp;
            }
            free(temp);
        }
        else //przypadek dla 2 dzieci, zamiana usuwanego wezla na nastepnika z prawego poddrzewa
        {
            avlnode *tmp=minvaluenode(node->right);
            node->val=tmp->val;
            node->right=deletenode(node->right,tmp->val);
        }
    }
    //balans tak jak w przypadku wstawiania
    if(node==NULL) 
    {
        return node;
    }
    //2. Aktualizacja wysokosci
    node->h=max(height(node->left),height(node->right))+1;
    //3. Sprawdzenie balansu drzewa
    int balance=getbalance(node);
    //Jesli drzewo bedzie niezbalansowane, mamy do rozpatrzenia 4 przypadki:
    if(balance>1 && getbalance(node->left)>=0)
    {
        return rightrotate(node);
    }
    if(balance<-1 && getbalance(node->right)<=0)
    {
        return leftrotate(node);
    }
    if(balance>1 && getbalance(node->left)<0)
    {
        node->left=leftrotate(node->left);
        return rightrotate(node);
    }
    if(balance<-1 && getbalance(node->right)>0)
    {
        node->right=rightrotate(node->right);
        return leftrotate(node);
    }
    return node;
}

void printtree(avlnode *node, int tab_count)
{
    if(node==NULL)
    {
        return;
    }
    printtree(node->right,tab_count+1);//ile pieter, tyle tabulatorow
    for(int i=0; i<=tab_count; i++)
    {
        printf("\t");
    }
    printf("%d\n",node->val);
    printtree(node->left,tab_count+1);
}
