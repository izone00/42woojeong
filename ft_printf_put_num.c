/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:32:34 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 13:33:51 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

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