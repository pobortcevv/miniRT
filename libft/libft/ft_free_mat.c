/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:05:16 by sabra             #+#    #+#             */
/*   Updated: 2021/01/06 17:40:51 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_mat(char **mat)
{
	int i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
}

void	ft_free_line(char *line)
{
	free(line);
	line = NULL;
}
