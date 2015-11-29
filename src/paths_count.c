/*
** paths_count.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 21:57:21 2015 Ronan Boiteau
** Last update Sun Nov 29 23:23:11 2015 Ronan Boiteau
*/

#include "ls_args.h"

int			_count_valid_paths(t_args *args)
{
  int			idx;
  int			paths;

  paths = 0;
  idx = 1;
  while (idx < args->argc)
    {
      if (args->argv[idx][0] != '-')
	paths += 1;
      idx += 1;
    }
  return (paths);
}
