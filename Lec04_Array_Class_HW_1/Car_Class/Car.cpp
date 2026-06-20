#include "Car.h"


int main(void)
{
	Car		  Morning(50, "Morning", 4);
	SportsCar Ferrari(200, "Ferrari", 5, false);

	Morning.display();
	Ferrari.display();

	Morning.changeGear(5);  //Morning.gear ->5
	Morning.speedUp();     // Morning.speed -> 55
	Morning.display();

	Ferrari.speedUp();     // not use bTurbo -> 205
	Ferrari.display();

	Ferrari.setTurbo(true); // use bTurbo
	Ferrari.changeGear(6);  // Ferrari.gear ->6
	Ferrari.speedUp();		// Ferrari.speed ->225
	Ferrari.display();


	return 0;
}