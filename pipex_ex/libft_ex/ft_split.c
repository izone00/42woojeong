/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:44:42 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/13 14:12:39 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	i;
	int	len;
	int	n;

	i = 0;
	len = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			len++;
		else if (len > 0)
		{
			n++;
			len = 0;
		}
		i++;
	}
	if (len > 0)
		n++;
	return (n);
}

static void	free_arr(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
}

static int	full(char **arr, char *str, int *len, int n)
{
	int		i;
	char	*arr_n;

	arr[n] = (char *)malloc(sizeof(char) * (*len + 1));
	arr_n = arr[n];
	if (arr_n == 0)
	{
		free_arr(arr, n);
		return (0);
	}
	i = 0;
	while (i < *len)
	{
		arr_n[i] = str[i];
		i++;
	}
	arr_n[i] = '\0';
	*len = 0;
	return (1);
}

static int	str_spl(const char *s, char c, char **arr)
{
	int	i;
	int	len;
	int	n;

	i = 0;
	len = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			len++;
		else if (len > 0)
		{
			if (full(arr, (char *)s + i - len, &len, n) == 0)
				return (0);
			n++;
		}
		i++;
	}
	if (len > 0)
	{
		if (full(arr, (char *)s + i - len, &len, n) == 0)
			return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (arr == 0)
		return (0);
	if (str_spl(s, c, arr) == 0)
	{
		free(arr);
		return (0);
	}
	arr[count(s, c)] = 0;
	return (arr);
}
