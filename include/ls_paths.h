#ifndef LS_PATHS_H_
# define LS_PATHS_H_

# include "ls_args.h"

typedef struct	s_path
{
  char		*dir;
  char		*filename;
}		t_path;

int		_count_valid_paths(t_args *args);
int		_check_args(t_args *args,
			    int only_errors,
			    int *extra_eol);

#endif /* !LS_PATHS_H_ */
