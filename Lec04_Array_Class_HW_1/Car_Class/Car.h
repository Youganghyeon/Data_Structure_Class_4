#pragma once
#include <cstdio>
#include <string.h>

class Car {
protected:
	int speed;
	char name[40];
public:
	int gear;

	Car(int s, const char* n, int g)
		: speed(s), gear(g) {
		strcpy_s(name, n);
	}
	void changeGear(int g = 4) {
		gear = g;
	}
	void speedUp() {
		speed += 5;
	}

	void display() {
		printf("[%s]: 기어=%d단 속도=%dkmph\n", name, gear, speed);
	}
	void whereAmI() {
		printf("객체 주소 = %p \n", (void*)this);
	}
};

class SportsCar : public Car
{
public:
	bool bTurbo;
	SportsCar(int s, const char* n, int g, bool bTrubo)
		:Car(s, n, g), bTurbo(false)
	{
	}
	void setTurbo(bool bTur) { bTurbo = bTur; }
	void speedUp() {
		if (bTurbo)	speed += 20;
		else Car::speedUp();
	}
};