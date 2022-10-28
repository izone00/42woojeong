#include "push_swap.h"

void	pre_merge_init(int argc)
{

}
void pre_merge_binary(t_stack *s1, t_stack * s2)
{
	int j = s1->spl;

	print_stack();
	while (s1->spl > ((j / 2) + (j % 2)))
	{
		push(s1, s2);
		get_spl();
	}
}
void	move_atob()
{
	int j = a.larr[a.spl-1];

	while (j > 0)
	{
		push(&a, &b);
		j--;
	}
}
void	move_btoa()
{
	int j = b.larr[b.spl-1];

	while (j > 0)
	{
		push(&b, &a);
		j--;
	}
}
void	pre_merge_sort(int argc)
{
	// pre_merge_init(argc);
	int n = 0;
	while (n < 1)
	{
		get_spl();
		
		move_atob();
		get_spl();
		print_stack();
		
		pre_merge_atob();
		get_spl();
		print_stack();
		
		move_atob();
		get_spl();
		print_stack();

		pre_merge_btoa();
		get_spl();
		print_stack();
		
		pre_merge_atob();
		get_spl();
		print_stack();
		
		while (a.spl > 2)
		{
			for (int i = 0; a.spl > b.spl; i++)
			{
				move_atob();
				get_spl();
			}
			print_stack();

			while (b.spl > 1)
			{
				pre_merge_btoa();
				get_spl();
			}
			print_stack();
			if (a.spl == 2)
				break;
			move_atob();
			get_spl();
			pre_merge_btoa();
			get_spl();
			pre_merge_atob();
			get_spl();
			print_stack();
		}

		move_atob();
		get_spl();
		pre_merge_btoa();
		get_spl();
		pre_merge_btoa();
		get_spl();
		n++;
	}
	while (0)
	{
		get_spl();
		if (b.len == 0)
			pre_merge_binary(&a, &b);
		else
			pre_merge_binary(&b, &a);
		// int sum_a = 0;
		// int sum_b = 0;
		// for (int i = 0; i < a.spl/2 || i < b.spl/2; i++)
		// {
		// 	sum_a += a.larr[a.spl-i] + b.larr[i];
		// 	sum_b += b.larr[b.spl-i] + a.larr[i];
		// }
		if ( 1 || (b.spl == 1 && a.spl == 1))
		{
			get_spl();
			print_stack();
			while (b.len > 0)
			{
				get_spl();
				printf("b->a: ");
				pre_merge_btoa(b.spl - 1);
			}
			if (a.spl == 1)
				break;
			print_stack();
		}
		else
		{
			get_spl();
			print_stack();
			while (a.len > 0)
			{
				get_spl();
				printf("a->b: ");
				pre_merge_atob(a.spl - 1);
			}
			if (b.spl == 1)
				break;
			print_stack();
		}
		n++;
	}
}

void	pre_merge_atob()
{
	int i = b.larr[0];
	int j = a.larr[a.spl-1];

	while (i + j > 0)
	{
		// printf("(%d)",i);
		if (j > 0 && (a.arr[a.len-1] < b.arr[0] || i == 0))
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
	// while (b.arr[b.len-1] > b.arr[0])
	// 	rotate_reverse(&b);
}

void	pre_merge_btoa()
{
	int i = a.larr[0];
	int j = b.larr[b.spl-1];
	
	while (i + j > 0)
	{
		// printf("(%d)",i);
		if (j > 0 && (b.arr[b.len-1] > a.arr[0] || i == 0))
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

	// do
	// {
	// 	// if (a.arr[a.len - 1] < a.arr[a.len - 2])
	// 	// {
	// 	// 	if (a.arr[a.len - 2] < a.arr[a.len - 3] || a.arr[a.len - 1] > a.arr[a.len - 3])
	// 	// 		swap(&a);
	// 	// }
	// 	while (1)
	// 	{
	// 		if ((b.len == 0 || a.arr[a.len - 1] > b.arr[b.len - 1]) && a.arr[a.len - 1] < a.arr[0])
	// 		{
	// 			rotate_reverse(&a);
	// 			continue;
	// 		}
	// 		if ((b.len > 0 && a.arr[a.len - 1] > b.arr[b.len - 1]) && a.arr[0] < b.arr[b.len - 1])
	// 		{
	// 			rotate_reverse(&a);
	// 			push(&a, &b);
	// 			continue;
	// 		}
	// 		break;
	// 	}
	// 	push(&a, &b);
	// 	get_spl();
	// } while (a.spl > b.spl);