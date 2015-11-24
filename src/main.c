/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Tue Nov 24 22:37:38 2015 Ronan Boiteau
*/

#include <sys/stat.h>
#include <dirent.h>
#include "my.h"
#include "my_macro.h"
#include "list.h"

static char		*_find_options(int argc, char **argv)
{
  char			*new_opt;
  char			*options;
  int			idx;

  options = NULL;
  idx = 0;
  while (idx < argc)
    {
      if (argv[idx][0] == '-')
	{
	  new_opt = NULL;
	  if ((new_opt = malloc(sizeof(char) * my_strlen(argv[idx]) +
				my_strlen(options) + 1)) == NULL)
	    {
	      my_putstr_fd(2, "Out of memory! malloc() failed\n");
	      exit(EXIT_FAILURE);
	    }
	  if (options != NULL)
	    my_strncpy(new_opt, options, my_strlen(options));
	  options = my_strncat(new_opt, argv[idx] + 1, my_strlen(argv[idx] + 1));
	}
      idx += 1;
    }
  return (options);
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

static void		_print_files(char *dir, DIR *dirp, char *options)
{
  struct dirent		*entry;

  /* if (match(options, "*R*")) */
  /*   _recursive_print(dir); */
  if (match(options, "*f*") || match(options, "*a*U*") ||
      match(options, "*U*a*"))
    {
      my_putstr(entry->d_name);
      my_putchar('\n');
    }
  else if (!match(entry->d_name, ".*") && match(options, "*U*"))
    {
      my_putstr(entry->d_name);
      my_putchar('\n');
    }
  else if (options == NULL && !match(entry->d_name, ".*"))
    {
      my_putstr(entry->d_name);
      my_putchar('\n');
    }
  return ;
}

static t_node		*_init_list(DIR *dirp)
{
  t_node		*list_start;
  t_node		*list_tmp;
  struct dirent		*entry;
  int			first_pass;

  list_start = malloc(sizeof(t_node));
  list_tmp = list_start;
  first_pass = TRUE;
  while ((entry = readdir(dirp)) != NULL)
    {
      if (first_pass == TRUE)
	{
	  _put_in_list(list_tmp, entry->d_name, TRUE);
	  first_pass = FALSE;
	}
      _put_in_list(list_tmp, entry->d_name, FALSE);
      _print_list(list_start);
      my_put_nbr(list_start);
    }
  return (list_start);
}

int			main(int argc, char **argv)
{
  DIR			*dirp;
  char			*dir;
  char			*options;
  t_node		*list;

  options = _find_options(argc, argv);
  dir = my_strdup(".");
  if ((dirp = opendir(dir)) == NULL)
    {
      my_putstr_fd(2, "ls: cannot access ");
      my_putstr_fd(2, dir);
      my_putstr_fd(2, ": No such file or directory\n");
      return (EXIT_FAILURE);
    }
  list = _init_list(dirp);
  _print_list(list);
  /* _print_files(dir, dirp, options); */
  free(options);
  free(list);
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
