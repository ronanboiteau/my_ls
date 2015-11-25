/*
** my_put_error.c for my_put_error in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 19:32:13 2015 Ronan Boiteau
** Last update Wed Nov 25 19:35:53 2015 Ronan Boiteau
*/

#include "my.h"
#include "variadic.h"

void			my_put_error(char *args, ...)
{
  va_list		error_msg;
  unsigned int		idx_arg;

  va_start(error_msg, args);
  idx_arg = 0;
  while (args[idx_arg])
    {
      if (args[idx_arg] == 'i')
	my_put_nbr_fd(2, va_arg(error_msg, int));
      else if (args[idx_arg] == 's')
	my_putstr_fd(2, va_arg(error_msg, char *));
      else if (args[idx_arg] == 'c')
	my_putchar_fd(2, va_arg(error_msg, int));
      idx_arg += 1;
    }
  va_end(error_msg);
  return ;
}
