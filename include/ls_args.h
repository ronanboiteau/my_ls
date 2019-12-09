#ifndef LS_ARGS_H_
# define LS_ARGS_H_

typedef struct	s_args
{
  int		argc;
  char		**argv;
  int		idx;
}		t_args;

void		_iterate_args(t_args *args,
			      char *options,
			      int errors,
			      int first_pass);

#endif /* !LS_ARGS_H_ */
