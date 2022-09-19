/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:44:51 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/09 20:44:51 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	int		i;
	char	*dup;

	i = 0;
	while (str1[i] != '\0')
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == 0)
		return (0);
	i = 0;
	while (str1[i] != '\0')
	{
		dup[i] = str1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
