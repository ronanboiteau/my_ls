/*
** ls_data.h for my_ls in /home/boitea_r
** 
** Made by Ronan Boiteau
** Login   <boitea_r@epitech.net>
** 
** Started on  Sun Nov 29 20:09:05 2015 Ronan Boiteau
** Last update Sun Nov 29 20:13:30 2015 Ronan Boiteau
*/

#ifndef LS_DATA_H_
# define LS_DATA_H_

typedef struct	s_data
{
  int		only_errors;
  int		extra_eol;
  int		full_path;
  char		*filename;
  char		*dir;
  int		idx;
}		t_data;

#endif /* !LS_DATA_H_ */
