#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

//tworzymy nowy wezel
node *new(int item)
{
    node *temp=(node *)malloc(sizeof(node)); //alokujemy pamiec
    temp->key=item; 
    temp->left=NULL;
    temp->right=NULL; //nadalismy mu wartosc z argumentu, synowie na razie sa nullami
    return temp;
}

//szukamy konkretnej wartosci
node *search(node *root, int key)
{
    if(root==NULL || root->key==key) //jesli drzewo jest puste, albo w korzeniu jest poszukiwana wartosc, zwracamy ja
    {
        return root;
    }
    if(root->key<key) //jesli nie, szukamy jej w glab drzewa
    {
        return search(root->right,key);
    }
    else
    {
        return search(root->left,key);
    }
}

//wstawiamy wezel do drzewa
node *insert(node *node, int key)
{
    if(node==NULL)
    {
        return new(key); //jesli drzewo jest puste, stworz pierwszy wezel (korzen)
    }
    if(key<node->key) //jesli nie, znajdz odpowiednie miejsce dla nowego wezla i wstaw go
    {
        node->left=insert(node->left,key);
    }
    else
    {
        node->right=insert(node->right,key);
    }
    return node; //zwroc drzewo z dodanym wezlem
}

//szukamy najmn wartosci w drzewie
node *minval(node *wezel)
{
    node *akt=wezel;
    while(akt && akt->left!=NULL) //idziemy w dol az znajdziemy
    {
        akt=akt->left;
    }
    return akt;
}

//usuwamy wezel z drzewa
node *delete(node *root, int key)
{
    if(root==NULL) //jesli drzewo puste, nie ma co usuwac
    {
        return root;
    }
    if(key<root->key) //jesli jest mniejszy od korzenia, to musi byc w lewym poddrzewie
    {
        root->left=delete(root->left,key);
    }
    else if(key>root->key) //jesli jest wiekszy od korzenia, to musi byc w prawym poddrzewie
    {
        root->right=delete(root->right,key);
    }
    else //jesli ma taka sama wartosc jak korzen, to znalezlismy i trzeba usunac
    { //przypadek dla 1 lub 0 dzieci
        if(root->left==NULL)
        {
            node *temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            node *temp=root->left;
            free(root);
            return temp;
        }
        node *temp=minval(root->right); //przypadek dla 2 dzieci, szukamy najmniejszego w prawym poddrzewie
        root->key=temp->key; //podmieniamy go
        root->right=delete(root->right,temp->key); //po podmienieniu kasujemy
    }
    return root;
}

//szukamy najm wartosci w drzewie
int minimum(node *root)
{
    if(root==NULL) //jesli drzewo puste, zwroc blad
    {
        return INT_MAX;
    }
    int wart=root->key; //porownamy 3 wartosci, korzen, minimum z prawego i lewego poddrzewa
    int lewy=minimum(root->left);
    int prawy=minimum(root->right);
    if(lewy<wart)
    {
        wart=lewy;
    }
    if(prawy<wart)
    {
        wart=prawy;
    }
    return wart;
}

// analogicznie szukamy najw wartosci w drzewie
int maksimum(node *root)
{
    if(root==NULL) 
    {
        return INT_MIN;
    }
    int wart=root->key;
    int lewy=maksimum(root->left);
    int prawy=maksimum(root->right);
    if(lewy>wart)
    {
        wart=lewy;
    }
    if(prawy>wart)
    {
        wart=prawy;
    }
    return wart;
}

//jednoczesnie szukamy poprzednika i nastepnika
void poprz_nast(node *root, int x, node **p, node **q)
{
    if(root==NULL)
    {
        return;
    }
    poprz_nast(root->left,x,p,q);
    if(root!=NULL && root->key>x) //jesli korzen wiekszy od a
    {
        if((!*q) || (*q) && (*q)->key>root->key) //szukamy nastepnika, czyli pierwszej wiekszej wartosci
        {
            *q=root;
        }
    }
    else if(root && root->key<x) //jesli mniejszy to bedzie poprzednikiem
    {
        *p=root;
    }
    poprz_nast(root->right,x,p,q);
}

void print_tree(node *root, int tab_count)
{
    if(root==NULL)
    {
        return;
    }
    print_tree(root->right,tab_count+1);//ile pieter, tyle tabulatorow
    for(int i=0; i<=tab_count; i++)
    {
        printf("\t");
    }
    printf("%d\n",root->key);
    print_tree(root->left,tab_count+1);
}
