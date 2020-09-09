#include "../includes/cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_column(t_env *env, char *image, int i)
{
	int res;
	int tab[3];
	tab[0] = 255;
	tab[1] = 0;
	tab[2] = 0;
	while (env->wall->start <= env->wall->end)
	{
		res = 4*i + 4*env->info->resol_x*env->wall->start;
		color_pixel(image, tab, res);
		env->wall->start++;
	}
}

void spread_rays(t_cam *cam, t_player *player)
{	
	cam->ray_x = player->dir_x + cam->plane_x * cam->cam_x;
	cam->ray_y = player->dir_y + cam->plane_y * cam->cam_x;
	if (cam->ray_x == 0)
		cam->delta_dist_x = 0;
	else
		cam->delta_dist_x = fabs(1 / cam->ray_x);
	if (cam->ray_y == 0)
		cam->delta_dist_y = 0;
	else	
		cam->delta_dist_y = fabs(1 / cam->ray_y);
}

void spread_rays2(t_cam *cam, t_player *player)
{
	if (cam->ray_x < 0)
	{
		cam->step_x = -1;
		cam->side_dist_x = ((player->x - (int)player->x) * cam->delta_dist_x);
	}
	if (cam->ray_x >= 0)
	{
		cam->step_x = 1;
		cam->side_dist_x = ((int)player->x + 1 - player->x) * cam->delta_dist_x;
	}
	if (cam->ray_y < 0)
	{
		cam->step_y = -1;
		cam->side_dist_y = (player->y - (int)player->y) * cam->delta_dist_y;
	}
	if (cam->ray_y >= 0)
	{
		cam->step_y = 1;
		cam->side_dist_y = ((int)player->y + 1 - player->y) * cam->delta_dist_y;
	}
}

void	hit_a_wall(t_info *info, t_player *player, t_cam *cam, t_wall *wall)
{
	int hit;

	hit = 0;
	wall->side = -1;
	wall->wall_x = (int)player->x;
	wall->wall_y = (int)player->y;
	while (!hit)
	{
		if (cam->side_dist_x < cam->side_dist_y)
		{
			cam->side_dist_x = cam->side_dist_x + cam->delta_dist_x;
			wall->wall_x = wall->wall_x + cam->step_x;
			wall->side = 0;
		}
		else 
		{
			cam->side_dist_y = cam->side_dist_y + cam->delta_dist_y;
			wall->wall_y = wall->wall_y + cam->step_y;
			wall->side = 1;
		}
		if (info->map[wall->wall_y][wall->wall_x] != '0' && 
				info->map[wall->wall_y][wall->wall_x] != '2')
			hit = 1; 
	}
}

void	dist_to_wall(t_env *env, t_cam *cam, t_wall *wall, int i)
{
	if (wall->side == 0 && env->player->dir_x > 0 && cam->ray_x != 0)
	{
		wall->distance = (wall->wall_x - env->player->x + (1 - cam->step_x) / 2) / cam->ray_x;
		wall->orientation = 'E';
	}
	if (wall->side == 0 && env->player->dir_x <= 0 && cam->ray_x != 0)
	{
		wall->distance = (wall->wall_x - env->player->x + (1 - cam->step_x) / 2) / cam->ray_x;
		wall->orientation = 'W';
	}
	if (wall->side == 1 && env->player->dir_y > 0 && cam->ray_y != 0)
	{
		wall->distance = (wall->wall_y - env->player->y + (1 - cam->step_y) / 2) / cam->ray_y;
		wall->orientation = 'S';
	}
	if (wall->side == 1 && env->player->dir_y <= 0 && cam->ray_y != 0)
	{
		wall->distance = (wall->wall_y - env->player->y + (1 - cam->step_y) / 2) / cam->ray_y;
		wall->orientation = 'N';
	}
	env->zbuffer[i] = wall->distance;
}

void	eight_wall_perspective(t_info *info, t_wall *wall, t_cam *cam)
{
	int h;

	h = info->resol_y;
	wall->eight_persp = h / wall->distance;
	wall->start = h / 2 - wall->eight_persp / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = h / 2 + wall->eight_persp / 2;
	if (wall->end >= h)
		wall->end = h - 1;
}

void	choose_textures(t_env *env, char *image, int i)
{
	if (env->wall->side == 0 && env->cam->ray_x > 0)
		draw_tex_column(image, env, env->textures[3], i);
	else if (env->wall->side == 0 && env->cam->ray_x <= 0)
		draw_tex_column(image, env, env->textures[2], i);
	else if (env->wall->side == 1 && env->cam->ray_y > 0)
		draw_tex_column(image, env, env->textures[1], i);
	else if (env->wall->side == 1 && env->cam->ray_y <= 0)
		draw_tex_column(image, env, env->textures[0], i);
}

int	raycast(t_env *env, char *image)
{
	int i;

	i = 0;
	if (!(env->zbuffer = (double *)malloc(env->info->resol_x * sizeof(double))))
	{
		error_messages_syst(env , 7);
		return (EXIT);
	}
	while (i <= env->info->resol_x)
	{
		env->cam->cam_x = ((2 * (double)i) / (double)env->info->resol_x - 1);
		spread_rays(env->cam, env->player);
		spread_rays2(env->cam, env->player);
		hit_a_wall(env->info, env->player, env->cam, env->wall);
		dist_to_wall(env, env->cam, env->wall, i);
		eight_wall_perspective(env->info, env->wall, env->cam);
		get_tex_x(env->wall, env->player, env->cam);
		choose_textures(env, image, i);
		i++;
	}
	return (SUCCESS);
}
