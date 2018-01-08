/*
** realloc.c for realloc in /home/chenne_a/rendu/tech2/PSU_2016_malloc
** 
** Made by chennetier
** Login   <arthur.chennetier@epitech.eu>
** 
** Started on  Sat Feb 11 18:03:52 2017 chennetier
** Last update Sat Feb 11 18:03:53 2017 chennetier
*/


#include <string.h>
#include "malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*new_tmp;

  if ((new_tmp = malloc(size * nmemb)) != NULL)
    bzero(new_tmp, (size * nmemb));
  return (new_tmp);
}

void	*realloc(void *ptr, size_t size)
{
  t_meta	*data;
  void		*new;

  size =  (size + 7) & ~7;
  if (ptr == NULL)
    return (malloc(size));
  else if (size == 0)
      {
	free(ptr);
	return (NULL);
      }
    else
      {
	data = ptr - SIZE_META;
	if (data->size >= size)
	  return (ptr);
	if ((new = malloc(size)) == NULL)
	  return (NULL);
	memcpy(new, ptr, data->size);
	free(ptr);
	return new;
      }
}

