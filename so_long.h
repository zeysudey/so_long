/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyilmaz <zyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:41 by zyilmaz           #+#    #+#             */
/*   Updated: 2025/03/16 17:57:53 by zyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
#include <unistd.h>
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"
typedef struct game
{
    char    *b_name;
    char    *map_name;
    int     map_x;
    int     map_y;
    char    **map;
    int		player_count;
	int		player_x;
	int		player_y;
    int     coin_count;
    int     exit_count;
    int     exit_y;
    int     exit_x;
    int     error_count;
    char    **map_clone;    
}   t_game;
void free_clone_map(t_game *game);
char	**clonemap(t_game *game);
void    object_check(t_game *game);
void	get_next_free(int fd);
char	*ft_strdup(const char *s1);
void    create_map(t_game *game);
int    ber_check(char *folder);
void    map_height(t_game *map);
int	handle_error(const char *msg, t_game *game);
void	map_linecheck(char *folder, t_game *game);
void    fill_map(t_game *game, int fd);
void    map_height(t_game *map);
void	free_map(t_game *game);
void	end_file_check(char *next, char *line, int fd);
void handle_error2(const char *msg, t_game *game);
#endif