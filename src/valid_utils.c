/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:18:18 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/21 22:15:08 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*skip_ws(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

int	is_ws_only(char *s)
{
	size_t	i;

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
		printf("Error\nInvalid file name\n");
		return (0);
	}
	return (1);
}

int	characker_check(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'O' || c == ' '
		|| c == '\t' || c == 'C');
}

char	**copy_map(t_config *data)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[data->height] = NULL;
	return (copy);
}
