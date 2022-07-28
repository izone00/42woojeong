/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:07:09 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 16:38:54 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int print_unsigned_int(unsigned long num, int *opt)
{
    t_container conUl;
    int num_len;

    init_container(&conUl);
    num_len = get_unsigned_str(&conUl, num);
    conUl.zero_len = get_zero(num_len, opt, conUl.sign);
    conUl.space_len = get_space_for_num(conUl, opt, num_len);
    if (opt[minus])
        return (left_align(conUl, num_len));
    else
        return (right_align(conUl, num_len));
}

int get_unsigned_str(t_container *conUl, unsigned long num)
{
    int idx;
;
    idx = 0;
    if (num == 0)
        (conUl -> str)[idx++] = '0';
    while (num)
    {
        (conUl -> str)[idx] = (num % 10) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        num /= 10;
        idx++;
    }
    (conUl -> str)[idx] = '\0';
    return (idx);
}