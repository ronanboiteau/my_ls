#include <stdbool.h>
#include <stdlib.h>
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
	return (true);
      idx += 1;
    }
  return (false);
}

static void		_file_not_found(int only_errors,
					char *dir,
					char *filename,
					int full_path)
{
  if (only_errors == true)
    {
      if (full_path == true)
  	my_dprintf(2, "ls: cannot access %s%s: No such file or directory\n", dir, filename);
      else
	my_dprintf(2, "ls: cannot access %s: No such file or directory\n", filename);
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
  found = false;
  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (match(path->filename, entry->d_name))
 	{
  	  if (only_errors == false)
  	    {
  	      if (full_path == true)
  		my_printf("%s", path->dir);
  	      my_printf("%s\n", entry->d_name);
  	      *extra_eol = true;
  	    }
  	  found = true;
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

  if (full_path == true)
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
  if (found == false && only_errors == true)
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
