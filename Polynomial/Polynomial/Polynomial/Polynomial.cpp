#include <stdio.h>

#define Max_count	10
#define Max_poly	2
#define Poly_ch1	0
#define Poly_ch2	1

typedef struct
{
	int coff[Max_count];
	int degree;
	void (*func)(void);
}Polynomial_tbl;

Polynomial_tbl polynomial[Max_poly];

void PolySet(Polynomial_tbl a)
{
	int coff, degree;
	printf("\n degree");
	scanf_s("%d", &degree);

	a.degree = degree;
	printf("\n coff: ");
	for (int i = degree; i >0; i--)
	{
		printf("\n");
		scanf_s("%d", &coff);
		a.coff[i] = coff;
	}
}

void PolyPrintf(Polynomial_tbl a)
{
	for (int i = a.degree; i > 0; i--)
	{
		printf("%dx^%d +", a.coff[i], i);
	}
	printf("\n");
};
void Polyadd(Polynomial_tbl a, Polynomial_tbl b)
{
 
}

int main(void)
{

	PolySet(polynomial[Poly_ch1]);
	PolySet(polynomial[Poly_ch2]);
	PolyPrintf(polynomial[Poly_ch1]);

	return 0;
}