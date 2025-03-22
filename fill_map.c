/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:59:41 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/22 18:28:05 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map_lines(t_game *game, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line && i < game->map_y)
	{
		game->map[i] = ft_strdup(line);
		if (!game->map[i])
		{
			free(line);
			handle_error("Error\nMemory allocation failed\n", game);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
}

void	rectangle(t_game *game)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	while (game->map[i] && game->map[i + 1])
	{
		len1 = ft_strlen(game->map[i]);
		len2 = ft_strlen(game->map[i + 1]);
		if (game->map[i][len1 - 1] == '\n')
			len1--;
		if (game->map[i + 1][len2 - 1] == '\n')
			len2--;
		if (len1 != len2)
			handle_error("Error\nMap is not rectangular!\n", game);
		i++;
	}
	game->map_x = ft_strlen(game->map[i]);
}

void	object_number(char obj, t_game *game, int pos_y, int pos_x)
{
	if (obj == 'P')
	{
		game->player_count++;
		game->player_x = pos_x;
		game->player_y = pos_y;
	}
	else if (obj == 'E')
		game->exit_count++;
	else if (obj == 'C')
		game->coin_count++;
	else if (obj != '0' && obj != '1')
		game->error_count++;
}

void	process_map_objects(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n')
		{
			object_number(game->map[i][j], game, i, j);
			j++;
		}
		i++;
	}
}

void	fill_map(t_game *game, int fd)
{
	read_map_lines(game, fd);
	rectangle(game);
	walls(game);
	process_map_objects(game);
}
