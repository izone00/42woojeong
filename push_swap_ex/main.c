#include "./push_swap.h"

t_stack a;
t_stack	b;
int b_flag = (-1);


int main(int argc, char *argv[])
{

	a.len = 0;
	b.len = 0;

	for (a.len = 0; (a.len) < 20; (a.len)++)
		scanf(" %d", (a.arr) + (a.len));

	if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
		swap(&a);
	rotate(&a);
	print_stack(&a);
	for (int i = 1; i < 19; i++)
	{
		if (b_flag == (-1))
		{
			if (((a.arr)[a.len-2] > (a.arr)[a.len-1]) && ((a.arr)[a.len-2] < (a.arr)[0]))
				swap(&a);
			if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
				b_flag *= (-1);
			rotate(&a);
		}
		else
		{
			if (b.len == 0)
				push(&a, &b);
			else 
			{
				if (((a.arr)[a.len-2] > (a.arr)[a.len-1]) && ((a.arr)[a.len-2] < (b.arr)[b.len - 1]))
					swap(&a);
				if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
					b_flag *= (-1);
				push(&a, &b);
			}
		}
		printf("\n");
	}
	print_count();
}

void print_stack()
{
	printf("b: %2d ", b_flag);
	printf("[");
	for (int i = 0; i < a.len; i++)
		printf("%d ", (a.arr)[i]);
	printf("] ");
	printf("[");
	for (int i = 0; i < b.len; i++)
		printf("%d ", (b.arr)[i]);
	printf("]\n");
}

/*

for (int i = 0; i < 20; i++)
		scanf(" %d", (a.arr) + i);
7 9 10 2 3 5 6 1 4 8
8 9 10 2 3 5 6 1 4 7

17 3 6 9 20 11 12 14 4 18 19 10 7 16 8 1 13 2 15 5 

*/