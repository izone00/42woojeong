/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:15:14 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/26 17:15:52 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int get_int_str(t_container *conInt, int num)
{
    int f_sign;
    int idx;

    f_sign = 1;
    if (num < 0)
        f_sign = -1;
    idx = 0;
    if (num == 0)
        (conInt -> str)[idx++] = '0';
    while (num)
    {
        (conInt -> str)[idx] = (num % 10) * f_sign + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        num /= 10;
        idx++;
    }
    (conInt -> str)[idx] = '\0';
    return (idx);
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

void    print_int(int num, int *opt)
{
    t_container conInt;
    int num_len;

    init_container(&conInt);
    num_len = get_int_str(&conInt, num);
    conInt.sign[0] = get_int_sign(opt, num);
    conInt.zero_len = get_zero(num_len, opt, conInt.sign);
    conInt.space_len = get_space(conInt, opt, num_len);
    if (opt[minus])
        left_align(conInt, num_len);
    else
        right_align(conInt, num_len);
}