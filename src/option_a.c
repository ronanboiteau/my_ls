#include <stdlib.h>
#include "my.h"
#include "ls_system.h"

void			_option_all(DIR *dir_ptr)
{
  struct dirent		*entry;

  while ((entry = readdir(dir_ptr)) != NULL)
    {
      my_printf("%s\n", entry->d_name);
    }
  return ;
}
