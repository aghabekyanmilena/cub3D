/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:31:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 14:38:13 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define VALID_CHARS "01NSEWD \n"
# define TILE_SIZE 32
# define WIDTH 1440
# define LENGTH 2560
# define texh 256
# define SPEED 0.025
# define STEP 0.0773

//keyboard keys
# define XK_ESCAPE 0xff1b

//walking
# define XK_WL 0x0077
# define XK_AL 0x0061
# define XK_SL 0x0073
# define XK_DL 0x0064
# define XK_A 0x0041
# define XK_D 0x0044
# define XK_W 0x0057
# define XK_S 0x0053
# define XK_LEFT 0xff51
# define XK_RIGHT 0xff53
# define XK_SPACE 0x20

typedef struct s_img
{
	int		wd;
	int		ht;
	int		endian;
	int		line_len;
	int		bits_per_pixel;
	char	*addr;
	void	*img;
}	t_img;

typedef struct s_color
{
	int	r;
	int	b;
	int	g;
}	t_color;

typedef struct s_wall
{
	int		tex_x;
	int		tex_y;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	step;
	double	tex_pos;
}	t_wall;

typedef struct s_ray
{
	double	camera_x;
	double	rayDir_x;
	double	rayDir_y;
	double	sideDist_x;
	double	sideDist_y;
	double	deltaDist_x;
	double	deltaDist_y;
	double	wallDist;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		prev_view;
	char	prev_char;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*texture_paths[4];
	void	*textures[4];
	int		widths[4];
	int		heights[4];
	char	**map;
}	t_data;

typedef struct s_config
{
	t_data		data;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			posX;//players position x and y
	int			posY;
	char		view;//uxxutyuny;
	char		**map;
	int			player_x;
	int			player_y; //sranq
	int			height; // mapi heighty
	int			width;
	int			player_count;
	int			is_open;
	t_player	player; //player structna
	t_ray		ray;
	t_wall		wall;
	t_img		img;
	t_img		south;
	t_img		north;
	t_img		east;
	t_img		west;
	t_img		open_door;
	t_img		closed_door;
	t_img		*up_down;
}	t_config;


// gnl
char	*ft_free_null(char *s);
int		ft_newline_instr(char *s);
char	*ft_strjoinn(char *s1, char *s2, size_t l1, size_t l2);
char	*get_next_line(int fd);

// 6 toxy.c
int		demi_6_toxy(char *line);
int		parse_et_6_toxy(t_config *data, char *line);
int		parse(t_config *data, char **lines, int *start_index);
int		parse_texture(t_config *data, int *flag, char *after_key, char *type);
int		parse_color(t_config *data, int *flag, char *after_key, char *type);

// parse map
int		parse_map(t_config *data, char **lines, int start_index);
bool	check_map(t_config *data);
bool	check_single_spawn(t_config *data);
bool	check_map_closed(t_config *data);

//start
void	start(t_config *config, char **map);

//start_utils
void	init_player_struct(t_config *config);
int		fri(t_config *config);
void	my_pixel_put(t_img *img, int x, int y, unsigned int color);
int		rgb_to_int(t_color c);

//textures
void	get_textures(t_config *config);

//move
int		check(int keycode, t_config *config);

//minimap
void	minimap(t_config *config, int j, int n);

//motion
int		mouse_motion(int x, int y, t_config *config);
void	rotate_view(t_config *config, double angle);
void	open_the_door(t_config *config);
unsigned int	get_pixel(t_img *tex, int x, int y);

//valid_utils
char	*skip_ws(char *s);
int		is_ws_only(char *s);
int		check_filename(char *filename);
int		characker_check(char c);
char	**copy_map(t_config *data);


// free functions
void	free_lines(char **lines);
void	free_map(t_config *data);
void	free_config(t_config *data);
void	free_map_copy(char ***map, int height);

// dfs
int	is_spawn_or_walkable(char c);
bool	dfs_outside(char **map, int row, int col, t_config *data);
int	check_door(char **lines);

// check_map
bool	check_map(t_config *data);




#endif