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
	screen[(rows/2) - 1][cols/2] = '*';
	screen[(rows/2) + 1][cols/2] = '*';
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
	if (row == rows - 1) endy = rows - 2;
	if (col == 0) startx = 0;
	if (col == cols - 1) endx = cols - 2;

	int count = 0;
	if (state[row][col] == '*') count--;
	for (int i = starty; i <= endy; ++i) {
		for(int j = startx; j <= endx; ++j) {
			if (state[i][j]) count++;
		}
	}
	//if (count > 0) printf("%i\n", count);
	// check conways rules
	if(state[row][col] != '*' && count == 3) return 1;
	else if(state[row][col] != '*') return 0;
	
	if(count < 2) return 0;
	if(count > 3) return 0;
	return 1;
}

char** update(char** state) {
	char** nextState = generate();
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j) {
			if (check(state, i ,j)) nextState[i][j] = '*';
			else nextState[i][j] = '\0';
		}
	}
	// free the memeory
	for(int i = 0; i < rows; ++i) {
		free(state[i]);
	}
	free(state);
	return nextState;
}

void display(char** state) {
	clear();
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
   	char** state = generate();
	init(state);
	while (1) {
		display(state);
		state = update(state);
		getch();
	}
	
	getch();
	endwin();
	return 0;
}
