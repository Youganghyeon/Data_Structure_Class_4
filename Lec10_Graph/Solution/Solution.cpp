#include "Solution.h"

#define STACK			1
#define QUEUE			2
#define DEQUE			3
#define ROW				6
#define COLUMN			6

// 입구에 대한 고민.
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	'1','1','1','0','1','1',
	'0','0','1','0','0','0',
	'1','0','1','0','1','1',
	'1','0','1','0','1','1',
	'0','0','1','0','0','0',
	'1','1','1','0','1','1',
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)return false;
	else return map[r][c] == '0';
};

void MapView(char map[MAZE_SIZE][MAZE_SIZE])
{
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{

			printf("%c | ", map[i][j]);
			if (j == MAZE_SIZE-1)
			{
				printf("\n");
				break;
			}
		}
	}
}

int Act(stack<Location2D> locStack, int i, int j)
{
	int count = 0;
	if (map[i][j] == '1')
		return 0;

	Location2D entry(i, j);
	locStack.push(entry);
	printf("\nEntry (%d %d) \n", i, j);
	while (locStack.empty() == false) {
		Location2D here = locStack.top();
		locStack.pop();

		int r = here.row, c = here.col;
		printf(" \n (%d, %d)", r, c);
		if (map[r][c] == '0') {
		}
		else {
			map[r][c] = '.';
			if ((r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)) return 0;
			if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
			if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
			if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
			if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
		}
	}
	printf("\n count! \n");
	count = 1;
	return count;
}

int  main(void)
{
	int column_check = 0;
	int counting = 0;
	MapView(map);
	/*stack<Location2D>locSt;
	locSt.push(Location2D(1, 0));
	Location2D p = locSt.top();
	locSt.pop();*/
	stack<Location2D>locStack;
	deque<Location2D>locDeque;
	queue<Location2D>locQueue;

	Location2D entry(1, 0);
	locStack.push(entry);
	int temp = 0;
	for (int i = 0; i < ROW; i++)
	{
		if (i == 0)
		{
			column_check = 1;
		}
		else if (i == ROW - 1)
		{
			column_check = 1;
		}
		else
		{
			column_check = 0;
		}

		for(int j=0; j<COLUMN; j++)
		{
			temp = Act(locStack, i, j);
			counting += temp;
			j++;
			if (column_check == 1)
			{
				j = COLUMN-1;
			}
			
		}
	}
	printf("counting : %d \n", counting);
	return 0;
}
