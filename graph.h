typedef struct graph {
	int size;
	int ** matrix;
	int *buf;
} graph;

typedef enum {
	GR_SUCCESS,
	GR_BADSIZE,
	GR_MALLOC,
	GR_EMPTY,
	GR_ERROR
} GRERR;

graph *init_graph(int size, GRERR *err);

void destroy_graph(graph *graph, GRERR *err);

void add_edge(graph *graph, int vertex1, int vertex2, GRERR *err);

void add_edges(graph *graph, int* vertices, int size, GRERR *err);

void print_graph(graph *graph, GRERR *err);

void print_buf(graph *graph, GRERR *err);

void dfs(graph *graph, int root, GRERR *err);

void dfs_visit(graph *graph, int v, int times);
