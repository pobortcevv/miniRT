/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:00:22 by sabra             #+#    #+#             */
/*   Updated: 2021/01/05 15:56:07 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "minirt.h"

# define RESOLUTION 1
# define AMBIANT 2
# define CAMERA 3
# define LIGHT 4
# define SPHERE 5


typedef struct	s_xyx
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
}		t_res;

typedef struct	s_cam
{
	t_xyz	pos;
	t_xyz	or;
	int	fov;
}		t_cam;

typedef struct	s_sp
{
	t_xyz	pos;
	float	r;
	t_color	color;
}		t_sp;

#endif
