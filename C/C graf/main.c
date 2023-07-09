#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "graf.h"

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        fprintf(stderr,"Nie podano pliku");
        return 0;
    }
    realizacja(argv[1]);
    return 0;
}