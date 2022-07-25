#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>/////////////////////////////////

//va_start(ap, str)
//va_grg(ap, 자료형)
//va_end(ap)

enum    option {
    flag = 0,
    width = 5,
    precision = 6,
    type = 7
};
enum    flag {
    minus = 0,
    plus = 1,
    zero = 2,
    space = 3,
    shop = 4
};

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
int    check_width(const char **p_str)
{
    return (change_num(p_str));
}

int     check_precision(const char **p_str, int *opt)
{
    //'.'이 찍혀있으면 일단 1을 opt[pre]에 넣어서 pre가 있음을 표시
    int exist_pre;

    exist_pre = 0;
    if (**p_str == '.')
    {
        exist_pre = change_num(p_str);
        if (exist_pre == 0)
            exist_pre = 1;
        (*p_str)++;
        return (exist_pre);
    }
    else
        return (0);
}

int    check_type(const char **p_str)
{
    while (**p_str)
    {
        if (**p_str == 'c' || **p_str == 'd' || **p_str == 'i' || **p_str == 'x' || **p_str == 'X' )
            break;
        else if (**p_str == 'd')
            break;
        else if (**p_str == 'p')
            break;
        else if (**p_str == '%')
            break;
        else if (**p_str == 's')
            break;
        (*p_str)++;
    }
    return (**p_str);
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

void    put_space(int len, int is_zero)
{
    char    space;

    if (is_zero)
        space = '0';
    else
        space = ' ';
    while (len-- > 0)
        write(1, &space, 1);
}

int len_int(int num)
{
    int len;

    len = 1;
    while (num / 10)
    {
        len++;
        num /= 10;
    }
    return (len);
}

void    put_int(int num, int *opt, int num_len, int word_len)
{
    int digit;

    if (num < 0)
        write(1, "-", 1);
    else if (opt[space] == 1)
        write(1, " ", 1);
    else if (opt[plus] == 1)
        write(1, "+", 1);
    else
        word_len++;
    put_space(word_len - num_len - 1, 1);
    ft_putnbr(num);        
}

void    print_int(int num, int *opt)
{
    int word_len;
    int num_len;
    
    num_len = len_int(num); //순수 숫자의 길이
    word_len = num_len; 
    if (num_len < opt[presicion])
        word_len = opt[presicion]; //정확도 추가
    if (num < 0 || opt[plus] == 1 || opt[space] == 1)
        word_len++;  //부호 추가
    if (opt[presicion] == 0 && opt[zero] == 1 && opt[width] > word_len) //정확도가 없는데 flag'0'가 사용되면
    {
        num_len += opt[width] - word_len;
        word_len = opt[width];
    }
    if (!opt[minus])
    {
        put_space(opt[width] - word_len, opt[zero] * (!opt[presicion]));
        put_int(num, opt, num_len, word_len);
    }
    else
    {
        put_int(num, opt, num_len, word_len);
        put_space(width - word_len, 0);
    }
}

void    convert_print(int *opt, va_list *ap, int *len)
{
    
    if (opt[type] == 'd' || opt[type] == 'i' )
        print_int(va_arg(*ap, int), opt);
    // else if (opt[type] == 'c')
    //     print_char(va_arg(*ap, int), opt);
    // else if (opt[type] == 'u')
    //     print_unsigned_int(va_arg(*ap, unsigned int), opt);
    // else if (opt[type] == 'x' || opt[type] == 'X' )
    //     print_sixteen(va_arg(*ap, unsigned int), opt);
    // else if (opt[type] == 'p')
    //     print_adress(va_arg(*ap, unsigned long), opt);
    // else if (opt[type] == 's')
    //     print_string(va_arg(*ap, char *), opt);
    // else if (opt[type] == '%')
    //     write(1, "%%", 1);
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
            //printf("is %%\n");
            init_option(opt);
            if (*str)
                str++;//str좌료 '%'에서 옮기기
            parse(&str, opt);
            // for (int i = 0; i < 6; i++)
            //     printf("(%d)%d ", i , opt[i]);
            // printf("(%d)%c ", 7 , opt[7]);
            // printf("\n");
            convert_print(opt, &ap, &len);
        }
        else
        {
            write(1, str, 1);
            len++;
        }
        if (*str)
            str++;
    }
    va_end(ap);
    return (len);
}



/*  flag_oder
10진수(%d, %i)
        무시됨(에러)        같이 적용됨       무시하고 적용    
' ' :     '+'(사용불가)     '-','0'          
'0' :     '-'(사용불가)     ' ','+'
'+' :     ' '(사용불가)     '-','0'
'-' :     '0'(사용불가)     ' ','+'

unsigned 10진수(%u)
            사용불가           사용가능(중복불가)
        ' ','+'(부호관련)       '-','0'

주소(%p)
        사용불가           사용가능(중복불가)
      ' ','+','0','#'            '-'

캐릭터(%c)
        사용불가           사용가능(중복불가)
      ' ','+','0'            '-'

문자열(%s)
        사용불가           사용가능(중복불가)
      ' ','+','0'            '-'

16진수(%x, %X)
            사용불가        사용가능(중복불가)
'#'쓸때 :    '+',' '        '-','0'                     
'#'안쓸때 :   '+',' '        '-','0'

문자'%' (%%)
    '%' 쓸데는 에러없이 플래그 전부 무시되고 '%'출력
*/


int main()
{
    //ft_printf("num1 : %+-0 #13.7d\n", 5);
    int num = 1;
    printf("[%-010x]", 16*16-10);
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

//출력시 공백 부호 숫자 세가지로