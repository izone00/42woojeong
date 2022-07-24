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

int     check_precision(const char **p_str)
{
    if (**p_str == '.')
    {
        (*p_str)++;
        return (change_num(p_str));
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

void    convert_print(int *opt, va_list *ap, int *len)
{
    // if (opt[type] == 'c' || opt[type] == 'd' || opt[type] == 'i' )
    //     print_int(va_arg(*ap, int), opt);
    // else if (opt[type] == 'u'|| opt[type] == 'x' || opt[type] == 'X' )
    //     print_unsigned_int(va_arg(*ap, unsigned int), opt);
    // else if (opt[type] == 'p')
    //     print_unsigend_long(va_arg(*ap, unsigned long), opt);
    // else if (opt[type] == '%')
    //     printf("%%");//보류
    // else if (opt[type] == 's')
    //     print_string(va_arg(*ap, char *), opt);
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

int main()
{
    ft_printf("num1 : %+-0 #13.7d\n", 5);
    printf("[%0.5x]", 16*16-10);
}