#ifndef LS_OPTIONS_H_
# define LS_OPTIONS_H_

# include "ls_system.h"

char		*_find_options(t_args *args);
void		_check_options(char *given_opt);
void		_no_option(DIR *dir_ptr);
void		_option_all(DIR *dir_ptr);
void		_option_reverse(DIR *dir_ptr, char *dir, int files);
int		_count_files(DIR *dir_ptr);

#endif /* !LS_OPTIONS_H_ */
