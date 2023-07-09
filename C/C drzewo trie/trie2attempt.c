#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define NUM_CHARS 256

typedef struct trienode{
    struct trienode *children[NUM_CHARS];
    bool terminal;
}trienode;

trienode *createnode()
{
    trienode *newnode=(trienode *)malloc(sizeof(trienode));
    for(int i=0; i<NUM_CHARS; i++)
    {
        newnode->children[i]=NULL;
    }
    newnode->terminal=false;
    return newnode;
}

bool trieinsert(trienode **root, char *signedtext)
{
    if(*root==NULL)
    {
        *root=createnode();
    }
    unsigned char *text=(unsigned char *)signedtext;
    trienode *tmp=*root;
    int length=strlen(signedtext);
    for(int i=0; i<length; i++)
    {
        if(tmp->children[text[i]]==NULL)
        {
            tmp->children[text[i]]=createnode();
        }
        tmp=tmp->children[text[i]];
    }
    if(tmp->terminal)
    {
        return false;
    }
    else
    {
        tmp->terminal=true;
        return true;
    }
}

void printtrie_rec(trienode *node, unsigned char *prefix, int length)
{
    unsigned char newprefix[length+2];
    memcpy(newprefix,prefix,length);
    newprefix[length+1]=0;
    if(node->terminal)
    {
        printf("%s\n",prefix);
    }
    for(int i=0; i<NUM_CHARS; i++)
    {
        if(node->children[i]!=NULL)
        {
            newprefix[length]=i;
            printtrie_rec(node->children[i],newprefix,length+1);
        }
    }
}

void printtrie(trienode *root)
{
    if(root==NULL)
    {
        fprintf(stderr,"Drzewo jest puste\n");
        return;
    }
    printtrie_rec(root,NULL,0);
}

bool searchtrie(trienode *root, char *signedtext)
{
    unsigned char *text=(unsigned char *)signedtext;
    int length=strlen(signedtext);
    trienode *tmp=root;
    for(int i=0; i<length; i++)
    {
        if(tmp->children[text[i]]==NULL)
        {
            return false;
        }
        tmp=tmp->children[text[i]];
    }
    return tmp->terminal;
}

bool node_has_children(trienode *node)
{
    if(node==NULL)
    {
        return false;
    }
    for(int i=0; i<NUM_CHARS; i++)
    {
        if(node->children[i]!=NULL)
        {
            return true;
        }
    }
    return false;
}

trienode *deletestr_rec(trienode *node, unsigned char *text, bool *deleted)
{
    if(node==NULL)
    {
        return node;
    }
    if(*text=='\0')
    {
        if(node->terminal)
        {
            node->terminal=false;
            *deleted=true;
            if(node_has_children(node)==false)
            {
                free(node);
                node=NULL;
            }
        }
        return node;
    }
    node->children[text[0]]=deletestr_rec(node->children[text[0]],text+1,deleted);
    if((*deleted) && node_has_children(node)==false && node->terminal==false)
    {
        free(node);
        node=NULL;
    }
    return node;
}

bool deletestr(trienode **root, char *signedtext)
{
    unsigned char *text=(unsigned char *)signedtext;
    bool result=false; //falsz - nic nie usunelismy, prawda - cos usunelismy
    if(*root==NULL)
    {
        return false;
    }
    *root=deletestr_rec(*root,text,&result);
    return result;
}

int main()
{
    trienode *root=NULL;
    /*trieinsert(&root,"kin");
    trieinsert(&root,"cat");
    trieinsert(&root,"happy");
    trieinsert(&root,"kit");
    trieinsert(&root,"cattle");
    printtrie(root);
    printf("search for cattle: %d\n",searchtrie(root,"cattle"));
    printf("search for kin: %d\n",searchtrie(root,"kin"));
    printf("search for kitten: %d\n",searchtrie(root,"kitten"));
    deletestr(&root,"kin");
    deletestr(&root,"cat");
    printtrie(root);*/
    return 0;
}