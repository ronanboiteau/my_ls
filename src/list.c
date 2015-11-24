/*
** list.c for push_swap in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Tue Nov  3 00:28:19 2015 Ronan Boiteau
** Last update Tue Nov 24 22:35:32 2015 Ronan Boiteau
*/

#include "my.h"
#include "my_macro.h"
#include "list.h"

void		_print_list(t_node *list_start)
{
  t_node	*tmp;

  while (tmp != NULL)
    {
      my_putstr(tmp->filename);
      my_putchar('\n');
      tmp = tmp->next;
    }
  return ;
}

void		_put_in_list(t_node *list_ptr, char *filename, int first)
{
  t_node	*new_elem;

  if (first == TRUE)
    {
      list_ptr->filename = my_strdup(filename);
      list_ptr->next = NULL;
    }
  while (list_ptr->next != NULL)
    list_ptr = list_ptr->next;
  if ((new_elem = malloc(sizeof(t_node))) == NULL)
    {
      my_putstr_fd(2, "malloc() failed: out of memory!\n");
      exit(1);
    }

  new_elem->filename = my_strdup(filename);
  new_elem->next = NULL;
  list_ptr->next = new_elem;
  return ;
}
