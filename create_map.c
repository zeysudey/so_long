/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:41:09 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/22 14:05:17 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_height_check(t_game *game)
{
	char	*next_line;
	char	*line;
	int		fd;

	fd = open(game->b_name, O_RDONLY);
	if (fd == -1)
		handle_error("Error\nCan't open the file.\n", NULL);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		handle_error("Error\nNo element in the file\n", NULL);
	}
	while (line != NULL)
	{
		next_line = get_next_line(fd);
		end_file_check(next_line, line, fd);
		game->map_y++;
		free(line);
		line = next_line;
	}
	close(fd);
}

void	create_map(t_game *game)
{
	int	fd;

	map_height_check(game);
	game->map = malloc(sizeof(char *) * (game->map_y + 1));
	if (!game->map)
		handle_error("Error\nMemory allocation failed\n", game);
	fd = open(game->b_name, O_RDONLY);
	if (fd < 0)
		handle_error("Error: Failed to open map file.\n", game);
	fill_map(game, fd);
}
