#include "cub3d.h"

void	get_animation_textures(t_config *config)
{
	int		i;
	char	*name;
	char	*num;

	config->up_down = (t_img *)malloc(26 * sizeof(t_img));
	if (!config->up_down)
		return ;
	i = 0;
	while (i < 26)
	{
		name = ft_itoa(i + 1);
		num = ft_strjoin("./textures/animation/New_Project_", name);
		free(name);
		name = ft_strjoin(num, ".xpm");
		free(num);
		config->up_down[i].ht = 1393;
		config->up_down[i].wd = 548;
		config->up_down[i].img = mlx_xpm_file_to_image(config->data.mlx, name, &config->up_down[i].wd, &config->up_down[i].ht);
		config->up_down[i].addr = mlx_get_data_addr(config->up_down[i].img, &config->up_down[i].bits_per_pixel,
			&config->up_down[i].line_len, &config->open_door.endian);
		i++;
		free(name);
	}
}

void	get_door_textures(t_config *config)
{
	char	*open_door_path;
	char	*closed_door_path;
	closed_door_path = "./textures/closed_door.xpm";
	open_door_path = "./textures/open_door.xpm";
	config->closed_door.ht = texh;
	config->closed_door.wd = texh;
	config->closed_door.img = mlx_xpm_file_to_image(config->data.mlx, closed_door_path, &config->closed_door.wd, &config->closed_door.ht);
	config->closed_door.addr = mlx_get_data_addr(config->closed_door.img, &config->closed_door.bits_per_pixel,
		&config->closed_door.line_len, &config->closed_door.endian);
	config->open_door.ht = texh;
	config->open_door.wd = texh;
	config->open_door.img = mlx_xpm_file_to_image(config->data.mlx, open_door_path, &config->open_door.wd, &config->open_door.ht);
	config->open_door.addr = mlx_get_data_addr(config->open_door.img, &config->open_door.bits_per_pixel,
		&config->open_door.line_len, &config->open_door.endian);
}

void	get_textures(t_config *config)
{
	get_animation_textures(config);
	get_door_textures(config);
	config->south.ht = texh;
	config->south.wd = texh;
	config->south.img = mlx_xpm_file_to_image(config->data.mlx, config->so_path, &config->south.wd, &config->south.ht);
	config->south.addr = mlx_get_data_addr(config->south.img, &config->south.bits_per_pixel,
			&config->south.line_len, &config->south.endian);
	config->north.img = mlx_xpm_file_to_image(config->data.mlx, config->no_path, &config->north.wd, &config->north.ht);
	config->north.ht = texh;
	config->north.wd = texh;
	config->north.addr = mlx_get_data_addr(config->north.img, &config->north.bits_per_pixel,
			&config->north.line_len, &config->north.endian);
	config->west.img = mlx_xpm_file_to_image(config->data.mlx, config->we_path, &config->west.wd, &config->west.ht);
	config->west.ht = texh;
	config->west.wd = texh;
	config->west.addr = mlx_get_data_addr(config->west.img, &config->west.bits_per_pixel,
			&config->west.line_len, &config->west.endian);
	config->east.img = mlx_xpm_file_to_image(config->data.mlx, config->ea_path, &config->east.wd, &config->east.ht);
	config->east.ht = texh;
	config->east.wd = texh;
	config->east.addr = mlx_get_data_addr(config->east.img, &config->east.bits_per_pixel,
			&config->east.line_len, &config->east.endian);
}
