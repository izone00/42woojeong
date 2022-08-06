/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:53:04 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/29 16:55:08 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_get_next_line.h"
//input 
// p_remain_box -> remain_box : (NULL, !NULL)
// remain_str : 빈 문자열 (!NULL)
// fd : (new fd, old fd)
int	check_fd_remain_box(t_fd_list **p_remain_box, char *read,int fd)
{
	t_fd_list   *box;
	int         read_len;

	if (*p_remain_box == NULL) // p_remain_box == NULL -> fd is new
	{
		if (new_fd_box(fd, p_remain_box) == (-1)) // new fd (생성을 위해 주소 전달)
			return (-1);
		box = *p_remain_box; 
	}
	else // p_remain_box != NULL
	{
		box = *p_remain_box;
		if(!search_fd_in_box(&box, fd)) // old fd
		{
			if (new_fd_box(fd, &(box -> next)) == (-1)) // new fd (생성을 위해 주소 전달)
				return (-1);
			box = box -> next; 
		} 
	} // box focus box of current fd
	// remain_len(>=0) == length of remain_str
	read_len = pull_from_box(read, box -> str);
	return (read_len);
}
//input
// read : (빈문자열)
// src : (남아 있던 문자열)
int pull_from_box(char *read, char *src)
{
	int	len;
	int	idx;

	len = 0;
	while (src[len])
	{
		read[len] = src[len];
		if (read[len] == '\n')
		{
			len++;
			break;
		}
		len++;
	}
	read[len] ='\0';
	idx = 0;
	while (src[len + idx])
	{
		src[idx] = src[len + idx];
		idx++;
	}
	src[idx] = '\0';
	return (len); // read의 길이
}
//input
// fd : (new fd)
// p_box -> box : (NULL)
int new_fd_box(int fd, t_fd_list **p_box)
{
	*p_box = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (*p_box == NULL)
		return (-1);
	(*p_box) -> fd = fd;
	((*p_box) -> str)[0] = '\0';
	(*p_box) -> next = NULL;
	return (1);// make new fd box success
}
//input
// p_box -> box : (!NULL) (거의 remain_box의 첫주소)
// fd : (new fd, old fd)
t_fd_list   *search_fd_in_box(t_fd_list **p_box, int fd)
{
	// t_fd_list	*find;

	// find = *p_box;
	// while (find)
	// {
	// 	*p_box = find;
	// 	if (find -> fd == fd);
	// 		return (*p_box); // old fd
	// 	find = find -> next;
	// }
	// return (0); // new fd

	while ((*p_box) -> next != NULL)
	{
		if ((*p_box) -> fd == fd)
			return (*p_box); // old fd
		(*p_box) = (*p_box) -> next;
	}
	if ((*p_box) -> fd == fd) // old fd
		return (*p_box);
	else // new fd
		return (0);
}

void    fd_free(int fd, t_fd_list **remain_box)
{
	t_fd_list *pre;
	t_fd_list *cur;

	cur = *remain_box;
	// printf("[cur -> fd : %d fd : %d\n", cur -> fd, fd);
	if (cur -> fd == fd)
	{
		*remain_box = (*remain_box) -> next;
		free(cur);
	}
	else
	{
		while (cur)
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