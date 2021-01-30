/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:10:56 by sabra             #+#    #+#             */
/*   Updated: 2021/01/29 10:21:38 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft/libft.h"
# include "objects.h"
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
//# include "mlx.h"

typedef struct	s_rt
{
	int	fd;
	int	depth;
	void	*mlx;
	void	*mlx_win;
	char	*line;
	char	**split;
	float	t1;
	float	t2;
	float	closest_t;
	t_elem	*closest_elem;
	t_res	res;
	t_cam	cam;
	t_amb	amb;
	t_list	*ob_lst;
	t_list	*lgt_lst;
	
}		t_rt; 

int		ft_pars(t_rt *rt);
void		ft_free_split(char **result, size_t last);
int             parse_sphere(t_rt *rt);
int             parse_camera(t_rt *rt);
int		parse_light(t_rt *rt);
int		parse_ambiant(t_rt *rt);
int             parse_res(t_rt *rt);
int		dushnila_defence(char *line, int id);
float		ft_dot(t_xyz *vec1, t_xyz *vec2);
void		render(t_rt *rt);
int		ft_color(int r, int g, int b);
void    	intersect_pl(t_rt *rt, t_elem *pl);
int     	intersect_sq(t_rt *rt, t_elem *sq);
t_elem		*ft_lstcnt(t_list *list, int index);
void		to_viewport(int x, int y, t_rt *rt);
int		parse_plane(t_rt *rt);
int		parse_square(t_rt *rt);
void		normalize(t_xyz *v);
t_xyz		cross(t_xyz v1, t_xyz v2);
t_xyz		v_new(t_xyz v1, t_xyz v2);
t_xyz		v_multi(t_xyz v, float n);
int		intersect_tr(t_rt *rt, t_elem *tr);
int		check_tr(t_rt *rt, t_xyz hit, t_elem *tr);
int		parse_triangle(t_rt *rt);
float		comp_light(t_rt *rt, t_elem *cl_elem, float t);
t_xyz		v_plus(t_xyz v1, t_xyz v2);
float		v_len(t_xyz v);


#endif
