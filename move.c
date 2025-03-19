/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:43:41 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/19 13:43:44 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	close_game_for_move(t_game *game)
{
	ft_printf("*** YOU WON THE GAME! TOTAL MOVES: %d ***\n", game->move_c);
    close_game(game);
}

static void	move_player(t_game *game, int dx, int dy)
{
    int     new_x;
    int     new_y;
    char    next_tile;
    char    curr_tile;

    new_y = game->player_y + dy;
    new_x = game->player_x + dx;
    next_tile = game->map[new_y][new_x];
    curr_tile = game->map[game->player_y][game->player_x];
    if (next_tile == '1')
        return ;
    if (next_tile == 'C') 
        game->coin_count--;
    if (next_tile != 'E')
    {
        game->map[game->player_y][game->player_x] = '0';
        game->map[new_y][new_x] = 'P';
        game->player_x = new_x;
        game->player_y = new_y;
        game->move_c++;
        ft_printf("Moves: %d\n", game->move_c);
    }
    if (next_tile == 'E' && game->coin_count == 0)
    close_game_for_move(game);
}

int    handle_key(int keycode, t_game *game)
{
    if (keycode == 65307)
        close_game(game);
    else if (keycode == 119 || keycode == 65362)
        move_player(game, 0, -1);
    else if (keycode == 115 || keycode == 65364)
        move_player(game, 0, 1);
    else if (keycode == 97 || keycode == 65361)
        move_player(game, -1, 0);
    else if (keycode == 100 || keycode == 65363)
        move_player(game, 1, 0);
    else
        return (0);
    render_map(game);
    return (0);
}