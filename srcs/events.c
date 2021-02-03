/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:03:22 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 16:27:03 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	error_exit(t_rt *rt, char *error_name)
{
	ft_printf("Error\n");
	ft_putstr_fd(error_name, 2);
	if (rt->closest_elem)
		free(rt->closest_elem);
	if (rt->ob_lst)
		ft_lstclear(&rt->ob_lst, free);
	if (rt->lgt_lst)
		ft_lstclear(&rt->lgt_lst, free);
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	exit(EXIT_FAILURE);
}

void	error_parse(t_rt *rt, char *error_name, t_elem *elem)
{
	ft_printf("Error\n");
	ft_putstr_fd(error_name, 2);
	free(elem);
	if (rt->split)
		ft_free_mat(rt->split);
	if (rt->line)
		ft_free_line(rt->line);
	if (rt->ob_lst)
		ft_lstclear(&rt->ob_lst, free);
	if (rt->lgt_lst)
		ft_lstclear(&rt->lgt_lst, free);
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	exit(EXIT_FAILURE);
}
