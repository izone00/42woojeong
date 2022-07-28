/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:15:23 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 16:38:54 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int get_hexa_str(t_container *conUl, unsigned long hexa, int type)
{
    int idx;
;
    idx = 0;
    if (hexa == 0)
        (conUl -> str)[idx++] = '0';
    while (hexa)
    {
        if (hexa % 16 <= 9)
            (conUl -> str)[idx] = (hexa % 16) + '0';//거꾸로 넣는다. 출력할때 거꾸로 해야됨
        else if (type == 'X')
            (conUl -> str)[idx] = (hexa % 16) + 55;//소문자로 표시
        else
            (conUl -> str)[idx] = (hexa % 16) + 87;//대문자로 표시
        hexa /= 16;
        idx++;
    }
    (conUl -> str)[idx] = '\0';
    return (idx);
}

void    get_hexa_sign(t_container *conUl, int shop)
{
    if (shop == 1)
    {
        (conUl -> sign)[0] = '0';
        (conUl -> sign)[1] = 'x';
    }
}

int print_hexa(unsigned long hexa, int *opt)
{
    t_container conUl;
    int num_len;

    init_container(&conUl);
    num_len = get_hexa_str(&conUl, hexa, opt[type]);
    get_hexa_sign(&conUl, opt[shop]);
    conUl.zero_len = get_zero(num_len, opt, conUl.sign);
    conUl.space_len = get_space_for_num(conUl, opt, num_len);
    if (opt[minus])
        return (left_align(conUl, num_len));
    else
        return (right_align(conUl, num_len));
}


// void    print_adress(unsigned long addr, int *opt)
// {
//     t_container conUl;
//     int num_len;

//     init_container(&conUl);
//     num_len = get_hexa_str(&conUl, addr, opt[type]);
//     get_hexa_sign(&conUl, 1);//opt[shop] = 1 대입
//     conUl.zero_len = get_zero(num_len, opt, conUl.sign);
//     conUl.space_len = get_space_for_num(conUl, opt, num_len);
//     if (opt[minus])
//         left_align(conUl, num_len);
//     else
//         right_align(conUl, num_len);
// }