/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:36:46 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:36:46 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*last;

	if (lst == 0)
		return ;
	ptr = *lst;
	while (ptr != 0)
	{
		last = ptr;
		del(ptr -> content);
		ptr = ptr -> next;
		free(last);
	}
	(*lst) = 0;
}
