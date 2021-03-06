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
	if (a == 'S' && b == ' ')
		i++;
	else 
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
	char *res2;
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
		res2 = ft_strtrim(line, ' ');
		res = ft_strjoin(res, res2);
		free (tmp);
		tmp = res;
		res = ft_strjoin(res, "%");
		free (tmp);
		free(res2);
	}
	info->map = ft_split(res, '%');
	free(res);
	free(line);
	return (0);
}

char *parse_info(t_env *env, int fd)
{
	char *lne;
	int i;

	while ((!env->map) && get_next_line(fd, &lne))
	{ 
		i = 0;
		while (lne[i] && lne[i] == ' ')
			i++;
		if (lne[i] == 'R')
			get_resolution(env->info, lne, i + 1);
		if (lne[i] == 'N' || lne[i] == 'S' || lne[i] == 'E' || lne[i] == 'W')
			get_path_tex(env->info, lne, i);
		if (lne[i] == 'F')
			get_color(env->info->color_f, lne, i + 1);
		if (lne[i] == 'C')
			get_color(env->info->color_c, lne, i + 1);
		if (lne[i] == '1' || lne[i] == '2' || lne[i] == '0')
			env->map = 1;
		if (!env->map)
			free(lne);
	}
	if (!env->map)
		env->error = 1;
	return (ft_strtrim(lne, ' '));
}
