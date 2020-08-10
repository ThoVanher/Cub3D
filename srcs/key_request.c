#include "../includes/cub3d.h"

int key_press(int key_code, t_move *move)
{
if (key_code == 53)
		move->esc = 1;
	else if (key_code == 13)
		move->forward = 1;
	else if (key_code == 1)
		move->backward = 1;
	else if (key_code == 8)
		move->left = 1;
	else if (key_code == 8)
		move->right = 1;
	else if (key_code == 2)
		move->turn_left = 1;
	else if (key_code == 0)
		move->turn_right = 1;
return (0);
}

int key_release(int key_code, t_move *move)
{
	if (key_code == 53)
		move->esc = 0;
	else if (key_code == 13)
		move->forward = 0;
	else if (key_code == 1)
		move->backward = 0;
	else if (key_code == 8)
		move->left = 0;
	else if (key_code == 8)
		move->right = 0;
	else if (key_code == 2)
		move->turn_left = 0;
	else if (key_code == 0)
		move->turn_right = 0;
return (0);
}
