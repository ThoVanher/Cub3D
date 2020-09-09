#include "../includes/cub3d.h"
#include <stdio.h>

void	error_messages_parsing(t_env *env, int error)
{
	env->error = 2;
	if (error == 1)
	{
		ft_putstr_fd("Error\nMap is missing in [*.cub] file\n", 1);
		env->error = 1;
	}
	if (error == 2)
	{
		ft_putstr_fd("Error\nCeiling and/or floor color(s) invalid\n", 1);
		ft_putstr_fd("Enter RGB values between 0 and 255\n", 1);
	}
	if (error == 3)
		ft_putstr_fd("Error\nMap not closed\n", 1);
	if (error == 4)
		ft_putstr_fd("Error\nInvalid character in map\n", 1);
	if (error == 5)
	{
		ft_putstr_fd("Error\nPlease enter a start position with 'N', 'S'", 1);
		ft_putstr_fd(", 'E', 'W' on map. Not none, not two, only one.\n", 1);
	}
	if (error == 6)
		ft_putstr_fd("Error\nToo many sprites, maximum 500\n" ,1);
}

void	error_messages_init(t_env *env, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Error\nmlx_init failed\n", 1);
		env->error = 2;
	}
	if (error == 2)
	{
		ft_putstr_fd("Error\nmlx_new_window failed\n" ,1);
		env->error = 3;
	}
	if (error == 3)
	{
		ft_putstr_fd("Error\nTextures loading failed, check paths of " ,1);
		ft_putstr_fd("the differents textures\n" ,1);
	}
}

void	error_messages_arguments(t_env *env, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Error\nProgram needs one or two arguments to be run:", 1);
		ft_putstr_fd("\nthe first one is a [*.cub] file", 1);
		ft_putstr_fd("\nthe second one (optionnal) is the option --save\n", 1);
	}
	if (error == 2)
		ft_putstr_fd("Error\nFirst argument need to be a [*.cub] file\n", 1);
	if (error == 3)
		ft_putstr_fd("Error\nSecond argument can be only option '--save'\n", 1);
	env->error = 1;
}

void	error_messages_syst2(t_env *env, int error)
{
	if (error == 5)
	{
		ft_putstr_fd("Error\nMalloc element 'win' of env failed", 1);
		env->error = 5;
	}
	if (error == 6)
	{
		ft_putstr_fd("Error\nMalloc element 'mov' of env failed", 1);
		env->error = 6;
	}
	if (error == 8)
		ft_putstr_fd("Error\nopen [*.xpm] sprite file failed\n" ,1);
	if (error == 9)
		ft_putstr_fd("Error\nclose [*.xpm] sprite file failed\n" ,1);
	if (error == 10)
		ft_putstr_fd("Error\nopen [*.cub] file failed\n" ,1);
	if (error == 11)
		ft_putstr_fd("Error\nclose [*.cub] file failed\n" ,1);
	if (error >= 8 && error <= 11)
		env->error = -1;
}

void	error_messages_syst(t_env *env, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Error\nMalloc element 'info' of env failed", 1);
		env->error = 1;
	}
	if (error == 2)
	{
		ft_putstr_fd("Error\nMalloc element 'player' of env failed", 1);
		env->error = 2;
	}
	if (error == 3)
	{
		ft_putstr_fd("Error\nMalloc element 'cam' of env failed", 1);
		env->error = 3;
	}
	if (error == 4)
	{
		ft_putstr_fd("Error\nMalloc element 'wall' of env failed", 1);
		env->error = 4;
	}
	error_messages_syst2(env, error);
}
