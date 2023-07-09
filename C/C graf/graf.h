typedef struct node{ //wezel listy sasiadow
    int vertex;
    struct node *next;
}node;

typedef struct graph{ //graf
    int num_vertices;
    bool *visited;
    node **adj_lists;
}graph;

node *createnode(int v);

graph *creategraph(int vertices);

void addedge(graph *g, int a, int b);

void printgraph(graph *g);

void dfs(graph *g, int vertex);

void skladowa(graph *g);

void realizacja(char c[]);

