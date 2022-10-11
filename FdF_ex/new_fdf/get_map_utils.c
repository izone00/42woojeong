/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:32:08 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 16:01:16 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	open_map(char *map)
{
	char	*map_path;
	int		fd;

	map_path = ft_strjoin("./", map);
	if (!map_path)
		return (0);
	fd = open(map_path, O_RDONLY);
	free(map_path);
	if (fd < 0)
		return (0);
	return (fd);
}

int	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

void	del_free(void *ptr)
{
	free((char *)ptr);
}

void	init_img(t_img *img)
{
	img -> x_size = 0;
	img -> y_size = 0;
	img -> max_alt = 0;
	(img -> move)[0] = 0;
	(img -> move)[1] = 0;
	img -> map_err = 0;
}

int	check_len(char **spl, int *len, t_img *img)
{
	*len = 0;
	while (spl[*len] && spl[*len][0] != '\n')
		(*len)++;
	if (img -> x_size == 0)
		img -> x_size = *len;
	else if (img -> x_size != *len)
	{
		img -> map_err = 1;
		return (free_split(spl));
	}
	return (1);
}
