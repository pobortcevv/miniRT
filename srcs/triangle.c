/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:17:50 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:32:52 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		intersect_tr(t_rt *rt, t_elem *tr, t_xyz start, t_xyz finish)
{
	float a;
	float f;
	float u;
	float v;

	tr->edge1 = v_new(tr->vertex1, tr->vertex0);
	tr->edge2 = v_new(tr->vertex2, tr->vertex0);
	tr->hight = v_cross(finish, tr->edge2);
	tr->ori = v_cross(tr->edge1, tr->edge2);
	a = ft_dot(&tr->edge1, &tr->hight);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	tr->s = v_new(start, tr->vertex0);
	f = 1 / a;
	u = f * ft_dot(&tr->s, &tr->hight);
	if (u < 0 || u > 1)
		return (0);
	tr->q = v_cross(tr->s, tr->edge1);
	v = f * ft_dot(&finish, &tr->q);
	if (v < 0 || v + u > 1)
		return (0);
	rt->t1 = f * ft_dot(&tr->edge2, &tr->q);
	if (rt->t1 <= EPSILON)
		rt->t1 = INT_MAX;
	return (1);
}

void	vertex_parse(t_xyz *vertex, char **place_split)
{
	vertex->x = ft_atof(place_split[0]);
	vertex->y = ft_atof(place_split[1]);
	vertex->z = ft_atof(place_split[2]);
}

void	parse_triangle_p2(t_rt *rt, t_elem *tr, char **place_split)
{
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	vertex_parse(&tr->vertex0, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	vertex_parse(&tr->vertex1, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	vertex_parse(&tr->vertex2, place_split);
	ft_free_mat(place_split);
}

int		parse_triangle(t_rt *rt)
{
	char	**place_split;
	t_elem	*tr;

	if (ft_split_size(rt->split) != 5 || ft_charcnt(rt->split[1], ',') != 2
			|| ft_charcnt(rt->split[2], ',') != 2 ||
			ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[4], ',') != 2)
		return (0);
	tr = ft_calloc(1, sizeof(t_elem));
	tr->id = TRIANGLE;
	place_split = ft_split(rt->split[1], ',');
	parse_triangle_p2(rt, tr, place_split);
	place_split = ft_split(rt->split[4], ',');
	if (ft_split_size(place_split) != 3 || !find_err(place_split[0], FLOAT)
			|| !find_err(place_split[1], FLOAT) ||
			!find_err(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	tr->color.b = ft_atof(place_split[0]);
	tr->color.g = ft_atof(place_split[1]);
	tr->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(tr->color))
		error_parse(rt, "TRIANGLE COLOR INFO ERROR\n", tr, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(tr));
	return (1);
}
