#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "./libft.h"

typedef struct s_stack {
	int len;
	int	spl;
	int larr[500];
	int arr[500];
} t_stack;

void	merge_atob(int idx);
void	merge_btoa(int idx);

void swap(t_stack *stack);
void push(t_stack *src, t_stack *dest);
void rotate_reverse(t_stack *stack);
void rotate(t_stack *stack);
void print_stack();

void	get_spl();
void print_count();



	//temp
	t_stack a;
	t_stack	b;
	int count;
	int b_flag;
	#include <stdio.h>
	#define SIZE 7
	//temp
#endif
