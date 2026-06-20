#include <cstdio>

#define	HEIGHT	8
#define	WIDTH	8

int GetMaxPixel(int(*image)[WIDTH]);

int GetMaxPixel(int(*image)[WIDTH])
{
	int temp = image[0][0];
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (temp < image[i][j])
			{
				temp = image[i][j];
			}

		}
	}
	return temp;

};
int image[HEIGHT][WIDTH] = {
  {  10,  30,  55,  80, 120, 160, 200, 230},
  {  20,  45,  70, 100, 140, 180, 220, 210},
  {  35,  60,  90, 130, 170, 210, 240, 190},
  {  50,  80, 115, 150, 190, 230, 255, 170},
  {  40,  65, 100, 140, 175, 215, 235, 150},
  {  25,  50,  80, 115, 155, 195, 210, 130},
  {  15,  35,  60,  90, 130, 165, 185, 110},
  {    5,  20,  40,  70, 105, 140, 160,  90},
};


int main(void)
{
	int Max_val;
	Max_val = GetMaxPixel(&image[0]);
	printf("MaxPixel: %d \n", Max_val);
	return 0;
}
