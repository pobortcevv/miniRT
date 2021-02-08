/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:03:22 by sabra             #+#    #+#             */
/*   Updated: 2021/02/08 17:59:07 by sabra            ###   ########.fr       */
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

void	error_parse(t_rt *rt, char *error_name, void *elem, char **place_split)
{
	ft_printf("Error\n");
	ft_putstr_fd(error_name, 2);
	if (elem)
		free(elem);
	if (place_split)
		ft_free_mat(place_split);
	if (rt->split)
		ft_free_mat(rt->split);
	if (rt->line)
		ft_free_line(&rt->line);
	if (rt->ob_lst)
		ft_lstclear(&rt->ob_lst, free);
	if (rt->lgt_lst)
		ft_lstclear(&rt->lgt_lst, free);
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	exit(EXIT_FAILURE);
}

int		normal_exit(t_rt *rt)
{
	if (rt->ob_lst)
		ft_lstclear(&rt->ob_lst, free);
	if (rt->lgt_lst)
		ft_lstclear(&rt->lgt_lst, free);
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	exit(EXIT_SUCCESS);
	return (1);
}
