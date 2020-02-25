#include<stdlib.h>
#include<ncurses.h>

int rows,cols;


char** generate() {
	getmaxyx(stdscr, rows, cols);
	
	char **screen = malloc(sizeof(char*) * rows);
	for (int i = 0; i < rows; ++i) {
		screen[i] = calloc(cols, sizeof(char));
	}
	return screen;
}

void init(char** screen){
	screen[rows/2][cols/2] = '*';
	// TODO read from conway file
}


int check(char** state, int row, int col) {
	int startx, starty, endx, endy;
	startx = col - 1;
	endx = col + 1;
	starty = row - 1;
	endy = row + 1;

	// make sure we dont go out of bounds
	if (row == 0) starty = 0;
	if (row == rows) endy = rows;
	if (col == 0) startx = 0;
	if (col == cols) endx = cols;

	int count = 0;
	for (int i = starty; i < endy; ++i) {
		for(int j = startx; j < endx; ++j) {
			if (state[i][j] == '*' && i != row && j != col) count++;
		}
	}

	// check conways rules
	int alive = state[row][col] == '*';
	
	if(!alive && count == 3) return 1;
	else if(!alive) return 0;
	
	if(count < 2) return 0;
	if(count > 3) return 0;
	return 1;
}

void update(char** state) {
	char** nextState = generate();
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j) {
			if (check(state, i ,j)) {
				nextState[i][j] = '*';
			}
		}
	}
	// free the memeory
	for(int i = 0; i < rows; ++i) {
		free(state[i]);
	}
	free(state);
	
	state = nextState;
}

void display(char** state) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if(state[i][j] == '*') mvprintw(i, j, "*");
		}
	}
	refresh();
}

int main(){
	initscr();
	raw();
	noecho();
	printf("here\n"); 
	char** state = generate();
	init(state);
		printf("here\n"); 
	while(1) {
		display(state);
		update(state);
	}
	
	refresh();
	getch();
	endwin();
	return 0;
}
