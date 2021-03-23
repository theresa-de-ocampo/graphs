#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y){
	static HANDLE h = NULL;  
	if(!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };  
	SetConsoleCursorPosition(h,c);
}

void
frame_1(){
	int t, l, b, r, vd, hd;
	system("cls");

	for (t = 1; t <= 79; t++){
		gotoxy(t, 2); printf("%c", 177);
	}

	for (l = 3; l <= 22; l++){
		gotoxy(1, l); printf("%c", 177);
	}

	for (b = 1; b <= 79; b++){
		gotoxy(b, 23); printf("%c", 177);
	}

	for (r = 22; r >= 2; r--){
		gotoxy(79, r); printf("%c", 177);
	}
}

void
frame_2(){
	int t, l, b, r, vd, hd;

	frame_1();

	for (vd = 2; vd <= 22; vd++){
		gotoxy(18, vd); printf("%c", 177);
	}

	for (hd = 18; hd <= 79; hd++){
		gotoxy(hd, 15); printf("%c", 177);
	}
	
	gotoxy(19, 3); printf("MONITOR");
	gotoxy(19, 16); printf("PROCESSOR");
}

void
main_menu(){
	gotoxy(5, 4); printf("MAIN MENU");
	gotoxy(3, 6); printf("[1] Undirected");
	gotoxy(3, 7); printf("[2] Directed");
	gotoxy(3, 8); printf("[3] Exit");
}

void
sub_menu(){
	gotoxy(8, 4); printf("MENU");
	gotoxy(3, 6); printf("[1] Insert");
	gotoxy(3, 7); printf("[2] Add Edge");
	gotoxy(3, 8); printf("[3] Delete");
	gotoxy(3, 9); printf("[4] Del Edge");
	gotoxy(3, 10); printf("[5] Neighbors");
	gotoxy(3, 11); printf("[6] Clear");
	gotoxy(3, 12); printf("[7] BFS");
	gotoxy(3, 13); printf("[8] Display");
}

void
refresh_sub_menu(){
	frame_2();
	sub_menu();
}


void
refresh_main_menu(){
	frame_2();
	main_menu();
}
