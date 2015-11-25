/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Wed Nov 25 23:59:10 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"
#include "ls_options.h"
#include "ls_paths.h"

/* struct stat	sb; */
/* if (stat('./toto.txt', &sb) */
/* static int		_recursive_print(char *dir) */
/* { */
/*   DIR			*dir_ptr; */
/*   struct dirent		*entry; */

/*   if ((dir_ptr = opendir(dir)) == NULL) */
/*     return (EXIT_FAILURE); */
/*   else */
/*     while ((entry = readdir(dir_ptr)) != NULL) */
/*       { */
/* 	my_putstr(entry->d_name); */
/* 	my_putchar('\n'); */
/*       } */
/*   return (EXIT_SUCCESS); */
/* } */

static void		_print_files(/* char *dir,  */DIR *dir_ptr, char *options)
{
  struct dirent		*entry;

  /* if (match(options, "*R*")) */
  /*   _recursive_print(dir); */
  while ((entry = readdir(dir_ptr)) != NULL)
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

void			_iterate_args(int argc,
				      char **argv,
				      char *options,
				      int errors)
{
  DIR			*dir_ptr;
  char			*dir;
  int			idx;
  int			first_pass;
  int			extra_eol;

  extra_eol = FALSE;
  _check_args(argc, argv, FALSE, &extra_eol);
  first_pass = TRUE;
  idx = 1;
  while (idx < argc)
    {
      if (argv[idx][0] != '-')
	{
	  dir = my_strdup(argv[idx]);
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
	      if (_count_valid_paths(argc, argv, errors) > 1 ||
		  extra_eol == TRUE)
		{
		  my_putstr(dir);
		  my_putstr(":\n");
		}
	      _print_files(/* dir,  */dir_ptr, options);
	    }
	  free(dir);
	}
      idx += 1;
    }
  if (first_pass == TRUE && errors == 0)
    {
      dir = my_strdup(".");
      if ((dir_ptr = opendir(dir)) != NULL)
	_print_files(/* dir,  */dir_ptr, options);

    }
  return ;
}

int			main(int argc, char **argv)
{
  char			*options;
  int			errors;

  options = _find_options(argc, argv);
  _check_options(options);
  errors = _check_args(argc, argv, TRUE, NULL);
  _iterate_args(argc, argv, options, errors);
  free(options);
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
**
** make re && ./my_ls . . ausret aunrsetauir aunsriet Make* lib
** make re && ./my_ls Makefile .
*/
