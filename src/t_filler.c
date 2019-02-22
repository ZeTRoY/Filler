#include "filler.h"

// t_piece			

t_filler		*ft_create_filler(void)
{
	t_filler	*new;

	if ((new = (t_filler *)malloc(sizeof(t_filler))) == NULL)
		return (NULL);
	new->m = 0;
	new->n = 0;
	new->place = 0;
	new->map = NULL;
	if ((new->piece = (t_piece *)malloc(sizeof(t_piece))) == NULL ||
		(new->shape = (t_shape *)malloc(sizeof(t_shape))) == NULL)
		return (NULL); //ft_strdel!
	new->sum = 1000000;
	new->piece->len[0] = 0;
	new->piece->len[1] = 0;
	new->coord[0] = 0;
	new->coord[1] = 0;
	return (new);
}

void			ft_refresh_filler(t_filler *filler)
{
	int i;
	int j;

	i = 0;
	while (i < filler->m)
	{
		free(filler->map[i]);
		i++;
	}
	free(filler->map);
	i = 0;
	while (i < filler->piece->len[1])
	{
		free(filler->piece->piece[i]);
		i++;
	}
	free(filler->piece->piece);
	i = 0;
	while (i < filler->shape->coord[1][0] - filler->shape->coord[0][0] + 1)
	{
		free(filler->shape->shape[i]);
		i++;
	}
	free(filler->shape->shape);
	filler->map = NULL;
	filler->sum = 1000000;
	filler->piece->len[0] = 0;
	filler->piece->len[1] = 0;
	filler->coord[0] = 0;
	filler->coord[1] = 0;
	filler->m = 0;
	filler->n = 0;
}