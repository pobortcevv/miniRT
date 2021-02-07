/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:45:37 by sabra             #+#    #+#             */
/*   Updated: 2021/02/07 12:28:45 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
 * Если в сплите не 3 элемента, выходить и чистить place_split
 */


int		parse_ambiant(t_rt *rt)
{
	char	**place_split;

	if (ft_charcnt(rt->split[2], ',') != 2 || ft_split_size(rt->split) != 3)
		return (0);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[1], FLOAT))
		return (0);
	rt->amb.color.b = ft_atof(place_split[0]);
	rt->amb.color.g = ft_atof(place_split[1]);
	rt->amb.color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if (!check_color_parse(rt->amb.color))
		return (0);
	if ((rt->amb.ratio = ft_atof(rt->split[1])) < 0 || (rt->amb.ratio > 1))
		return (0);
	rt->amb.id = 1;
	return (1);
}

int		parse_light(t_rt *rt)
{
	char	**place_split;
	t_lgt	*l;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
		return (0);
	l = ft_calloc(1, sizeof(t_lgt));
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[2], FLOAT))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	l->pos.x = ft_atof(place_split[0]);
	l->pos.y = ft_atof(place_split[1]);
	l->pos.z = ft_atof(place_split[2]);
	if ((l->bright = ft_atof(rt->split[2])) < 0 || (l->bright > 1))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "LIGHT INFO ERROR\n", l, place_split);
	l->color.b = ft_atof(place_split[0]);
	l->color.g = ft_atof(place_split[1]);
	l->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(l->color))
		error_parse(rt, "LIGHT COLOR INFO ERROR\n", l, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->lgt_lst, ft_lstnew(l));
	return (1);
}

int		parse_sphere(t_rt *rt)
{
	char	**place_split;
	t_elem	*sp;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
		return (0);
	sp = ft_calloc(1, sizeof(t_elem));
	sp->id = SPHERE;
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[2], FLOAT))
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	sp->pos.x = ft_atof(place_split[0]);
	sp->pos.y = ft_atof(place_split[1]);
	sp->pos.z = ft_atof(place_split[2]);
	if ((sp->r = ft_atof(rt->split[2]) / 2) < 0)
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "SPHERE INFO ERROR\n", sp, place_split);
	sp->color.b = ft_atof(place_split[0]);
	sp->color.g = ft_atof(place_split[1]);
	sp->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(sp->color))
		error_parse(rt, "SPHERE COLOR INFO ERROR\n", sp, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(sp));
	return (1);
}

/*
 *	Добавить обработку place_split от segfault остальным фигурам
 */

int		parse_plane(t_rt *rt)
{
	char	**place_split;
	t_elem	*pl;

	if (ft_split_size(rt->split) != 4 || ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	pl = ft_calloc(1, sizeof(t_elem));
	pl->id = PLANE;
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||	
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->pos.x = ft_atof(place_split[0]);
	pl->pos.y = ft_atof(place_split[1]);
	pl->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->ori.x = ft_atof(place_split[0]);
	pl->ori.y = ft_atof(place_split[1]);
	pl->ori.z = ft_atof(place_split[2]);
	if (!normal_check(pl->ori))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "PLANE INFO ERROR\n", pl, place_split);
	pl->color.b = ft_atof(place_split[0]);
	pl->color.g = ft_atof(place_split[1]);
	pl->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(pl->color))
		error_parse(rt, "PLANE COLOR INFO ERROR\n", pl, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(pl));
	return (1);
}

int		parse_square(t_rt *rt)
{
	char	**place_split;
	t_elem	*sq;

	if (ft_split_size(rt->split) != 5 || ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[4], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	sq = ft_calloc(1, sizeof(t_elem));
	sq->id = SQUARE;
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT) ||
			!dushnila_defence(rt->split[3], FLOAT))
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	sq->pos.x = ft_atof(place_split[0]);
	sq->pos.y = ft_atof(place_split[1]);
	sq->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	sq->ori.x = ft_atof(place_split[0]);
	sq->ori.y = ft_atof(place_split[1]);
	sq->ori.z = ft_atof(place_split[2]);
	if ((sq->len = ft_atof(rt->split[3])) < 0)
		error_parse(rt, "SQUARE INFO ERROR\n", sq, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[4], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
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

int		parse_cylinder(t_rt *rt)
{
	char	**place_split;
	t_elem	*cy;

	if (ft_split_size(rt->split) != 6 || ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[2], ',') != 2 ||
			ft_charcnt(rt->split[5], ',') != 2)
		return (0);
	cy = ft_calloc(1, sizeof(t_elem));
	cy->id = CYLINDER;
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT) ||
			!dushnila_defence(rt->split[3], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->pos.x = ft_atof(place_split[0]);
	cy->pos.y = ft_atof(place_split[1]);
	cy->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->ori.x = ft_atof(place_split[0]);
	cy->ori.y = ft_atof(place_split[1]);
	cy->ori.z = ft_atof(place_split[2]);
	if((cy->r = ft_atof(rt->split[3]) / 2) < 0 || (cy->cy_hight = ft_atof(rt->split[4])) < 0)
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[5], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	cy->color.b = ft_atof(place_split[0]);
	cy->color.g = ft_atof(place_split[1]);
	cy->color.r = ft_atof(place_split[2]);
	if (!check_color_parse(cy->color))
		error_parse(rt, "CYLINDER INFO ERROR\n", cy, place_split);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(cy));
	return (1);
}

int		parse_triangle(t_rt *rt)
{
	char	**place_split;
	t_elem	*tr;

	if (ft_split_size(rt->split) != 5 ||  ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[2], ',') != 2 ||
			ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[4], ',') != 2)
		return (0);
	tr = ft_calloc(1, sizeof(t_elem));
	tr->id = TRIANGLE;
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	tr->vertex0.x = ft_atof(place_split[0]);
	tr->vertex0.y = ft_atof(place_split[1]);
	tr->vertex0.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	tr->vertex1.x = ft_atof(place_split[0]);
	tr->vertex1.y = ft_atof(place_split[1]);
	tr->vertex1.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		error_parse(rt, "TRIANGLE INFO ERROR\n", tr, place_split);
	tr->vertex2.x = ft_atof(place_split[0]);
	tr->vertex2.y = ft_atof(place_split[1]);
	tr->vertex2.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[4], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
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

int		parse_camera(t_rt *rt)
{
	char	**place_split;

	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[3], INT))
		return (0);
	rt->cam.pos.x = ft_atof(place_split[0]);
	rt->cam.pos.y = ft_atof(place_split[1]);
	rt->cam.pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	rt->cam.ori.x = ft_atof(place_split[0]);
	rt->cam.ori.y = ft_atof(place_split[1]);
	rt->cam.ori.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if((rt->cam.fov = ft_atof(rt->split[3]) * (3.14/180)) < 0)
		return (0);
	rt->cam.num += 1;
	return (1);
}

int		parse_res(t_rt *rt)
{
	if (!dushnila_defence(rt->split[1], INT) || !dushnila_defence(rt->split[2], INT)
			|| ft_split_size(rt->split) != 3 || rt->res.id == 1)
		return (0);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	if (rt->res.x < 0 || rt->res.y < 0)
		return (0);
	rt->res.id = 1;
	return (1);
}
