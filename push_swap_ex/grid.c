#include "./push_swap.h"

int	abs(int num)
{
	if (num > 0)
		return (num);
	return (-num);
}
void	print(int *arr)
{
	printf("[ ");
	for (int i = 0; i < a.len; i++)
		printf("%d ", arr[i]);
	printf("]\n");
}

int	check_diff()
{
	int	idx;
	int sum;
	int	min_devi = -1;
	int min_sum;

	for (int i = 0; i < a.len; i++)
	{
		rotate(&a);
		count--;
		idx = 0;
		sum = 0;
		while (idx < a.len)
		{
			// printf(" dif = %d - %d(%d)\n", idx, sorted[(a.arr)[idx]], (a.arr)[idx]);
			diff[idx] = sorted[(a.arr)[idx]] - idx;
			if (diff[idx] < 0)
				diff[idx] += a.len;
			sum += diff[idx];
			idx++;
		}
		int devi_sum = 0;
		idx = 0;
		sum /= a.len;
		while (idx < a.len)
		{
			if (abs(diff[idx] - sum) < (a.len / 2))
				devi[idx] = diff[idx] - sum;
			else
				devi[idx] = a.len - abs(diff[idx] - sum);
			if (devi[idx] > 0)
				devi_sum += devi[idx];
			else
				devi_sum -= devi[idx];
			idx++;
		}
		if (min_devi > devi_sum || min_devi < 0)
		{
			min_devi = devi_sum;
			min_sum = sum;
		}
	}
	printf("average: %d\n", min_sum);
	print(diff);
	printf("deviation min: %d\n", min_devi);
	print(devi);
	print_stack();
	return (min_devi);
}

int rd;
int rrd;

void	DFSr(int cur_devi, int n)
{
	int	de;

	swap(&a);
	de = check_diff();
	if (cur_devi > de)
	{
		rd = n;
		swap(&a);
		return ;
	}
	swap(&a);
	count -= 2;
	rotate(&a);
	DFSr(cur_devi, n+1);
	rotate_reverse(&a);
}

void	DFSrr(int cur_devi, int n)
{
	int	de;

	swap(&a);
	de = check_diff();
	if (cur_devi > de)
	{
		rrd = n;
		swap(&a);
		return ;
	}
	swap(&a);
	count -= 2;
	rotate_reverse(&a);
	DFSrr(cur_devi, n+1);
	rotate(&a);
}
void	grid_sort()
{
	for (int i = 0; i < a.len; i++)
		sorted[i+1] = a.len - i - 1;
	// for (int i = 0; i < a.len+1; i++)
	// 	printf("%d ", sorted[i]);
	// printf("\n");
	
	int	cur_devi = check_diff();
	// rotate(&a);
	// check_diff();
	// rotate(&a);
	// check_diff();
	// swap(&a);
	// check_diff();
	// rotate_reverse(&a);
	// check_diff();
	DFSr(cur_devi, 1);
	DFSrr(cur_devi, 1);
	if (rd < rrd)
		printf("rotate\n");
	else
		printf("rotate_reverse\n");
}