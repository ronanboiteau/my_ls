/*
** paths.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Wed Nov 25 21:15:48 2015 Ronan Boiteau
** Last update Wed Nov 25 22:32:36 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"

static void		_arg_isfile(char *dir, int only_errors, int *extra_eol)
{
  DIR			*dirp;
  struct dirent		*entry;
  int			found;

  dirp = opendir(".");
  found = FALSE;
  while ((entry = readdir(dirp)) != NULL)
    {
      if (match(entry->d_name, dir))
	{
	  if (only_errors == FALSE)
	    {
	      my_putstr(entry->d_name);
	      my_putchar('\n');
	      *extra_eol = TRUE;
	    }
	  found = TRUE;
	}
    }
  if (found == FALSE && only_errors == TRUE)
    my_put_error("sss", "ls: cannot access ", dir, ": No such file or directory\n");
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
  DIR			*dirp;
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
	  if ((dirp = opendir(dir)) == NULL)
	    {
	      _arg_isfile(dir, only_errors, extra_eol);
	      errors += 1;
	    }
	  free(dir);
	  closedir(dirp);
	}
      idx += 1;
    }
  return (errors);
}
