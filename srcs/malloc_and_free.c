#include "../includes/cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	free_parsing(t_env *env)
{
	int i;

	i = -1;
	if (env->error >= 2)
	{
		while (env->info->map[++i])
			free(env->info->map[i]);
		free (env->info->map);
		free(env->info->north_tex);
		free(env->info->south_tex);
		free(env->info->east_tex);
		free(env->info->west_tex);
		free(env->info->sprite_tex);
	}
//	free(env->info);
//	free(env->player);
//	free(env->cam);
//	free(env->move);
//	free(env->wall);
//	if (env->error <= 2)
//		free(env);
}

void	free_all(t_env *env)
{
	int i;

	i = -1;
	if (env->error > 0)
		free_parsing(env);
	if (env->error >= 4)
	{
		mlx_clear_window(env->win->mlx_ptr, env->win->mlx_win);
		mlx_destroy_window(env->win->mlx_ptr, env->win->mlx_win);
	}
	if (env->error >= 5)
	{
		while (++i < env->error - 4 && i <= 4)
			free(env->textures[i].ptr);
	}
	i = -1;
	if (env->error >= 10)
	{
		while (++i < env->error - 9 && i <= 4)
			free(env->textures[i].im);
	}
	if (env->error > 2)
		free(env);
}

void	free_malloc_failed(t_env *env)
{
	if (env->error > 1)
		free(env->info);
	if (env->error > 2)
		free(env->player);
	if (env->error > 3)
		free(env->cam);
	if (env->error > 4)
		free(env->wall);
	if (env->error > 5)
		free(env->win);
	free(env);
}

t_env	*malloc_environnement2(t_env *env)
{
	t_cam		*cam;
	t_wall		*wall;
	t_window	*win;
	t_move		*move;

	if(!(cam = (t_cam *)malloc(sizeof(t_cam))))
		error_messages_syst(env, 3);
	if(!(wall = (t_wall *)malloc(sizeof(t_wall))))
		error_messages_syst(env, 4);
	if(!(win = (t_window *)malloc(sizeof(t_window))))
		error_messages_syst(env, 5);
	if(!(move = (t_move *)malloc(sizeof(t_move))))
		error_messages_syst(env, 6);
	if (!env->error) 
	{
		ft_bzero(win, sizeof(t_window));
		ft_bzero(move, sizeof(t_move));
		ft_bzero(cam, sizeof(t_cam));
		ft_bzero(wall, sizeof(t_wall));
		env->win = win;
		env->move = move;
		env->cam = cam;
		env->wall = wall;
	}
	return (env);
}

t_env	*malloc_environnement()
{
	t_env		*env;
	t_info		*info;
	t_player	*player;

	if(!(env = (t_env*)malloc(sizeof(t_env))))
	{
		ft_putstr_fd("Error\nmalloc env failed\n", 1);
		return (EXIT);
	}
	ft_bzero(env, sizeof(t_env));
	if(!(info = (t_info*)malloc(sizeof(t_info))))
		error_messages_syst(env, 1);
	if(!(player = (t_player *)malloc(sizeof(t_player)))) 
		error_messages_syst(env, 2);
	if (!env->error)
	{
		ft_bzero(info, sizeof(t_info));
		ft_bzero(player, sizeof(t_player));
		env->info = info;
		env->player = player;
		malloc_environnement2(env);
	}
	return (env);
}
