/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:31:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/02 16:33:04 by miaghabe         ###   ########.fr       */
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

# define VALID_CHARS "01NSEWD \n"

typedef struct s_color
{
	int	r;
	int	b;
	int	g;
}	t_color;

typedef struct s_config
{
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
}	t_config;



#endif