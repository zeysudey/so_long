/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:18:41 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/22 16:56:37 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	allzero(t_game *game)
{
	game->map = 0;
	game->b_name = NULL;
	game->map_x = 0;
	game->map_y = 0;
	game->player_count = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->coin_count = 0;
	game->exit_count = 0;
	game->error_count = 0;
	game->map_clone = NULL;
	game->move_c = 0;
}

int	main(int ac, char **argv)
{
	t_game	game;

	if (ac != 2)
		handle_error("Error\nArgumants invalid\n", NULL);
	allzero(&game);
	ber_check(argv[1]);
	game.b_name = argv[1];
	create_map(&game);
	check(&game);
	desing(&game);
	render_map(&game);
	hook_setup(&game);
	mlx_loop(game.mlx);
	if (game.map)
		free_map(&game);
}
