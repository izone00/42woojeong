/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:44:32 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/11 11:53:29 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	get_digit2(int n)
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

static void	full3(char *str, int n, int digit)
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

static char	*f_itoa(int n, char *nbr)
{
	if (nbr == 0)
		return (0);
	full3(nbr, n, get_digit2(n) - 1);
	nbr[get_digit2(n)] = '\0';
	return (nbr);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	*str;
	char	nbr[20];
	int		i;

	str = f_itoa(n, nbr);
	i = 0;
	while (str[i] != '\0')
		i++;
	write(fd, str, i);
}
