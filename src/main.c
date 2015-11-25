/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Wed Nov 25 19:54:33 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "system.h"

static char		*_find_path(int argc, char **argv)
{
  int			idx;

  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	return (argv[idx]);
      idx += 1;
    }
  return (".");
}

static char		*_find_options(int argc, char **argv)
{
  char			*new_opt;
  char			*options;
  int			idx;

  options = NULL;
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] == '-')
	{
	  new_opt = NULL;
	  if ((new_opt = malloc(sizeof(char) * my_strlen(argv[idx]) +
				my_strlen(options) + 1)) == NULL)
	    {
	      my_putstr_fd(2, "Out of memory! malloc() failed\n");
	      exit(EXIT_SERIOUS_TROUBLE);
	    }
	  if (options != NULL)
	    my_strncpy(new_opt, options, my_strlen(options));
	  options = my_strncat(new_opt, argv[idx] + 1, my_strlen(argv[idx] + 1));
	}
      idx += 1;
    }
  return (options);
}

static void		_check_options(char *given_opt)
{
  unsigned int		idx_given;
  unsigned int		idx_auth;
  int			found_opt;
  char			*authorized_opt;

  authorized_opt = my_strdup("aUf");
  idx_given = 0;
  while (given_opt != NULL && given_opt[idx_given])
    {
      idx_auth = 0;
      found_opt = FALSE;
      while (authorized_opt[idx_auth])
	{
	  if (given_opt[idx_given] == authorized_opt[idx_auth])
	    found_opt = TRUE;
	  idx_auth += 1;
	}
      if (found_opt == FALSE)
	my_exit(EXIT_SERIOUS_TROUBLE, "scs", "ls: invalid option -- '", given_opt[idx_given], "'\n");
      idx_given += 1;
    }
  free(authorized_opt);
  return ;
}

/* struct stat	sb; */
/* if (stat('./toto.txt', &sb) */
/* static int		_recursive_print(char *dir) */
/* { */
/*   DIR			*dirp; */
/*   struct dirent		*entry; */

/*   if ((dirp = opendir(dir)) == NULL) */
/*     return (EXIT_FAILURE); */
/*   else */
/*     while ((entry = readdir(dirp)) != NULL) */
/*       { */
/* 	my_putstr(entry->d_name); */
/* 	my_putchar('\n'); */
/*       } */
/*   return (EXIT_SUCCESS); */
/* } */

static void		_print_files(/* char *dir,  */DIR *dirp, char *options)
{
  struct dirent		*entry;

  /* if (match(options, "*R*")) */
  /*   _recursive_print(dir); */
  while ((entry = readdir(dirp)) != NULL)
    {
      if (my_strstr(options, "f") || my_strstr(options, "aU") ||
	  my_strstr(options, "Ua"))
	{
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
      else if (!match(entry->d_name, ".*") && my_strstr(options, "U"))
	{
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
      else if (options == NULL && !match(entry->d_name, ".*"))
	{
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
    }
  return ;
}

static void		_arg_isfile(char *dir)
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
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	  found = TRUE;
	}
    }
  if (found == FALSE)
    my_put_error("sss", "ls: cannot access ", dir, ": No such file or directory\n");
  return ;
}

static int		_count_paths(int argc, char **argv)
{
  int			idx;
  int			paths;

  paths = 0;
  idx = 0;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	paths += 1;
      idx += 1;
    }
  return (paths);
}

int			main(int argc, char **argv)
{
  DIR			*dirp;
  char			*dir;
  char			*options;
  int			idx;

  options = _find_options(argc, argv);
  _check_options(options);
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	{
	  dir = my_strdup(argv[idx]);
	  if ((dirp = opendir(dir)) == NULL)
	    _arg_isfile(dir);
	  else
	    _print_files(/* dir,  */dirp, options);
	  free(dir);
	}
      idx += 1;
    }
  free(options);
  closedir(dirp);
  return (EXIT_SUCCESS);
}

/*
** ls | cat
**
** Environnement interactif ou pas ?
** Si non pas de couleurs, etc -> OBLIGATOIRE
** Si oui termcaps (couleurs, mise en page) -> BONUS
**
** Handled options:
** -aU
** -f
** -U
*/
