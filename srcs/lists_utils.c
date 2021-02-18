/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:03:45 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 15:24:55 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_lgt	*ft_lstlgt(t_list *list, int index)
{
	int		i;
	t_list	*lst;
	t_lgt	*lgt;

	lst = list;
	lgt = lst->content;
	i = 0;
	while (i != index)
	{
		lst = lst->next;
		lgt = lst->content;
		i++;
	}
	return (lgt);
}

t_elem	*ft_lstcnt(t_list *list, int index)
{
	int		i;
	t_list	*lst;
	t_elem	*elem;

	lst = list;
	elem = lst->content;
	i = 0;
	while (i != index)
	{
		lst = lst->next;
		elem = lst->content;
		i++;
	}
	return (elem);
}

t_cam	*ft_lstcam(t_list *list, int index)
{
	int		i;
	t_list	*lst;
	t_cam	*cam;

	lst = list;
	cam = lst->content;
	i = 0;
	while (i != index)
	{
		lst = lst->next;
		cam = lst->content;
		i++;
	}
	return (cam);
}
