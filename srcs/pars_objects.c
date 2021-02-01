/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:45:37 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 16:08:48 by sabra            ###   ########.fr       */
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
	return (1);
}

int		parse_light(t_rt *rt)
{
	char	**place_split;
	t_lgt	*l;

	l = ft_calloc(1, sizeof(t_lgt));
	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[2], FLOAT))
		return (0);
	l->pos.x = ft_atof(place_split[0]);
	l->pos.y = ft_atof(place_split[1]);
	l->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if ((l->bright = ft_atof(rt->split[2])) < 0 || (l->bright > 1))
		return (0);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	l->color.b = ft_atof(place_split[0]);
	l->color.g = ft_atof(place_split[1]);
	l->color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if (!check_color_parse(l->color))
		return (0);
	ft_lstadd_back(&rt->lgt_lst, ft_lstnew(l));
	return (1);
}

int		parse_sphere(t_rt *rt)
{
	char	**place_split;
	t_elem	*sp;

	sp = ft_calloc(1, sizeof(t_elem));
	sp->id = SPHERE;
	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2
			|| ft_split_size(rt->split) != 4)
	{
		free(sp);
		return (0);
	}
	place_split = ft_split(rt->split[1], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT)
			|| !dushnila_defence(rt->split[2], FLOAT))
		return (0);
	sp->pos.x = ft_atof(place_split[0]);
	sp->pos.y = ft_atof(place_split[1]);
	sp->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if ((sp->r = ft_atof(rt->split[2]) / 2) < 0)
		return (0);
	place_split = ft_split(rt->split[3], ',');
	if (ft_split_size(place_split) != 3 || !dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	sp->color.b = ft_atof(place_split[0]);
	sp->color.g = ft_atof(place_split[1]);
	sp->color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	if (!check_color_parse(sp->color))
		return (0);
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

	pl = ft_calloc(1, sizeof(t_elem));
	pl->id = PLANE;
	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	pl->pos.x = ft_atof(place_split[0]);
	pl->pos.y = ft_atof(place_split[1]);
	pl->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	pl->ori.x = ft_atof(place_split[0]);
	pl->ori.y = ft_atof(place_split[1]);
	pl->ori.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	pl->color.b = ft_atof(place_split[0]);
	pl->color.g = ft_atof(place_split[1]);
	pl->color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(pl));
	return (1);
}

int		parse_square(t_rt *rt)
{
	char	**place_split;
	t_elem	*sq;

	sq = ft_calloc(1, sizeof(t_elem));
	sq->id = SQUARE;
	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[4], ',') != 2 ||
			ft_charcnt(rt->split[2], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT) ||
			!dushnila_defence(rt->split[3], FLOAT))
		return (0);
	sq->pos.x = ft_atof(place_split[0]);
	sq->pos.y = ft_atof(place_split[1]);
	sq->pos.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	sq->ori.x = ft_atof(place_split[0]);
	sq->ori.y = ft_atof(place_split[1]);
	sq->ori.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	sq->len = ft_atof(rt->split[3]);
	place_split = ft_split(rt->split[4], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	sq->color.b = ft_atof(place_split[0]);
	sq->color.g = ft_atof(place_split[1]);
	sq->color.r = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	ft_lstadd_back(&rt->ob_lst, ft_lstnew(sq));
	return (1);
}

int		parse_triangle(t_rt *rt)
{
	char	**place_split;
	t_elem	*tr;

	tr = ft_calloc(1, sizeof(t_elem));
	tr->id = TRIANGLE;
	if (ft_charcnt(rt->split[1], ',') != 2 || ft_charcnt(rt->split[2], ',') != 2 ||
			ft_charcnt(rt->split[3], ',') != 2 ||
			ft_charcnt(rt->split[4], ',') != 2)
		return (0);
	place_split = ft_split(rt->split[1], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	tr->a.x = ft_atof(place_split[0]);
	tr->a.y = ft_atof(place_split[1]);
	tr->a.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[2], ',');
if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	tr->b.x = ft_atof(place_split[0]);
	tr->b.y = ft_atof(place_split[1]);
	tr->b.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[3], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	tr->c.x = ft_atof(place_split[0]);
	tr->c.y = ft_atof(place_split[1]);
	tr->c.z = ft_atof(place_split[2]);
	ft_free_mat(place_split);
	place_split = ft_split(rt->split[4], ',');
	if (!dushnila_defence(place_split[0], FLOAT) || !dushnila_defence(place_split[1], FLOAT) ||
			!dushnila_defence(place_split[2], FLOAT))
		return (0);
	tr->color.b = ft_atof(place_split[0]);
	tr->color.g = ft_atof(place_split[1]);
	tr->color.r = ft_atof(place_split[2]);
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
	rt->cam.fov = ft_atof(rt->split[3]) * (3.14/180);
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
