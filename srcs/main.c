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
	rt->mlx_win = mlx_new_window(rt->mlx, rt->res.x, rt->res.y, "hello");
	render(rt);


	mlx_loop(rt->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_rt	rt;

	ft_bzero(&rt, sizeof(t_rt));
	if(!(rt.mlx = mlx_init()))
	{
		ft_printf("mlx error\n");
		return (0);
	}
	if (ac > 3 || ac == 1 || (ac == 2 && !ft_check_file(av[1])))
	{
		ft_printf("arguments error\n");
		return (0);
	}
	if (!(rt.fd = open(av[1], O_RDONLY)))
	{
		ft_printf("open fail\n");
		return (0);
	}
	if (ft_pars(&rt) != 1)
		ft_putstr_fd("Pars error\n", 2);
	else
		ft_putstr_fd("everything ok\n", 1);
	start_rt(&rt);
	return (1);
}

