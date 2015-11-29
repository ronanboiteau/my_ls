/*
** ls_options.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 14:54:25 2015 Ronan Boiteau
** Last update Sun Nov 29 21:22:23 2015 Ronan Boiteau
*/

#ifndef LS_OPTIONS_H_
# define LS_OPTIONS_H_

# include "ls_system.h"

char		*_find_options(t_args *args);
void		_check_options(char *given_opt);
void		_no_option(DIR *dir_ptr);
void		_option_all(DIR *dir_ptr);
void		_option_long(DIR *dir_ptr);
void		_option_reverse(DIR *dir_ptr, char *dir, int files);
int		_count_files(DIR *dir_ptr);

#endif /* !LS_OPTIONS_H_ */
