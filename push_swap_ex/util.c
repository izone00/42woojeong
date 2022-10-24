#include	 "push_swap.h"

int count = 0;

void swap(t_stack *stack)
{
	int	temp;

	if (stack -> len <= 1)
		return ;
	else
	{
		temp = (stack -> arr)[(stack -> len) - 1];
		(stack -> arr)[(stack -> len) - 1] = (stack -> arr)[(stack -> len) - 2];
		(stack -> arr)[(stack -> len) - 2] = temp;
	}
	print_stack();
	count++;
}

void push(t_stack *src, t_stack *dest)
{
	if (src -> len == 0)
		return ;
	else
	{
		(dest -> arr)[dest -> len] = (src -> arr)[(src -> len) - 1];
		(dest -> len)++;
		(src -> len)--;
	}
	print_stack();
	count++;
}

void rotate_reverse(t_stack *stack)
{
	int	temp;
	int	i;

	temp = (stack -> arr)[0];
	i = 0;
	while (i < (stack -> len) - 1)
	{
		(stack -> arr)[i] = (stack -> arr)[i + 1];
		i++;
	}
	(stack -> arr)[(stack -> len) - 1] = temp;
	print_stack();
	count++;
}

void rotate(t_stack *stack)
{
	int temp;
	int i;

	temp = (stack -> arr)[(stack -> len) - 1];
	i = (stack -> len) - 1;
	while (i >= 1 )
	{
		(stack -> arr)[i] = (stack -> arr)[i - 1];
		i--;
	}
	(stack -> arr)[0] = temp;
	print_stack();
	count++;
}

void print_count()
{
	printf("\ncount: %d\n", count);
}


