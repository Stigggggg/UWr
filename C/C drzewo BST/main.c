#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bst.h"

int main()
{
    node *root=NULL;
    root=insert(root, 50);
    root=insert(root, 30);
    root=insert(root, 20);
    root=insert(root, 40);
    root=insert(root, 70);
    root=insert(root, 60);
    root=insert(root, 80);
    while(1==1)
    {
        printf("\nJaka operacje chcesz wykonac?");
        char tab[5];
        scanf("%s",&tab);
        if(!strcmp("quit",tab))
        {
            return 0;
        }
        else if(!strcmp("min",tab))
        {
            if(minimum(root)==INT_MAX)
            {
                fprintf(stderr,"Drzewo jest puste");
            }
            else
            {
                int mini=minimum(root);
                printf("%d",mini);
            }
        }
        else if(!strcmp("max",tab))
        {
            if(maksimum(root)==INT_MIN)
            {
                fprintf(stderr,"Drzewo jest puste");
            }
            else
            {
                int maxi=maksimum(root);
                printf("%d",maxi);
            }
        }
        else if(!strcmp("print",tab))
        {
            print_tree(root,0);
        }
        else if(!strcmp("prev",tab))
        {
            printf("Podaj wartosc");
            int x;
            scanf("%d",&x);
            if(minimum(root)==INT_MAX)
            {
                fprintf(stderr,"Drzewo jest puste");
            }
            else if(minimum(root)>=x)
            {
                fprintf(stderr,"X jest wartoscia minimalna");
            }
            node *p=NULL;
            node *n=NULL;
            poprz_nast(root,x,&p,&n);
            if(p)
            {
                printf("%d",p->key);
            }
        }
        else if(!strcmp("next",tab))
        {
            printf("Podaj wartosc");
            int x;
            scanf("%d",&x);
            if(maksimum(root)==INT_MIN)
            {
                fprintf(stderr,"Drzewo jest puste");
            }
            else if(maksimum(root)<=x)
            {
                fprintf(stderr,"X jest wartoscia maksymalna");
            }
            node *p=NULL;
            node *n=NULL;
            poprz_nast(root,x,&p,&n);
            if(n)
            {
                printf("%d",n->key);
            }
        }
        else if(!strcmp("ins",tab))
        {
            int x;
            scanf("%d",&x);
            node *found=search(root,x);
            if(!found)
            {
                root=insert(root,x);
                printf("Dodano element");
            }
            else
            {
                fprintf(stderr,"Nie dodano, element juz tam jest");
            }
        }
        else if(!strcmp("del",tab))
        {
            printf("Podaj wartosc");
            int x;
            scanf("%d",&x);
            node *found=search(root,x);
            if(!found)
            {
                fprintf(stderr,"Nie ma takiej wartosci");
            }
            else
            {
                root=delete(root,x);
                printf("Usunieto element");
            }
        }
        else if(!strcmp("srch",tab))
        {
            printf("Podaj wartosc");
            int x;
            scanf("%d",&x);
            node *found=search(root,x);
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