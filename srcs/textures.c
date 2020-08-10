#include "../includes/cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>


int	init_textures(t_info *info, t_window *window, t_textures *textures)
{
int width;
int height;

width = 64;
height = 64;
	if ((textures[0].ptr = mlx_xpm_file_to_image(window->mlx_ptr, 
				info->north_tex, &width, &height)) == 0)
		return (0);
	if ((textures[1].ptr = mlx_xpm_file_to_image(window->mlx_ptr, 
				info->south_tex, &width, &height)) == 0) 
		return (0);
	if ((textures[2].ptr= mlx_xpm_file_to_image(window->mlx_ptr, 
				info->west_tex, &width, &height)) == 0)   
		return (0);
	if ((textures[3].ptr = mlx_xpm_file_to_image(window->mlx_ptr, 
				info->east_tex, &width, &height)) == 0)
		return (0);
	if ((textures[4].ptr = mlx_xpm_file_to_image(window->mlx_ptr, 
				info->sprite_tex, &width, &height)) == 0)
		return (0);
	init_data_textures(textures);
return (1);
}

int	init_data_textures(t_textures *textures)
{
	if ((textures[0].im = mlx_get_data_addr(textures[0].ptr, &textures[0].bpp, 
				&textures[0].size_line, &textures[0].endian)) == 0)
	return (0);
	if ((textures[1].im = mlx_get_data_addr(textures[1].ptr, &textures[1].bpp, 
				&textures[1].size_line, &textures[1].endian)) == 0)
	return (0);
	if ((textures[2].im = mlx_get_data_addr(textures[2].ptr, &textures[2].bpp, 
				&textures[2].size_line, &textures[2].endian)) == 0)
	return (0);
	if ((textures[3].im = mlx_get_data_addr(textures[3].ptr, &textures[3].bpp, 
				&textures[3].size_line, &textures[3].endian)) == 0)
	return (0);
	if ((textures[4].im = mlx_get_data_addr(textures[4].ptr, &textures[4].bpp, 
			&textures[4].size_line, &textures[4].endian)) == 0)
	return (0);
	return (1);
}

void get_tex_x(t_wall *wall, t_player *player, t_cam *cam)
{
	if (wall->side == 0) 
		wall->wall_hit_x = player->y + wall->distance * cam->ray_y;
	else 
		wall->wall_hit_x = player->x + wall->distance * cam->ray_x;
	wall->wall_hit_x = wall->wall_hit_x - floor(wall->wall_hit_x);
	wall->tex_x = (int)(wall->wall_hit_x * 64);
	if (wall->side == 0 && cam->ray_x > 0)
		wall->tex_x = 64 - wall->tex_x - 1;
	if (wall->side == 1 && cam->ray_y > 0)
		wall->tex_x = 64 - wall->tex_x - 1;
}

void draw_tex_column(char *image, t_env *env, t_textures textures, int i)
{
	double	tex_pos;
	double	step_tex;
	int		tex_y;
	int 	res;
	int 	res2;

	step_tex = 64.0 / (double)env->wall->eight_persp;
	tex_pos = (env->wall->start - env->info->resol_y / 2 + env->wall->eight_persp / 2) * step_tex;
	while (env->wall->start < env->wall->end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= 64)
			tex_y = 63;
		tex_pos += step_tex;
		res = 4*i + 4*env->info->resol_x*env->wall->start;
		res2 = 4*env->wall->tex_x + 4*64*tex_y;
		image[res] = textures.im[res2];  
		image[res + 1] = textures.im[res2 + 1];  
		image[res+ 2] = textures.im[res2 + 2];  
		image[res+ 3] = textures.im[res2 + 3];  
		env->wall->start++;
	}
}

