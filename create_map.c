#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void rectangle(t_game *game)
{
    int i = 0;
    int len1;
    int len2;
    int last;

    if (!game->map || !game->map[0])  // NULL kontrolü
        handle_error("Error\n Map is empty!\n", game);
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
    last = ft_strlen(game->map[i]);
    if (game->map[i][last - 1] == '\n')
        last--;
    game->map_x = last;
}

static void    map_height_check(char *str,t_game *game)
{
    char	*next_line;
	char	*line;
	int		fd;
	int		x;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		handle_error("Error\nCan't open the file.\n", NULL);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		handle_error("Error\nNo element in the file\n", NULL);
	}
	x = ft_strlen(line);
	while (line != NULL)
	{
		next_line = get_next_line(fd);
		end_file_check(next_line, line, fd);
		game->map_y++;
        free(line);
		line = next_line;
	}
    close(fd);
	game->map_x = x - 1;
}
static void	object_number(char obj, t_game *game, int pos_y, int pos_x)
{
	if (obj == 'P')
	{
		game->player_count++;
		game->player_x = pos_x;
		game->player_y = pos_y;
	}
	else if (obj == 'E')
	{
		game->exit_count++;
		game->exit_x = pos_x;
		game->exit_y = pos_y;
	}
	else if (obj == 'C')
		game->coin_count++;
	else if (obj != '0' && obj != '1')
		game->error_count++;
}
void    fill_map(t_game *game, int fd)
{
    int i;
	int	j;
    char *line;
    
    i = 0;
    line = get_next_line(fd);
    while (line && i < game->map_y)
    {
        game->map[i] = ft_strdup(line);
        if (!game->map[i])
            handle_error("Error\nMemory allocation failed\n", game);       
		j = 0;
        while (line[j] != '\0' && line[j] != '\n')
        {
            object_number(line[j], game, i , j);
            j++;
		}
        free(line);
        line = get_next_line(fd);
        i++;
    }
	/*ft_printf("%d\n",game->coin_count);
	ft_printf("%d\n",game->player_count);
	ft_printf("%d\n",game->exit_count);*/

    game->map[i] = NULL;
    close(fd);
    rectangle(game);
}

void    create_map(t_game *game)
{
        int fd;
        map_height_check(game->b_name, game);
        game->map = malloc(sizeof(char *) * (game->map_y + 1));
        if (!game->map)
            handle_error("Error\nMemory allocation failed\n", game);
		fd = open(game->b_name, O_RDONLY);
        if (fd < 0)
            handle_error("Error: Failed to open map file.\n", game);
        fill_map(game, fd);
        if (!game->map[0])
        {
            write(2, "Empty map\n", 10);
            free_map(game);            
            return ;
        }      
}
