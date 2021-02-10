#include "../includes/minirt.h"

float **x_matrix(float cos_a, float sin_a)
{
	int 	i;	
	float 	**m;

	i = 0;
	m = (float **)malloc(3 * sizeof(float *));
	while (i < 3)
		m[i++] = (float *)malloc(3 * sizeof(float));
	m[0][0] = 1; 
	m[0][1] = 0; 
	m[0][2] = 0; 
	m[1][0] = 0; 
	m[1][1] = cos_a; 
	m[1][2] = -sin_a; 
	m[2][0] = 0;
	m[2][1] = sin_a; 
	m[2][2] = cos_a; 
	return (m);
}

float **y_matrix(float cos_a, float sin_a)
{
	int 	i;	
	float 	**m;

	i = 0;
	m = (float **)malloc(3 * sizeof(float *));
	while (i < 3)
		m[i++] = (float *)malloc(3 * sizeof(float));
	m[0][0] = cos_a; 
	m[0][1] = 0; 
	m[0][2] = sin_a; 
	m[1][0] = 0; 
	m[1][1] = 1; 
	m[1][2] = 0; 
	m[2][0] = -sin_a;
	m[2][1] = 0;
	m[2][2] = cos_a; 
	return (m);
}

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

float **matrix_multi(float **x_m, float **y_m)
{
	int 	i;
	int		j;
	int		k;
	float 	**res;

	j = 0;
	res = (float **)malloc(3 * sizeof(float *));
	while (j < 3)
		res[j++] = (float *)malloc(3 * sizeof(float));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = 0;
			k = 0;
			while (k < 3)
			{
				res[i][j] += x_m[i][k] * y_m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	ft_free_float_mat(x_m);
	ft_free_float_mat(y_m);
	return (res);
}

float **rotation_matrix(t_xyz ori)
{
	float **x_m;	
	float **y_m;	
	float cos_a;
	float sin_a;

	normalize(&ori);
	//if (v_len(ori) == 0)
		//return ;
	cos_a = ori.x;
	sin_a = sqrt(1 - cos_a * cos_a);
	x_m = x_matrix(cos_a, sin_a);
	cos_a = ori.y;
	sin_a = sqrt(1 - cos_a * cos_a);
	y_m = y_matrix(cos_a, sin_a);
	return (matrix_multi(x_m, y_m));
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
	ft_free_float_mat(r_m);
	return (c_pos);
}
//
//int main (void)
//{
	//t_xyz ori = {0.3, 0.5, 0.0};
	//t_xyz pos = {5, 4, 7};
	//float **result;
//
	//result = rotation_matrix(ori);
	//pos = rotate_scene(pos, result);
	//sleep(1000);
//}
