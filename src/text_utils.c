/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:03:48 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 15:20:12 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// for color
static int	guyni_stugum(char **str)
{
	int	val;

	val = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	while (ft_isdigit(**str))
		val = val * 10 + *((*str)++) - '0';
	if (val < 0 || val > 255)
		return (-1);
	return (val);
}

static int	parse_component(char **str)
{
	int	val;

	val = guyni_stugum(str);
	if (*(*str) == ',')
		(*str)++;
	return (val);
}

static int	validate_color(char *tmp, t_color *color)
{
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (ft_putendl_fd("Error", 2), 0);
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp != '\0')
		return (ft_putendl_fd("Error", 2), 0);
	return (1);
}

int	parse_color(t_config *data, int *flag, char *skip, char *type)
{
	char	*tmp;
	t_color	*color;

	tmp = skip_ws(skip);
	if (*flag)
		return (ft_putendl_fd("Error", 2), 0);
	if (type[0] == 'F')
		color = &data->floor;
	else
		color = &data->ceiling;
	color->r = parse_component(&tmp);
	color->g = parse_component(&tmp);
	color->b = parse_component(&tmp);
	if (!validate_color(tmp, color))
		return (0);
	*flag = 1;
	return (1);
}
