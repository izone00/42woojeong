#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include "./libft_ex/libft.h"

typedef struct s_stack {
	int len;
	int	spl;
	int larr[500];
	int *arr;
} t_stack;

void	merge_sort(int argc);
void	merge_atob(int idx);
void	merge_btoa(int idx);

void	pre_merge_sort(int argc);
void	pre_merge_btoa();
void	pre_merge_atob();

void swap(t_stack *stack);
void push(t_stack *src, t_stack *dest);
void rotate_reverse(t_stack *stack);
void rotate(t_stack *stack);
void print_stack();

int	get_last_spl_re_a();
int	get_last_spl_re_b();
void	get_spl();
void print_count();


void	grid_sort();

int	*parse_argv(int argc, char *argv[]);

	//temp
	t_stack a;
	t_stack	b;
	int count;
	int b_flag;
	int diff[1000];
	int sorted[1000];
	int devi[1000];
	#include <stdio.h>
	#define SIZE 7
	//temp
#endif
