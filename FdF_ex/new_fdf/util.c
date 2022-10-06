#include "./fdf.h"

t_point	**free_point_arr(t_point **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}