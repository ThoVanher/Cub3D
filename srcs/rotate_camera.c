#include "../includes/cub3d.h"

void	rotate_left(t_player *player, t_cam *cam)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x *cos(cam->rot_speed) - player->dir_y * 
		sin(cam->rot_speed);
	player->dir_y = old_dir_x * sin(cam->rot_speed) + player->dir_y * 
		cos(cam->rot_speed);
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(cam->rot_speed) - cam->plane_y * 
		sin(cam->rot_speed);
	cam->plane_y = old_plane_x * sin(cam->rot_speed) + cam->plane_y * 
		cos(cam->rot_speed);
}

void	rotate_right(t_player *player, t_cam *cam)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x *cos(cam->rot_speed * (-1)) - player->dir_y * 
		sin(cam->rot_speed * (-1));
	player->dir_y = old_dir_x * sin(cam->rot_speed * (-1)) + player->dir_y * 
		cos(cam->rot_speed * (-1));
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(cam->rot_speed * (-1)) - cam->plane_y * 
		sin(cam->rot_speed * (-1));
	cam->plane_y = old_plane_x * sin(cam->rot_speed * (-1)) + cam->plane_y * 
		cos(cam->rot_speed * (-1));
}

void	rotate(t_env *env)
{
if (env->move->turn_left == 1)
	rotate_left(env->player, env->cam);
if (env->move->turn_right == 1)
	rotate_right(env->player, env->cam);
}
