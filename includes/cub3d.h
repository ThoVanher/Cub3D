#ifndef CUB3D_H
 #define CUB3D_H

# include <sys/types.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "get_next_line.h"
# include <unistd.h>

# define SUCCESS 1
# define EXIT 0
# define ESC_GAME 18

typedef struct	s_info
{
	char		**map;
	int			length_x;
	int			length_y;
	int			resol_x;
	int			resol_y;
	int			h;
	char		*north_tex;
	char		*south_tex;
	char		*east_tex;
	char		*west_tex;
	char		*sprite_tex;
	int 		tex_width;
	int 		tex_height;
	int			color_f[3];
	int			color_c[3];
	int			nb_sprite;
}				t_info;

typedef struct	s_player
{
	char		dir;
	int			nb_dir;
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		step;
}				t_player;

typedef struct	s_cam
{
	double		plane_x;
	double		plane_y;
	double		cam_x;
	double		ray_x;
	double		ray_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	double		rot_speed;
}				t_cam;

typedef struct	s_wall
{
	int			wall_x;
	int			wall_y;
	double		distance;
	int			eight_persp;
	char		orientation;
	int			start;
	int			end;
	int			side;
	double		wall_hit_x;
	int			tex_x;
	double		step_tex;
}				t_wall;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_image;
	int			bpp;
	int			size_line;
	int			endian;
	char		*image;
}				t_window;

typedef struct s_textures
{
	void		*ptr;
	char		*im;
	int			bpp;
	int			size_line;
	int			endian;
}				t_textures;

typedef struct s_move
{
	int			esc;
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
}				t_move;

typedef struct s_sprite
{
	double 		x;
	double 		y;
}				t_sprite;

typedef struct s_sprite_info
{
	double 		x;
	double 		y;
	double 		inv_det;
	double 		transformx;
	double 		transformy;
	int			screenx;
	int 		height;
	int 		width;
	int 		drawstart_x;
	int 		drawend_x;
	int 		drawstart_y;
	int 		drawend_y;
	int 		texx;
	int 		texy;
	int 		i;
}			t_sprite_info;

typedef struct	s_env
{
	t_info		*info;
	t_player	*player;
	t_cam		*cam;
	t_wall		*wall;
	t_window	*win;
	t_move		*move;
	t_textures	textures[5];
	t_sprite	sprites[500];
	int			save;
	int			map;
	int			error;
	double		*zbuffer;
}				t_env;

int				ft_atoi(const char *str);
char			*ft_strtrim(char *line, char c);
int				ft_isdigit(int c);
int				ft_strlen(char *str);
char			*ft_substr(const char *src, unsigned int start, size_t len);
void			*ft_bzero(void *b, size_t len);
char			**ft_split(const char *str, char c);
t_env			*malloc_environnement(void);
void 			ft_putstr_fd(char *str, int fd);
void 			error_messages_parsing(t_env *env, int error);
void 			error_messages_arguments(t_env *env, int error);
void 			error_messages_init(t_env *env, int error);
void 			error_messages_syst(t_env *env, int error);
int 			parse(char *map, t_env *env);
int				check_all_infos(t_env *env);
int				parse_map(t_info *info, char *line, int fd);
void 			free_info(t_info *info);
char 			*parse_info(t_env *env, int fd);
int				create_image(t_env *env);
int				raycast(t_env *env, char *image);
void			color_pixel(char *image, int tab[3], int res);
void			init_dir_player_and_cam(t_cam *cam, t_player *player);
int				init_textures(t_info *info, t_window *win, t_textures *text,
				t_env *env);
void			get_tex_x(t_wall *wall, t_player *player, t_cam *cam);
void			draw_tex_column(char *image, t_env *e, t_textures texts, int i);
void			move_player(t_player *pl, t_info *inf, t_move *mov, t_cam *cam);
int				key_press(int key_code, t_move *move);
int				key_release(int key_code, t_move *move);
void			rotate(t_env *env);
void			sprite(t_env *env, char *image);
void			ft_putstr_fd(char *str, int fd);
void			free_all(t_env *env);
void			free_malloc_failed(t_env *env);
void			ft_putchar_fd(char c, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				check_file_extension(char *file);
int				save(t_env *env, char *image);
#endif
