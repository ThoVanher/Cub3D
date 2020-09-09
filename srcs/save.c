#include "../includes/cub3d.h"
#include <stdio.h>

void	create_file_header(t_env *env, int fd)
{
	int	offset;
	int file_size;

	offset = 54;
	file_size = 54 + 4 * env->info->resol_x * env->info->resol_y;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &offset, 4);
}

void	create_image_header(t_env *env, int fd)
{
	int	image_header_size;
	int	plane;
	int image_size;

	image_header_size = 40;
	plane = 1;
	image_size = 4 * env->info->resol_x * env->info->resol_y;
	write(fd, &image_header_size, 4);
	write(fd, &env->info->resol_x, 4);
	write(fd, &env->info->resol_y, 4);
	write(fd, &plane, 2);
	write(fd, &env->win->bpp, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &image_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 4);
}

void	fill_bitmap(t_env *env, char *image, int fd)
{
	int res;
	int x;
	int y;

	y = env->info->resol_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < env->info->resol_x)
		{
			res = image[4 * x + env->info->resol_x * 4 * y];
			write(fd, &res, 1);
			res = image[4 * x + env->info->resol_x * 4 * y + 1];
			write(fd, &res, 1);
			res = image[4 * x + env->info->resol_x * 4 * y + 2];
			write(fd, &res, 1);
			write(fd, "\0", 1);
			x++;
		}
		y--;
	}
}

int		save(t_env *env, char *image)
{
	int fd;

	fd = open("cub3D.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("Creation of bitmap file failed\n", 1);
		return (0);
	}
	create_file_header(env, fd);
	create_image_header(env, fd);
	fill_bitmap(env, image, fd);
	free(image);
	close(fd);
	return (SUCCESS);
}
