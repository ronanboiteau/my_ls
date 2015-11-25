/*
** paths.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:15:48 2015 Ronan Boiteau
** Last update Wed Nov 25 23:57:59 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"

static void		_arg_isfile(char *dir, int only_errors, int *extra_eol)
{
  DIR			*dir_ptr;
  struct dirent		*entry;
  int			found;
  int			idx;
  char			*filename;
  int			full_path;

  filename = my_strdup(dir);
  full_path = FALSE;
  idx = 0;
  while (dir[idx])
    {
      if (dir[idx] == '/')
	full_path = TRUE;
      idx += 1;
    }
  if (full_path == TRUE)
    {
      idx = my_strlen(dir) - 1;
      while (dir[idx] && dir[idx] != '/')
	{
	  dir[idx] = '\0';
	  idx -= 1;
	}
      idx = my_strlen(dir);
      while (filename[idx] && filename[idx] != '/')
	idx -= 1;
      filename += idx + 1;
    }
  else
    dir = my_strdup(".");
  dir_ptr = opendir(dir);
  found = FALSE;
  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (match(entry->d_name, filename))
  	{
  	  if (only_errors == FALSE)
  	    {
	      if (full_path == TRUE)
		my_putstr(dir);
  	      my_putstr(entry->d_name);
  	      my_putchar('\n');
  	      *extra_eol = TRUE;
  	    }
  	  found = TRUE;
  	}
    }
  if (found == FALSE && only_errors == TRUE)
    my_put_error("ssss", "ls: cannot access ", dir, filename, ": No such file or directory\n");
  return ;
}

int			_count_valid_paths(int argc, char **argv, int errors)
{
  int			idx;
  int			paths;

  paths = 0;
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	paths += 1;
      idx += 1;
    }
  return (paths - errors);
}

int			_check_args(int argc,

				    char **argv,
				    int only_errors,
				    int *extra_eol)
{
  DIR			*dir_ptr;
  char			*dir;
  int			idx;
  int			errors;

  errors = 0;
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	{
	  dir = my_strdup(argv[idx]);
	  if ((dir_ptr = opendir(dir)) == NULL)
	    {
	      _arg_isfile(dir, only_errors, extra_eol);
	      errors += 1;
	    }
	  free(dir);
	  closedir(dir_ptr);
	}
      idx += 1;
    }
  return (errors);
}
