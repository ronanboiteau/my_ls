/*
** ls_paths.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:17:11 2015 Ronan Boiteau
** Last update Wed Nov 25 21:19:36 2015 Ronan Boiteau
*/

#ifndef LS_PATHS_H_
# define LS_PATHS_H_

int			_count_valid_paths(int argc, char **argv, int errors);
int			_check_args(int argc,
				    char **argv,
				    int only_errors,
				    int *extra_eol);

#endif /* !LS_PATHS_H_ */
