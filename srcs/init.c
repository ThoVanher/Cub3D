#include <stdio.h>
#include "../includes/cub3d.h"

void	init_dir_player(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	init_dir_plane_cam(t_cam *cam, t_player *player)
{
	if (player->dir == 'N')
	{
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	if (player->dir == 'S')
	{
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
	if (player->dir == 'E')
	{
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
	if (player->dir == 'W')
	{
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
}

void init_dir_player_and_cam(t_cam *cam, t_player *player)
{
init_dir_player(player);
init_dir_plane_cam(cam, player);
}
