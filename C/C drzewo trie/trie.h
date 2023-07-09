#define alfabet 26

typedef struct trienode{
    struct trienode *children[alfabet]; 
    int occur; 
}trienode;

trienode *createnode();

void lowercase(char *c);

void insertnode(trienode **root, char *text);

int searchnode(trienode *root, char *text);

void freetrie(trienode *root);

bool isleaf(trienode *root);

void printtrie(trienode *root, char str[], int level);

