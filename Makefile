NAME = cub3D

SRCS = srcs/parse_info.c srcs/rotate_camera.c srcs/move_player.c srcs/key_request.c srcs/parse_info2.c srcs/check_info.c srcs/utils.c srcs/utils2.c gnl/get_next_line.c gnl/get_next_line_utils.c srcs/expose.c srcs/raycast.c srcs/init.c srcs/textures.c srcs/sprite.c srcs/sprites.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I.

CC = gcc
FLAGS = -Wall -Werror -Wextra -I$(INCLUDE)
RM = rm -rf
MLX = -L ./mlx -lmlx -framework OpenGL -framework Appkit

all : $(NAME)

$(NAME) : $(OBJS)
		make -C mlx
		$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(MLX)

clean : 
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all

.PHONY : re clean fclean all
