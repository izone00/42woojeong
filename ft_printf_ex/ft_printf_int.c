/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:15:14 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/31 17:56:52 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int    print_int(int num, int *opt)
{
	t_container int_con;
	int num_len;

	init_container(&int_con);
	num_len = get_int_str(&int_con, num);
	int_con.sign[0] = get_int_sign(opt, num);
	int_con.zero_len = get_zero(num_len, opt, int_con.sign);
	int_con.space_len = get_space_for_num(int_con, opt, num_len);
	if (opt[minus])
		return (left_align(int_con, num_len));
	else
		return (right_align(int_con, num_len));
}

int get_int_str(t_container *int_con, int num)
{
	int int_sign;
	int idx;

	int_sign = 1;
	if (num < 0)
		int_sign = -1;
	idx = 0;
	if (num == 0)
		(int_con -> str)[idx++] = '0';
	while (num)
	{
		(int_con -> str)[idx] = (num % 10) * int_sign + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
		num /= 10;
		idx++;
	}
	(int_con -> str)[idx] = '\0';
	return (idx); //길이 반환
}

int get_int_sign(int *opt, int num)
{
	if (num < 0)
		return ('-');
	else if (opt[plus])
		return ('+');
	else if (opt[space])
		return (' ');
	else
		return (0); 
}

