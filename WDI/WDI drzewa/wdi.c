#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}node;

node *newnode(int key)
{
    node *new=malloc(sizeof(node));
    new->val=key;
    new->left=NULL;
    new->right=NULL;
    return new;
}

node *insert(node *node, int key)
{
    if(node==NULL)
    {
        return newnode(key); //jesli drzewo jest puste, stworz pierwszy wezel (korzen)
    }
    if(key<node->val) //jesli nie, znajdz odpowiednie miejsce dla nowego wezla i wstaw go
    {
        node->left=insert(node->left,key);
    }
    else
    {
        node->right=insert(node->right,key);
    }
    return node; //zwroc drzewo z dodanym wezlem
}

int nodecount(node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    int l=nodecount(root->left);
    int r=nodecount(root->right);
    return r+l+1;
}

int maxi(int a, int b)
{
    if(a>b) return a;
    else return b;
}

int mini(int a, int b)
{
    if(a>b) return b;
    else return a;
}

int treeheight(node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    int left_height=treeheight(root->left);
    int right_height=treeheight(root->right);
    return maxi(left_height,right_height)+1;
}

void positivenodes(node *root)
{
    if(root!=NULL)
    {
        positivenodes(root->left);
        if(root->val>0)
        {
            printf("%d ",root->val);
        }
        positivenodes(root->right);
    }
}

int minval(node *root)
{
    if(root==NULL)
    {
        return INT_MAX;
    }
    int value=root->val;
    int leftmin=minval(root->left);
    int rightmin=minval(root->right);
    return mini(value,mini(leftmin,rightmin));
}

int maxval(node *root)
{
    if(root==NULL)
    {
        return INT_MIN;
    }
    int value=root->val;
    int leftmax=maxval(root->left);
    int rightmax=maxval(root->right);
    return maxi(value,maxi(leftmax,rightmax));
}

int isbst(node *root)
{
    if(root==NULL)
    {
        return 1;
    }
    if(root->left!=NULL && maxval(root->left)>root->val)
    {
        return 0;
    }
    if(root->right!=NULL && maxval(root->right)<root->val)
    {
        return 0;
    }
    if(isbst(root->left)==0 || isbst(root->right)==0)
    {
        return 0;
    }
    return 1;
}

node *mergetrees(node *root1, node *root2)
{
    if(!root1 && !root2)
    {
        return NULL;
    }
    if(!root1)
    {
        return root2;
    }
    if(!root2)
    {
        return root1;
    }
    root1->val=root1->val+root2->val;
    root1->left=mergetrees(root1->left,root2->left);
    root1->right=mergetrees(root1->right,root2->right);
    return root1;
}

node *iter_insert(node *root, int key)
{
    node *new=newnode(key);
    node *x=root;
    node *y=NULL;
    while(x!=NULL)
    {
        y=x;
        if(key<x->val)
        {
            x=x->left;
        }
        else
        {
            x=x->right;
        }
    }
    if(y==NULL)
    {
        y=new;
    }
    else if(key<y->val)
    {
        y->left=new;
    }
    else
    {
        y->right=new;
    }
    return y;
}

bool czykopiec(node *drzewo)
{
    if(drzewo->left==NULL || drzewo->right==NULL)
    {
        return true;
    }
    if(drzewo->left==NULL && drzewo->right!=NULL)
    {
        return false;
    }
    if(drzewo->left!=NULL && drzewo->right==NULL)
    {
        return false;
    }
    else
    {
        if(drzewo->val<drzewo->left->val && drzewo->val<drzewo->right->val)
        {
            if(czykopiec(drzewo->left) && czykopiec(drzewo->right))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}

int max_path(node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    int maxl=root->val+max_path(root->left);
    int maxr=root->val+max_path(root->right);
    if(maxl>maxr)
    {
        return maxl;
    }
    else return maxr;
}

int ciezar(node *root)
{
    if(root==NULL)
    {
        return 0;
    }
    int l=ciezar(root->left);
    int r=ciezar(root->right);
    return root->val+l+r;
}

bool zrown(node *root)
{
    if(root==NULL)
    {
        return 1;
    }
    int wagal=root->val+zrown(root->left);
    int wagar=root->val+zrown(root->right);
    if(wagal==wagar)
    {
        return 1;
    }
    return 0;
}

int main()
{
    node *root=newnode(5);
    root->left=newnode(6);
    root->right=newnode(12);
    root->left->left=newnode(3);
    root->left->right=newnode(3);
    printf("%d",zrown(root));
    return 0;
}