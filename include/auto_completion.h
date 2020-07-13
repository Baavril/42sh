/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:04:49 by yberramd          #+#    #+#             */
/*   Updated: 2020/07/13 16:17:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H

# include <stdlib.h>
# include <dirent.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "shell_variables.h"
# include "libft.h"
# include "input.h"
# include "expansions.h"

typedef struct		s_tst
{
	char			c;
	_Bool			end;
	struct s_tst	*left;
	struct s_tst	*middle;
	struct s_tst	*right;
}					t_tst;

typedef struct		s_int
{
	int	len;
	int	index;
}					t_int;

t_tst				*ft_tst(void);
void				del_double_char(char **tab2);
void				print_double_char(char **tab);
void				ft_assign_tmp(char *d_name, int *i, int *y, char *tmp);
char				**ft_binary(t_tst *tst, char *input);
char				*ft_add_string(char *input, char **binary, int start);
char				**create_binary(char **path_dir);
int					go_to_char(t_tst **tst, char *input);
int					pos_start2(char *input, int start);
int					dynamic_comp(char **binary, char *input, char **equal,
										int start);
int					ft_env_var(char *input, int dollar, char ***words);
int					create_tst(char **binaires, t_tst **tst);
int					ft_string(char **buff, char **binary, t_tst *tst,
									t_cursor *cursor);
int					assign_words(t_tst *tst, char **words, char *input,
										int len);
int					del_tst(t_tst *tst);
int					ft_cmp_str(char *str1, char *str2);
int					init_w_dollar(int start, char *input, char ***w);
int					new_word(char *str, t_tst **tst, int i);
int					reinitialize_input(char *input, int cursor, char tmp,
										int ret);
int					search_tst(t_tst *tst, char *str);
int					ft_init_words(int *i, char ***words, char *input);
int					ft_auto_completion(t_tst *tst, char *input, char ***words,
											int start);
int					add_file(struct dirent *dirent, char ***words, int *i,
										char *point);
DIR					*ft_assign_char(char *input, char **words);
char				**ft_path(char *input);

#endif
