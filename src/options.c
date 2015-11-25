/*
** options.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:11:14 2015 Ronan Boiteau
** Last update Wed Nov 25 21:15:09 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"

char			*_find_options(int argc, char **argv)
{
  char			*new_opt;
  char			*options;
  int			idx;

  options = NULL;
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] == '-')
	{
	  new_opt = NULL;
	  if ((new_opt = malloc(sizeof(char) * my_strlen(argv[idx]) +
				my_strlen(options) + 1)) == NULL)
	    {
	      my_putstr_fd(2, "Out of memory! malloc() failed\n");
	      exit(EXIT_SERIOUS_TROUBLE);
	    }
	  if (options != NULL)
	    my_strncpy(new_opt, options, my_strlen(options));
	  options = my_strncat(new_opt, argv[idx] + 1, my_strlen(argv[idx] + 1));
	}
      idx += 1;
    }
  return (options);
}

void			_check_options(char *given_opt)
{
  unsigned int		idx_given;
  unsigned int		idx_auth;
  int			found_opt;
  char			*authorized_opt;

  authorized_opt = my_strdup("aUf");
  idx_given = 0;
  while (given_opt != NULL && given_opt[idx_given])
    {
      idx_auth = 0;
      found_opt = FALSE;
      while (authorized_opt[idx_auth])
	{
	  if (given_opt[idx_given] == authorized_opt[idx_auth])
	    found_opt = TRUE;
	  idx_auth += 1;
	}
      if (found_opt == FALSE)
	my_exit(EXIT_SERIOUS_TROUBLE, "scs", "ls: invalid option -- '", given_opt[idx_given], "'\n");
      idx_given += 1;
    }
  free(authorized_opt);
  return ;
}
