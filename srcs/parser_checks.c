/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cheaks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:44:58 by sabra             #+#    #+#             */
/*   Updated: 2021/02/05 16:32:22 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		normal_check(t_xyz norm)
{
	if (norm.x < -1 || norm.x > 1)
		return (0);
	if (norm.y < -1 || norm.y > 1)
		return (0);
	if (norm.z < -1 || norm.z > 1)
		return (0);
	return (1);
}

int	check_color_parse(t_color c)
{
	if (c.r < 0 || c.g < 0 || c.b < 0 || c.r > 255 || c.g > 255 || c.b > 255)
		return (0);
	return (1);
}

int		ft_split_size(char **split)
{
	int 	size;

	size = -1;
	while(split[++size]);
	return(size);
}

int		dushnila_defence(char *line, int id)
{
	if (id == INT)
	{
		if (ft_charcnt(line, '-') > 1 || (ft_charcnt(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (!(ft_inset(line, "-0123456789")))
			return (0);
	}
	if (id == FLOAT)
	{
		if (ft_charcnt(line, '-') > 1 || (ft_charcnt(line, '-') > 0 && line[0] != '-'))
			return (0);
		if (ft_charcnt(line, '.') > 1 || (!(ft_isdigit(line[0])) && !(line[0] == '-')))
			return (0);
		if (!(ft_inset(line, "-0123456789.")))
			return (0);
	}
	if (id == STRING)
	{
		if (ft_strncmp(line, "R", ft_strlen(line)) != 0 && ft_strncmp(line, "A", ft_strlen(line)) != 0
			&& ft_strncmp(line, "c", ft_strlen(line)) != 0
			&& ft_strncmp(line, "l", ft_strlen(line)) != 0
			&& ft_strncmp(line, "pl", ft_strlen(line)) != 0
			&& ft_strncmp(line, "sp", ft_strlen(line)) != 0
			&& ft_strncmp(line, "sq", ft_strlen(line)) != 0
			&& ft_strncmp(line, "cy", ft_strlen(line)) != 0
			&& ft_strncmp(line, "tr", ft_strlen(line)) != 0)
			return (0);
	}
	return (1);
}
