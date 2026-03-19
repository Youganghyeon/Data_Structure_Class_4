#include <cstdio>


#define USER_CODE 0

int findMax(int score[], int n)
{
	int tmp = score[0];
	for (int i = 0; i < n; i++)
	{
		if (score[i] > tmp) {
			tmp = score[i];
		}
	}
	return tmp;
}

void main()
{
	int score[5] = { 1,10,2,4,5 };
	int out;
	out = findMax(score, 5);
	printf("result = %d", out);
}


#if USER_CODE
#define Max 5

int findMax(int* p_node, int n);

int main(void)
{
	int test[Max] = { 1,10,2,4,5 };
	int max;
	max=findMax(&test[0], Max);
	printf("%d \n", max);
	return 0;
}

int findMax(int* p_node, int n)
{
	if (p_node == NULL || n <= 0)
	{
		return -1;
	}
	int* temp = p_node;
	for (int i = 0; i < Max; i++)
	{
		if (*temp < p_node[i])
		{
			temp = &p_node[i];
		}

	}
	return *temp;

}
#endif
