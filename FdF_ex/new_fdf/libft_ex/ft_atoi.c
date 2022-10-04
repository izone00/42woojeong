/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:54:55 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:09:39 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	over_ll(const char *str_i, long long re, int sign)
{
	if (ft_isdigit(*str_i))
	{
		if (re > 922337203685477580 || \
				(re == 922337203685477580 && *str_i >= '8'))
			return (-1);
		else if (re < (-922337203685477580) || \
				(re == (-922337203685477580) && *str_i == '9'))
			return (0);
		else if (ft_isdigit(*(str_i + 1)))
		{
			if (re > 0)
				return (-1);
			else
				return (0);
		}
		else
			return (re * 10 + sign * (*str_i - '0'));
	}
	else
		return (re);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0') * sign;
		if (result >= 100000000000000000 || result <= (-100000000000000000))
			return (over_ll(str + i + 1, result, sign));
		i++;
	}
	return (result);
}
