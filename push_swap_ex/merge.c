#include "push_swap.h"

void	merge_atob(int idx)
{
	int ai = a.larr[a.spl-1];
	int bi = b.larr[b.spl-1];

	while (ai + bi > 0)
	{
		if (ai > 0 && (bi == 0 || a.arr[a.len-1] > b.arr[b.len-1]))
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
		if (bi > 0 && (ai == 0 || a.arr[a.len-1] < b.arr[b.len-1]))
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