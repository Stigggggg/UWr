#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}node;

node *pos;
node *neg;

void traverse(node *head)
{
    node *temp=head;
    while(temp!=NULL)
    {
        printf("%d-->",temp->val);
        temp=temp->next;
    }
}

void insert(node **head, int data)
{
    node *newnode=(node *)malloc(sizeof(node)); //alokujemy pamiec
    node *last=*head; //tworzymy liste
    newnode->val=data; //dajemy wartosc 
    newnode->next=NULL; //skoro ma byc na koncu to next=NULL
    if(*head==NULL) //jesli pusta lista to ustawic na korzen
    {
        *head=newnode;
        return;
    }
    while(last->next!=NULL) //jesli nie, to jazda na koniec
    {
        last=last->next;
    }
    last->next=newnode; //ustawiamy ostatniego nexta
    return;
}

void del(node **head, int data)
{
    if(*head!=NULL)
    {
        if((*head)->next==NULL)
        {
            *head=NULL;
        }
        else
        {
            node *temp=*head;
            while(temp->next->next!=NULL)
            {
                temp=temp->next;
            }
            node *last=temp->next;
            temp->next=NULL;
            free(last);
        }
    }
}

void append(node *head1, node *head2)
{
    node *akt=head1;
    while(akt->next!=NULL)
    {
        akt=akt->next;
    }
    node *temp=akt->next;
    akt->next=head2;
    while(head2->next!=NULL)
    {
        head2=head2->next;
    }
    head2->next=temp;
}

node *del_by_data(node *head, int data)
{
    if(!head)
    {
        return head;
    }
    while(head && head->val==data)
    {
        head=head->next;
    }
    node *akt=head;
    node *poprz=NULL;
    while(akt)
    {
        if(akt->val==data)
        {
            poprz->next=akt->next;
        }
        else
        {
            poprz=akt;
        }
        akt=akt->next;
    }
    return head;
}

void print_reverse(node *head)
{
    if(head==NULL)
    {
        return;
    }
    print_reverse(head->next);
    printf("%d-->",head->val);
}

void reverse(node **head)
{
    node *poprz=NULL;
    node *akt=*head;
    node *nast=NULL;
    while(akt!=NULL)
    {
        nast=akt->next;
        akt->next=poprz;
        poprz=akt;
        akt=nast;
    }
    *head=poprz;
}

void split(node *head)
{
    node *link;
    node *akt;
    while(head!=NULL)
    {
        node *link=(node *)malloc(sizeof(node));
        link->val=head->val;
        link->next=NULL;
        if(head->val>0)
        {
            if(pos==NULL)
            {
                pos=link;
                head=head->next;
                continue;
            }
            else
            {
                akt=pos;
                while(akt->next!=NULL)
                {
                    akt=akt->next;
                    akt->next=link;
                }
            }
            head=head->next;
        }
        else
        {
            if(neg=NULL)
            {
                neg=link;
                head=head->next;
                continue;
            }
            else
            {
                akt=neg;
                while(akt->next!=NULL)
                {
                    akt=akt->next;
                    akt->next=link;
                }
            }
            head=head->next;
        }
    }
}

node *rev(node *head)
{
    if(head->next==NULL)
    {
        return head;
    }
    node *rest=rev(head->next);
    head->next->next=head;
    head->next=NULL;
    return rest;
}

node *sortedmerge(node *a, node *b)
{
    a=rev(a);
    b=rev(b);
    node *head=NULL;
    node *temp;
    while(a!=NULL && b!=NULL)
    {
        if(a->val>=b->val)
        {
            temp=a->next;
            a->next=head;
            head=a;
            a=temp;
        }
        else
        {
            temp=b->next;
            b->next=head;
            head=b;
            b=temp;
        }
    }
    while(a!=NULL)
    {
        temp=a->next;
        a->next=head;
        head=a;
        a=temp;
    }
    while(b!=NULL)
    {
        temp=b->next;
        b->next=head;
        head=b;
        b=temp;
    }
    return head;
}

node *usunmax(node *lista)
{
    node *temp=lista;
    int maxi=lista->val;
    while(temp!=NULL)
    {
        if(temp->val>maxi)
        {
            maxi=temp->val;
        }
        temp=temp->next;
    }
    temp=lista;
    node *prev=NULL;
    while(temp)
    {
        if(temp->val!=maxi)
        {
            prev=temp;
        }
        else
        {
            prev->next=temp->next;
        }
        temp=temp->next;
    }
    return lista;
}

node *usunparz(node *lista)
{
    node *curr=lista;
    node *prev=NULL;
    while(curr)
    {
        if(curr->val%2!=0)
        {
            prev=curr;
        }
        else
        {
            prev->next=curr->next;
        }
        curr=curr->next;
    }
    return lista;
}

int main()
{
    node *head=NULL;
    //node *head2=NULL;
    //node *wyn=NULL;
    /*insert(&head,7);
    insert(&head,2);
    insert(&head,3);
    insert(&head,2);
    insert(&head,8);
    insert(&head,1);
    insert(&head,2);
    insert(&head,2);
    insert(&head2,11);
    insert(&head2,12);
    insert(&head2,13);
    insert(&head2,14);
    append(head,head2);
    reverse(&head);
    print_reverse(head);*/
    insert(&head,5);
    insert(&head,10);
    insert(&head,15);
    insert(&head,40);
    insert(&head,2);
    insert(&head,3);
    insert(&head,20);
    head=usunparz(head);
    traverse(head);
    return 0;
}