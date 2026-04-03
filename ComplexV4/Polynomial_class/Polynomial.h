#pragma once
#include <cstdio>
#define Max_coeff 10
class Polynomial {
private:
	int degree;
	int coeff[Max_coeff];
public:
	void readPolynomial(void)
	{
		printf("degree: \n");
		scanf_s("%d", &degree);
		printf("coeff: \n");
		for (int i = 0; i <= degree; i++)
		{
			scanf_s("%d", &coeff[i]);
		}
	}

	void printPolynomial(void)
	{
		for (int i = 0; i <= degree; i++)
		{
			printf("%dx^%d", coeff[i], degree - i);
			if ((i + 1) != degree && coeff[i + 1] != 0)
			{
				printf("+");
			}
		}
		printf("\n");
	}

	void addPolynomial(Polynomial a, Polynomial b)
	{
		if (a.degree < b.degree)
		{
			diff=
			for(int i=)
		}
		else if (a.degree > b.degree)
		{

		}
	}
};

