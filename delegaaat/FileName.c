#include <stdio.h>
#include <stdlib.h>
int summ(int, int);
int sub(int, int);

typedef int (*f) (int, int);
typedef f* delegat;
int n = 0;

void addFunction(delegat d, f func) 
{
	n++;
	d = (delegat)realloc(d, n * sizeof(f));
	d[n - 1] = func;
}
void remAllFunction(delegat d) //удаление всех функций
{
	for (int i = 0; i < n; i++)
	{
		d[i] = NULL;
	}
	n -= n;
	d = (delegat)realloc(d, 1 * sizeof(f));
}
void remOne(delegat d, int i) 
{
	for (size_t j = i; j < n-1; j++)
	{
		d[j] = d[j + 1];
		d[j + 1] = NULL;
	}
}
void remFunction(delegat d, f func) //удаление конкретной функции
{
	int del = 0;

	for (int i = 0; i < n; i++)
	{
		if (d[i] == func)
		{
			remOne(d, i);
			del++;
			if (d[i] == func) 
			{
				remOne(d, i);
				del++;
			}
		}
	}
	n -= del;
	d = (delegat)realloc(d, n * sizeof(f));
}
void remDuble(delegat d) 
{
	int del = 0;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (d[i] == d[j] && j > i && d[i]!= NULL)
			{
				remOne(d, j);
				del++;
			}
		}
	}
	n -= del;
	d = (delegat)realloc(d, n * sizeof(f));
}
void printFunction(delegat d, int a, int b) 
{
	if (n == 0) printf("empty");
	else {
		for (int i = 0; i < n; i++)
			printf("%d ", d[i](a, b));
	}
}
int main() 
{
	delegat del = malloc(n + 1, sizeof(f));
	addFunction(del, summ);
	addFunction(del, sub);
	addFunction(del, summ);
	addFunction(del, sub);
	addFunction(del, sub);
	addFunction(del, summ);
	addFunction(del, summ);

	printf("Output of all functions: ");
	printFunction(del, 2, 5);
	remAllFunction(del);//удаление всех функций
	//remFunction(del, summ);//удаление конкретной функции
	//remDuble(del);//удаление повторяющихся функций

	printf("\nDelegate after removing functions: ");
	printFunction(del, 2, 5);
}
int summ(int a, int b) {
	return  a + b;
}
int sub(int a, int b) {
	return  b - a;
}
