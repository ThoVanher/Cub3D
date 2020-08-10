#include "../includes/cub3d.h"
#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	free_info(t_info *info)
{
	int i = 0;
	while (info->map[i])
	{
		free(info->map[i]);
		i++;
	}
	free (info->map);
	free(info->north_tex);
	free(info->south_tex);
	free(info->east_tex);
	free(info->west_tex);
	free(info->sprite_tex);
	free(info);
}

int	init_game(t_env *env)
{
	env->win->mlx_ptr = mlx_init();
	env->win->mlx_win = mlx_new_window(env->win->mlx_ptr, env->info->resol_x, env->info->resol_y, "Cub3D");
	init_dir_player_and_cam(env->cam, env->player);
	get_nb_sprite_and_pos(env);
	if (!(init_textures(env->info, env->win, env->textures)))
		return (0);
	mlx_hook(env->win->mlx_win, 2, 1, key_press, env->move);
	mlx_hook(env->win->mlx_win, 3, 2, key_release, env->move);
	mlx_loop_hook(env->win->mlx_ptr, &create_image, env);
	mlx_loop(env->win->mlx_ptr);
	return (1);
}

int	parse(char *map, t_info *info, t_player *player)
{
	char *first_map_line;
	int fd;

	fd = open(map, O_RDONLY);
	first_map_line = parse_info(info, fd);
	parse_map(info, first_map_line, fd);
	if (!parsing_errors(info, player))
		return (0);
	return (1);
}

int	malloc_environnement2(t_env *env)
{
	t_window	*win;
	t_move		*move;

	if (!(win = (t_window *)malloc(sizeof(t_window))) || !(move = (t_move *)malloc(sizeof(t_move))))
	{
		ft_putstr_fd("Error\nMalloc failed", 1);
		return (0);
	}
	ft_bzero(win, sizeof(t_window));
	ft_bzero(move, sizeof(t_move));
	env->win = win;
	env->move = move;
	return (1);
}

t_env	*malloc_environnement()
{
	t_env		*env;
	t_info		*info;
	t_player	*player;
	t_cam		*cam;
	t_wall		*wall;


	if(!(info = (t_info*)malloc(sizeof(t_info))) || 
			!(player = (t_player *)malloc(sizeof(t_player))) || 
			!(cam = (t_cam *)malloc(sizeof(t_cam))) || 
			!(wall = (t_wall *)malloc(sizeof(t_wall))) ||
			!(env = (t_env*)malloc(sizeof(t_env))))
	{
		ft_putstr_fd("Error\nMalloc failed", 1);
		return (0);
	}
	ft_bzero(info, sizeof(t_info));
	ft_bzero(player, sizeof(t_player));
	ft_bzero(cam, sizeof(t_cam));
	ft_bzero(wall, sizeof(t_wall));
	env->info = info;
	env->player = player;
	env->cam = cam;
	env->wall = wall;
	malloc_environnement2(env);
	return (env);
}

int main(int argc, char **argv)
{
	t_env		*env;
	if (argc != 2)
		return (0);
	if (!(env = malloc_environnement()) || !(parse(argv[1], env->info, env->player)))
		return (0);
	init_game(env);
	return (0);
} 
