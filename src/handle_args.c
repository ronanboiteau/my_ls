#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "my_macro.h"
#include "ls_args.h"
#include "ls_paths.h"
#include "ls_options.h"
#include "ls_system.h"

static void		_print_files(char *dir, DIR *dir_ptr, char *options)
{
  if (my_strstr(options, "r"))
    _option_reverse(opendir(dir), dir, _count_files(dir_ptr));
  else if (my_strstr(options, "f") || my_strstr(options, "aU") ||
      my_strstr(options, "Ua") || my_strstr(options, "a"))
    _option_all(dir_ptr);
  else if (options == NULL)
    _no_option(dir_ptr);
  return ;
}

static int		_print_extra_eol(int extra_eol,
					 int first_pass,
					 int errors)
{
  if (first_pass == true)
    {
      if (errors > 0 && extra_eol == true)
	my_printf("\n");
      first_pass = false;
    }
  else
    my_printf("\n");
  return (first_pass);
}

static void		_print_dirname(t_args *args,
				       int extra_eol,
				       char *dir)
{
  if (_count_valid_paths(args) > 1 ||
      extra_eol == true)
    {
      my_printf("%s", dir);
      my_printf(":\n");
    }
  return ;
}

static void		_if_no_arg(int first_pass,
				   int errors,
				   char *options)
{
  DIR			*dir_ptr;
  char			*dir;

  if (first_pass == true && errors == 0)
    {
      dir = my_strdup(".");
      if ((dir_ptr = opendir(dir)) != NULL)
	_print_files(dir, dir_ptr, options);
      closedir(dir_ptr);
      free(dir);
    }
}

void			_iterate_args(t_args *args,
				      char *options,
				      int errors,
				      int first_pass)
{
  DIR			*dir_ptr;
  char			*dir;
  int			extra_eol;

  extra_eol = false;
  _check_args(args, false, &extra_eol);
  args->idx = 1;
  while (args->idx < args->argc)
    {
      if (args->argv[args->idx][0] != '-')
	{
	  dir = my_strdup(args->argv[args->idx]);
	  if ((dir_ptr = opendir(dir)) != NULL)
	    {
	      first_pass = _print_extra_eol(extra_eol, first_pass, errors);
	      _print_dirname(args, extra_eol, dir);
	      _print_files(dir, dir_ptr, options);
	    }
	  closedir(dir_ptr);
	  free(dir);
	}
      args->idx += 1;
    }
  _if_no_arg(first_pass, errors, options);
  return ;
}
