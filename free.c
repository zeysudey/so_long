/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:17:25 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/20 14:36:56 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_clone_map(t_game *game)
{
	int	i;

	if (!game || !game->map_clone)
		return ;
	i = 0;
	while (game->map_clone[i])
	{
		free(game->map_clone[i]);
		i++;
	}
	free(game->map_clone);
	game->map_clone = NULL;
}

void	get_next_free(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}
