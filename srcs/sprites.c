#include "../includes/cub3d.h"
#include <stdio.h>

void	sort_sprites(int *sprite_order, double *sprite_distance, int sprite_nb)
{
	int i;
	int tmp_order;
	double tmp_dist;

	i = 0;
	while (i < sprite_nb - 1)
	{
		if (sprite_distance[i] < sprite_distance[i + 1])
		{
			tmp_dist = sprite_distance[i];
			sprite_distance[i] = sprite_distance[i + 1];
			sprite_distance[i + 1] = tmp_dist;
			tmp_order = sprite_order[i];
			sprite_order[i] = tmp_order;
			sprite_order[i] = sprite_order[i + 1];
			sprite_order[i + 1] = tmp_order;
			i = -1;
		}
		i++;
	}
}

void	dist_player_sprites(t_env *env, int *sprite_order, double *sprite_distance)
{
	int i;

	i = 0;

	while (i < env->info->nb_sprite)
	{
		sprite_distance[i] = (env->player->x - env->sprites[i].x) * (env->player->x - env->sprites[i].x) + (env->player->y - env->sprites[i].y) * (env->player->y - env->sprites[i].y);
		sprite_order[i] = i;
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, env->info->nb_sprite);
}

void	size_sprite(t_sprite_info *s_i, t_sprite *sprites, int *sprite_order, t_env *e)
{
	s_i->x = sprites[sprite_order[s_i->i]].x - e->player->x;
	s_i->y = sprites[sprite_order[s_i->i]].y - e->player->y;
	s_i->inv_det = 1.0 / (e->cam->plane_x * e->player->dir_y - e->player->dir_x *e->cam->plane_y);
	s_i->transformx = s_i->inv_det * (e->player->dir_y * s_i->x - e->player->dir_x * s_i->y);
	s_i->transformy = s_i->inv_det * (-e->cam->plane_y * s_i->x + e->cam->plane_x * s_i->y);
	s_i->screenx = (int)((e->info->resol_x / 2) * (1 + s_i->transformx / s_i->transformy));
	s_i->height = abs((int)(e->info->resol_y / (s_i->transformy)));
	s_i->drawstart_y = -s_i->height / 2 + e->info->resol_y / 2;
	if (s_i->drawstart_y < 0)
		s_i->drawstart_y = 0;
	s_i->drawend_y = s_i->height / 2 + e->info->resol_y / 2;
	if (s_i->drawend_y >= e->info->resol_y)
		s_i->drawend_y = e->info->resol_y - 1;
	s_i->width = abs((int)(e->info->resol_y / s_i->transformy));
	s_i->drawstart_x = -s_i->width / 2 + s_i->screenx;
	if (s_i->drawstart_x < 0)
		s_i->drawstart_x = 0;
	s_i->drawend_x = s_i->width / 2 + s_i->screenx;
	if (s_i->drawend_x >= e->info->resol_x)
		s_i->drawend_x = e->info->resol_x - 1;
}

int is_black(int texx, int texy, t_textures textures)
{
	int res;

	res = 4*texx + 4*64*texy;
	if (textures.im[res] == 0 && textures.im[res + 1] == 0 && textures.im[res + 2] == 0)
		return (1);
	else 
		return (0);
}

void put_stripe_in_image(t_env *env, char *image, t_sprite_info *s_i, int y, int stripe)
{
	int res;
	int res2;
	int d;

	d = y * 256 - env->info->resol_y * 128 + s_i->height * 128;
	s_i->texy = ((d * env->info->tex_height) / s_i->height) / 256;
	if (!is_black(s_i->texx, s_i->texy, env->textures[4]))
	{
		res = y * env->info->resol_x * 4 + stripe * 4;
		res2 = s_i->texy * env->textures[4].size_line + s_i->texx * env->textures[4].bpp/8;
		image[res] = env->textures[4].im[res2];
		image[res + 1] = env->textures[4].im[res2 + 1];
		image[res + 2] = env->textures[4].im[res2 + 2];
		image[res + 3] = env->textures[4].im[res2 + 3];
	}
}

void	draw_sprite(t_env *env, t_sprite_info *s_i, char *image, int *sprite_order)
{
	int stripe;
	int y;
	int d;
	t_sprite	*sprite;

	stripe = s_i->drawstart_x;
	while (stripe < s_i->drawend_x)
	{
		if (s_i->transformy > 0  && s_i->transformy < env->zbuffer[stripe])
		{
			y = s_i->drawstart_y;
			s_i->texx = (int)((256 * (stripe - (-s_i->width / 2 + s_i->screenx)) * env->info->tex_width / s_i->width) / 256);
			while (y < s_i->drawend_y)
			{
				put_stripe_in_image(env, image, s_i, y, stripe);
				y++;
			}
		}
		stripe++;
	}
}

void	sprite(t_env *env, char *image)
{
	int		sprite_order[env->info->nb_sprite];
	double	sprite_distance[env->info->nb_sprite];
	t_sprite_info s_i;
	int i;

	i = 0;
	dist_player_sprites(env, sprite_order, sprite_distance);
	s_i.i = 0;
	while (s_i.i < env->info->nb_sprite)
	{
		size_sprite(&s_i, env->sprites, sprite_order, env);
		draw_sprite(env, &s_i, image, sprite_order);
		s_i.i++;
	}
}

