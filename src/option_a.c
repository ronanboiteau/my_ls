/*
** option_a.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 19:46:05 2015 Ronan Boiteau
** Last update Sun Nov 29 19:46:05 2015 Ronan Boiteau
*/

#include "my.h"
#include "ls_system.h"

void			_option_all(DIR *dir_ptr)
{
  struct dirent		*entry;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      my_putstr(entry->d_name);
      my_putchar('\n');
    }
  return ;
}
