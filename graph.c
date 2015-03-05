#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

graph *init_graph(int size, GRERR *err) {
	// if(err == NULL) {
	// 	*err = GR_ERROR;
	// 	return NULL;
	// }

	if(size <= 0) {
		*err = GR_BADSIZE;
		return NULL;
	}

	struct graph *gr;
	if((gr = (struct graph *) malloc(sizeof(struct graph))) < 0) {
		*err = GR_MALLOC;
		return NULL;
	}

	if((gr->matrix = (int **) malloc(size * sizeof(int *))) < 0) {
		*err = GR_MALLOC;
		return NULL;
	}

	int i;
	for(i = 0; i < size; i++) {
		if((gr->matrix[i] = (int *) malloc(size * sizeof(int))) < 0) {
			*err = GR_MALLOC;
			return NULL;
		}
	}

	gr->size = size;
	*err = GR_SUCCESS;
	return gr;
}

void destroy_graph(graph *graph, GRERR *err) {
	// if(err == NULL) {
	// 	*err = GR_ERROR;
	// 	return;
	// }

	if(graph == NULL) {
		*err = GR_EMPTY;
		return;
	}

	int i;
	for(i = 0; i < graph->size; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
	*err = GR_SUCCESS;
	return;
}