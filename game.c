/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:42:53 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/20 13:51:38 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	mlx_destroy_image(game->mlx, game->img_ptr.player);
	mlx_destroy_image(game->mlx, game->img_ptr.wall);
	mlx_destroy_image(game->mlx, game->img_ptr.floor);
	mlx_destroy_image(game->mlx, game->img_ptr.collectible);
	mlx_destroy_image(game->mlx, game->img_ptr.exit);
	mlx_destroy_window(game->mlx, game->win);
	free_map(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

void	hook_setup(t_game *game)
{
	mlx_hook(game->win, 2, 1, handle_key, game);
	mlx_hook(game->win, 17, 17, close_game, game);
}
