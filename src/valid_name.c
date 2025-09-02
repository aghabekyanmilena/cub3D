/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:47:08 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/01 17:32:39 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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