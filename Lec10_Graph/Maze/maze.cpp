#include "maze.h"

#define STACK			1
#define QUEUE			2
#define DEQUE			3
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	'1','1','1','1','1','1',
	'e','0','1','0','0','1',
	'1','0','0','0','1','1',
	'1','0','1','0','1','1',
	'1','0','1','0','0','x',
	'1','1','1','1','1','1',
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)return false;
	else return map[r][c] == '0' || map[r][c]=='x';
};

int main(void)
{
	int ch;
	printf("1: Stack 2: Deque(queue) 3: Deque(stack)\n");
	scanf_s("%d", &ch);
	printf("\n");
	/*stack<Location2D>locSt;
	locSt.push(Location2D(1, 0));
	Location2D p = locSt.top();
	locSt.pop();*/
	stack<Location2D>locStack;
	deque<Location2D>locDeque;
	queue<Location2D>locQueue;

	Location2D entry(1, 0);
	switch (ch)
	{
	case STACK:
		//Location2D entry(1, 0);
		locStack.push(entry);

		while (locStack.empty() == false) {
			Location2D here = locStack.top();
			locStack.pop();

			int r = here.row, c = here.col;
			printf("(%d, %d)", r, c);
			if (map[r][c] == 'x') {
				printf("Success \n");
				return 0;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
			}
		}
		printf("fail!");
	case QUEUE:
		locQueue.push(entry);

		while (locQueue.empty() == false) {
			Location2D here = locQueue.front();
			locQueue.pop();

			int r = here.row, c = here.col;
			printf("(%d, %d)", r, c);
			if (map[r][c] == 'x') {
				printf("Success \n");
				return 0;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locQueue.push(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locQueue.push(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locQueue.push(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locQueue.push(Location2D(r, c + 1));
			}
		}
		printf("fail!");
	case DEQUE:
		//Location2D entry(1, 0);
		locDeque.push_front(entry);

		while (locDeque.empty() == false) {
			Location2D here = locDeque.front();
			locDeque.pop_front();

			int r = here.row, c = here.col;
			printf("(%d, %d)", r, c);
			if (map[r][c] == 'x') {
				printf("Success \n");
				return 0;
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
			}
		}
		printf("fail!");

	}
	
	return 0;
}
