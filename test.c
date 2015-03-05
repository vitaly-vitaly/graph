#include "graph.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("hello\n");
	GRERR err;
	printf("osjf\n");

	// fprintf(stdout, "Test init_graph #1 ");
	// init_graph(1, NULL);
	// (err == GR_ERROR) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test init_graph #2 ");
	init_graph(-1, &err);
	(err == GR_BADSIZE) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test init_graph #3 ");
	graph* gr = init_graph(10, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	// fprintf(stdout, "Test destroy_graph #1 ");
	// destroy_graph(NULL, NULL);
	// (err == GR_ERROR) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test destroy_graph #2 ");
	destroy_graph(NULL, &err);
	(err == GR_EMPTY) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");

	fprintf(stdout, "Test destroy_graph #3 ");
	destroy_graph(gr, &err);
	(err == GR_SUCCESS) ? fprintf(stdout, "PASSED\n") : fprintf(stdout, "FAILED\n");


	return 0;
}