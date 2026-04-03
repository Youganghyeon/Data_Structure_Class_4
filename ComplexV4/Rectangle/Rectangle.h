#pragma once
#include <cstdio>
class Rectangle {
private: 
	int width;
	int height;
public :
	void ReadRectangle(void)
	{
		printf("width \n");
		scanf_s("%d", width);
		printf("height \n", height);
		scanf_s("%d", height);
	}

	void printRectangle(void)
};