#include "cub3d.h"

void	put_miniback(t_config *config, int j, int n)
{
	int	i;
	int	k;
	int	m;
	int	c;

	while (config->map[j])
	{
		i = 0;
		while (i++ < 10)
		{
			k = 0;
			m = 0;
			while (config->map[j][k] != '\0')
			{
				c = 0;
				while (c++ < 10)
					my_pixel_put(&config->img, m++, n, 0x404040);
				k++;
			}
			n++;
		}
		j++;
	}
}

void	minimap(t_config *config, int j, int n)
{
	int	i;
	int	k;
	int	m;
	int c;

	put_miniback(config, j, n);
	while (config->map[j])
	{
		i = 0;
		while (i < 10)
		{
			k = 0;
			m = 0;
			while (config->map[j][k] != '\0')
			{
				c = 0;
				if (config->map[j][k] == '1')
					while (c < 10)
						my_pixel_put(&config->img, m + c++, n, 0x000000);
				else if (config->map[j][k] == 'C' || config->map[j][k] == 'O')
					while (c < 10)
						my_pixel_put(&config->img, m + c++, n, 0x000090);
				m += 10;
				k++;
			}
			c = 0;
			while (c < 6 && i < 6)
				my_pixel_put(&config->img, (config->player.pos_y * 10 + c++
						- 3), (config->player.pos_x * 10 + i - 3), 0xF02020);
			i++;
			n++;
		}
		j++;
	}
}