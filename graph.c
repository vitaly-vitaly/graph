#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2

graph *init_graph(int size, GRERR *err) {
	if(size <= 0) {
		if(err != NULL) *err = GR_BADSIZE;
		return NULL;
	}

	struct graph *gr;
	if((gr = (struct graph *) malloc(sizeof(struct graph))) < 0) {
		if(err != NULL) *err = GR_MALLOC;
		return NULL;
	}

	if((gr->matrix = (int **) malloc(size * sizeof(int *))) < 0) {
		if(err != NULL) *err = GR_MALLOC;
		return NULL;
	}

	int i;
	for(i = 0; i < size; i++) {
		if((gr->matrix[i] = (int *) calloc(size, sizeof(int))) < 0) {
			if(err != NULL) *err = GR_MALLOC;
			return NULL;
		}
	}
	if((gr->buf = (int *) calloc(size, sizeof(int))) < 0) {
		if(err != NULL) *err = GR_MALLOC;
		return NULL;
	}

	gr->size = size;
	if(err != NULL) *err = GR_SUCCESS;
	return gr;
}

void destroy_graph(graph *graph, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}

	int i;
	for(i = 0; i < graph->size; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph->buf);
	free(graph);
	if(err != NULL) *err = GR_SUCCESS;
	return;
}

void add_edge(graph *graph, int vertex1, int vertex2, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}

	if((vertex1 < 0) || (vertex1 >= graph->size) || (vertex2 < 0) || (vertex2 >= graph->size)) {
		if(err != NULL) *err = GR_BADSIZE;
		return;
	}

	graph->matrix[vertex1][vertex2] = 1;
	if(err != NULL) *err = GR_SUCCESS;
	return;
}

void add_edges(graph *graph, int* vertices, int size, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}

	int i;
	for(i = 0; i < size; i++) {
		add_edge(graph, *(vertices + i * 2), *(vertices + i * 2 + 1), err);
	}
	if(err != NULL) *err = GR_SUCCESS;
	return;
}

void print_graph(graph *graph, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}

	int i, j;
	fprintf(stdout, "\n");
	for(i = 0; i < graph->size; i++) {
		for(j = 0; j < graph->size; j++){
			fprintf(stdout, "%d ", graph->matrix[i][j]);
		}
		fprintf(stdout, "\n");
	}

	if(err != NULL) *err = GR_SUCCESS;
	return;	
}

void print_buf(graph *graph, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}
	
	fprintf(stdout, "\n");
	int i;
	for(i = 0; i < graph->size; i++) {
		fprintf(stdout, "%d ", graph->buf[i]);
	}
	fprintf(stdout, "\n");

	if(err != NULL) *err = GR_SUCCESS;
	return;	
}

void dfs(graph *graph, int root, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}
	if(root < 0 || root >= graph->size) {
		if(err != NULL) *err = GR_BADSIZE;
		return;
	}

	int i;
	for(i = 0; i < graph->size; i++) {
		if(i != root) {
			graph->buf[i] = -1;
		}
	}

	graph->buf[root] = 2;
	dfs_visit(graph, root, 0);
	if(err != NULL) *err = GR_SUCCESS;
	return;	
}

void dfs_visit(graph *graph, int v, int times) {
	int i;
	graph->buf[v] = 2;
	for(i = 0; i < graph->size; i++) {
		if(graph->matrix[v][i] > 0 && graph->buf[i] == -1) {
			dfs_visit(graph, i, times+1);
		}
	}
	graph->buf[v] = 1;
}

void bfs(graph *graph, int root, GRERR *err) {
	if(graph == NULL) {
		if(err != NULL) *err = GR_EMPTY;
		return;
	}
	if(root < 0 || root >= graph->size) {
		if(err != NULL) *err = GR_BADSIZE;
		return;
	}

	int *color;
	if((color = (int *) calloc(graph->size, sizeof(int))) < 0) {
		if(err != NULL) *err = GR_MALLOC;
		return;
	}
	int *q;
	if((q = (int *) calloc(graph->size, sizeof(int))) < 0) {
		if(err != NULL) *err = GR_MALLOC;
		return;
	}
	int qstart = 0, qend = 0;

	int i;
	for(i = 0; i < graph->size; i++) {
		graph->buf[i] = -1;
		color[i] = WHITE;
	}

	graph->buf[root] = 0;
	color[root] = GRAY;

	q[qend++] = root;

	while(qstart != qend) {
		int u = q[qstart++];
		int v;
		for(v = 0; v < graph->size; v++) {
			if(graph->matrix[u][v] > 0 && u != v) {
				if(color[v] == WHITE) {
					color[v] = GRAY;
					graph->buf[v] = graph->buf[u] + 1;
					q[qend++] = v;
				}
			}
		}
		color[u] = BLACK;
	}

	free(color);
	free(q);

	if(err != NULL) *err = GR_SUCCESS;
	return;	
}