/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:57:53 by woojeong          #+#    #+#             */
/*   Updated: 2022/08/02 10:57:54 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "new_gnl.h"

int	cpy_until_nl(char *dest, char *src)
{
	int	len;

	len = 0;
	while (src[len])
	{
		dest[len] = src[len];
		if (dest[len] =='\n')
		{
			len++;
			break;
		}
		len++;
	}
	dest[len] = '\0';
	return (len);
}

void	update_fd(char *dest, char *src)
{
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
}

void	fd_free(t_fd_list **p_fd_lst, int fd)
{
	t_fd_list *pre;
	t_fd_list *cur;

	cur = *p_fd_lst;
	if (cur -> fd == fd)// 첫 fd를 검사
	{
		*p_fd_lst = (*p_fd_lst) -> next;
		free(cur);
	}
	else
	{
		while (cur -> next)// 나머지 fd를 검사 (사실상 fd가 무조건 존재하므로 1로 적어도 무방)
		{
			pre = cur;
			cur = cur -> next;
			if (cur -> fd == fd)
			{
				pre -> next = cur -> next;
				free(cur);
				return;
			}
		}
	}
}
// read_free에 malloc을 하지않아 free할게없을때도 함수를 부르지만 작동하지 않게되있다.
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
