/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:07:09 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/31 17:56:45 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int print_unsigned_int(unsigned int num, int *opt)
{
	t_container ul_con;
	int num_len;

	init_container(&ul_con);
	num_len = get_unsigned_str(&ul_con, num);
	ul_con.zero_len = get_zero(num_len, opt, ul_con.sign);
	ul_con.space_len = get_space_for_num(ul_con, opt, num_len);
	if (opt[minus])
		return (left_align(ul_con, num_len));
	else
		return (right_align(ul_con, num_len));
}

int get_unsigned_str(t_container *ul_con, unsigned int num)
{
	int idx;
;
	idx = 0;
	if (num == 0)
		(ul_con -> str)[idx++] = '0';
	while (num)
	{
		(ul_con -> str)[idx] = (num % 10) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
		num /= 10;
		idx++;
	}
	(ul_con -> str)[idx] = '\0';
	return (idx);
}