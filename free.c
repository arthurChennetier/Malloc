/*
** free.c for free in /home/chenne_a/rendu/tech2/PSU_2016_malloc
** 
** Made by chennetier
** Login   <arthur.chennetier@epitech.eu>
** 
** Started on  Thu Jan 26 17:49:20 2017 chennetier
** Last update Mon Jan 30 13:08:37 2017 chennetier
*/


#include <stdio.h>
#include "malloc.h"

t_meta		*left_concate(t_meta *to_free)
{
  t_meta	*next;

  if (to_free->prev->free == 1 && to_free->prev != head)
    {
      to_free->prev->next = to_free->next;
      to_free->prev->size = to_free->prev->size + to_free->size + SIZE_META;
      if (to_free != last)
	{
	  next = (void*)to_free + to_free->size + SIZE_META;
	  next->prev = to_free->prev;
	}
      else
	{
	  last = to_free->prev;
	  to_free->prev->next = NULL;
	}
      to_free = to_free->prev;
    }
  return (to_free);
}

t_meta		*right_concate(t_meta *to_free)
{
  t_meta	*next;
  t_meta	*tmp;

  if (to_free->next != NULL)
    {
      if (to_free->next->free == 1 && to_free->next->prev == to_free)
	{
	  tmp = to_free->next;
	  to_free->next = tmp->next;
	  to_free->size = to_free->size + tmp->size + SIZE_META;
	  if (tmp != last)
	    {
	      next = (void *) tmp + SIZE_META + tmp->size;
	      next->prev = to_free;
	    }
	  else
	    {
	      last = tmp->prev;
	      to_free->next = NULL;
	    }
	}
    }
  return (to_free);
}

void		memory_clean(t_meta *to_free, int indic)
{
  t_meta	*tmp;

  if (last->free != 0)
    {
      to_free = last;
      while (to_free->size > (unsigned int) SIZE_PAGE)
	{
	  to_free->size = to_free->size - SIZE_PAGE;
	  if ((indic = to_free->size) <= 0)
	    {
	      last = last->prev;
	      last->next = NULL;
	    }
	  if (sbrk(-SIZE_PAGE) == (void *) -1)
	    return ;
	}
      if (indic == 0)
	{
	  if ((tmp = last->prev) == NULL)
	    return ;
	  while (tmp->prev && tmp->free == 0)
	    tmp = tmp->prev;
	  tmp->next = last;
	}
    }
}

void		free(void *ptr)
{
  t_meta	*to_free;
  t_meta	*tmp;

  if (ptr == NULL)
    return ;
  to_free = ptr - SIZE_META;
  if (to_free->free == 1)
    return ;
  to_free->free = 1;
  tmp = to_free->prev;
  while (tmp->free != 1 && tmp->prev != NULL)
    tmp = tmp->prev;
  if (tmp->next == to_free)
    to_free->next = NULL;
  else
    to_free->next = tmp->next;
  tmp->next = to_free;
  to_free = left_concate(to_free);
  to_free = right_concate(to_free);
  memory_clean(to_free, 1);
}