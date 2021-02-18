/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:10:19 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:17:38 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		intersect_sq(t_rt *rt, t_elem *sq, t_xyz start, t_xyz finish)
{
	t_xyz	co;
	t_xyz	hit;
	float	k1;
	float	k2;

	co = v_new(sq->pos, start);
	normalize(&sq->ori);
	k1 = ft_dot(&sq->ori, &co);
	rt->t2 = INT_MAX;
	k2 = ft_dot(&finish, &sq->ori);
	if (k2 == 0)
	{
		rt->t1 = INT_MAX;
		return (0);
	}
	rt->t1 = k1 / k2;
	hit = v_plus(start, v_multi(finish, rt->t1));
	if ((fabs(hit.x - sq->pos.x) > (sq->len / 2)
				|| (fabs(hit.y - sq->pos.y) > (sq->len / 2)
				|| (fabs(hit.z - sq->pos.z) > (sq->len / 2)))))
		rt->t1 = INT_MAX;
	return (1);
}

void	parse_square_p2(t_rt *rt, t_elem *sq, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT) ||
			!find_err(rt->split[3], FLOAT))
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	sq->pos.x = ft_atof(place_split[0]);
	sq->pos.y = ft_atof(place_split[1]);
	sq->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	sq->ori.x = ft_atof(place_split[0]);
	sq->ori.y = ft_atof(place_split[1]);
	sq->ori.z = ft_atof(place_split[2]);
	if ((sq->len = ft_atof(rt->split[3])) < 0)
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	ft_free_mat(place_split);
}

int		parse_square(t_rt *rt)
{
	char	**place_split;
	t_elem	*sq;

	if (ft_split_size(rt->split) != 5 || ft_charcnt(rt->split[1], ',') != 2
			|| ft_charcnt(rt->split[4], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	sq = ft_calloc(1, sizeof(t_elem));
	sq->id = SQUARE;
	place_split = ft_split(rt->split[1], ',');
	parse_square_p2(rt, sq, place_split);
	place_split = ft_split(rt->split[4], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	sq->color.b = ft_atof(place_split[0]);
	sq->color.g = ft_atof(place_split[1]);
	sq->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(sq->color))
		error_parse(rt, "SQUARE INFO COLOR ERROR\n", sq, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(sq));
	return (1);
}
