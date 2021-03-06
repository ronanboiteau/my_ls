#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "my_macro.h"
#include "ls_args.h"
#include "ls_paths.h"
#include "ls_options.h"

int			main(int argc, char **argv)
{
  t_args		*args;
  char			*options;
  int			errors;

  if ((args = malloc(sizeof(t_args))) == NULL)
    return (EXIT_SERIOUS_TROUBLE);
  args->argv = argv;
  args->argc = argc;
  args->idx = 1;
  options = _find_options(args);
  _check_options(options);
  errors = _check_args(args, true, NULL);
  _iterate_args(args, options, errors, true);
  free(options);
  free(args);
  return (EXIT_SUCCESS);
}
