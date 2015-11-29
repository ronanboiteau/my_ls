/*
** ls_paths.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:17:11 2015 Ronan Boiteau
** Last update Sun Nov 29 21:49:38 2015 Ronan Boiteau
*/

#ifndef LS_PATHS_H_
# define LS_PATHS_H_

# include "ls_args.h"

typedef struct	s_path
{
  char		*dir;
  char		*filename;
}		t_path;

int		_count_valid_paths(t_args *args, int only_errors);
int		_check_args(t_args *args,
			    int only_errors,
			    int *extra_eol);

#endif /* !LS_PATHS_H_ */
