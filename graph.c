#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

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
		if((gr->matrix[i] = (int *) malloc(size * sizeof(int))) < 0) {
			if(err != NULL) *err = GR_MALLOC;
			return NULL;
		}
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