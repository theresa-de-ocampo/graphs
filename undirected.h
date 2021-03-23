#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <unistd.h>
#include "border.h"
#include "both.h"
#define MAX 50
#define ERROR 0
#define SUCCESS 1

void insert(char adj_matrix[][MAX], int *n);
int vertex_is_valid(char adj_matrix[][MAX], int n, int new_vertex);
int edge(char adj_matrix[][MAX], int *n, char v1, char v2);
int edge_is_valid(int v1, int v2);
int add_edge(char adj_matrix[][MAX], int n, char v1, char v2);
int del(char adj_matrix[][MAX], int *n, char vertex_to_be_del);
int del_edge(char adj_matrix[][MAX], int n, char v1, char v2);

// Helper Functions
int find_indices(char adj_matrix[][MAX], int n, char v1, char v2, int *x, int *y);  // For add_edge and del_edge
void check_display(char adj_matrix[][MAX], int status, int n);						// For del and del_edge

void
undirected(){
	int choice, status;
	char sagot, v1, v2, vertex_to_be_del;
	// Initial pre-made graph
	char adj_matrix[MAX][MAX] = {
		{'-', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
		{'A', '0', '1', '1', '1', '1', '1', '1', '0'},
		{'B', '1', '0', '1', '0', '0', '1', '0', '0'},
		{'C', '1', '1', '0', '0', '0', '0', '1', '0'},
		{'D', '1', '0', '0', '0', '1', '0', '0', '1'},
		{'E', '1', '0', '0', '1', '0', '0', '0', '1'},
		{'F', '1', '1', '0', '0', '0', '0', '0', '1'},
		{'G', '1', '0', '1', '0', '0', '0', '0', '1'},
		{'H', '0', '0', '0', '1', '1', '1', '1', '0'}
	};
	int no_vertices = 8;
	
	frame_1();
	gotoxy(3, 3);  printf("To help you get started with this program,");
	gotoxy(3, 4);  printf("    here's a pre-made graph where you could test the operations.");
	gotoxy(3, 5);  printf("You could always destroy the graph if you want to start with a blank slate.");
	display_fixed(adj_matrix, no_vertices, 30, 9);
	gotoxy(3, 20); printf("Press any key to continue...");
	getchar();
	
	do{
		refresh_sub_menu();
		gotoxy(3, 16); printf("Pick a no.: ");
		status = scanf("%d", &choice);
		switch(choice){
			case 1:
				if (no_vertices == MAX - 1){
					gotoxy(20, 19); printf("*** [ERROR] This program only accommodates a max of %d nodes ***", MAX - 1);
				}
				else
					insert(adj_matrix, &no_vertices);
				break;
			case 2:
				gotoxy(25, 6); printf("Sample Format: A B");
				do{
					refresh_sub_menu();
					gotoxy(25, 8); printf("Edge: ");
				    scanf(" %c %c", &v1, &v2);
					v1 = toupper(v1);
					v2 = toupper(v2);
					edge(adj_matrix, &no_vertices, v1, v2);
					gotoxy(25, 9); printf("Add another edge? ");
					sagot = get_sagot();
				} while (sagot == 'Y');
				break;
			case 3:
				do{
					refresh_sub_menu();
					if (no_vertices == 0){
						gotoxy(25, 19); printf("*** [ERROR]: Graph is already empty! ***");
						sagot = 'N';
					}
					else{
						gotoxy(25, 6); printf("Vertex: ");
						scanf(" %c", &vertex_to_be_del);
						vertex_to_be_del = toupper(vertex_to_be_del);
						status = del(adj_matrix, &no_vertices, vertex_to_be_del);
						check_display(adj_matrix, status, no_vertices);
						gotoxy(25, 9); printf("Delete another node? ");
						sagot = get_sagot();
					}
				} while (sagot == 'Y');
				break;
			case 4:
				do{
					refresh_sub_menu();
					gotoxy(25, 6); printf("Sample Format: A B");
					gotoxy(25, 8); printf("Edge: ");
					scanf(" %c %c", &v1, &v2);
					v1 = toupper(v1);
					v2 = toupper(v2);
					status = del_edge(adj_matrix, no_vertices, v1, v2);
					check_display(adj_matrix, status, no_vertices);
					gotoxy(25, 9); printf("Delete another edge? ");
					sagot = get_sagot();
				} while (sagot == 'Y');
				break;
			case 5:
				do{
					refresh_sub_menu();
					gotoxy(25, 6); printf("Vertex: ");
					scanf(" %c", &v1);
					v1 = toupper(v1);
					neighbors(adj_matrix, no_vertices, v1);
					gotoxy(25, 10); printf("Examine another vertex? ");
					sagot = get_sagot();
				} while (sagot == 'Y');
				break;
			case 6:
				no_vertices = 0;
				gotoxy(25, 9); printf("Graph was successfully cleared!\n");
				break;
			case 7:
				bfs(adj_matrix, no_vertices);
				break;
			case 8:
				output_and_refresh(adj_matrix, no_vertices);
				break;
			default:
				gotoxy(25, 19); printf("*** [ERROR]: Invalid Selection! ***");
		}
		gotoxy(25, 13); printf("Choose from our menu again? ");
		sagot = get_sagot();
	} while(sagot == 'Y' || status == ERROR);
}

void
insert(char adj_matrix[][MAX], int *n){
	char new_vertex, adjacent_vertex, sagot;
	int more;
	do{
		refresh_sub_menu();
		gotoxy(25, 6); printf("Vertex: ");
		scanf(" %c", &new_vertex);
		new_vertex = toupper(new_vertex);
		if (vertex_is_valid(adj_matrix, *n, new_vertex)){
			++*n;
			add_vertex(adj_matrix, *n, new_vertex);
			gotoxy(26, 19); printf("[NOTE] Enter 0 if %c is an isolated vertex.", new_vertex);
			do{
				refresh_sub_menu();
				gotoxy(25, 7); printf("Edge: %c---", new_vertex);
				scanf(" %c", &adjacent_vertex);
				adjacent_vertex = toupper(adjacent_vertex);
				more = edge(adj_matrix, n, new_vertex, adjacent_vertex);
				if (more == 0)
					sagot = 'N';
				else{
					gotoxy(25, 9); printf("Add another edge? ");
					sagot = get_sagot();
				}
			} while (sagot == 'Y');
			gotoxy(25, 11); printf("Insert another node? ");
			sagot = get_sagot();
		}
		else{
			gotoxy(20, 19); printf("* [ERROR] Please choose a unique label for the node. *");
			sleep(1.5);
			sagot = 'Y';
		}
	} while (sagot == 'Y');
}

int
edge(char adj_matrix[][MAX], int *n, char v1, char v2){
	int status;
	if (edge_is_valid(v1, v2)){
		if (v2 == '0'){
			output_and_refresh(adj_matrix, *n);
			return 0;
		}
		else{
			status = add_edge(adj_matrix, *n, v1, v2);
			if (status == ERROR){
				gotoxy(23, 19); printf("* [ERROR] Please insert the vertex/vertices first. *");
			}
			else
				output_and_refresh(adj_matrix, *n);
		}
	}
	else{
		gotoxy(20, 19); printf("* [ERROR] Self-loop is not allowed in undirected graphs! *");
	}
	return 1;
}

int
edge_is_valid(int v1, int v2){
	if (v1 == v2)
		return ERROR;
	else
		return 1;
}

int
add_edge(char adj_matrix[][MAX], int n, char v1, char v2){
	int status, x = 0, y = 0;
	status = find_indices(adj_matrix, n, v1, v2, &x, &y);
	if (status == ERROR)
		return ERROR;
	else{
		adj_matrix[x][y] = '1';
		adj_matrix[y][x] = '1';
		return SUCCESS;
	}
}

int
del_edge(char adj_matrix[][MAX], int n, char v1, char v2){
	int status, x = 0, y = 0;
	status = find_indices(adj_matrix, n, v1, v2, &x, &y);
	if (status == ERROR){
		gotoxy(25, 19); printf("*** [ERROR]: Vertex not found! ***");
		return ERROR;
	}
	else{
		adj_matrix[x][y] = '0';
		adj_matrix[y][x] = '0';
		return SUCCESS;
	}
}

int
find_indices(char adj_matrix[][MAX], int n, char v1, char v2, int *x, int *y){
	for (int i = 0; i <= n; ++i){
		if (adj_matrix[0][i] == v1)
			*x = i;
		if (adj_matrix[0][i] == v2)
			*y = i;
	}
	if  (*x == ERROR || *y == ERROR)
	    return ERROR;
	else
		return 1;
}
