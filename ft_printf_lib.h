/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:19:54 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/26 17:26:01 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdarg.h>
#include <unistd.h>

typedef struct s_container {
    int     sign[2];
    char    str[30];                
    int     zero_len;
    int     space_len;
} t_container;

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

int     ft_printf(const char *str, ...);
void    init_option(int *opt);
void    parse(const char **p_str, int *opt);
void    convert_print(int *opt, va_list *ap, int *len);
int     check_flag(const char **p_str, int *opt);
int     check_width(const char **p_str);
int     check_precision(const char **p_str);
int     check_type(const char **p_str);
int     change_num(const char **p_str);
void    init_container(t_container *con);
int     get_zero(int num_len, int *opt, int *sign);
int     get_space(t_container conInt, int *opt, int num_len);
void    left_align(t_container conInt, int len);
void    right_align(t_container conInt, int len);
void    print_int(int num, int *opt);
int     get_int_sign(int *opt, int num);
int     get_int_str(t_container *conInt, int num);
void    print_unsigned_int(unsigned long num, int *opt);
int     get_unsign_str(t_container *conUl, unsigned long num);
void    print_sixteen(unsigned int hexa, int *opt);
int     get_hexa_str(t_container *conUl, unsigned long hexa, int type);
void    get_hexa_sign(t_container *conUl, int shop);
void    print_char(char ch, int *opt);
void    print_string(char *str, int *opt);
int     ft_strlen(const char *str);