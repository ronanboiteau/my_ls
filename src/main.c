/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Sun Nov 29 20:54:52 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"
#include "ls_options.h"
#include "ls_paths.h"
#include "ls_args.h"

static void		_print_files(char *dir, DIR *dir_ptr, char *options)
{
  if (my_strstr(options, "l"))
    _option_long(dir_ptr);
  else if (my_strstr(options, "r"))
    _option_reverse(opendir(dir), dir, _count_files(dir_ptr));
  else if (my_strstr(options, "f") || my_strstr(options, "aU") ||
      my_strstr(options, "Ua") || my_strstr(options, "a"))
    _option_all(dir_ptr);
  else if (options == NULL)
    _no_option(dir_ptr);
  return ;
}

static void		_iterate_args(t_args *args,
				      char *options,
				      int errors)
{
  DIR			*dir_ptr;
  char			*dir;
  int			first_pass;
  int			extra_eol;

  extra_eol = FALSE;
  first_pass = TRUE;
  _check_args(args, FALSE, &extra_eol);
  args->idx = 1;
  while (args->idx < args->argc)
    {
      if (args->argv[args->idx][0] != '-')
	{
	  dir = my_strdup(args->argv[args->idx]);
	  if ((dir_ptr = opendir(dir)) != NULL)
	    {
	      if (first_pass == TRUE)
		{
		  if (errors > 0 && extra_eol == TRUE)
		    my_putchar('\n');
		  first_pass = FALSE;
		}
	      else
		my_putchar('\n');
	      if (_count_valid_paths(args, errors) > 1 ||
		  extra_eol == TRUE)
		{
		  my_putstr(dir);
		  my_putstr(":\n");
		}
	      _print_files(dir, dir_ptr, options);
	    }
	  closedir(dir_ptr);
	  free(dir);
	}
      args->idx += 1;
    }
  if (first_pass == TRUE && errors == 0)
    {
      dir = my_strdup(".");
      if ((dir_ptr = opendir(dir)) != NULL)
	_print_files(dir, dir_ptr, options);
      closedir(dir_ptr);
      free(dir);
    }
  return ;
}

int			main(int argc, char **argv)
{
  t_args		*args;
  char			*options;
  int			errors;

  args = malloc(sizeof(t_args));
  args->argv = argv;
  args->argc = argc;
  args->idx = 0;
  options = _find_options(args);
  _check_options(options);
  errors = _check_args(args, TRUE, NULL);
  _iterate_args(args, options, errors);
  free(options);
  free(args);
  return (EXIT_SUCCESS);
}
