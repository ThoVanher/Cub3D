NAME = cub3D

SRCS =	srcs/cub3D.c srcs/save.c srcs/libft.c srcs/parse_info.c srcs/parse_info2.c srcs/rotate_camera.c srcs/move_player.c srcs/key_request.c srcs/check_file.c srcs/utils.c srcs/utils2.c gnl/get_next_line.c gnl/get_next_line_utils.c srcs/expose.c srcs/raycast.c srcs/init.c srcs/textures.c srcs/sprites.c srcs/malloc_and_free.c srcs/errors.c\

OBJS = $(SRCS:.c=.o)

INCLUDE = -I.

CC = gcc
FLAGS = -Wall -Werror -Wextra -I$(INCLUDE)
RM = rm -rf
LIBS = -L ./mlx -lmlx -framework OpenGL -framework Appkit 

all : $(NAME)

$(NAME) : $(OBJS)
		make -C mlx
		$(CC) -o $(NAME) $(FLAGS) $(OBJS) $(LIBS)  

clean : 
	make clean -C mlx
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all

.PHONY : re clean fclean all
