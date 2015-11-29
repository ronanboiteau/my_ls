/*
** option_r.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 19:46:26 2015 Ronan Boiteau
** Last update Sun Nov 29 19:46:27 2015 Ronan Boiteau
*/

#include "my.h"
#include "ls_system.h"

int			_count_files(DIR *dir_ptr)
{
  struct dirent		*entry;
  int			files;

  files = 0;
  while ((entry = readdir(dir_ptr)) != NULL)
    files += 1;
  return (files - 1);
}

void			_option_reverse(DIR *dir_ptr, char *dir, int files)
{
  struct dirent		*entry;
  int			idx;

  idx = 0;
  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (idx == files)
  	{
  	  if (entry->d_name[0] != '.')
  	    {
  	      my_putstr(entry->d_name);
  	      my_putchar('\n');
  	    }
  	  _option_reverse(opendir(dir), dir, files - 1);
  	}
      idx += 1;
    }
  return ;
}
