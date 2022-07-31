/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:32:34 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/31 17:56:26 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int sum_len(t_container con, int num_len)
{
	int total_len;

	total_len = 0;
	total_len += con.space_len;
	total_len += con.sign[0] + con.sign[1];
	total_len += con.zero_len;
	total_len += num_len;
	return (total_len);
}

void    put_space(int len)
{
	while (len--)
		write(1, " ", 1);
}

void    put_sign(int *sign)
{
	if (sign[0] != 0)
		write(1, &(sign[0]), 1);
	if (sign[1] != 0)
		write(1, &(sign[1]), 1);
}

void    put_zero(int len)
{
	while (len--)
		write(1, "0", 1);
}

void    put_str_rev(char *str, int len)
{
	int idx;

	idx = len - 1;
	while (idx >= 0)
	{
		write(1, str + idx, 1); 
		idx --;
	}
}