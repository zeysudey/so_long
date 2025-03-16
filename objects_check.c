/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:32:36 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/16 21:23:09 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void validate_map_walls(t_game *game)
{
    int index;
    char **map_data;

    map_data = game->map;
    index = 0;
    if (game->error_count)
        handle_error("Error: Unknown object detected", game);
    
    // **Üst ve Alt Kenar Kontrolü**
    while (map_data[0][index] && map_data[game->map_y - 1][index])
    {
        if (map_data[0][index] != '1' || map_data[game->map_y - 1][index] != '1')
            handle_error("Error: Map boundaries are not properly enclosed!", game);
        index++;
    }

    // **Sol ve Sağ Kenar Kontrolü**
    index = 1; 
    while (index < game->map_y - 1)//satır kadar gidiiyor yani
    {
        if (map_data[index][0] != '1' || map_data[index][game->map_x - 1] != '1')
            handle_error("Error: Side walls are not properly enclosed!", game);
        index++;
    }
}
static int  flood_fill(int x, int y, char **map, t_game *game)
{
    if (x < 0 || y < 0 || x >= game->map_x || y >= game->map_y)
        return (1);
    if (map[y][x] == 'E' && game->exit_count == 1)
		game->exit_count--;
	if (map[y][x] == 'C' && game->coin_count > 0)
		game->coin_count--;
	if (game->coin_count == 0 && game->exit_count == 0)
		return (0);
	if (map[y][x] != '1' && map[y][x] != 'E' && map[y][x] != 'Z')
	{
		map[y][x] = 'Z';
		flood_fill(x + 1, y, map, game);
		flood_fill(x - 1, y, map, game);
		flood_fill(x, y + 1, map, game);
		flood_fill(x, y - 1, map, game);
	}
	if (game->coin_count == 0 && game->exit_count == 0)
		return (0);
	return (1);
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
    int		coin;

	coin = game->coin_count;
	if (game->coin_count < 1)
		handle_error("Wrong map,no coin", game);
	if (game->player_count!= 1)
		handle_error("error, the number of players is not 1", game);
	if (game->exit_count < 1)
        handle_error("error exit cant be less than 1", game);
    validate_map_walls(game);
    game->map_clone = clonemap(game);
    if (!game->map_clone)
    	handle_error("Error: Failed to clone the map!", game);
    if (flood_fill(game->player_x, game->player_y, game->map_clone, game))
        handle_error2("exit or coin is closed", game);
    if (game->map_clone)
    {
        free_clone_map(game);
        game->map_clone = NULL;
    }
}