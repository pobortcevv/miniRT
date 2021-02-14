#include "../includes/minirt.h"

float **ft_free_float_mat(float **m)
{
	int i;

	i = 0;
	while (i < 3)
	{
		free(m[i]);
		i++;
	}
	free(m);
	return (m);
}

float **rotation_matrix(t_xyz ori)
{
	float cos_x;
	float cos_y;
	int	 i;
	float **m;

	i = 0;
	if (ori.z < 0)
		ori.y = -ori.y;
	cos_y = sqrt(pow(ori.x, 2) + pow(ori.z, 2));
	cos_x = sqrt(pow(ori.z, 2) + pow(ori.y, 2));
	if (ori.z < 0)
		cos_x = -cos_x;
	m = (float **)malloc(3 * sizeof(float *));
	while (i < 3)
		m[i++] = (float *)malloc(3 * sizeof(float));
	m[0][0] = cos_x;
	m[0][1] = -ori.y * ori.x;
	m[0][2] = -ori.x * cos_y;
	m[1][0] = 0;
	m[1][1] = cos_y;
	m[1][2] = -ori.y;
	m[2][0] = ori.x;
	m[2][1] = cos_x * ori.y;
	m[2][2] = cos_x * cos_y;
	return (m);
}

t_xyz	rotate_scene(t_xyz c_pos, float **r_m)
{
	float	res[3];
	float	pos[3];
	int		i;
	int		j;

	pos[0] = c_pos.x;
	pos[1] = c_pos.y;
	pos[2] = c_pos.z;
	i = 0;
	while (i < 3)
	{
		j = 0;
		res[i] = 0;
		while (j < 3)
		{
			res[i] += r_m[i][j] * pos[j];
			j++;
		}
		i++;
	}
	c_pos.x = res[0];
	c_pos.y = res[1];
	c_pos.z = res[2];
	return (c_pos);
}
