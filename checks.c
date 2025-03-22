/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:32:36 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/22 21:20:24 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(int i, int j, t_game *game)
{
	if (i < 0 || i >= game->map_y || j < 0 || j >= game->map_x)
		return ;
	if (game->map_clone[i][j] == '1' || game->map_clone[i][j] == 'Z')
		return ;
	if (game->map_clone[i][j] == 'E')
		{
			game->exit_reachable = 1;
			game->map_clone[i][j] = 'Z';
			return ;
		}
	game->map_clone[i][j] = 'Z';
	flood_fill(i + 1, j, game);
	flood_fill(i - 1, j, game);
	flood_fill(i, j + 1, game);
	flood_fill(i, j - 1, game);
}

int	validcheck(t_game *game)
{
	int	i;
	int	j;

	game->exit_reachable = 0; 
	flood_fill(game->player_y, game->player_x, game);
	i = 0;
	if (game->exit_reachable == 0)
		return (1);
	while (i < game->map_y)
	{
		j = 0;
		while (j < game->map_x)
		{
			if (game->map_clone[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check(t_game *game)
{
	if (game->coin_count < 1)
		handle_error("Error\nThe number of coins must be at least 1.\n", game);
	if (game->player_count != 1)
		handle_error("Error\nPlayer count must be exactly 1\n", game);
	if (game->error_count)
		handle_error("Error\nUnknown object detected\n", game);
	if (game->exit_count != 1)
		handle_error("Error\nExit count must be exactly 1\n", game);
	game->map_clone = clonemap(game);
	if (!game->map_clone)
		handle_error("Error\nFailed to clone the map\n", game);
	if (validcheck(game))
		handle_error("Error\nPlayer cant acces other objects\n", game);
	if (game->map_clone)
	{
		free_clone_map(game);
		game->map_clone = NULL;
	}
}
