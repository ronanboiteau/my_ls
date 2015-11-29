/*
** handle_args.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 21:18:20 2015 Ronan Boiteau
** Last update Sun Nov 29 23:23:58 2015 Ronan Boiteau
*/

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
  if (first_pass == TRUE)
    {
      if (errors > 0 && extra_eol == TRUE)
	my_putchar('\n');
      first_pass = FALSE;
    }
  else
    my_putchar('\n');
  return (first_pass);
}

static void		_print_dirname(t_args *args,
				       int extra_eol,
				       char *dir)
{
  if (_count_valid_paths(args) > 1 ||
      extra_eol == TRUE)
    {
      my_putstr(dir);
      my_putstr(":\n");
    }
  return ;
}

static void		_if_no_arg(int first_pass,
				   int errors,
				   char *options)
{
  DIR			*dir_ptr;
  char			*dir;

  if (first_pass == TRUE && errors == 0)
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

  extra_eol = FALSE;
  _check_args(args, FALSE, &extra_eol);
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
