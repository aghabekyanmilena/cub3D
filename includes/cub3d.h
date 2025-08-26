/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:31:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/23 16:29:09 by atseruny         ###   ########.fr       */
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

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*texture_paths[4];
	void	*textures[4];
	int		widths[4];
	int		heights[4];
	char	**map;
	int		map_width;
	int		map_height;
}	t_data;

typedef struct s_config
{
	t_data	graphics;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	t_color	floor;
	t_color	ceiling;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	**map;
	int		height; // mapi heighty
	int		player_count;
}	t_config;


// valid_map u dfs
char	**copy_map(char **map, int height);
int	is_invalid_tile(char c);
int	qaylelu_tex(char c);
int	dfs(char **map, int x, int y, int max_y);
int	parse_map(t_config *data, char **lines, int start_index);

// gnl
char	*ft_free_null(char *s);
int	ft_newline_instr(char *s);
char	*ft_strjoinn(char *s1, char *s2, size_t l1, size_t l2);
char	*get_next_line(int fd);

// valid.c
int	check_filename(char *filename);
int	demi_6_toxy(char *line);
int	parse_et_6_toxy(t_config *data, char *line);
int	parse_texture(char **dest, int *flag, char *path, char *type);
int	parse(t_config *data, char **lines, int *start_index);
int	parse_color(t_color *color, int *flag, char *line, char *type);

//start
void start(t_config *config, char **map);

// texture
void	draw_tile(t_data *data, int x, int y, void *img);
void	render_map(t_config *config);
void	init_window_and_textures(t_config *config);

#endif