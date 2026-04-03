#pragma once
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

class Pet {
protected:
	string name;
	int age;
	string type;
public:
	Pet(string name_i, int age_i, string type_i)
	{
		name = name_i;
		age = age_i;
		type = type_i;
	}
	string getName() {
		return name;
	}
	int getage() {
		return age;
	}
	string getType() {
		return type;
	}
};

class Puppy : public Pet {
private:
	string breed;
public:
	Puppy(string n, int a, string f, string h)
		:Pet(n, a, f), breed(h)
	{

	}
	string getBreed() {
		return breed;
	}
};