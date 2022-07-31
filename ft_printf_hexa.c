/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:15:23 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/31 17:48:39 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int print_hexa(unsigned long long hexa, int *opt)
{
	t_container hex_con;
	int num_len;

	init_container(&hex_con);
	num_len = get_hexa_str(&hex_con, hexa, opt[type]);
	get_hexa_sign(&hex_con, opt[shop]);
	hex_con.zero_len = get_zero(num_len, opt, hex_con.sign);
	hex_con.space_len = get_space_for_num(hex_con, opt, num_len);
	if (opt[minus])
		return (left_align(hex_con, num_len));
	else
		return (right_align(hex_con, num_len));
}

int get_hexa_str(t_container *hex_con, unsigned long long hexa, int type)
{
	int idx;

	idx = 0;
	if (hexa == 0)
		(hex_con -> str)[idx++] = '0';
	while (hexa)
	{
		if (hexa % 16 <= 9)
			(hex_con -> str)[idx] = (hexa % 16) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
		else if (type == 'X')
			(hex_con -> str)[idx] = (hexa % 16) + 55;//소문자로 표시
		else
			(hex_con -> str)[idx] = (hexa % 16) + 87;//대문자로 표시
		hexa /= 16;
		idx++;
	}
	(hex_con -> str)[idx] = '\0';
	return (idx);
}

void    get_hexa_sign(t_container *hex_con, int shop)
{
	if (shop == 1)
	{
		(hex_con -> sign)[0] = '0';
		(hex_con -> sign)[1] = 'x';
	}
}

// void    print_adress(unsigned long addr, int *opt)
// {
//     t_container hex_con;
//     int num_len;

//     init_container(&hex_con);
//     num_len = get_hexa_str(&hex_con, addr, opt[type]);
//     get_hexa_sign(&hex_con, 1);//opt[shop] = 1 대입
//     hex_con.zero_len = get_zero(num_len, opt, hex_con.sign);
//     hex_con.space_len = get_space_for_num(hex_con, opt, num_len);
//     if (opt[minus])
//         left_align(hex_con, num_len);
//     else
//         right_align(hex_con, num_len);
// }