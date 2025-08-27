/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:31:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/27 14:03:22 by anush            ###   ########.fr       */
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
# include "../libft/libft.h"
# include "get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define VALID_CHARS "01NSEWD \n"
# define TILE_SIZE 32
# define WIDTH 1000
# define LENGTH 1800

//keyboard keys
# define XK_ESCAPE 0xff1b
# define XK_WL 0x0077
# define XK_AL 0x0061
# define XK_SL 0x0073
# define XK_DL 0x0064
# define XK_A 0x0041
# define XK_D 0x0044
# define XK_W 0x0057
# define XK_S 0x0053

typedef struct s_color
{
	int	r;
	int	b;
	int	g;
}	t_color;

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
	char	hit;
	int		side;
}	t_ray;

typedef struct s_player {
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
}	t_player;

typedef struct s_data {
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
	int			height; // mapi heighty
	int			player_count;
	t_player	player;//player structna
	t_ray		ray;
}	t_config;


// valid_map u dfs
char	**copy_map(char **map, int height);
int	is_invalid_tile(char c);
int	qaylelu_tex(char c);
int	dfs(char **map, int x, int y, int max_y);
int	parse_map(t_config *data, char **lines, int start_index);

// gnl
char	*ft_free_null(char *s);
int		ft_newline_instr(char *s);
char	*ft_strjoinn(char *s1, char *s2, size_t l1, size_t l2);
char	*get_next_line(int fd);

// valid.c
int	check_filename(char *filename);
int	demi_6_toxy(char *line);
int	parse_et_6_toxy(t_config *data, char *line);
int	parse(t_config *data, char **lines, int *start_index);
int parse_texture(t_config *data, int *flag, char *after_key, char *type);
int parse_color(t_config *data, int *flag, char *after_key, char *type);
int is_ws_only(char *s);

// texture
void	draw_tile(t_data *data, int x, int y, void *img);
void	render_map(t_config *config);
void	init_window_and_textures(t_config *config);
void	init_window_and_textures(t_config *config);

//start
void	start(t_config *config, char **map);

#endif