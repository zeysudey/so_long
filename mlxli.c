/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxli.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:01:34 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/18 18:51:33 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


static void	put_image(t_game *game, int x, int y, char obj)
{
	if (obj == 'P') // pandoş
		mlx_put_image_to_window(game->mlx, game->win, game->img_ptr.player, x * 64, y * 64);
	else if (obj == '1') // Duvar
		mlx_put_image_to_window(game->mlx, game->win, game->img_ptr.wall, x * 64, y * 64);
	else if (obj == 'C') // Toplanabilir nesne
		mlx_put_image_to_window(game->mlx, game->win, game->img_ptr.collectible, x * 64, y * 64);
	else if (obj == '0') 
		mlx_put_image_to_window(game->mlx, game->win, game->img_ptr.floor, x * 64, y * 64);
	else if (obj == 'E') // Çıkış
		mlx_put_image_to_window(game->mlx, game->win, game->img_ptr.exit, x * 64, y * 64);
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

void	desing(t_game *game)
{
    int	width;
	int	height;
	game->mlx = mlx_init();
	if (!(game->mlx))
		handle_error("Error\nmlx cannot initialized\n", game);
	game->win = mlx_new_window(game->mlx, game->map_x * 64,
			game->map_y * 64, "so_long");
	if (!(game->win))
		handle_error("Error\nmlx window cannot initialized\n", game);
	(game->img_ptr).player = mlx_xpm_file_to_image(game->mlx,"img/panda.xpm", &width, &height);
	(game->img_ptr).wall = mlx_xpm_file_to_image(game->mlx,"img/bambu.xpm", &width, &height);
	(game->img_ptr).collectible = mlx_xpm_file_to_image(game->mlx,"img/mama.xpm", &width, &height);
	(game->img_ptr).floor = mlx_xpm_file_to_image(game->mlx,"img/yol.xpm", &width, &height);
		(game->img_ptr).exit = mlx_xpm_file_to_image(game->mlx,"img/e.xpm", &width, &height);

	
    if (!(game->img_ptr).floor)
        ft_printf("xpm loaderror");
}
