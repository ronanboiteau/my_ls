/*
** ls_args.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 17:15:48 2015 Ronan Boiteau
** Last update Sun Nov 29 18:46:39 2015 Ronan Boiteau
*/

#ifndef LS_ARGS_H_
# define LS_ARGS_H_

typedef struct	s_args
{
  int		argc;
  char		**argv;
  int		idx;
}		t_args;

#endif /* !LS_ARGS_H_ */
