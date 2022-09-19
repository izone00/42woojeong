/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:42:06 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:42:06 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;

	if (lst == 0)
		return (0);
	new = ft_lstnew(f(lst -> content));
	if (new == 0)
		return (0);
	start = new;
	lst = lst -> next;
	while (lst != 0)
	{
		new -> next = ft_lstnew(f(lst -> content));
		new = new -> next;
		if (new == 0)
		{
			ft_lstclear(&start, del);
			return (0);
		}
		lst = lst -> next;
	}
	return (start);
}
