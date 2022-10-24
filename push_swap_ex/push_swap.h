#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "./libft.h"
	//temp
	#include <stdio.h>
	//temp

typedef struct s_stack {
	int len;
	int arr[500];
} t_stack;

void swap(t_stack *stack);
void push(t_stack *src, t_stack *dest);
void rotate_reverse(t_stack *stack);
void rotate(t_stack *stack);
void print_stack();
void print_count();
#endif
