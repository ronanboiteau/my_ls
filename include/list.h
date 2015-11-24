/*
** list.h for push_swap in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov  8 18:48:40 2015 Ronan Boiteau
** Last update Tue Nov 24 22:35:39 2015 Ronan Boiteau
*/

#ifndef LIST_H_
# define LIST_H_

typedef struct	s_node
{
  char		*filename;
  struct s_node	*next;
}		t_node;

void		_print_list(t_node *list_start);
void		_put_in_list(t_node *list_ptr, char *filename, int first);

#endif /* !LIST_H_ */
