#include "mlx.h"
#include <stdio.h>
#include "test.h"
#include <stdlib.h>
#include "../includes/cub3d.h"
int create_image(t_storage *storage)
{
	int i;
	int j;
	int res;
	char *im_data;
	int bpp;
	int size_line;
	int endian;
	void *mlx_image;
	i = 0;
	j = 0;
	printf("%p\n", storage->mlx_ptr);
	mlx_image = mlx_new_image(storage->mlx_ptr, 400, 400);
	printf("%p\n", storage->mlx_ptr);
	im_data = mlx_get_data_addr(mlx_image, &bpp, &size_line, &endian);
	printf("%p\n", storage->mlx_ptr);
	while (i < 400)
	{
		while (j < 400)
		{
			res = 4*i + 4*400*j;
			if (i <= 200 && j <= 200)
			{
				im_data[res] = (char)255 - (255 * (1 - storage->l));
				im_data[res + 1] = (char)255 - (255 * (1 - storage->l));
				im_data[res + 2] = (char)255 - (255 * storage->l);
			}
			else if (i > 200 && j <= 200)
			{
				im_data[res] = (char)255 - (255 * storage->l);
				im_data[res + 1] = (char)255 - (255 * (1 - storage->l));
				im_data[res + 2] = (char)255 - (255 * (1 - storage->l));
			}
			else if (i > 200 && j > 200)
			{
				im_data[res] = (char)255 - (255 * storage->l);
				im_data[res + 1] = (char)255 - (255 * storage->l);
				im_data[res + 2] = (char)255 - (255 * storage->l);
			}
			else
			{
				im_data[res] = (char)255 - (255 * (1 - storage->l));
				im_data[res + 1] = (char)255 - (255 * storage->l);
				im_data[res + 2] = (char)255 - (255 * (1 - storage->l));
			}
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(storage->mlx_ptr, storage->mlx_win, mlx_image, 0, 0);
	printf("%p\n", storage->mlx_ptr);
	return (0);
}

int key_press(int keycode, void *s)
{
	t_storage *storage;

	storage = (t_storage *)s;
	if (keycode == 126)
		storage->l = 1;
	create_image(storage);
	return (0);
}

int key_release(int keycode, t_storage *storage)
{
	if (keycode == 126)
		storage->l = 0;
	create_image(storage);
	return (0);
}

int main()
{
	t_storage *storage;

	if (!(storage = (t_storage *)malloc(sizeof(t_storage))))
	return (0);
	storage->l = 0;
	storage->mlx_ptr = mlx_init();
	storage->mlx_win = mlx_new_window(storage->mlx_ptr, 400, 400, "fenetre test");
	create_image(storage);
	mlx_hook(storage->mlx_win, 2, 1, key_press, storage);
	mlx_hook(storage->mlx_win, 3, 2, key_release, storage);
	mlx_loop_hook(storage->mlx_ptr, create_image, storage);
	mlx_loop(storage->mlx_ptr);
	return (0);
}
