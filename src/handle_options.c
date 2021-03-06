#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "my_macro.h"
#include "ls_system.h"
#include "ls_args.h"

char			*_find_options(t_args *args)
{
  char			*new_opt;
  char			*options;

  options = NULL;
  args->idx = 1;
  while (args->idx < args->argc)
    {
      if (args->argv[args->idx][0] == '-')
	{
	  new_opt = NULL;
	  if ((new_opt = malloc(sizeof(char) *
				my_strlen(args->argv[args->idx]) +
				my_strlen(options) + 1)) == NULL)
	    {
	      my_dprintf(2, "Out of memory! malloc() failed\n");
	      exit(EXIT_SERIOUS_TROUBLE);
	    }
	  if (options != NULL)
	    my_strncpy(new_opt, options, my_strlen(options));
	  options = my_strncat(new_opt, args->argv[args->idx] + 1,
			       my_strlen(args->argv[args->idx] + 1));
	}
      args->idx += 1;
    }
  return (options);
}

void			_check_options(char *given_opt)
{
  unsigned int		idx_given;
  unsigned int		idx_auth;
  int			found_opt;
  char			*authorized_opt;

  authorized_opt = my_strdup("aUfRrl");
  idx_given = 0;
  while (given_opt != NULL && given_opt[idx_given])
    {
      idx_auth = 0;
      found_opt = false;
      while (authorized_opt[idx_auth])
	{
	  if (given_opt[idx_given] == authorized_opt[idx_auth])
	    found_opt = true;
	  idx_auth += 1;
	}
      if (found_opt == false)
	my_exit(EXIT_SERIOUS_TROUBLE, "scs", "ls: invalid option -- '",
		given_opt[idx_given], "'\n");
      idx_given += 1;
    }
  free(authorized_opt);
  return ;
}
