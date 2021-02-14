/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:00:22 by sabra             #+#    #+#             */
/*   Updated: 2021/02/12 15:22:17 by sabra            ###   ########.fr       */
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
# define START_RAY 14
# define MIRROR 15
# define EPSILON 0.001
# define CAMERA_START 0
# define REFLECTION_RATE 0.6
# define MIRRORING_DEPTH_VALUE 3
# define BRIGHT_RATE 100


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
}		t_cam;

typedef struct	s_amb
{
	float	ratio;
	int		id;
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
	float	cy_hight;
	float	r;
	float	n_dot_l;
	float	r_dot_v;
	float	a;
	float	ck_1;
	float	ck_2;
	t_xyz	v_r;
	t_xyz	p;
	t_xyz	p_2;
	t_xyz	l;
	t_xyz	vertex0;
	t_xyz	vertex1;
	t_xyz	vertex2;
	t_xyz	edge1;
	t_xyz	edge2;
	t_xyz	hight;
	t_xyz	s;
	t_xyz	q;
	t_xyz	norm;
	t_xyz	ori;
	t_xyz	pos;
	t_color	color;
}		t_elem;

#endif
