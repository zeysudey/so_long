/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:18:41 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/16 21:09:27 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void handle_error2(const char *msg, t_game *game)
{
	ft_printf("%s", msg);
	if (game && game->map)
		free_map(game);
	if (game->map_clone)
    {
        free_clone_map(game);
        game->map_clone = NULL;
    }
	exit (EXIT_FAILURE);
}
int	handle_error(const char *msg, t_game *game)
{
	ft_printf("%s", msg);
	if (game && game->map)
		free_map(game);
	exit (EXIT_FAILURE);
	return (0);
}

static void	allzero(t_game *game)//TODO calloc ile aç
{
	game->map = 0;
	game->b_name = NULL;
	game->map_name = NULL;
	game->map_x = 0;
	game->map_y = 0;	
	game->player_count = 0;
	game->coin_count = 0;
	game->exit_count = 0;
	game->error_count = 0;
}
static void print_map(t_game *game)
{
    int i = 0;

    if (!game->map)
    {
        ft_printf("Error: Map is not loaded!\n");
        return;
    }

    ft_printf("Map Layout:\n");
    while (i < game->map_y) // map_y = Haritanın satır sayısı
    {
        ft_printf("%s", game->map[i]); // Satırı yazdır
        i++;
    }
    ft_printf("\n");
}

int main(int ac, char **argv)
{
	t_game game;
	if (ac != 2)
		handle_error("Argumants invalid", &game);
	allzero(&game);
	game.b_name = argv[1];
	ber_check(argv[1]);
	create_map(&game);
	object_check(&game);
	print_map(&game);
	free_map(&game);
}