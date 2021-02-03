/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:17:38 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 16:35:17 by sabra            ###   ########.fr       */
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
	rt->mlx_win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "minirt");
	render(rt);
	//mlx_hook(rt->mlx_win, 17, 1L<<0, close, rt);

	mlx_loop(rt->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	ft_bzero(&rt, sizeof(t_rt));
	if(!(rt.mlx = mlx_init()))
		error_exit(&rt, "MLX ERROR\n");
	if (ac > 3 || ac == 1 || (ac == 2 && !ft_check_file(av[1])))
		error_exit(&rt, "ARGUMENTS ERROR\n");
	if (!(rt.fd = open(av[1], O_RDONLY)))
		error_exit(&rt, "OPEN FILE ERROR\n");
	if (ft_pars(&rt) != 1)
		error_exit(&rt, "PARSER ERROR\n");
	ft_putstr_fd("everything ok\n", 1);
	start_rt(&rt);
	return (1);
}
