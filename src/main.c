/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Thu Nov 26 19:20:11 2015 Ronan Boiteau
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
/*   closedir(dir_ptr); */
/*   return (EXIT_SUCCESS); */
/* } */

static void		_option_all(DIR *dir_ptr)
{
  struct dirent		*entry;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      my_putstr(entry->d_name);
      my_putchar('\n');
    }
  return ;
}

static void		_no_option(DIR *dir_ptr)
{
  struct dirent		*entry;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (entry->d_name[0] != '.')
	{
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
    }
  return ;
}

static void		_print_files(/* char *dir,  */DIR *dir_ptr, char *options)
{
  /* if (my_strstr(options, "R")) */
  /*   _recursive_print(dir); */
  if (my_strstr(options, "f") || my_strstr(options, "aU") ||
      my_strstr(options, "Ua") || my_strstr(options, "a"))
    _option_all(dir_ptr);
  else if (options == NULL)
    _no_option(dir_ptr);
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
	  closedir(dir_ptr);
	  free(dir);
	}
      idx += 1;
    }
  if (first_pass == TRUE && errors == 0)
    {
      dir = my_strdup(".");
      if ((dir_ptr = opendir(dir)) != NULL)
	_print_files(/* dir,  */dir_ptr, options);
      closedir(dir_ptr);
      free(dir);
    }
  return ;
}

int			main(int argc, char **argv)
{
  char			*options;
  int			errors;
  int			idx;

  options = _find_options(argc, argv);
  _check_options(options);
  errors = _check_args(argc, argv, TRUE, NULL);
  _iterate_args(argc, argv, options, errors);
  free(options);
  return (EXIT_SUCCESS);
}

/*
** Currently handling:
** -a
** -f -Ua -aU
**
** Todo:
** -Rlrtd
** Bonus:
** -uFg
** -U
** -A
** --help
** --directory, etc. (long options)
**
** SEGFAULTS:
** ./my_ls ls/../
** ./my_ls my_ls/../
** ./my_ls /.ls/
** ./my_ls *u
** ./my_ls /dev/sda* *r
*/
