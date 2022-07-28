/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:13:06 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 13:40:14 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int    check_flag(const char **p_str, int *opt)
{
    // printf("in check_flag : %c\n", **p_str);
    if (**p_str == '-')
        return (opt[minus] = 1);
    else if (**p_str == '+')
        return (opt[plus] = 1);
    else if (**p_str == '0')
        return (opt[zero] = 1);
    else if (**p_str == ' ')
        return (opt[space] = 1);
    else if (**p_str == '#')
        return (opt[shop] = 1);
    else
        return (0);
}

int    check_width(const char **p_str)
{
    return (change_num(p_str));
}

int     check_precision(const char **p_str)
{
    //'.'이 찍혀있으면 일단 1을 opt[precision]에 넣어서 정확도가 있음을 표시
    int exist_pre;

    exist_pre = 0;
    if (**p_str == '.')
    {
        (*p_str)++;
        exist_pre = change_num(p_str);
        if (exist_pre == 0)
            exist_pre = 1;
        return (exist_pre);
    }
    else
        return (0);
}

int     change_num(const char **p_str)
{
    int rst;

    rst = 0;
    while ('0' <= **p_str && '9' >= **p_str)
    {
        rst= rst * 10 + **p_str - '0';
        (*p_str)++;
    }
    return (rst);
}

int    check_type(const char **p_str)
{
    while (**p_str)
    {
        if (**p_str == 'c' || **p_str == 'd' || **p_str == 'i' || **p_str == 'u' \
         || **p_str == 'x' || **p_str == 'X' || **p_str == 'p' || **p_str == '%' \
         || **p_str == 's')
            break;
        (*p_str)++;
    }
    return (**p_str);
}

