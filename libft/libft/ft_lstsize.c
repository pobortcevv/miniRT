/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:39:39 by sabra             #+#    #+#             */
/*   Updated: 2021/02/11 16:56:29 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		len;
	t_list		*list;

	list = lst;
	len = 0;
	if (!lst)
		return (0);
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}
