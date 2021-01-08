/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:10:56 by sabra             #+#    #+#             */
/*   Updated: 2021/01/08 14:22:33 by sabra            ###   ########.fr       */
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
//# include "mlx.h"

typedef struct	s_rt
{
	int	fd;
	void	*mlx;
	void	*mlx_win;
	char	*line;
	char	**split;
	
	t_res	res;
	t_cam	cam;
	t_sp	sp;
	
}		t_rt; 

int		ft_pars(t_rt *rt);
void		ft_free_split(char **result, size_t last);
int             parse_sphere(t_rt *rt);
int             parse_camera(t_rt *rt);
int             parse_res(t_rt *rt);
int		dushnila_defence(char *line, int id);

#endif

