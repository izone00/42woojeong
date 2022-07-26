/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:11:47 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/26 17:20:35 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <stdio.h>/////////////////////////////////

int ft_printf(const char *str, ...)
{
    va_list    ap;
    int     len;
    int     type;
    int     opt[10];

    va_start(ap, str);
    len = 0;
    while(*str)
    {
        if (*str == '%')
        {
            init_option(opt); //opt초기화
            str++; //str좌표 '%'에서 다음으로옮기기
            parse(&str, opt); //str읽어서 opt채우고 str이 마지막 type문자를 가르친다.
            // for (int i = 0; i < 6; i++)
            //     printf("(%d)%d ", i , opt[i]);
            // printf("(%d)%c ", 7 , opt[7]);
            // printf("\n");
            convert_print(opt, &ap, &len); //변환해서 출력
        }
        else
        {
            write(1, str, 1); //그냥 문자 출력
            len++;
        }
        if (*str) 
            str++;
    }
    va_end(ap);
    return (len);
}

void init_option(int *opt)
{
    int i = 0;
    
    while (i < 10)
    {
        opt[i] = 0;
        i++;
    }
}

void    parse(const char **p_str, int *opt)
{
    while (check_flag(p_str, opt))
        (*p_str)++;
    // printf("after flag : %c\n", **p_str);
    opt[width] = check_width(p_str);
    // printf("width : %d \n", opt[width]);
    // printf("after width : %c \n", **p_str);
    opt[precision] = check_precision(p_str);
    // printf("precision : %d\n", opt[precision]);
    // printf("after precision : %c\n", **p_str);
    opt[type] = check_type(p_str);
//     printf("type : %c", opt[type]);
}

void    convert_print(int *opt, va_list *ap, int *len)
{
    if (opt[type] == 'd' || opt[type] == 'i' )
        print_int(va_arg(*ap, int), opt);
    else if (opt[type] == 'u')
        print_unsigned_int((unsigned long)va_arg(*ap, unsigned int), opt);
    else if (opt[type] == 'x' || opt[type] == 'X' )
        print_sixteen((unsigned long)va_arg(*ap, unsigned int), opt);
    else if (opt[type] == 'p')
    {
        opt[shop] = 1;
        print_sixteen(va_arg(*ap, unsigned long), opt);
    }
    else if (opt[type] == 'c')
         print_char(va_arg(*ap, int), opt);
    else if (opt[type] == 's')
        print_string(va_arg(*ap, char *), opt);
    else if (opt[type] == '%')
        write(1, "%%", 1);
}







/*  flag_oder
10진수(%d, %i)
         무시됨(에러)      같이 적용됨       무시하고 적용    
' ' :    '+'(사용불가)     '-','0'          
'0' :    '-'(사용불가)     ' ','+'
'+' :    ' '(사용불가)     '-','0'
'-' :    '0'(사용불가)     ' ','+'
precision : 가능

unsigned 10진수(%u)
            사용불가           사용가능(중복불가)
        ' ','+'(부호관련)       '-','0'
precision : 가능

16진수(%x, %X)
            사용불가        사용가능(중복불가)
'#'쓸때 :    '+',' '        '-','0'                     
'#'안쓸때 :   '+',' '        '-','0'
precision : 가능

주소(%p)
        사용불가           사용가능(중복불가)
      ' ','+','0','#'            '-'
precision : 사용불가

캐릭터(%c)
        사용불가           사용가능(중복불가)
      ' ','+','0'            '-'
precision : 사용불가

문자열(%s)
        사용불가           사용가능(중복불가)
      ' ','+','0'            '-'
precision : 사용불가



문자'%' (%%)
    '%' 쓸데는 에러없이 플래그 전부 무시되고 '%'출력
*/


int main()
{
    //ft_printf("num1 : %+-0 #13.7d\n", 5);
    int num = 1;
    ft_printf("ft_printf : [%-20X %%]\n", 16*16-9);
       printf("  printf  : [%-20X %%]\n", 16*16-9);
}
/*width_precision

width : 부호와 공백 포함 전체 길이
precition : 부호와 공백을 제외하고 0과 숫자까지의 길이ㅣ

(wid == 0) && (pre > 0)
    부호제외 0과 숫자의 길이가 pre
(wid > 0) && (pre == 0)
    공백 부호 숫자 모두합이 wid
(wid == 0) && (pre == 0)
    공백없이 부호 숫자만 알맞게 출력
(wid > 0) && (pre > 0)
    우선적으로 pre만큼 숫자와 0을 찍고
    부호를 찍고
    wid가 남으면 공백을 찍는다

####precision이 적용될때 '0'flag는 무시되고 pre를 초과하는 공백은 무조건 ' '으로 표시
*/