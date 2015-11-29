/*
** ls_args.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 17:15:48 2015 Ronan Boiteau
** Last update Sun Nov 29 17:49:23 2015 Ronan Boiteau
*/

#ifndef LS_ARGS_H_
# define LS_ARGS_H_

typedef struct	s_args
{
  int		argc;
  char		**argv;
  unsigned int	idx;
}		t_args;

#endif /* !LS_ARGS_H_ */

