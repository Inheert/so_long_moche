/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:56:22 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/17 15:01:15 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define MALLOC_ERROR "Malloc error.\n\0"
# define MALLOC_OVEFLOW "Malloc overflow.\n\0"
# define NO_VALID_ARGS_COUNT "Args count is no equal to 2.\n\0"
# define NO_VALID_ARG "Arg don't have .ber extension or dont have a valid \
path\n\0"
# define MAP_TOO_LARGE "Map size is too large.\n\0"
# define NO_VALID_MAP "Map is not valid.\n\0"
# define NO_VALID_MAP_LINE_LEN "Map line len is not equal to the first \
line len\n\0"
# define UNKNOW_MAP_SYMBOL "Unknow map symbol.\n\0"
# define MISSING_SYMBOL "There is missing symbols (start, exit or \
collectible).\n\0"
# define TOO_MANY_SYMBOLS "There is too many symbols (start, exit or \
collectible).\n\0"
# define NO_VALID_PATH "Map have no valid path.\n\0"
# define MLX_ERROR "A problem has occured when using MLX.\n\0"
# define MLX_IMG_ERROR "A problem has occured when using MLX image.\n\0"
# define MLX_WIN_WIDTH 2100
# define MLX_WIN_HEIGHT 2100

# define MLX_MAX_MAP_WIDTH 50
# define MLX_MAX_MAP_HEIGHT 50

# define EMPTY_SLOT_COLOR 0x00FFFFFF
# define WALL_SLOT_COLOR 0x006666FF
# define PLAYER_SLOT_COLOR 0x00FF6633
# define COLLECTIBLE_SLOT_COLOR 0x0066FFFF
# define EXIT_SLOT_COLOR 0x009900FF

typedef enum s_garbage_action
{
	INIT,
	ADD,
	ADD_TEXTURE,
	ADD_IMG,
	DELETE,
	DELETE_TEXTURE,
	CLEAR,
	DISPLAY,
}	t_garbage_action;

typedef struct s_garbage
{
	void				*content;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_check_symbols
{
	int		is_exit_exist;
	int		is_start_exist;
	int		is_collectible_exist;
}	t_check_symbols;

typedef struct s_map
{
	char			slot[2];
	int				x;
	int				y;
	bool			is_end;
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*upper;
	struct s_map	*below;
}	t_map;

typedef struct s_map_info
{
	mlx_t			*mlx;
	t_map			*map;
	int				map_width;
	int				map_height;
	int				slot_width;
	int				slot_height;
	mlx_image_t		*img;
}	t_map_info;

ssize_t		str_ptr_len(char **str);
void		*ft_malloc(size_t size, size_t nmemb);
void		raise_error(char *error, void *ptr);
void		garbage_collector(t_garbage_action action, void *ptr);
void		check_args(int argc, char **argv);
char		*ft_strjoin_enhanced(char *s1, char *s2);
char		*get_full_path(char *filename);
int			is_valid_symbol(char symbol[2]);
int			is_wall_valid(t_map *map);
int			is_char_missing(t_map *map, t_map *tmp);
int			is_valid_path_exist(t_map *map);
int			is_valid_char_number(t_map *map);

void		close_mlx(void *ptr);
void		start_mlx(t_map_info *map_info);
void		init_mlx_hooks(mlx_t *mlx, t_map_info *map_info);
void		draw_pixels(t_map_info *map_info, int x, int y, uint32_t color);
void		moove_player(int x_dir, int y_dir, t_map_info *map_info);

t_map_info	*map_parsing(char *filename);
t_map		*map_new(char slot[2]);
t_map		*copy_map(t_map *map);
t_map		*get_player_pos(t_map *map);
int			*get_map_len(t_map *map);
void		map_add_right(t_map **map, t_map *new);
void		map_add_below(t_map **map, t_map *new);
void		map_link_lines(t_map *first_line, t_map *second_line);

#endif
