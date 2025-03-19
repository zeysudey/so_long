/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:32:36 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/19 15:12:22 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void walls(t_game *game)
{
    int index;
    char **map_data;

    map_data = game->map;
    index = 0;
    if (game->error_count)
        handle_error("Error\nUnknown object detected\n", game);
    while (map_data[0][index] && map_data[game->map_y - 1][index])
    {
        if (map_data[0][index] != '1' || map_data[game->map_y - 1][index] != '1')
            handle_error("Error\nMap boundaries are not enclosed\n", game);
        index++;
    }
    index = 1; 
    while (index < game->map_y - 1)
    {
        if (map_data[index][0] != '1' || map_data[index][game->map_x - 1] != '1')
            handle_error("Error\nSide walls are not enclosed\n", game);
        index++;
    }
}

static int flood_fill(int x, int y, char **map, t_game *game)
{
    if (x < 0 || y < 0 || x >= game->map_x || y >= game->map_y)
        return (1);
    if (map[y][x] == '1' || map[y][x] == 'Z') 
        return (1);
    if (map[y][x] == 'E')  
        return (1);
    if (map[y][x] == 'C')  
        game->coin_copy--;
    map[y][x] = 'Z';
    if (game->coin_copy == 0 && game->exit_count == 0)
        return (0);
    flood_fill(x + 1, y, map, game);
    flood_fill(x - 1, y, map, game);
    flood_fill(x, y + 1, map, game);
    flood_fill(x, y - 1, map, game);
    return (0);
}

void free_clone_map(t_game *game)
{
     int i;

    if (!game || !game->map_clone)
        return;
    i = 0;
    while (game->map_clone[i])
    {
        free(game->map_clone[i]);
        i++;
    }
    free(game->map_clone);
    game->map_clone = NULL;
}
void    object_check(t_game *game)
{
    game->coin_copy = game->coin_count;
	if (game->coin_count < 1)
		handle_error("Error\nNo coin\n", game);
	if (game->player_count!= 1)
		handle_error("Error\nThe number of players is not 1\n", game);
	if (game->exit_count != 1)
        handle_error("Error\nExit count must be 1\n", game);
    walls(game);
    game->map_clone = clonemap(game);
    if (!game->map_clone)
    	handle_error("Error\nFailed to clone the map\n", game);
    if (flood_fill(game->player_x, game->player_y, game->map_clone, game))
        handle_error2("Error\nPlayer cant acces other objects\n", game);
    int k=0;
    while (game->map_clone[k])
    {
        ft_printf("%s",game->map_clone[k]);
        k++;
    }
    if (game->map_clone)
    {
        free_clone_map(game);
        game->map_clone = NULL;
    }
}
