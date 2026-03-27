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
	scanf("%d", &degree);

	a.degree = degree;
	printf("\n coff: ");
	for (int i = degree; i > 0; i--)
	{
		printf("\n");
		scanf("%d", &coff);
		a.coff[i] = coff;
	}
}

void PolyPrintf(Polynomial_tbl a)
{
	printf()
}
void Polyadd(Polynomial_tbl a, Polynomial_tbl b)
{
 
}

void Poly

int main(void)
{

	PolySet(polynomial[Poly_ch1]);
	PolySet(polynomial[Poly_ch2]);

	return 0;
}