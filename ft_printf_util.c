/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:05:48 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/26 17:20:54 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void    init_container(t_container *con)
{
    int idx;

    idx = 0;
    (con -> sign)[0] = 0;
    (con -> sign)[1] = 0;
    con -> zero_len = 0;
    con -> space_len = 0;
    while (idx < 30)
    {
        (con -> str)[idx] = 0;
        idx++;
    }
}

int get_zero(int num_len, int *opt, int *sign)
{
    if (opt[precision] > 0) //정확도에 대한 정보가 있을때
    {
        if (opt[precision] > num_len) //정확도가 숫자의 길이를 넘을때
            return (opt[precision] - num_len);
        else
            return (0);
    }
    else if (opt[zero]) //정확도에 대한 정보가 없고 '0'flag가 쓰일때 ('-'플래그의 유무를 고려해야됨!!!!!!!!!!!)
    {
        num_len += (sign[0] != 0);//부호의 첫칸
        num_len += (sign[1] != 0);//부호의 두번째칸 16진수에서 사용됨
        return (opt[width] - num_len);
    }
    else //정확도에 대한 정보가없고 '0'flag가쓰이지않을때
        return (0); 
}

int get_space(t_container conInt, int *opt, int num_len)
{
    int word_len;

    word_len = 0;
    word_len += num_len;
    word_len += (conInt.sign[0] != 0);
    word_len += (conInt.sign[1] != 0);
    word_len += conInt.zero_len;
    if (word_len < opt[width])
        return (opt[width] - word_len);
    else
        return (0);
}

void    right_align(t_container conInt, int len)
{
    int idx;
    while ((conInt.space_len)--)
        write(1, " ", 1);
    if (conInt.sign[0] != 0)
        write(1, &(conInt.sign[0]), 1);
    if (conInt.sign[1] != 0)
        write(1, &(conInt.sign[1]), 1);
    while ((conInt.zero_len)--)
        write(1, "0", 1);
    idx = len - 1; //인덱스를 끝에서 부터 시작해 반대로 출력한다.
    while (idx >= 0)
    {
        write(1, conInt.str + idx, 1); 
        idx --;
    }
}

void    left_align(t_container conInt, int len)
{
    int idx;

    if (conInt.sign[0] != 0)
        write(1, &(conInt.sign[0]), 1);
    if (conInt.sign[1] != 0)
        write(1, &(conInt.sign[1]), 1);
    while ((conInt.zero_len)--)
        write(1, "0", 1);
    idx = len - 1; //인덱스를 끝에서 부터 시작해 반대로 출력한다.
    while (idx >= 0)
    {
        write(1, conInt.str + idx, 1); 
        idx --;
    }
    while ((conInt.space_len)--)
        write(1, " ", 1);
}