/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:45:39 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/11 11:55:20 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char const *set, char ch)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

static void	full_trim(char *str, int start, int end, char const *s1)
{
	int	i;

	i = 0;
	while (start + i <= end)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
}

static int	get_end(char const *s1, char const *set)
{
	int	end;

	end = 0;
	while (s1[end] != '\0')
		end++;
	end--;
	while (check_set(set, s1[end]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*str;

	start = 0;
	while (check_set(set, s1[start]))
		start++;
	if (s1[start] == '\0')
	{
		str = (char *)malloc(sizeof(char));
		if (str == 0)
			return (0);
		str[0] = '\0';
	}
	else
	{
		end = get_end(s1, set);
		str = (char *)malloc(sizeof(char) * (end - start + 2));
		if (str == 0)
			return (0);
		full_trim(str, start, end, s1);
	}
	return (str);
}
