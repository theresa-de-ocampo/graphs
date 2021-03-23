/* DE OCAMPO, MARIA THERESA G.
 * BSIT 2 -3
 * GRAPHS
 * 23-09-2019
 */
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <unistd.h>
#include "undirected.h"
#include "directed.h"

#define ERROR 0

int
main(){
	int choice, status;
	char sagot;
	do{
		refresh_main_menu();
		gotoxy(4, 14); printf("Pick a no.: ");
		status = scanf("%d", &choice);
		getchar();
		sleep(0.10);
		switch(choice){
			case 1:
				undirected();
				break;
			case 2:
				directed();
				break;
			case 3:
				system("cls");
				exit(EXIT_SUCCESS);
				break;
			default:
				gotoxy(25, 19); printf("*** [ERROR] Invalid Selection! ***");
		}
		sleep(2);
	} while (choice != 3 || status == ERROR);
	return 0;
}
