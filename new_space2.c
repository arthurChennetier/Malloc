/*
** new_space2.c for PSU_2016_malloc in /home/chenne_a/delivery/PSU_2016_malloc/new_space2.c
**
** Made by Prenom Nom
** Login   <arthur.chennetier@epitech.eu>
**
** Started on  sam. févr. 11 16:44:48 2017 Prenom Nom
** Last update sam. févr. 11 16:44:48 2017 Prenom Nom
*/

#include "malloc.h"

t_meta		*new_space_head(int size)
{
  t_meta	*to_malloc;

  to_malloc = (void *) head + SIZE_META;
  to_malloc->prev = head;
  to_malloc->free = 0;
  to_malloc->size = size;
  return (to_malloc);
}

t_meta		*new_space_body(int size, t_meta *prev)
{
  t_meta	*to_malloc;

  if ((size + SIZE_META) % SIZE_PAGE != 0)
    {
      if ((to_malloc = sbrk(SIZE_PAGE * (((size + SIZE_META) /
					  SIZE_PAGE) + 1))) == (void *) - 1)
	return (NULL);
    }
  else
    {
      if ((to_malloc = sbrk(SIZE_PAGE * (size + SIZE_META) /
			    SIZE_PAGE)) == (void *) -1)
	return (NULL);
    }
  to_malloc->prev = prev;
  to_malloc->free = 0;
  to_malloc->size = size;
  return (to_malloc);
}