#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<ncurses.h>

int rows,cols;

/**
 * generates a board
 */
char** generate() {
	getmaxyx(stdscr, rows, cols);
	
	char **screen = malloc(sizeof(char*) * rows);
	for (int i = 0; i < rows; ++i) {
		screen[i] = calloc(cols, sizeof(char));
	}
	return screen;
}

/**
 * initalizes the game by reading the input file
 */
void init(char** screen, char* filename){
	int centery = rows/2;
	int centerx = cols/2;

	char file[100] = "patterns/";
	strcat(file, filename);
	FILE *fp =fopen(file, "r");
	if (fp == NULL) {
		printf("Can't open file for reading\n");
		endwin();
		exit(1);
	}

	char* line = NULL;
	size_t len = 0;

	while(getline(&line, &len, fp) > 0) {
		if (!strcmp(line,"0")) break;
		int col = atoi(strtok(line, ","));
		int row = atoi(strtok(NULL,","));
		screen[centery + row][centerx + col] = '*';
	}
	fclose(fp);
}

/**
 * Checks the board at position with predefined rules
 */
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

/**
 * Updates the board each tick acording to the rules
 */
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

/**
 * updates the output on the display
 */
void display(char** state) {
	clear();
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if(state[i][j] == '*') mvprintw(i, j, "*");
		}
	}
	refresh();
	//  0.5 seconds
	usleep(500000);
}

/**
 * Main funtion loop for the game of life
 */
int main(int argc, char* argv[]){
	// Checks the args
	if (argc !=  2) {
		printf("Usage: life <pattern>, life -list\n");
		exit(1);
	}
	if (argc == 2 && !strcmp(argv[1],"-list")) {
		struct dirent *de;
		DIR *dr = opendir("patterns/.");
		if (dr == NULL){
			printf("Failed to open directory ./patterns\n");
			exit(1);
		}

		while ((de = readdir(dr)) != NULL)
			if (strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
			printf("%s\n", de->d_name);

		closedir(dr);
		exit(1);
	}

	initscr();
	noecho();
	curs_set(0);

	char** state = generate();
	init(state, argv[1]);
	
	// loop, ctrl-c to break
	while (1) {
		display(state);
		state = update(state);
	}
	
	endwin();
	return 0;
}
