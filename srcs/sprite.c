#include "../includes/cub3d.h"

int get_nb_sprite_and_pos(t_env *env)
{
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	n = 0;
	while (env->info->map[i])
	{
		while (env->info->map[i][j] && env->info->nb_sprite < 100)
		{
			if (env->info->map[i][j] == '2')
			{
				env->sprites[n].x = j + 0.5;
				env->sprites[n].y = i + 0.5;
				env->info->nb_sprite++;
				n++;
			}
		j++;
		}
	i++;
	}
	if (env->info->nb_sprite > 100)
		return (0);
return (1);
}
