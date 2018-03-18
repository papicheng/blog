#include "stdio.h"
#include "math.h"
int howlon(int x);

int main(void)
{
	int i = 0;
	int j = 0;
	int a = 0;
	int b = 0;
	int N = 0;
	int lon = 0;
	int pt = 0;
	int p0 = 0;
	printf("Please input the N!\n");
	scanf_s("%d", &N);
	lon = howlon(pow(2, N)-1);

	for (i = 0;i < pow(2, N);i++)
	{
		p0 = 0;
		pt = 0;
		for (j = lon - howlon(i);j >0 ;j--)
		{
			printf("0");
			pt++;
		}
		a = i;
		while (a != 0)
		{
			b = a % 2;
			a /= 2;
			if (p0 == 0&&b==0)
			{
				continue;
			}
			printf("%d", b);
			p0++;
			pt++;
		}
		for (j = 0;j < lon - pt;j++)
		{
			printf("0");
		}
		printf("\n");
	}

	return 0;
}
int howlon(int x)
{
	double f = 0;
	int exp = 0;
	f = frexp(x, &exp);
	return exp;
}