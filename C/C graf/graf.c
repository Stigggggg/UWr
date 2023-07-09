#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "graf.h"

node *createnode(int v)
{
    node *newnode=(node *)malloc(sizeof(node));
    newnode->vertex=v;
    newnode->next=NULL;
    return newnode;
}

graph *creategraph(int vertices)
{
    graph *g=(graph *)malloc(sizeof(graph));
    g->num_vertices=vertices;
    g->adj_lists=malloc(vertices*sizeof(node*));
    g->visited=malloc(vertices*sizeof(int));
    for(int i=0; i<vertices; i++)
    {
        g->adj_lists[i]=NULL;
        g->visited[i]=false;
    }
    return g;
}

void addedge(graph *g, int a, int b)
{
    node *newnode=createnode(b);
    newnode->next=g->adj_lists[a];
    g->adj_lists[a]=newnode;
    node *newnode2=createnode(a);
    newnode2->next=g->adj_lists[b];
    g->adj_lists[b]=newnode2;
}

void printgraph(graph *g)
{
    for(int v=0; v<g->num_vertices; v++)
    {
        node *temp=g->adj_lists[v];
        printf("%d: ",v);
        while(temp)
        {
            printf("%d ",temp->vertex);
            temp=temp->next;
        }
        printf("\n");
    }
}

void dfs(graph *g, int vertex)
{
    node *l=g->adj_lists[vertex];
    node *temp=l;
    g->visited[vertex]=true;
    printf("Odwiedzono %d\n",vertex);
    while(temp!=NULL)
    {
        int connected=temp->vertex;
        if(g->visited[connected]==false)
        {
            dfs(g,connected);
        }
        temp=temp->next;
    }
}

void skladowa(graph *g)
{
    for(int v=0; v<g->num_vertices; v++)
    {
        g->visited[v]=false;
    }
    int count=0;
    for(int v=0; v<g->num_vertices; v++)
    {
        if(g->visited[v]==false)
        {
            dfs(g,v);
            count++;
        }
    }
    printf("%d",count);
}

void realizacja(char c[])
{
    FILE *f=fopen(c,"r");
    int a,b,n,m;
    fscanf(f,"%d %d",&n,&m);
    graph *g=creategraph(n);
    for(int i=0; i<m; i++)
    {
        fscanf(f,"%d %d",&a,&b);
        addedge(g,a,b);
    }
    skladowa(g);
    fclose(f);
}

