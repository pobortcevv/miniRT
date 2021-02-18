/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:28:43 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 15:31:56 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		normal_exit(t_rt *rt)
{
	free_lists(rt);
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	exit(EXIT_SUCCESS);
	return (1);
}
