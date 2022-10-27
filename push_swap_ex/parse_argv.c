#include "./push_swap.h"

static int	*av_err(int *stack)
{
	free(stack);
	write(2, "Error\n", 6);
	return (NULL); // Error msg
}
static int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
static int	check_dup(int *stack, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < i)
		{
			if (stack[j] == stack[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	*parse_argv(int argc, char *argv[])
{
	int	i;
	int *stack;

	stack = (int *)malloc(sizeof(int) * (argc - 1)); // malloc
	if (!stack)
	{
		write(2, "malloc err\n", 11);
		return (NULL); // malloc err
	}
	i = 1;
	while (i < argc)
	{
		if (!is_digit_str(argv[i]))
			return (av_err(stack));
		stack[argc - 1 - i] = ft_atoi(argv[i]);
		i++;
	}
	if (!check_dup(stack, argc - 1))
		return (av_err(stack));
	return (stack);
}

