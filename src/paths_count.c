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
