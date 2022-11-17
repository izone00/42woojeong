/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:19:54 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/31 19:20:45 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct s_container {
	int		sign[2];
	char	str[30];
	int		zero_len;
	int		space_len;
}	t_container;

enum e_option {
	minus = 0,
	plus = 1,
	zero = 2,
	space = 3,
	shop = 4,
	width = 5,
	precision = 6,
	type = 7
};

int		ft_printf(const char *str, ...);
void	init_option(int *opt);
void	get_option(const char **p_str, int *opt);
int		convert_print(int *opt, va_list *ap);
int		check_flag(const char **p_str, int *opt);
int		check_width(const char **p_str);
int		check_precision(const char **p_str);
int		check_type(const char **p_str);
int		change_num(const char **p_str);
void	init_container(t_container *con);
int		get_zero(int num_len, int *opt, int *sign);
int		get_space_for_num(t_container conInt, int *opt, int num_len);
int		left_align(t_container conInt, int len);
int		right_align(t_container conInt, int len);
int		print_int(int num, int *opt);
int		get_int_sign(int *opt, int num);
int		get_int_str(t_container *conInt, int num);
int		print_unsigned_int(unsigned int num, int *opt);
int		get_unsigned_str(t_container *conUl, unsigned int num);
int		print_hexa(unsigned long long hexa, int *opt);
int		get_hexa_str(t_container *conUl, unsigned long long hexa, int type);
void	get_hexa_sign(t_container *conUl, int shop);
int		print_char(char ch, int *opt);
int		print_string(char *str, int *opt);
int		ft_strlen(const char *str);
int		get_space_for_str(int str_len, int *opt);
void	put_str(int *opt, char *str, int str_len, int space_len);
int		sum_len(t_container con, int num_len);
void	put_space(int len);
void	put_sign(int *sign);
void	put_zero(int len);
void	put_str_rev(char *str, int len);
#endif