#include "filler.h"

t_filler		*ft_create_filler(void)
{
	t_filler	*new;

	new = (t_filler *)malloc(sizeof(t_filler));
	new->playermark = 0;
	new->x = 0;
	new->y = 0;
	new->map = NULL;
	return (new);
}