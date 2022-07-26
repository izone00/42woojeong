/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:08:32 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/26 17:15:38 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void    print_char(char ch, int *opt)
{
    int space_len;

    if (1 < opt[width])
        space_len = opt[width] - 1;
    else
        space_len = 0;
    if (opt[minus])
    {
        write(1, &ch, 1);
        while (space_len--)
            write(1, " ", 1);
    }
    else
    {
        while (space_len--)
            write(1, " ", 1);
        write(1, &ch, 1);
    }
}

void    print_string(char *str, int *opt)
{
    int str_len;
    int space_len;

    str_len = ft_strlen(str);
    if (str_len < opt[width])
        space_len = opt[width] - str_len;
    else
        space_len = 0;
    if (opt[minus])
    {
        write(1, str, str_len);
        while (space_len--)
            write(1, " ", 1);
    }
    else
    {
        while (space_len--)
            write(1, " ", 1);
        write(1, str, str_len);
    }
}

int     ft_strlen(const char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
                i++;
        return (i);
}