/*
** paths.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:15:48 2015 Ronan Boiteau
** Last update Sun Nov 29 22:40:19 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"
#include "ls_args.h"
#include "ls_paths.h"

static int		_isdir(char *dir)
{
  int			idx;

  idx = 0;
  while (dir[idx])
    {
      if (dir[idx] == '/')
	return (TRUE);
      idx += 1;
    }
  return (FALSE);
}

static void		_file_not_found(int only_errors,
					char *dir,
					char *filename,
					int full_path)
{
  if (only_errors == TRUE)
    {
      if (full_path == TRUE)
  	my_put_error("ssss", "ls: cannot access ", dir, filename,
		     ": No such file or directory\n");
      else
	my_put_error("sss", "ls: cannot access ", filename,
		     ": No such file or directory\n");
    }
  return ;
}

static int		_print_arg_files(t_path *path,
					 int only_errors,
					 int full_path,
					 int *extra_eol)
{
  DIR			*dir_ptr;
  int			found;
  struct dirent		*entry;

  dir_ptr = opendir(path->dir);
  found = FALSE;
  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (match(path->filename, entry->d_name))
 	{
  	  if (only_errors == FALSE)
  	    {
  	      if (full_path == TRUE)
  		my_putstr(path->dir);
  	      my_putstr(entry->d_name);
  	      my_putchar('\n');
  	      *extra_eol = TRUE;
  	    }
  	  found = TRUE;
  	}
    }
  return (found);
}

static void		_arg_isfile(t_path *path,
				    int only_errors,
				    int *extra_eol,
				    int full_path)
{
  DIR			*dir_ptr;
  int			idx;
  int			found;

  if (full_path == TRUE)
    {
      idx = my_strlen(path->dir) - 1;
      while (path->dir[idx] && path->dir[idx] != '/')
	{
	  path->dir[idx] = '\0';
	  idx -= 1;
	}
      idx = my_strlen(path->dir);
      while (path->filename[idx] && path->filename[idx] != '/')
	idx -= 1;
      path->filename += idx + 1;
      if ((dir_ptr = opendir(path->dir)) == NULL)
	return (_file_not_found(only_errors, path->dir, path->filename,
				full_path));
    }
  else
    path->dir = my_strdup(".");
  found = _print_arg_files(path, only_errors, full_path, extra_eol);
  if (found == FALSE && only_errors == TRUE)
    _file_not_found(only_errors, path->dir, path->filename, full_path);
}

int			_check_args(t_args *args,
				    int only_errors,
				    int *extra_eol)
{
  DIR			*dir_ptr;
  int			errors;
  t_path		*path;

  if ((path = malloc(sizeof(t_path))) == NULL)
    return (EXIT_SERIOUS_TROUBLE);
  errors = 0;
  args->idx = 1;
  while (args->idx < args->argc)
    {
      if (args->argv[args->idx][0] != '-')
	{
	  path->dir = my_strdup(args->argv[args->idx]);
	  path->filename = my_strdup(args->argv[args->idx]);
	  if ((dir_ptr = opendir(path->dir)) == NULL)
	    {
	      _arg_isfile(path, only_errors, extra_eol, _isdir(path->dir));
	      errors += 1;
	    }
	  closedir(dir_ptr);
	}
      args->idx += 1;
    }
  free(path);
  return (errors);
}
