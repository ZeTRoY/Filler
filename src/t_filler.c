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
	return (new);
}