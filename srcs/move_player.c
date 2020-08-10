#include "../includes/cub3d.h"

void	move_player_left(t_player *player, t_info *info, t_cam *cam)
{
	if (cam->plane_x >= 0)
	{
		if ((player->x - cam->plane_x * player->step > (int)player->x) ||
			(info->map[(int)player->y][(int)player->x - 1] == '0'))
				player->x = player->x - cam->plane_x * player->step;
		}
	else
	{
		if ((player->x - cam->plane_x * player->step < (int)player->x + 1)
			|| (info->map[(int)player->y][(int)player->x + 1] == '0'))
				player->x = player->x - cam->plane_x * player->step;
		}
	if (cam->plane_y >= 0)
	{
		if ((player->y - cam->plane_y * player->step > (int)player->y) ||
			(info->map[(int)player->y - 1][(int)player->x] == '0'))
				player->y = player->y - cam->plane_y * player->step;
		}
	else
	{
		if ((player->y -cam-> plane_y * player->step < (int)player->y + 1) ||
			(info->map[(int)player->y + 1][(int)player->x] == '0'))
				player->y = player->y - cam->plane_y * player->step;
		}
}

void	move_player_right(t_player *player, t_info *info, t_cam *cam)
{
	if (cam->plane_x >= 0)
	{
		if ((player->x + cam->plane_x * player->step < (int)player->x + 1) ||
			(info->map[(int)player->y][(int)player->x + 1] == '0'))
				player->x = player->x + cam->plane_x * player->step;
		}
	else
	{
		if ((player->x + cam->plane_x * player->step < (int)player->x)
			|| (info->map[(int)player->y][(int)player->x -1] == '0'))
				player->x = player->x + cam->plane_x * player->step;
		}
	if (cam->plane_y >= 0)
	{
		if ((player->y + cam->plane_y * player->step < (int)player->y + 1) ||
			(info->map[(int)player->y + 1][(int)player->x] == '0'))
				player->y = player->y + cam->plane_y * player->step;
		}
	else
	{
		if ((player->y + cam->plane_y * player->step > (int)player->y) ||
			(info->map[(int)player->y + 1][(int)player->x] == '0'))
				player->y = player->y - cam->plane_y * player->step;
		}
}

void	move_player_forward(t_player *player, t_info *info)
{
	if (player->dir_x >= 0)
	{
		if ((player->x + player->dir_x * player->step < (int)player->x + 1)
				|| (info->map[(int)player->y][(int)player->x + 1] == '0'))
			player->x = player->x + player->dir_x * player->step;
	}
	else
	{
		if ((player->x + player->dir_x * player->step > (int)player->x)
				|| (info->map[(int)player->y][(int)player->x - 1] == '0'))
			player->x = player->x + player->dir_x * player->step;
	}
	if (player->dir_y >= 0)
	{
		if ((player->y + player->dir_y * player->step < (int)player->y + 1)
				|| (info->map[(int)player->y + 1][(int)player->x] == '0'))
			player->y = player->y + player->dir_y * player->step;
	}
	else
	{
		if ((player->y + player->dir_y * player->step > (int)player->y)
				|| (info->map[(int)player->y - 1][(int)player->x] == '0'))
			player->y = player->y + player->dir_y * player->step;
	}
}

void	move_player_backward(t_player *player, t_info *info)
{
	if (player->dir_x >= 0)
	{
		if ((player->x - player->dir_x * player->step < (int)player->x)
				|| (info->map[(int)player->y][(int)player->x - 1] == '0'))
			player->x = player->x - player->dir_x * player->step;
	}
	else
	{
		if ((player->x - player->dir_x * player->step < (int)player->x + 1)
				|| (info->map[(int)player->y][(int)player->x + 1] == '0'))
			player->x = player->x - player->dir_x * player->step;
	}
	if (player->dir_y >= 0)
	{
		if ((player->y - player->dir_y * player->step > (int)player->y)
				|| (info->map[(int)player->y - 1][(int)player->x] == '0'))
			player->y = player->y - player->dir_y * player->step;
	}
	else
	{
		if ((player->y - player->dir_y * player->step < (int)player->y + 1)
				|| (info->map[(int)player->y + 1][(int)player->x] == '0'))
			player->y = player->y - player->dir_y * player->step;
	}
}

void move_player(t_player *player, t_info *info, t_move *mov, t_cam *cam)
{
if (mov->left == 1)
move_player_left(player, info, cam);
else if (mov->right == 1)
move_player_right(player, info, cam);
else if (mov->forward == 1)
move_player_forward(player, info);
else if (mov->backward == 1)
move_player_backward(player, info);
}
