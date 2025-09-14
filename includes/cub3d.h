/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:31:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/14 22:44:55 by miaghabe         ###   ########.fr       */
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
	int		width;
	int		player_count;
	int		player_x;
	int		player_y;
}	t_config;

// gnl
char	*ft_free_null(char *s);
int		ft_newline_instr(char *s);
char	*ft_strjoinn(char *s1, char *s2, size_t l1, size_t l2);
char	*get_next_line(int fd);

// valid and texture
int		check_filename(char *filename);
int		demi_6_toxy(char *line);
int		parse_et_6_toxy(t_config *data, char *line);
int		parse(t_config *data, char **lines, int *start_index);
int		parse_texture(t_config *data, int *flag, char *after_key, char *type);
int		parse_color(t_config *data, int *flag, char *after_key, char *type);
int		is_ws_only(char *s);
char	*skip_ws(char *s);

// parse and valid map and also dfs
bool	check_map_closed(t_config *cfg);
int		parse_map(t_config *data, char **lines, int start_index);

#endif