#include "graph.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	GRERR err = GR_SUCCESS;

	int vertices[5][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 0}, {1, 3}};

	fprintf(stdout, "Test init_graph #1 ");
	init_graph(-1, &err);
	(err == GR_BADSIZE) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test init_graph #2 ");
	graph* gr = init_graph(5, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test add_edge #1 ");
	add_edge(NULL, 1, 1, &err);
	(err == GR_EMPTY) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test add_edge #2 ");
	add_edge(gr, 10, -1, &err);
	(err == GR_BADSIZE) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test add_edge #3 ");
	add_edge(gr, 2, 1, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test add_edges #1 ");
	add_edges(NULL, &vertices[0][0], 5, &err);
	(err == GR_EMPTY) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test add_edges #2 ");
	add_edges(gr, &vertices[0][0], 5, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test print_graph #1 ");
	print_graph(NULL, &err);
	(err == GR_EMPTY) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test print_graph #2 ");
	print_graph(gr, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test destroy_graph #1 ");
	destroy_graph(NULL, &err);
	(err == GR_EMPTY) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test destroy_graph #2 ");
	destroy_graph(gr, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	return 0;
}