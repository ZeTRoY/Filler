#include "filler.h"

// t_piece			

t_filler		*ft_create_filler(void)
{
	t_filler	*new;

	if ((new = (t_filler *)malloc(sizeof(t_filler))) == NULL)
		return (NULL);
	new->playermark = 0;
	new->m = 0;
	new->n = 0;
	new->map = NULL;
	if ((new->piece = (t_piece *)malloc(sizeof(t_piece))) == NULL)
		return (NULL); //ft_strdel!
	new->piece->x = 0;
	new->piece->y = 0;
	new->coord[0] = 0;
	new->coord[1] = 0;
	return (new);
}

void			ft_destroy_filler(t_filler **filler)
{
	int i;
	int j;

	i = 0;
	while (i < (*filler)->m)
	{
		free((*filler)->map[i]);
		free((*filler)->piece->piece[i]);
		// while (j < (*filler)->n)
		// {
		// 	j = 0;
		// 	free((*filler)->board->distance[i][j]);
		// }
		// free((*filler)->board->distance[i]);
	}
	free((*filler)->piece);
	// free((*filler)->board);
	free(*filler);
	filler = 0;
}