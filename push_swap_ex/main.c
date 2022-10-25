#include "./push_swap.h"

t_stack a;
t_stack	b;
int b_flag = (-1);
int count = 0;

int main(int argc, char *argv[])
{

	a.len = 0;
	b.len = 0;
	a.spl = 1;
	b.spl = 1;

	for (a.len = 0; (a.len) < SIZE; (a.len)++)
		scanf(" %d", (a.arr) + (a.len));
	printf("start: ");
	print_stack();
	if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
		swap(&a);
	rotate(&a);
	print_stack();
	for (int i = 1; i < SIZE-1; i++)
	{
		if (b_flag == (-1))
		{
			if (((a.arr)[a.len-2] > (a.arr)[a.len-1]) && ((a.arr)[a.len-2] < (a.arr)[0]))
				swap(&a);
			if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
				b_flag = 1;
			rotate(&a);
		}
		else
		{
			if (b_flag == 1)
			{
				if (((a.arr)[a.len-2] < (a.arr)[a.len-1]))
					swap(&a);
				push(&a, &b);
				b_flag++;
			}
			else 
			{
				if (((a.arr)[a.len-2] < (a.arr)[a.len-1]) && ((a.arr)[a.len-2] > (b.arr)[b.len - 1]))
					swap(&a);
				if (((a.arr)[a.len-2] < (a.arr)[a.len-1]))
					b_flag = (-1);
				push(&a, &b);
			}
		}
		print_stack();
	}
	print_stack();
	int i = 0;
	while (0)
	{
		get_spl();
		if (a.spl <= b.spl)
		{
			printf("b->a: ");
			merge_btoa(b.spl-1);
			if (b.spl == 1)
				break;
		}
		else
		{
			printf("a->b: ");
			merge_atob(a.spl-1);
		}
		print_stack();
		i++;
	}

	// get_spl();
	// printf("mergea\n");
	// merge_atob(2);
	// get_spl();
	// printf("mergeb\n");
	// merge_btoa(1);
	// get_spl();
	// printf("mergea\n");
	// merge_atob(1);
	// get_spl();
	// printf("mergeb\n");
	// merge_btoa(0);
	// printf("merge\n");
	// mergeatob(0);
	print_stack();
	printf("count: %d\n", count);
}



/*

for (int i = 0; i < 20; i++)
		scanf(" %d", (a.arr) + i);
7 9 10 2 3 5 6 1 4 8
8 9 10 2 3 5 6 1 4 7

17 3 6 9 20 11 12 14 4 18 19 10 7 16 8 1 13 2 15 5 

12 10 6 1 9 19 23 29 27 5 4 7 21 8 16 14 3 2 30 28 26 20 15 22 13 11 18 25 17 24 

19 35 34 29 40 16 6 32 39 18 26 41 27 49 21 14 47 4 2 31 13 50 36 12 46 30 17 44 25 28 33 10 48 15 43 22 37 38 24 23 20 8 7 45 9 11 5 42 3 1 
　
*/