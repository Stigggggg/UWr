#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

int main()
{
    avlnode *root=NULL;
    /*root=insertnode(root,10);
    root=insertnode(root,20);
    root=insertnode(root,30);
    root=insertnode(root,40);
    root=insertnode(root,50);
    root=insertnode(root,25);
    root=deletenode(root,20);
    root=deletenode(root,50);
    root=deletenode(root,40);
    printtree(root,0);*/
    while(1)
    {
        printf("\nPodaj operacje:");
        char tab[5];
        scanf("%s",&tab);
        if(!strcmp("quit",tab))
        {
            return 0;
        }
        else if(!strcmp("print",tab))
        {
            printtree(root,0);
        }
        else if(!strcmp("ins",tab))
        {
            int x;
            scanf("%d",&x);
            avlnode *found=searchnode(root,x);
            if(!found)
            {
                root=insertnode(root,x);
                printf("Dodano element");
            }
            else
            {
                fprintf(stderr,"Nie dodano, element juz tam jest");
            }
        }
        else if(!strcmp("del",tab))
        {
            int x;
            scanf("%d",&x);
            avlnode *found=searchnode(root,x);
            if(!found)
            {
                fprintf(stderr,"Nie ma takiej wartosci");
            }
            else
            {
                root=deletenode(root,x);
                printf("Usunieto element");
            }
        }
        else if(!strcmp("srch",tab))
        {
            int x;
            scanf("%d",&x);
            avlnode *found=searchnode(root,x);
            if(!found)
            {
                printf("NIE");
            }
            else
            {
                printf("TAK");
            }
        }
        else
        {   
            fprintf(stderr,"Nie ma takiej operacji");
        }
    }
    return 0;
}