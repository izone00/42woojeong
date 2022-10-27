#include "push_swap.h"

void	get_spl()
{
	int j = 0;
	a.larr[0] = 0;
	b.larr[0] = 0;
	a.spl = 1;
	b.spl = 1;
	for (int i = 0; i < a.len; i++)
	{
		a.larr[j]++;
		if (i < a.len-1 && a.arr[i] < a.arr[i+1])
		{
			a.spl++;
			j++;
			a.larr[j] = 0;
		}
	}
	j = 0;
	for (int i = 0; i < b.len; i++)
	{
		b.larr[j]++;
		if (i < b.len-1 && b.arr[i] < b.arr[i+1])
		{
			b.spl++;
			j++;
			b.larr[j] = 0;
		}
	}
	// for (int i = 0; i < a.spl; i++)
	// 	printf("%d ", a.larr[i]);
	// printf(" ");
	// for (int i = 0; i < b.spl; i++)
	// 	printf("%d ", b.larr[i]);
	// printf("  a.spl: %d, b.spl: %d", a.spl, b.spl);
	// printf("\n");
}

void print_stack()
{
	// printf("b: %2d ", b_flag);
	printf("[");
	for (int i = 0; i < a.len; i++)
	{
		printf("%d ", (a.arr)[i]);
		if (i < a.len-1 && a.arr[i] < a.arr[i+1])
			printf("| ");
	}
	printf("] ");
	printf("[");
	for (int i = 0; i < b.len; i++)
	{
		printf("%d ", (b.arr)[i]);
		if (i < b.len-1 && b.arr[i] < b.arr[i+1])
			printf("| ");
	}
	printf("] count: %d len_a: %d len_b: %d\n", count, a.len, b.len);
	printf("\n");
}

