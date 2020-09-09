#include "../includes/cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	exit_prog(t_env *env)
{
	env->error = ESC_GAME;
	free_all(env);
	exit(0);
return (1);
}

int	play(t_env *env)
{
	mlx_hook(env->win->mlx_win, 2, 1, key_press, env->move);
	mlx_hook(env->win->mlx_win, 3, 2, key_release, env->move);
	mlx_hook(env->win->mlx_win, 17, 0, exit_prog, env);
	mlx_loop_hook(env->win->mlx_ptr, &create_image, env);
	mlx_loop(env->win->mlx_ptr);
	return (1);
}

int	init_game(t_env *env)
{
	if (!(env->win->mlx_ptr = mlx_init()))
	{
		error_messages_init(env, 1);
		return (EXIT);
	}
	if (!(env->win->mlx_win = mlx_new_window(env->win->mlx_ptr, 
					env->info->resol_x, env->info->resol_y, "Cub3D")))
	{
		error_messages_init(env, 2);
		return (EXIT);
	}
	if (init_textures(env->info, env->win, env->textures, env))
	{
		error_messages_init(env, 3);
		return (EXIT);
	}
	init_dir_player_and_cam(env->cam, env->player);
	if (env->save)
		create_image(env);
	else 
		play(env);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_env		*env;

	env = 0;
	if (!(env = malloc_environnement()))
		return (0);
	if (env->error)
	{
		free_malloc_failed(env);
		return (0);
	}
	if (argc == 1 || argc > 3)
		error_messages_arguments(env, 1);
	if (!env->error && !check_file_extension(argv[1]))
		error_messages_arguments(env, 2);
	if (!env->error && argc == 3  && ft_strncmp(argv[2], "--save", 6) != 0)
		error_messages_arguments(env, 3);
	if (!env->error)
		parse(argv[1], env);
	if (argc == 3)
		env->save = 1;
	if (!env->error)
		init_game(env);
	free_all(env);
	return (0);
} 
