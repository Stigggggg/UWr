typedef struct avlnode{  //struktura drzewa AVL
    int val;  //wartość
    struct avlnode *left;  //wskaznik na lewe dziecko
    struct avlnode *right;  //wskaznik na prawe dziecko
    int h; //wysokosc drzewa
}avlnode;

int max(int a, int b);

int height(avlnode *node);

avlnode *newnode(int key);

avlnode *rightrotate(avlnode *y);

avlnode *leftrotate(avlnode *x);

int getbalance(avlnode *node);

avlnode *searchnode(avlnode *node, int key);

avlnode *insertnode(avlnode *node, int key);

avlnode *minvaluenode(avlnode *node);

avlnode *deletenode(avlnode *node, int key);

void printtree(avlnode *node, int tab_count);