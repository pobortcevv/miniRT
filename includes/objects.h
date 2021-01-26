/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:00:22 by sabra             #+#    #+#             */
/*   Updated: 2021/01/18 18:56:46 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define EMPTY_LINE 10
# define INT 11
# define FLOAT 12
# define STRING 13

typedef struct	s_xyz
{
	float x;
	float y;
	float z;
}		t_xyz;

typedef struct	s_color
{
	float r;
	float g;
	float b;
}		t_color;

typedef struct	s_res
{
	int x;
	int y;
	int id;
}		t_res;

typedef struct	s_cam
{
	t_xyz	d;
	t_xyz	pos;
	t_xyz	ori;
	float	fov;
	int	num;
}		t_cam;

typedef struct	s_amb
{
	float	ratio;
	t_color	color;
}		t_amb;

typedef struct	s_lgt
{
	t_xyz	pos;
	float	bright;
	t_color	color;
}		t_lgt;

typedef struct	s_elem
{
	int	id;
	
	float	len;
	float	h;
	float	r;
	float	n_dot_l;
	t_xyz	a;
	t_xyz	b;
	t_xyz	c;
	t_xyz	p;
	t_xyz	l;
	t_xyz	norm;
	t_xyz	ori;
	t_xyz	pos;
	t_color	color;
}		t_elem;

#endif
