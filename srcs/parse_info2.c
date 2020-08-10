#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	get_resolution(t_info *info, char *line, int i)
{
	while (line[i] == ' ')
		i++;
	info->resol_x = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	info->resol_y = ft_atoi(&line[i]);
}

void	get_path_tex(t_info *info, char *line, int i)
{
	char a;
	char b;

	a = line[i];
	b = line[i + 1];
	i += 2;
	while (line[i] == ' ')
		i++;
	if (a == 'N' && b == 'O')
		info->north_tex = ft_substr(line, i, 1000);
	if (a == 'S' && b == 'O')
		info->south_tex = ft_substr(line, i, 1000);
	if (a == 'E' && b == 'A')
		info->east_tex = ft_substr(line, i, 1000);
	if (a == 'W' && b == 'E')
		info->west_tex = ft_substr(line, i, 1000);
	if (a == 'S' && b == ' ')
		info->sprite_tex = ft_substr(line, i, 1000);
}

void	get_color(int tab[3], char *line, int i)
{
	while (line[i] == ' ')
		i++;
	tab[0] = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	tab[1] = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	tab[2]  = ft_atoi(&line[i]);
	if (tab[0] < 0 || tab[0] > 255 || tab[1] < 0 || tab[1] > 255 || tab[2] < 0 
			|| tab[2] > 255)
		tab[0] = -1;
}

int	parse_map(t_info *info, char *line, int fd)
{
	char *res;
	char *tmp;
	int len;

	len = ft_strlen(line);
	res = line;
	tmp = res;
	res = ft_strjoin(res, "%");
	free(tmp);
	while (get_next_line(fd, &line))
	{
		tmp = res;
		res = ft_strjoin(res, line);
		free (tmp);
		tmp = res;
		res = ft_strjoin(res, "%");
		free (tmp);
		free(line);
	}
	info->map = ft_split(res, '%');
	free(res);
	free(line);
	return (0);
}

char *parse_info(t_info *info, int fd)
{
	char *line;
	int i;
	int map;

	i = 0;
	map = 0;
	while (!map)
	{
		get_next_line(fd, &line); 
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == 'R')
			get_resolution(info, line, i + 1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			get_path_tex(info, line, i);
		if (line[i] == 'F')
			get_color(info->color_f, line, i + 1);
		if (line[i] == 'C')
			get_color(info->color_c, line, i + 1);
		if (line[i] == '1' || line[i] == '2' || line[i] == '0')
			map = 1;
		if (!map)
			free(line);
	}
	return (line);
}
