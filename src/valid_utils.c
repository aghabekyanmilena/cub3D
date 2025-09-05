/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:18:18 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/03 19:30:31 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *skip_ws(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

int is_ws_only(char *s)
{
	size_t i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	return (s[i] == '\0');
}

int	check_filename(char *filename)
{
	char	*name;

	name = ft_strchr(filename, '.');
	if (!name || ft_strcmp(name, ".cub") != 0 || ft_strlen(name) != 4)
	{
		printf("Invalid file name\n");
		return (0);
	}
	return (1);
}
