/*
** new_space.c for PSU_2016_malloc in /home/chenne_a/delivery/PSU_2016_malloc/new_space.c
**
** Made by Prenom Nom
** Login   <arthur.chennetier@epitech.eu>
**
** Started on  sam. févr. 11 15:43:45 2017 Prenom Nom
** Last update sam. févr. 11 15:43:45 2017 Prenom Nom
*/

#include "malloc.h"

t_meta		*new_space_add_memory(int size, t_meta *to_malloc, t_meta *tmp)
{
  t_meta	*new_block;
  int 		indic;

  indic = (unsigned long) ((void *)to_malloc + SIZE_META + size + SIZE_META +
			   1 - (unsigned long)sbrk(0));
  if (sbrk(SIZE_PAGE) == (void *) - 1)
    return (NULL);
  new_block = (void *)to_malloc + to_malloc->size + SIZE_META;
  to_malloc->next = new_block;
  new_block->prev = to_malloc;
  new_block->free = 1;
  new_block->next = NULL;
  tmp->next = new_block;
  new_block->size = SIZE_PAGE - (SIZE_META - indic);
  last = new_block;
  return (to_malloc);
}

t_meta		*new_space_no_add_memory(int size, t_meta *to_malloc,
					       t_meta *tmp, t_meta *prev)
{
  t_meta	*new_block;

  new_block = (void *)to_malloc + SIZE_META + to_malloc->size;
  to_malloc->next = new_block;
  new_block->prev = to_malloc;
  new_block->free = 1;
  tmp->next = new_block;
  new_block->next = NULL;
  if ((size + SIZE_META) % SIZE_PAGE != 0 && prev == NULL)
    new_block->size = SIZE_PAGE * ((size + SIZE_META) / SIZE_PAGE + 1)
		      - to_malloc->size - SIZE_META * 3;
  else if ((size + SIZE_META) % SIZE_PAGE != 0)
    new_block->size = SIZE_PAGE * ((size + SIZE_META) / SIZE_PAGE + 1)
		      - to_malloc->size - SIZE_META * 2;
  else
    new_block->size = SIZE_PAGE * ((size + SIZE_META) / SIZE_PAGE)
		      - to_malloc->size - SIZE_META;
  last = new_block;
  return (to_malloc);
}

t_meta		*new_space_last_free(t_meta *prev)
{
  t_meta	*tmp;

  tmp = prev;
  if (prev->free != 1)
    {
      tmp = last;
      while (tmp->free != 1 && tmp->prev != NULL)
	tmp = tmp->prev;
    }
  return (tmp);
}

void		*new_space(t_meta *prev, size_t size)
{
  void		*ptr;
  t_meta	*to_malloc;
  t_meta	*tmp;

  tmp = head;
  if (prev == NULL)
    to_malloc = new_space_head(size);
  else
    {
      if ((to_malloc = new_space_body(size, prev)) == NULL)
	return (NULL);
      tmp = new_space_last_free(prev);
    }
  if ((void *)to_malloc + to_malloc->size + SIZE_META == sbrk(0))
    {
      last = to_malloc;
      to_malloc->next = NULL;
      tmp->next = NULL;
    }
  else if ((void *)to_malloc + to_malloc->size + (SIZE_META * 2) >= sbrk(0))
    to_malloc = new_space_add_memory(size, to_malloc, tmp);
  else if ((void *)to_malloc + to_malloc->size + SIZE_META * 2 < sbrk(0))
    to_malloc = new_space_no_add_memory(size, to_malloc, tmp, prev);
  ptr = (void *)to_malloc + SIZE_META;
  return (ptr);
}