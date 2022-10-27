/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:36:26 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/11 11:52:35 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(int n)
{
	int		dig;
	long	num;

	dig = 1;
	num = (long)n;
	if (n < 0)
	{
		dig++;
		num = (long)n * (-1);
	}
	while (num >= 10)
	{
		num /= 10;
		dig++;
	}
	return (dig);
}

static void	full2(char *str, int n, int digit)
{
	int	i;
	int	sign;

	i = digit;
	sign = 1;
	if (n < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	else if (n == 0)
	{
		str[0] = '0';
		return ;
	}
	while (n != 0)
	{
		str[digit] = (n % 10) * sign + '0';
		digit--;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;

	str = malloc(sizeof(char) * (get_digit(n) + 1));
	if (str == 0)
		return (0);
	full2(str, n, get_digit(n) - 1);
	str[get_digit(n)] = '\0';
	return (str);
}
