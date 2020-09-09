#include "../mlx/mlx.h"
#include "../includes/cub3d.h"
#include <stdio.h>

void color_pixel(char *image, int tab[3], int res)
{
	image[res] = tab[2];
	image[res + 1] = tab[1];
	image[res + 2] = tab[0];
}

void	draw_ceiling_floor(t_env *env, char *image)
{
	int i;
	int j;
	int res;
	int max;

	i = 0;
	j = 0;
	max = 4*env->info->resol_x*env->info->resol_y;
	while (i < env->info->resol_y)
	{
		while (j < env->info->resol_x)
		{
			res = 4*j + 4*env->info->resol_x*i;
			if (res < max / 2)
				color_pixel(image, env->info->color_c, res);
			else
				color_pixel(image, env->info->color_f, res);
			j++;
		}
		j = 0;
		i++;
	}
}

int		create_image(t_env *env)
{
	int max;
	char *image;

	env->win->mlx_image = mlx_new_image(env->win->mlx_ptr, env->info->resol_x, env->info->resol_y);
	image = mlx_get_data_addr(env->win->mlx_image, &(env->win->bpp), &(env->win->size_line), &(env->win->endian));
	draw_ceiling_floor(env, image);	
	raycast(env, image);
	sprite(env, image);
	free(env->zbuffer);
	if (env->save)
	{
		save(env, image);
		return(0);
	}
	env->player->step = 0.07;
	env->cam->rot_speed = 0.05;
	move_player(env->player, env->info, env->move, env->cam);
	rotate(env);
	mlx_put_image_to_window(env->win->mlx_ptr, env->win->mlx_win, env->win->mlx_image, 0, 0);
	mlx_destroy_image(env->win->mlx_ptr, env->win->mlx_image);
	return (0);
}
