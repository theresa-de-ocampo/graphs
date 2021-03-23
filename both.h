#include <stdio.h>
#include <string.h>
#define MAX 50
#define ERROR 0
#define SUCCESS 1

void add_not_visited(char q[], int *rear, char v);
void traverse_sub_graph(char adj_matrix[][MAX], int n, int *front, int *rear, int *last);
char remove_fr_q(char q[], int *front);
int present(char q[], int last, char v);
void add_visited(char q[], int *last, char v);
int find_pos(char adj_matrix[][MAX], int n, int v);
void display_visited(char q[], int last);
void display(char adj_matrix[][MAX], int n);
void display_fixed(char adj_matrix[][MAX], int n, int x, int y);

char
get_sagot(){
	char sagot;
	scanf(" %c", &sagot);
	return toupper(sagot);
}

void
add_vertex(char adj_matrix[][MAX], int n, char new_vertex){
	adj_matrix[n][0] = adj_matrix[0][n] = new_vertex;
	for (int i = 1; i <= n; ++i)
		adj_matrix[n][i] = adj_matrix[i][n] = '0';
}

int
vertex_is_valid(char adj_matrix[][MAX], int n, int new_vertex){
	for (int i = 0; i <= n; ++i)
		if (adj_matrix[0][i] == new_vertex)
			return ERROR;
	return 1;
}

void
output_and_refresh(char adj_matrix[][MAX], int n){
	system("cls");
	display(adj_matrix, n);
	printf("\nPress any key to continue...");
	getchar();
	getchar();
	refresh_sub_menu();
}

void
check_display(char adj_matrix[][MAX], int status, int n){
	if (status == SUCCESS)	
		output_and_refresh(adj_matrix, n);
}

int
del(char adj_matrix[][MAX], int *n, char vertex_to_be_del){
	int x, r, c;
	x = find_pos(adj_matrix,*n, vertex_to_be_del);
	if (x == ERROR){
		gotoxy(20, 19); printf("*** [ERROR]: Vertex to be deleted does not exist! ***");
		return ERROR;
	}
	else{
		if (x == 1)
			for (c = x; c <= *n; ++c)
				adj_matrix[0][c] = adj_matrix[0][c + 1]; 
		else{
			for (c = x; c <= *n; c++)
				for (r = 0; r < x; r++)
					adj_matrix[r][c] = adj_matrix[r][c + 1]; 
		}
			
		for (r = x; r <= *n; ++r)			
		    for (c = 0; c <= *n; ++c)
		   		if (c >= x)
		   			adj_matrix[r][c] = adj_matrix[r + 1][c + 1];
		   		else
		   			adj_matrix[r][c] = adj_matrix[r + 1][c];
		--*n; 
	}
	return SUCCESS;
}

void
neighbors(char adj_matrix[][MAX], int n, int v){
	int r, c, x = 25, y = 8;
	for (r = 1; r <= n; ++r)
		if (adj_matrix[0][r] == v)
			break;
	if (r > n){
		gotoxy(25, 19); printf("*** [ERROR]: Vertex does not exist! ***");
	}
	else{
		for (c = 1; c <= n; ++c){
			if (adj_matrix[r][c] == '1'){
				gotoxy(x, y); printf("%c ", adj_matrix[0][c]); 
				x += 2;
			}
			if (x > 75)
				++y;
		}
	}
}

void
bfs(char adj_matrix[][MAX], int n){
	char visited[MAX], not_visited[MAX], v, start;
	int front = -1, rear = -1, last = -1, pos;
	
	do{
		gotoxy(25, 6); printf("Starting Vertex: ");
		scanf(" %c", &start);
		start = toupper(start);
		pos = find_pos(adj_matrix, n, start);
		if (pos == ERROR){
			gotoxy(25, 19); printf("*** [ERROR]: Vertex does not exist! ***");
		}
	} while (pos == ERROR);
	
	do{
		add_not_visited(not_visited, &rear, adj_matrix[pos][0]);
		while (front <= rear){
			v = remove_fr_q(not_visited, &front);
			if (!(present(visited, last, v)))
				add_visited(visited, &last, v);
			pos = find_pos(adj_matrix, n, v);
			for (int i = 1; i <= n; ++i)
				if (adj_matrix[pos][i] == '1')
					if (!(present(not_visited, n, adj_matrix[0][i])) && !(present(visited, n, adj_matrix[0][i])))
						add_not_visited(not_visited, &rear, adj_matrix[0][i]);
		}
		
		// Checks if there is an unreachable (node or) subgraph from the starting vertex
		// and if there is, another breadth-first search will be done on the other subgraph/s
		for (int i = 1; i <= n; ++i)
			if (!(present(visited, last, adj_matrix[i][0]))){
				pos = i;
				break;
			}
	} while (last < n);
	display_visited(visited, last);
}

void
add_not_visited(char q[], int *rear, char v){
	q[++*rear] = v;
}

char
remove_fr_q(char q[], int *front){
	char ch = q[*front];
	++*front;
	return ch;
}

int
present(char q[], int last, char v){
	int result = 0;
	for (int i = 0; i <= last; ++i)
		if (q[i] == v){
			result = 1;
			break;
		}
	return result;
}

void
add_visited(char q[], int *last, char v){
	q[++*last] = v;
}

void
display_visited(char q[], int last){
	int x = 25, y = 8;
	for (int i = 0; i <= last; ++i){
		gotoxy(x, y); printf("%c ", q[i]); 
		x += 2;
		if (x > 75)
			++y;
	}
}

int
find_pos(char adj_matrix[][MAX], int n, int v){
	for (int i = 0; i <= n; ++i)
		if (adj_matrix[i][0] == v)
			return i;
	return ERROR;
}

void
display(char adj_matrix[][MAX], int n){
	for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= n; ++j)
			printf("%c ", adj_matrix[i][j]);
		printf("\n");
	}
}

void
display_fixed(char adj_matrix[][MAX], int n, int x, int y){
	int init_x = x;
	for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= n; ++j){
			gotoxy(x, y); printf("%c", adj_matrix[i][j]); ++x;
			gotoxy(x, y); printf(" "); ++x;
		}
		x = init_x; ++y;
	}
}
