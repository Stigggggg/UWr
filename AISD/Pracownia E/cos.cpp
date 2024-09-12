#include <iostream>
#include <climits>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height; 
    int minRight;
};

int height(Node* node) 
{
    if(node==nullptr)
        return 0;
    return node->height;
}

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

Node* newNode(int x) 
{
    Node* temp=new Node;
    temp->data=x;
    temp->left=temp->right=nullptr;
    temp->height=1;
    temp->minRight=INT_MAX;
    return temp;
}

Node* rightRotate(Node* y) 
{
    Node* x=y->left;
    Node* T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    y->minRight=min(y->data,min(y->right!=nullptr ? y->right->minRight : INT_MAX, y->left!=nullptr ? y->left->minRight : INT_MAX));
    x->minRight=min(x->data,min(x->right!=nullptr ? x->right->minRight : INT_MAX, x->left!=nullptr ? x->left->minRight : INT_MAX));
    return x;
}

Node* leftRotate(Node* x) {
    Node* y=x->right;
    Node* T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    x->minRight=min(x->data,min(x->right!=nullptr ? x->right->minRight : INT_MAX, x->left!=nullptr ? x->left->minRight : INT_MAX));
    y->minRight=min(y->data,min(y->right!=nullptr ? y->right->minRight : INT_MAX, y->left!=nullptr ? y->left->minRight : INT_MAX));
    return y;
}

int getBalance(Node* node) 
{
    if (node==nullptr)
        return 0;
    return height(node->left)-height(node->right);
}

Node* insert(Node* root,int x) 
{
    if (root==nullptr)
        return newNode(x);
    if (x<root->data)
        root->left=insert(root->left,x);
    else if (x>root->data)
        root->right=insert(root->right,x);
    else
        return root;
    root->height=1+max(height(root->left),height(root->right));
    root->minRight=min(root->data,min(root->right!=nullptr ? root->right->minRight : INT_MAX, root->left!=nullptr ? root->left->minRight : INT_MAX));
    int balance=getBalance(root);
    if (balance>1 && x <root->left->data)
        return rightRotate(root);
    if (balance<-1 && x>root->right->data)
        return leftRotate(root);
    if (balance>1 && x>root->left->data) 
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance<-1 && x<root->right->data) 
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* minValueNode(Node* node) 
{
    Node* current=node;
    while(current && current->left!=nullptr)
        current=current->left;
    return current;
}

Node* deleteNode(Node* root,int x) 
{
    if(root==nullptr)
        return root;
    if (x<root->data)
        root->left=deleteNode(root->left,x);
    else if (x>root->data)
        root->right=deleteNode(root->right,x);
    else 
    {
        if((root->left==nullptr) || (root->right==nullptr)) 
        {
            Node* temp=root->left ? root->left : root->right;
            if(temp==nullptr) 
            {
                temp=root;
                root=nullptr;
            } 
            else
                *root=*temp; 
            delete temp;
        } 
        else 
        {
            Node* temp=minValueNode(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right, temp->data);
        }
    }
    if(root==nullptr)
        return root;
    root->height=1+max(height(root->left),height(root->right));
    root->minRight=min(root->data,min(root->right != nullptr ? root->right->minRight : INT_MAX, root->left != nullptr ? root->left->minRight : INT_MAX));
    int balance = getBalance(root);
    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);
    if(balance>1 && getBalance(root->left)<0) 
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0)
        return leftRotate(root);
    if(balance<-1 && getBalance(root->right)>0) 
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int lower(Node* root,int x) 
{
    int result=INT_MIN;
    while(root!=nullptr) 
    {
        if(root->data<=x) 
        {
            result=root->data;
            root=root->right;
        } 
        else
            root=root->left;
    }
    return result;
}

int upper(Node* root, int x) 
{
    int result=INT_MAX;
    while(root!=nullptr) 
    {
        if(root->data>=x) 
        {
            result=root->data;
            root=root->left;
        } 
        else
            root = root->right;
    }
    return result;
}

int main() 
{
    Node* root=nullptr;
    int N;
    cin>>N;
    for(int i=0; i<N; ++i) 
    {
        char op;
        int x;
        cin>>op>>x;
        switch(op) 
        {
            case 'I':
                root=insert(root, x);
                break;
            case 'D':
                if(root!=nullptr && (lower(root,x)==x || upper(root,x)==x)) 
                {
                    root=deleteNode(root, x);
                    cout<<"OK"<< endl;
                } 
                else
                    cout<<"BRAK"<<endl;
                break;
            case 'L':
                if(lower(root,x)!=INT_MIN)
                    cout<<lower(root, x)<<endl;
                else
                    cout<<"BRAK"<<endl;
                break;
            case 'U':
                if (upper(root,x)!=INT_MAX)
                    cout<<upper(root,x)<<endl;
                else
                    cout<<"BRAK"<<endl;
                break;
        }
    }
    return 0;
}