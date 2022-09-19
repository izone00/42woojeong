/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:36:35 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:36:36 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (*lst == 0)
		(*lst) = new;
	else
	{
		ptr = *lst;
		while (ptr -> next != 0)
			ptr = ptr -> next;
		ptr -> next = new;
	}
}
