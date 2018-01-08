/*
** malloc.h for malloc in /home/chenne_a/rendu/tech2/PSU_2016_malloc
** 
** Made by chennetier
** Login   <arthur.chennetier@epitech.eu>
** 
** Started on  Wed Jan 25 11:25:41 2017 chennetier
** Last update Fri Jan 27 10:43:22 2017 chauvin
*/

#include <stdlib.h>
#include <unistd.h>

#ifndef MALLOC_H_
# define MALLOC_H_

# define SIZE_PAGE getpagesize()

typedef struct 	s_meta
{
  struct s_meta *next;
  struct s_meta	*prev;
  size_t 	size;
  int		free;
}		t_meta;

# define SIZE_META sizeof(t_meta)

extern t_meta	*head;
extern t_meta	*last;

void		*new_space(t_meta *prev, size_t size);
t_meta		*new_space_head(int size);
t_meta		*new_space_body(int size, t_meta *prev);

extern void	*malloc(size_t size);
extern void	free(void *ptr);
extern void	*realloc(void *ptr, size_t size);
extern void	*calloc(size_t, size_t);
extern void	show_alloc_mem();

# endif /* !MALLOC */
