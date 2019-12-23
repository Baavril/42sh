/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:04:49 by yberramd          #+#    #+#             */
/*   Updated: 2019/09/19 15:33:38 by yberramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H
# include <stdlib.h>
# include <dirent.h>
# include <stdbool.h>
# include "libft.h"

typedef struct		s_tst
{
	char			c;
	_Bool			end;
	struct s_tst	*left;
	struct s_tst	*middle;
	struct s_tst	*right;
}					t_tst;

t_tst	*ft_tst(void);
void	del_double_char(char **tab2);
void	print_double_char(char **tab);
void	del_tst(t_tst *tst);
int		search_tst(t_tst *tst, char *str);
int 	ft_auto_completion(t_tst *tst, char *input, char ***words);

#endif
