/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <baavril@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:52:32 by baavril           #+#    #+#             */
/*   Updated: 2020/02/29 16:13:20 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define MAX_DIR 8192
# define HIDEN_FILE '.'
# define CURRENT_DIR "."
# define PATH_DIR "/"
# define NEXT_DIR '/'
# define GLOBING 3

typedef struct		s_checker
{
	int				i;
	int				j;
	int				flag;
	char			c;
	char			len;
	char			*tmp;
	char			*ptm;
}					t_checker;

typedef struct		s_deploy
{
	int				i;
	int				j;
	int				flag;
	int				dash;
	char			*keep;
	char			*tmp;
	char			*ptm;
	char			*range;
}					t_deploy;

typedef struct		s_glob
{
	int				i;
	int				j;
	int				x;
	int				n;
	int				f;
	int				nul;
	char			*tmp_file;
	char			**free_dir;
	char			**dir;
	char			**tmp_dir;
	char			**ret;
	struct dirent	*filedata;
	DIR				*dirhandle;
}					t_glob;

typedef struct		s_pattern
{
	int				i;
	int				x;
	int				n;
	int				j;
	int				w;
	int				s;
	int				k;
	int				flag;
	int				len_s;
	int				len_m;
	char			c;
	int				diff;
}					t_pattern;

char				**globing(char **split, char *token);
int					scan_indepth_dirs(t_glob *var, char **indepth);
int					scan_current_dir(t_glob *var, char **indepth);
int					sort_ascii_tab(char **tab);
int					ft_strspecasecmp(char *s1, char *s2);
void				ft_str_swap(char **a, char **b);

char				*matching_ret(char *token, char *match, int flag);
char				*ft_strrev(char *token);
int					ft_spechrlen(char *token);
int					check_deploy(char *str, char *match, int flag,
																t_pattern *var);
int					get_deploy(char **match);
char				*ft_alpharange(char c, char x);
char				*ft_strneg(char *match);
int					ft_strlchr(char *str, char c);

char				*pattern_matching(char *token, char *match, int flag);
int					complex_pattern_matching(t_pattern *var, char *match,
																	char *str);
int					simple_pattern_matching(t_pattern *var, char *match,
																	char *str);
int					matching_patterns(t_pattern *var, char *match, char *str);
int					recursive_matching(t_pattern *var, char *match, char *str);
int					deployement_limit(t_pattern *var, char *match, char *str);
int					match_cmp(t_pattern *var, char *match, char *str);
int					deployement_support(t_pattern *var, char *match, char *str);
int					islast(t_pattern *var, char *str, char c);
int					deploy_case(t_pattern *var, char **str, t_checker *elem);
void				ft_freeintab(char **tab);
int					get_btw_square(char **match);

#endif
