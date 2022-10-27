#include "./push_swap.h"

t_stack a;
t_stack	b;
int b_flag = (-1);
int count = 0;

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(1);
	a.arr = parse_argv(argc, argv);
	if (!a.arr)
		exit(1);
	b.arr = (int *)malloc(sizeof(int) * (argc - 1));
	a.len = argc - 1;
	b.len = 0;
	a.spl = 1;
	b.spl = 1;

	printf("start: ");
	// print_stack();
	// merge_sort(argc);
	grid_sort();
	// printf("\n");
	// print_stack();
	printf("count: %d\n", count);
}

/*

for (int i = 0; i < 20; i++)
		scanf(" %d", (a.arr) + i);
2 3 4 1 5

7 9 10 2 3 5 6 1 4 8
8 9 10 2 3 5 6 1 4 7

17 3 6 9 20 11 12 14 4 18 19 10 7 16 8 1 13 2 15 5 

12 10 6 1 9 19 23 29 27 5 4 7 21 8 16 14 3 2 30 28 26 20 15 22 13 11 18 25 17 24 

19 35 34 29 40 16 6 32 39 18 26 41 27 49 21 14 47 4 2 31 13 50 36 12 46 30 17 44 25 28 33 10 48 15 43 22 37 38 24 23 20 8 7 45 9 11 5 42 3 1 
　
*/