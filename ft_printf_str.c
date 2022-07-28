/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:08:32 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/27 16:58:32 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

int print_char(char ch, int *opt)
{
    int space_len;
    int word_len;

    space_len = get_space_for_str(1, opt);
    word_len = space_len + 1;
    put_str(opt, &ch, 1, space_len);
    return (word_len);
}

int print_string(char *str, int *opt)
{
    int str_len;
    int space_len;
    int word_len;

    str_len = ft_strlen(str);
    space_len = get_space_for_str(str_len, opt);
    word_len = space_len + str_len;
    put_str(opt, str, str_len, space_len);
    return (word_len);
}

void    put_str(int *opt, char *str, int str_len, int space_len)
{
    if (opt[minus])
    {
        write(1, str, str_len);
        put_space(space_len);
    }
    else
    {
        put_space(space_len);
        write(1, str, str_len);
    }
}

int get_space_for_str(int str_len, int *opt)
{
    if (str_len < opt[width])
        return (opt[width] - str_len);
    else
        return (0);
}

int     ft_strlen(const char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
                i++;
        return (i);
}