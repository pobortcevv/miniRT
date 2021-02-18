/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:17:38 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:40:10 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_check_file(char *file)
{
	char		*dot_p;

	if (!(dot_p = ft_strchr(file, '.')))
		return (0);
	if (ft_strncmp(dot_p, ".rt", ft_strlen(dot_p)) == 0)
		return (1);
	return (0);
}

int	start_rt(t_rt *rt)
{
	rt->mlx_win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "miniRT");
	rt->cam = *ft_lstcam(rt->cmr_lst, 0);
	render(rt);
	mlx_hook(rt->mlx_win, 17, 0, normal_exit, rt);
	mlx_key_hook(rt->mlx_win, key_use, rt);
	mlx_loop(rt->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	if ((ac == 2 && ft_check_file(av[1]))
				|| ((ac == 3 && ft_check_file(av[1])
				&& ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)))
	{
		ft_bzero(&rt, sizeof(t_rt));
		if (!(rt.mlx = mlx_init()))
			error_exit(&rt, "MLX ERROR\n");
		if ((rt.fd = open(av[1], O_RDONLY)) == -1)
			error_exit(&rt, "OPEN FILE ERROR\n");
		rt.file_name = av[1];
		if (ft_pars(&rt) != 1)
			error_exit(&rt, "PARSER ERROR\n");
		if (ac == 3 && ft_check_file(av[1])
				&& ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
			create_bmp(&rt);
		close(rt.fd);
		start_rt(&rt);
	}
	ft_putstr_fd("WRONG ANGUMENTS\n", 2);
	return (0);
}
