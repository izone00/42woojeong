#include "push_swap.h"

void	merge_sort(int argc)
{
	for (int i = 0 ; i < (argc - 1) / 2; i++)
		push(&a, &b);
	print_stack();
	int i = 0;
	while (1)
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
}
void	merge_atob(int idx)
{
	int ai = a.larr[a.spl-1];
	int bi = b.larr[b.spl-1];

	while (ai + bi > 0)
	{
		if (ai > 0 && (bi == 0 || a.arr[a.len-1] < b.arr[b.len-1]))
		{
			push(&a, &b);
			ai--;
		}
		else
			bi--;
		rotate(&b);
	}
}
void	merge_btoa(int idx)
{
	int ai = a.larr[a.spl-1];
	int bi = b.larr[b.spl-1];

	while (ai + bi > 0)
	{
		if (bi > 0 && (ai == 0 || a.arr[a.len-1] > b.arr[b.len-1]))
		{
			push(&b, &a);
			bi--;
		}
		else
			ai--;
		rotate(&a);
	}
}
void	pre_merge_atob(int idx)
{
	int i = b.larr[0];
	int j = a.larr[a.spl-1];

	while (i + j > 0)
	{
		// printf("(%d)",i);
		if (j > 0 && (a.arr[a.len-1] > b.arr[0] || i == 0))
		{
			push(&a, &b);
			j--;
		}
		else
		{
			rotate_reverse(&b);
			i--;
		}
	}
	while (b.arr[b.len-1] > b.arr[0])
		rotate_reverse(&b);
}

void	pre_merge_btoa(int idx)
{
	int i = a.larr[0];
	int j = b.larr[b.spl-1];
	
	while (i + j > 0)
	{
		// printf("(%d)",i);
		if (j > 0 && (b.arr[b.len-1] < a.arr[0] || i == 0))
		{
			push(&b, &a);
			j--;
		}
		else
		{
			rotate_reverse(&a);
			i--;
		}
		
	}
	// while (a.arr[a.len-1] < a.arr[0])
	// 	rotate_reverse(&a);
}

// if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
// 	swap(&a);
// rotate(&a);
// print_stack();
// for (int i = 1; i < (argc - 1 - 1); i++)
// {
// 	if (b_flag == (-1))
// 	{
// 		if (((a.arr)[a.len-2] > (a.arr)[a.len-1]) && ((a.arr)[a.len-2] < (a.arr)[0]))
// 			swap(&a);
// 		if (((a.arr)[a.len-2] > (a.arr)[a.len-1]))
// 			b_flag = 1;
// 		rotate(&a);
// 	}
// 	else
// 	{
// 		if (b_flag == 1)
// 		{
// 			if (((a.arr)[a.len-2] < (a.arr)[a.len-1]))
// 				swap(&a);
// 			push(&a, &b);
// 			b_flag++;
// 		}
// 		else 
// 		{
// 			if (((a.arr)[a.len-2] < (a.arr)[a.len-1]) && ((a.arr)[a.len-2] > (b.arr)[b.len - 1]))
// 				swap(&a);
// 			if (((a.arr)[a.len-2] < (a.arr)[a.len-1]))
// 				b_flag = (-1);
// 			push(&a, &b);
// 		}
// 	}
// 	// print_stack();
// }
