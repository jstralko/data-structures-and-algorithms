/**
 * Topo Sort.
 *
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX	8

int adj[MAX][MAX];
char sorted[MAX];

struct vertex {
	char label;
	bool visited;
};

struct vertex graph[MAX];
int num_vertices = 0;

int no_successors()
{
	int i, j;
	bool edge;

	for (i = 0; i < num_vertices; i++) {
		edge = false;
		for (j = 0; j < num_vertices; j++)
			if (adj[i][j] != 0) {
				edge = true;
				break;
			}

		if (!edge) return i;
	}
	//Graph has cycles?
	return -1;
}

/*
 * Directed Graph.  One Way
 */
void add_edge(int a, int b)
{
	adj[a][b] = 1;
}

void add_vertex(char l)
{
	if (num_vertices == MAX) {
		printf("ERROR: graph is maxed out\n");
		return;
	}

	graph[num_vertices].label = l;
	graph[num_vertices].visited = false;
	num_vertices++;
}

void delete_vertex(int v)
{
	int row, col;

	/*
	 * Move up everything
	 */
	for (row = v; row < num_vertices; row++) {
		graph[row] = graph[row+1];
		for (col = 0; col < num_vertices; col++)
		       adj[row][col] = adj[row+1][col]; 	
	}

	/*
	 * Move the adj matrix left
	 */
	for (row = 0; row < num_vertices; row++) {
		for (col = v; col < num_vertices; col++) {
			adj[row][col] = adj[row][col+1];
		}
	}
	
	num_vertices--;
}

void print_sorted()
{
	int i;

	for (i = 0;i < MAX; i++)
		printf("%c", sorted[i]);
	printf("\n");
}

void topo()
{
	int s;

	while (num_vertices > 0) {
		s = no_successors();
		if (s == -1) {
			printf("graph has cycles\n");
			return;
		}

		sorted[num_vertices-1] = graph[s].label;
		delete_vertex(s);
	}

	print_sorted();
		
}

int main(int argv, char *argc[])
{
	add_vertex('a'); //0
	add_vertex('b'); //1
	add_vertex('c'); //2
	add_vertex('d'); //3
	add_vertex('e'); //4
	add_vertex('f'); //5
	add_vertex('g'); //6
	add_vertex('h'); //7

	add_edge(0,3);	//ad
	add_edge(0,4);	//ae
	add_edge(1,4);	//be
	add_edge(2,5);	//cf
	add_edge(3,6);  //dg
	add_edge(4,6);  //eg
	add_edge(5,7);	//fh
	add_edge(6,7);	//gh

	topo();

	return 0;
}
