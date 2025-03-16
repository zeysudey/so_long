/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:17:25 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/15 13:54:16 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (i < game->map_y)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}