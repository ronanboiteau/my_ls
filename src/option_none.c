#include <stdlib.h>
#include "my.h"
#include "ls_system.h"

void			_no_option(DIR *dir_ptr)
{
  struct dirent		*entry;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      if (entry->d_name[0] != '.')
	{
	  my_printf("%s\n", entry->d_name);
	}
    }
  return ;
}
