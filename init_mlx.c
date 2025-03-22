/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:01:34 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/22 21:28:09 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, int x, int y, char obj)
{
	if (obj == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_ptr.wall, x * 64, y * 64);
	else if (obj == '0')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_ptr.floor, x * 64, y * 64);
	else if (obj == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_ptr.collectible, x * 64, y * 64);
	else if (obj == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_ptr.exit, x * 64, y * 64);
	else if (obj == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_ptr.player, x * 64, y * 64);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			put_image(game, j, i, game->map[i][j]);
			j++;
		}
		i++;
	}
}

void	size_control(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (game->map_x * 64 > screen_width || game->map_y * 64 > screen_height)
		handle_error_mlx("Error\nMap size exceeds screen size!\n", game);
}

void	desing(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!(game->mlx))
		handle_error("Error\nmlx cannot initialized\n", game);
	size_control(game);
	game->win = mlx_new_window(game->mlx, game->map_x * 64,
			game->map_y * 64, "so_long");
	if (!(game->win))
		handle_error("Error\nmlx window cannot initialized\n", game);
	(game->img_ptr).player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &width, &height);
	(game->img_ptr).wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &width, &height);
	(game->img_ptr).floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &width, &height);
	(game->img_ptr).collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &width, &height);
	(game->img_ptr).exit = mlx_xpm_file_to_image(game->mlx,
			"textures/e.xpm", &width, &height);
	if (!(game->img_ptr).floor || !(game->img_ptr).wall
		|| !(game->img_ptr).player || !(game->img_ptr).collectible
		|| !(game->img_ptr).exit)
		handle_error_mlx_img("Error\nxpm loaderror\n", game);
}
