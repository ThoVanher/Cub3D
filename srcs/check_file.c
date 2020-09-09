#include "../includes/cub3d.h"
#include <stdio.h>

int	check_file_extension(char *file)
{
	int len;

	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".cub", 4) != 0)
		return (EXIT);
	return (SUCCESS);
}

int check_map_closed(t_info *info, t_player *player, int i, int j)
{
	char **map;

	map = info->map;
	if (!i || (i && map[i - 1][j] == ' '))
		return (0);
	else if (!map[i + 1] || (map[i + 1] && map[i + 1][j] == ' '))
		return (0);
	else if (!j || (j && map[i][j - 1] == ' '))
		return (0);
	else if (!map[i][j + 1] || (map[i][j + 1] && map[i][j + 1] == ' '))
		return (0);
	if (map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != '2')
	{
		player->dir = map[i][j];
		player->x = (double)(j) + 0.5;
		player->y = (double)(i) + 0.5;
		info->map[i][j] = '0';
		player->nb_dir++;
		if (player->nb_dir != 1)
			return (-1);
	}
	return (SUCCESS);
}

int check_map(t_info *info, t_player *player)
{
	int i;
	int j;
	int ret;
	char **map;

	i = -1;
	j = -1;
	map = info->map;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '2' &&
					map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' &&
					map[i][j] != 'W' && map[i][j] != ' ')
				return (2);
			if (map[i][j] != '1' && map[i][j] != ' ' &&
					(ret = check_map_closed(info, player, i, j)) != 1)
				return (ret);
		}
		j = -1;
	}
	if (!player->nb_dir)
		return (-1);
	return (SUCCESS);
}

int	check_all_infos(t_env *env)
{
	int ret;
	if (env->error)
	{
		error_messages_parsing(env, 1);
		return (EXIT);
	}
	ret = check_map(env->info, env->player);
	if (!env->error && (env->info->color_c[0] == -1 || 
				env->info->color_f[0] == -1))
		error_messages_parsing(env, 2);
	if (!env->error && ret == 0)
		error_messages_parsing(env, 3);
	if (!env->error && ret == 2)
		error_messages_parsing(env, 4);
	if (!env->error && ret == -1)
		error_messages_parsing(env, 5);
	if (env->error)
		return (EXIT);
	return (SUCCESS);
}
