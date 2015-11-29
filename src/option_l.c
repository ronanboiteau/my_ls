/*
** option_l.c for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 19:46:16 2015 Ronan Boiteau
** Last update Sun Nov 29 22:35:28 2015 Ronan Boiteau
*/

#include "my.h"
#include "ls_system.h"

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

/* static void		_print_perms(mode_t mode) */
/* { */
/*   (mode & S_IFMT) == S_IFREG ? my_putchar('-') : my_putchar('a'); */
/*   return ; */
/* } */

void			_option_long(DIR *dir_ptr)
{
  struct dirent		*entry;
  struct stat		file_info;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (stat(entry->d_name, &file_info) == -1)
	my_exit(EXIT_SERIOUS_TROUBLE, "s", "stat() failed!");
      if (entry->d_name[0] != '.')
	{
	  /* _print_perms(file_info.st_mode); */
	  _print_usr_grp(file_info.st_uid, file_info.st_gid);
	  my_putstr(entry->d_name);
	  my_putchar('\n');
	}
    }
  return ;
}
