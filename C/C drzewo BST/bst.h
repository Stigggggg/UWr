typedef struct node{
    int key;
    struct node *left; 
    struct node *right;
}node;

node *new(int item);

node *search(node *root, int key);

node *insert(node *node, int key);

node *minval(node *wezel);

node *delete(node *root, int key);

int minimum(node *root);

int maksimum(node *root);

void poprz_nast(node *root, int x, node **p, node **q);

void print_tree(node *root, int tab_count);
