/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:57:10 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/23 15:18:28 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_error_mlx(const char *msg, t_game *game)
{
	ft_printf("%s", msg);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	handle_error(NULL, game);
}

void	handle_error_mlx_img(const char *msg, t_game *game)
{
	ft_printf("%s", msg);
	if (game)
	{
		if (game->img_ptr.player)
			mlx_destroy_image(game->mlx, game->img_ptr.player);
		if (game->img_ptr.wall)
			mlx_destroy_image(game->mlx, game->img_ptr.wall);
		if (game->img_ptr.floor)
			mlx_destroy_image(game->mlx, game->img_ptr.floor);
		if (game->img_ptr.collectible)
			mlx_destroy_image(game->mlx, game->img_ptr.collectible);
		if (game->img_ptr.exit)
			mlx_destroy_image(game->mlx, game->img_ptr.exit);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		handle_error(NULL, game);
	}
}

int	handle_error(const char *msg, t_game *game)
{
	if (msg)
		ft_printf("%s", msg);
	if (game)
	{
		if (game->map)
			free_map(game);
		if (game->map_clone)
		{
			free_clone_map(game);
			game->map_clone = NULL;
		}
	}
	exit(EXIT_FAILURE);
	return (0);
}
