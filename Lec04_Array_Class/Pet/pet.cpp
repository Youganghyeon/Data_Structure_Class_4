#include "pet.h"
#include <cstdio>

using namespace std;
int main(void)
{
	Pet a("puppy", 10, "puddle");
	Puppy b("youganghyeon", 10, "puppy", "puddle");

	cout << "Name \t" << b.getName() << endl;
	cout << "age \t" << b.getage()<< endl;
	cout << "type \t" << b.getType() << endl;
	cout << "breed \t" << b.getBreed() << endl;
	return 0;
}