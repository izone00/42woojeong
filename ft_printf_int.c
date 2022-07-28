/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:15:14 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 16:54:24 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int    print_int(int num, int *opt)
{
    t_container conInt;
    int num_len;

    init_container(&conInt);
    num_len = get_int_str(&conInt, num);
    conInt.sign[0] = get_int_sign(opt, num);
    conInt.zero_len = get_zero(num_len, opt, conInt.sign);
    conInt.space_len = get_space_for_num(conInt, opt, num_len);
    if (opt[minus])
        return (left_align(conInt, num_len));
    else
        return (right_align(conInt, num_len));
}

int get_int_str(t_container *conInt, int num)
{
    int Int_sign;
    int idx;

    Int_sign = 1;
    if (num < 0)
        Int_sign = -1;
    idx = 0;
    if (num == 0)
        (conInt -> str)[idx++] = '0';
    while (num)
    {
        (conInt -> str)[idx] = (num % 10) * Int_sign + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        num /= 10;
        idx++;
    }
    (conInt -> str)[idx] = '\0';
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

