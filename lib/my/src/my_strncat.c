/*
** my_strncat.c for my_strncat in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Tue Oct  6 20:46:17 2015 Ronan Boiteau
** Last update Tue Nov 24 20:27:29 2015 Ronan Boiteau
*/

#include "my.h"

char		*my_strncat(char *dest, const char *src, unsigned int nbr)
{
  unsigned int	idx_dest;
  unsigned int	idx_src;

  idx_dest = my_strlen(dest);
  idx_src = 0;
  while (src[idx_src] && idx_src < nbr)
    {
      dest[idx_dest] = src[idx_src];
      idx_dest += 1;
      idx_src += 1;
    }
  dest[idx_dest] = '\0';
  return (dest);
}