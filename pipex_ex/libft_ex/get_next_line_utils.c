/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:57:53 by woojeong          #+#    #+#             */
/*   Updated: 2022/08/04 17:27:00 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	cpy_until_nl(char *dest, char *src)
{
	int	len;

	len = 0;
	while (src[len])
	{
		dest[len] = src[len];
		if (dest[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	dest[len] = '\0';
	return (len);
}

void	update_save(char *dest, char *src)
{
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
}

void	fd_free(t_fd_list **p_save, int fd)
{
	t_fd_list	*pre;
	t_fd_list	*cur;

	cur = *p_save;
	if (cur -> fd == fd)
	{
		*p_save = (*p_save)-> next;
		free(cur);
	}
	else
	{
		while (cur -> next)
		{
			pre = cur;
			cur = cur -> next;
			if (cur -> fd == fd)
			{
				pre -> next = cur -> next;
				free(cur);
				return ;
			}
		}
	}
}

int	read_free(t_read lst)
{
	t_read	*pre;
	t_read	*cur;

	cur = lst.next;
	while (cur)
	{
		pre = cur;
		cur = cur -> next;
		free(pre);
	}
	return (0);
}
