#pragma once
#include <cstdio>
#include <iostream>
class Rectangle {
private:
	double width;
	double height;
public:
	Rectangle(double w, double h) {
		width = w;
		height = h;
	}
	void printRectangle(void)
	{
		printf("width:%lf \n", width);
		printf("height:%lf \n", height);
	}

	double getsizeRectangle(void)
	{
		return  (width * height);
	}

	double getclrcRectangle(void)
	{
		return 2 * (width + height);
	}
	
	bool IsSquare(void) {
		return ((width == height) ? 1 : 0);
	}

};