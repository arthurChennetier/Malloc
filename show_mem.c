/*
** show_mem.c for show_mem in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_malloc
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Sun Feb 12 21:38:37 2017 chauvin
** Last update Sun Feb 12 22:15:49 2017 chennetier
*/

#include "malloc.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int 	i;

  i = 0;
  while (str[i])
    {
      my_putchar(str[i]);
      i++;
    }
}

int	my_strlen(char *str)
{
  int 	i;

  i = 0;
  while (str[i])
    i++;
  return (i);
}

int    my_put_nbrbase(unsigned long nb, char *base)
{
  unsigned long result;
  int   divisor;

  divisor = 1;
  while ((nb / divisor) >= (unsigned int)my_strlen(base))
    divisor = divisor * my_strlen(base);
  while (divisor > 0)
    {
      result = (nb / divisor) % my_strlen(base);
      if (result > 9)
	my_putchar(base[result]);
      else
	my_putchar((char) (48 + result));
      divisor = divisor / my_strlen(base);
    }
  return (0);
}

void	show_alloc_mem()
{
  t_meta *tmp;

  tmp = last;
  if (tmp == NULL)
    return ;
  while (tmp && tmp->prev != head)
    tmp = tmp->prev;
  my_putstr("break : ");
  my_put_nbrbase((unsigned long) sbrk(0), "0123456789ABCDEF");
  my_putstr("\n");
  while (tmp != last && tmp)
    {
      if (tmp->free == 0)
	{
	  my_put_nbrbase((unsigned long) (void*)tmp + SIZE_META,
			 "0123456789ABCDEF");
	  my_putstr(" - ");
	  my_put_nbrbase((unsigned long) (void *) tmp + SIZE_META
			 + tmp->size, "0123456789ABCDEF");
	  my_putstr(" : ");
	  my_put_nbrbase((unsigned long) tmp->size, "0123456789");
	  my_putstr(" bytes\n");
	}
      tmp = (void*) tmp + tmp->size + SIZE_META;
    }
}
