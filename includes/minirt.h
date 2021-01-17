/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:10:56 by sabra             #+#    #+#             */
/*   Updated: 2021/01/16 17:05:57 by sabra            ###   ########.fr       */
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
	void	*mlx;
	void	*mlx_win;
	char	*line;
	char	**split;
	float	t1;
	float	t2;

	t_res	res;
	t_cam	cam;
	t_list	*ob_lst;
	
}		t_rt; 

int		ft_pars(t_rt *rt);
void		ft_free_split(char **result, size_t last);
int             parse_sphere(t_rt *rt);
int             parse_camera(t_rt *rt);
int             parse_res(t_rt *rt);
int		dushnila_defence(char *line, int id);
float		ft_dot(t_xyz *vec1, t_xyz *vec2);
void		render(t_rt *rt);
int		trace_ray(t_rt *rt, float min_t);
int		ft_color(int r, int g, int b);
void		intersect_sp(t_rt *rt, t_elem *sp);
void		intersect_init(t_rt *rt, t_elem *elem);
t_elem		*ft_lstcnt(t_list *list, int index);
void		to_viewport(int x, int y, t_rt *rt);
int		parse_plane(t_rt *rt);

#endif
