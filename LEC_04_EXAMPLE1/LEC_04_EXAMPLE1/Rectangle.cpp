#include "rectangle.h"

using namespace std;

int main(void)
{
	Rectangle a(3.4, 2.5);
	cout << "Rectangle 1: " << endl;
	printf("Rectangle : \n");
	cout << "Area \t" << a.getsizeRectangle() << endl;
	cout << "clrc\t " << a.getclrcRectangle() << endl;
	cout << "IsSquare \t" << boolalpha<<a.IsSquare() << endl;
	//boolalpha 0:false 1:true·Î .
}