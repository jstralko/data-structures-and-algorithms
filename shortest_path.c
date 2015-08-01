/*
 * Shortest Path using Dijkstra's alogrithm
 *
 * Big-O is (log(v)*(v + e))
 *
 * Assume no negative paths are possbile
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX		10
#define INFINITY	99999

int adj[MAX][MAX];

struct shortest_path {
	int distance;
	int parent;
};

struct vertex {
	char label;
	bool in_tree;
};

struct vertex graph[MAX];
int num_vertices = 0;
int num_tree = 0;

struct shortest_path s_path[MAX];

int get_min_path(int v)
{
	int index, min_distance, i;

	index = -1;
	min_distance = INFINITY;

	for (i = 0; i < num_vertices; i++) {
		if (!graph[i].in_tree &&
			s_path[i].distance < min_distance) {
			min_distance = s_path[i].distance;
			index = i;
		}
	}

	return index;
}

void update_path(int current_index, int current_distance)
{
	int col, fringe;

	for(col = 1; col < num_vertices; col++) {
		if (graph[col].in_tree)
			continue;
		fringe = adj[current_index][col];

		fringe += current_distance;
		if (s_path[col].distance > fringe) {
			/*
			 * Found a shorter path,
			 * what our s_path
			 */
			s_path[col].distance = fringe;
			s_path[col].parent = current_index;
		}
	}
}

void find_shortest_path()
{
	int i, current_vertex, current_distance;

	current_vertex = 0;
	graph[current_vertex].in_tree = true;
	s_path[current_vertex].distance = 0;
	s_path[current_vertex].parent = 0; 	//make self parent
	num_tree++;

	//init path with what the distance of adj matrix
	for (i = 1; i < num_vertices; i++) {
		s_path[i].distance = adj[current_vertex][i];
	}

	while (num_tree < num_vertices) {
		int min_index;

		min_index = get_min_path(current_vertex);
		if (min_index == -1) {
			printf("Graph is not connected. Fail to find shortest path\n");
			return;
		}

		current_distance = s_path[min_index].distance;
		current_vertex = min_index;
		graph[current_vertex].in_tree = true;
		num_tree++;

		update_path(current_vertex, current_distance);
	}
}

void add_vertex(char c)
{
	if (num_vertices == MAX) {
		printf("Failed to add %c graph is full!\n", c);
		return;
	}

	graph[num_vertices++].label = c;	
}

void add_edge(int a, int b, int weight)
{
	adj[a][b] = weight; //directed graph
}

void init_adj()
{
	int i, j;

	for(i = 0; i < num_vertices; i++)
		for(j = 0; j < num_vertices; j++)
			adj[i][j] = INFINITY;
}

void display_paths()
{
	char parent;
	int i;

	for (i = 0; i < num_vertices; i++) {
		printf("%c = ", graph[i].label);
		if (s_path[i].distance == INFINITY)
			printf("inf");
		else
			printf("%d", s_path[i].distance);
		
		parent = graph[s_path[i].parent].label;
		printf("(%c) ", parent);
	}
	printf("\n");
}

int main(int argv, char *argc[])
{
	//init our graph
	add_vertex('a'); 	//0
	add_vertex('b'); 	//1
	add_vertex('c'); 	//..
	add_vertex('d');
	add_vertex('e'); 	//4

	//init every edge to INFINITY
	init_adj();

	add_edge(0, 1, 50); 	// AB 50
	add_edge(0, 3, 80); 	// AD 80
	add_edge(1, 2, 60); 	// BC 60
	add_edge(1, 3, 90); 	// BD 90
	add_edge(2, 4, 40);	// CE 40
	add_edge(3, 2, 20);	// DC 20
	add_edge(3, 4, 70);	// DE 70
	add_edge(4, 1, 50);	// EB 50

	find_shortest_path();
	display_paths();

	return 0;
}
