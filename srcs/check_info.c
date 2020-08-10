#include "../includes/cub3d.h"
#include <stdio.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
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
		if (player->nb_dir > 1)
			return (-1);
	}
	return (1);
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
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '2' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != ' ')
				return (2);
			if (map[i][j] != '1' && map[i][j] != ' ' &&
					(ret = check_map_closed(info, player, i, j)) != 1)
				return (ret);
		}
		if (j > info->length_x)
			info->length_x = j;
		j = -1;
	}
	info->length_y = i;
	return (1);
}

int	parsing_errors(t_info *info, t_player *player)
{
	int ret;

	ret = check_map(info, player);
	if (info->color_c[0] == -1 || info->color_f[0] == -1)
	{
		ft_putstr_fd("Error\nCeiling and/or floor color(s) invalid\nEnter RGB values between 0 and 255\n", 1);
		ret = -2;
	}
	if (!ret)
		ft_putstr_fd("Error\nMap not closed\n", 1);
	if (ret == 2)
		ft_putstr_fd("Error\nInvalid character in map\n", 1);
	if (ret == -1)
		ft_putstr_fd("Error\nTwo (or more) start position\n", 1);
	if (ret != 1)
	{
		free_info(info);
		free(player);
		return (0);
	}
	return (1);
}
