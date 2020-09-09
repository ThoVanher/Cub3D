#include "../includes/cub3d.h"
#include <stdio.h>

void	save_sprite(t_env *env, int i, int j, int *n)
{
	env->sprites[*n].x = j + 0.5;
	env->sprites[*n].y = i + 0.5;
	env->info->nb_sprite++;
	(*n)++;
}

int		get_nb_sprite_and_pos(t_env *env)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	while (env->info->map[i])
	{
		j = 0;
		while (env->info->map[i][j])
		{
			if (!env->error && env->info->nb_sprite == 500)
			{
				error_messages_parsing(env, 6);
				return (EXIT);
			}
			if (env->info->map[i][j] == '2')
				save_sprite(env, i, j, &n);
			j++;
		}
		i++;
	}
	return (1);
}

int		get_width_eight_of_sprite(t_env *env)
{
	int fd;
	char *line;
	int i;

	if ((fd = open(env->info->sprite_tex, O_RDONLY)) < 0)
	{
		error_messages_syst(env, 8);
		return (EXIT);
	}
	line = "start";
	i = 0;
	while (line[0] != '"')
		get_next_line(fd, &line);
	while (!ft_isdigit(line[i]))
		i++;
	env->info->tex_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	env->info->tex_height = ft_atoi(&line[i]);
	free(line);
	if (close(fd) == -1)
		error_messages_syst(env, 9);
	return (1);
}

void	verif_resolution(t_info *info)
{
if (info->resol_x < 150 || info->resol_x > 1200)
	info->resol_x = 1200;
if (info->resol_y < 150 || info->resol_y > 675)
	info->resol_y = 675;
}

int	parse(char *map, t_env *env)
{
	char *first_map_line;
	int fd;

	if ((fd = open(map, O_RDONLY)) < 0)
	{
		error_messages_syst(env, 10);
		return (EXIT);
	}
	first_map_line = parse_info(env, fd);
	parse_map(env->info, first_map_line, fd);
	check_all_infos(env);
	get_nb_sprite_and_pos(env);
	verif_resolution(env->info);
	if (!env->error)
		get_width_eight_of_sprite(env);
	if (close(fd) == -1)
		error_messages_syst(env, 11); 
	if (env->error)
		return (EXIT);
	return (SUCCESS);
}
