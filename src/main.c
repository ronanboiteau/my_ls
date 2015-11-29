/*
** main.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Mon Nov 23 14:30:02 2015 Ronan Boiteau
** Last update Sun Nov 29 18:15:40 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "ls_system.h"
#include "ls_options.h"
#include "ls_paths.h"

/* static void		_option_recursive(DIR *dir_ptr, char *dir) */
/* { */
/*   struct dirent		*entry; */

/*   while (dir_ptr != NULL && (entry = readdir(dir_ptr)) != NULL) */
/*     { */
/*       if (entry->d_type == DT_DIR) */
/*       	{ */
/*       	  if (entry->d_name[0] != '.') */
/*       	    { */
/*       	      my_putchar('\n'); */
/* 	      my_putstr(dir); */
/* 	      if (dir[0] == '.') */
/* 		my_putchar('/'); */
/*       	      my_putstr(entry->d_name); */
/*       	      my_putstr(":\n"); */
/*       	      _option_recursive(opendir(entry->d_name), entry->d_name); */
/*       	    } */
/*       	} */
/*       else if (entry->d_name[0] != '.') */
/*       	{ */
/*       	  my_putstr(entry->d_name); */
/*       	  my_putchar('\n'); */
/*       	} */
/*     } */
/*   return ; */
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

static int		_count_files(DIR *dir_ptr)
{
  struct dirent		*entry;
  int			files;

  files = 0;
  while ((entry = readdir(dir_ptr)) != NULL)
    files += 1;
  return (files - 1);
}

static void		_option_reverse(DIR *dir_ptr, char *dir, int files)
{
  struct dirent		*entry;
  int			idx;

  idx = 0;
  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (idx == files)
  	{
  	  if (entry->d_name[0] != '.')
  	    {
  	      my_putstr(entry->d_name);
  	      my_putchar('\n');
  	    }
  	  _option_reverse(opendir(dir), dir, files - 1);
  	}
      idx += 1;
    }
  return ;
}

static void		_print_usr_grp(uid_t uid, gid_t gid)
{
  struct passwd		*usr_info;
  struct group		*grp_info;

  if ((usr_info = getpwuid(uid)) == NULL)
    my_exit(EXIT_SERIOUS_TROUBLE, "s", "getpwuid() failed to handle uid!");
  my_putstr(usr_info->pw_name);
  my_putchar(' ');
  if ((grp_info = getgrgid(gid)) == NULL)
    my_exit(EXIT_SERIOUS_TROUBLE, "s", "getgrgid() failed to handle gid!");
  my_putstr(grp_info->gr_name);
  my_putchar(' ');
  return ;
}

static void		_option_long(DIR *dir_ptr)
{
  struct dirent		*entry;
  struct stat		file_info;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (stat(entry->d_name, &file_info) == -1)
	my_exit(EXIT_SERIOUS_TROUBLE, "s", "stat() failed!");
      if (entry->d_name[0] != '.')
	{
	  _print_usr_grp(file_info.st_uid, file_info.st_gid);
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
    }
  return ;
}

static void		_print_files(char *dir, DIR *dir_ptr, char *options)
{
  /* _option_long(dir_ptr, dir, OPTIONS (for all)); */

  /* if (my_strstr(options, "R")) */
  /*   _option_recursive(dir_ptr, dir); */

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

static void		_iterate_args(int argc,
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
  first_pass = TRUE;
  _check_args(argc, argv, FALSE, &extra_eol);
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
	      _print_files(dir, dir_ptr, options);
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
	_print_files(dir, dir_ptr, options);
      closedir(dir_ptr);
      free(dir);
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
** Currently handling:
** -r
** -a
** -f -Ua -aU
**
** Todo:
** -Rltd
*/
