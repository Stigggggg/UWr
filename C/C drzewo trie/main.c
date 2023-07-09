#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "trie.h"

int main(int argc, char *argv[])
{
    trienode *root=NULL;
    if(argc<2)
    {
        fprintf(stderr,"Nie podano plikow\n");
        return 0;
    }
    for(int i=1; i<argc; i++)
    {
        FILE *f=fopen(argv[i],"r");
        char temp_word_storage[40]={0};
        while(fscanf(f," %40s",temp_word_storage)==1)
        {
            insertnode(&root,temp_word_storage);
        }
        fclose(f);
    }
    while(1==1)
    {
        printf("Jaka operacje chcesz wykonac?\n");
        char tab[10];
        scanf("%s",&tab);
        if(!strcmp("quit",tab))
        {
            return 0;
        }
        else if(!strcmp("print",tab))
        {
            int level=0;
            char str[40];
            printtrie(root,str,level);
        }
        else if(!strcmp("free",tab))
        {
            freetrie(root);
            printf("Drzewo usuniete\n");
        }
        else if(!strcmp("search",tab))
        {
            char slowo[40];
            scanf("%s",slowo);
            if(searchnode(root,slowo)==0)
            {
                fprintf(stderr,"Nie ma takiego slowa\n");
            }
            else
            {
                printf("%s %d\n",slowo,searchnode(root,slowo));
            }
        }
        else
        {
            fprintf(stderr,"Nie ma takiej operacji\n");
        }
    }    
    return 0;
}