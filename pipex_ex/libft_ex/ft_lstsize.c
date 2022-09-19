/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:42:15 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:42:15 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (lst == 0)
		return (0);
	count = 1;
	while (lst -> next != 0)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}
