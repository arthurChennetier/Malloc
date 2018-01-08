/*
** malloc.c for malloc in /home/chenne_a/rendu/tech2/PSU_2016_malloc
** 
** Made by chennetier
** Login   <arthur.chennetier@epitech.eu>
** 
** Started on  Wed Jan 25 11:24:28 2017 chennetier
** Last update Fri Jan 27 10:44:54 2017 chauvin
*/

#include <stdio.h>
#include <limits.h>
#include "malloc.h"

t_meta *head = NULL;
t_meta *last = NULL;

t_meta		*check_size_init(t_meta *prev_elem, size_t size)
{
  t_meta	*to_malloc;

  to_malloc = (void *)prev_elem + SIZE_META + size;
  to_malloc->free = 1;
  to_malloc->prev = prev_elem;
  to_malloc->next = prev_elem->next;
  to_malloc->size = prev_elem->size - SIZE_META - size;
  return  (to_malloc);
}

void		check_size(t_meta *prev_elem, size_t size)
{
  t_meta	*to_malloc;
  t_meta	*tmp;

  to_malloc = NULL;
  tmp = head;
  while ((tmp->free != 1 || tmp->next != prev_elem) && tmp->next != NULL)
    tmp = tmp->next;
  if (size + (SIZE_META * 2) + 8 < prev_elem->size)
    {
      to_malloc = check_size_init(prev_elem, size);
      tmp->next = to_malloc;
      if (prev_elem != last)
	{
	  tmp = (void *) prev_elem + prev_elem->size + SIZE_META;
	  tmp->prev = to_malloc;
	}
      else
	{
	  last = to_malloc;
	  to_malloc->next = NULL;
	}
      prev_elem->size = size;
    }
  else
    tmp->next = prev_elem->next;
}

void		*check_memory(size_t size, int check)
{
  t_meta	*tmp;
  t_meta	*smallest;
  void		*ptr;

  tmp = head->next;
  smallest = tmp;
  while (tmp != NULL && smallest != NULL && check != 0)
    {
      if (tmp->size >= size)
	{
	  smallest = tmp;
	  check = 0;
	}
      else if (tmp->size >= size && tmp->size < smallest->size && check == 0)
	  smallest = tmp;
      tmp = tmp->next;
    }
  if (smallest == NULL)
    return (NULL);
  if (smallest->size < size || smallest->free != 1)
    return (NULL);
  ptr = (void *)smallest + SIZE_META;
  smallest->free = 0;
  check_size(smallest, size);
  return (ptr);
}

void		*init_head(size_t size)
{
  void		*ptr;

  if ((size + SIZE_META * 2) % SIZE_PAGE != 0 ||
      (size + SIZE_META * 2) / SIZE_PAGE == 0)
    {
      if ((head = sbrk(SIZE_PAGE * (((size + SIZE_META * 2)
				     / SIZE_PAGE) + 1))) == (void *) - 1)
	return (NULL);
    }
  else
    {
      if ((head = sbrk(SIZE_PAGE * (size + SIZE_META * 2)
		       / SIZE_PAGE)) == (void *) -1)
	return (NULL);
    }
  head->free = 1;
  head->prev = NULL;
  head->size = 0;
  if ((ptr = new_space(NULL, size)) == NULL)
    return (NULL);
  return (ptr);
}

void 	*malloc(size_t size)
{
  void	*ptr;

  size = (size + 7) & ~7;
  if (size >= LONG_MAX)
    return (NULL);
  if (!head)
    {
      if ((ptr = init_head(size)) == NULL)
	{
	  head = NULL;
	  last = NULL;
	  return (NULL);
	}
      return (ptr);
    }
  else
    {
      if ((ptr = check_memory(size, 1)) == NULL)
	{
	  if ((ptr = new_space(last, size)) == NULL)
	    return (NULL);
	}
    }
  return (ptr);
}