/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:10:56 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 19:50:04 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft/libft.h"
# include "objects.h"
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "mlx.h"

typedef struct	s_rt
{
	int		fd;
	int		depth;
	int		cam_count;
	void	*mlx;
	void	*mlx_win;
	char	*line;
	char	*file_name;
	char	**split;
	float	t;
	float	t1;
	float	t2;
	float	closest_t;
	t_elem	*cl_el;
	t_cam	cam;
	t_res	res;
	t_amb	amb;
	t_list	*ob_lst;
	t_list	*lgt_lst;
	t_list	*cmr_lst;
}				t_rt;

int				ft_pars(t_rt *rt);
void			ft_free_split(char **result, size_t last);
int				parse_sphere(t_rt *rt);
int				parse_camera(t_rt *rt);
int				parse_light(t_rt *rt);
int				parse_ambiant(t_rt *rt);
int				parse_res(t_rt *rt);
int				normal_check(t_xyz norm);
int				find_err(char *line, int id);
float			ft_dot(t_xyz *vec1, t_xyz *vec2);
void			render(t_rt *rt);
int				parse_plane(t_rt *rt);
int				parse_square(t_rt *rt);
int				parse_cylinder(t_rt *rt);
int				parse_triangle(t_rt *rt);
void			normalize(t_xyz *v);
t_xyz			v_cross(t_xyz v1, t_xyz v2);
t_xyz			v_new(t_xyz v1, t_xyz v2);
t_xyz			v_multi(t_xyz v, float n);
int				check_tr(t_rt *rt, t_xyz hit, t_elem *tr);
t_color			comp_light(t_rt *rt, t_elem *cl_elem, float t);
t_xyz			v_plus(t_xyz v1, t_xyz v2);
float			v_len(t_xyz v);
int				ft_color(int r, int g, int b);
void			color_light(t_color *res, float light);
t_color			c_null(void);
t_color			c_one(void);
void			color_ambiant(t_color *c, t_color light_color);
t_color			c_plus(t_color c1, t_color c2);
int				c_isnull(t_color c);
t_color			cs_multi(t_color c1, t_color c2);
t_color			c_multi(t_color c, float n);
t_elem			*ft_lstcnt(t_list *list, int index);
t_cam			*ft_lstcam(t_list *list, int index);
t_lgt			*ft_lstlgt(t_list *list, int index);
void			intersect_pl(t_rt *rt, t_elem *pl, t_xyz start, t_xyz finish);
void			intersect_cy(t_rt *rt, t_elem *cy, t_xyz start, t_xyz finish);
int				intersect_sq(t_rt *rt, t_elem *sq, t_xyz start, t_xyz finish);
void			intersect_sp(t_rt *rt, t_elem *sp, t_xyz start, t_xyz finish);
int				intersect_tr(t_rt *rt, t_elem *tr, t_xyz start, t_xyz finish);
void			intersect_init(t_rt *rt, t_elem *elem,
		t_xyz start, t_xyz finish);
void			to_viewport(int x, int y, t_rt *rt);
float			shadow_intersect(t_rt *rt, t_elem *cl_elem);
t_xyz			reflect_ray(t_xyz r, t_xyz norm);
int				ft_split_size(char **split);
void			close_hook(t_rt *rt);
void			error_exit(t_rt *rt, char *error_name);
void			error_parse(t_rt *rt, char *error_name,
			void *elem, char **place_split);
int				normal_exit(t_rt *rt);
int				check_color_parse(t_color c);
t_xyz			rotate_scene(t_xyz c_pos, float **r_m);
float			**rotation_matrix(t_xyz ori);
void			cam_to_world(t_rt *rt, float **rotation_m, t_cam *cam);
void			change_frame(t_rt *rt, t_cam *cam);
float			**ft_free_float_mat(float **m);
int				key_use(int keycode, t_rt *rt);
int				create_bmp(t_rt *rt);
t_color			trace_ray(t_rt *rt, t_xyz start, t_xyz finish, int id);
void			free_lists(t_rt *rt);
t_xyz			cy_normal(t_elem cy, t_xyz cp);

#endif
