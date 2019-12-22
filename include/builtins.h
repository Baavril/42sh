/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/12/16 14:51:02 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define UNVALID_ALIAS			" \n\t/$=()\'`\"|&><\\;"

/*
** Utils for builtins
*/
int				ft_putenv_table(char ***env, const char *name,
				const char *value, int overwrite);
int				is_a_builtin(char *cmd);

int				ft_inbintable(char *bin_name, char **ret_val, char flag);
void			ft_insert_bintable(char *bin_name, char *bin_path,
													unsigned int hit_val);
void			ft_free_bintable(void);
void			ft_treat_alias(char **first_arg);
void			ft_free_aliastable(void);

/*
** Functions in builtins.c
*/
int				cmd_unsetenv(int argc, char **argv);
int				cmd_setenv(int argc, char **argv);
int				cmd_echo(int agrc, char **argv);
int				cmd_type(int agrc, char **argv);
int				cmd_exit(int argc, char **argv);
int				cmd_test(int argc, char **argv);
int				cmd_true(int argc, char **argv);
int				cmd_false(int argc, char **argv);
int				cmd_env(int argc, char **argv);
int				cmd_pwd(int argc, char **argv);
int				cmd_hash(int argc, char **argv);
int				cmd_cd(int argc, char **argv);
int				cmd_history(int argc, char **argv);
int				cmd_alias(int ac, char **av);
int				cmd_unalias(int ac, char **av);
int				cmd_set(int argc, char **argv);
int				cmd_unset(int argc, char **argv);
int				cmd_export(int argc, char **argv);
int				cmd_fc(int argc, char **argv);
int				cmd_fg(int ac, char **av);
int				cmd_bg(int ac, char **av);
int				cmd_jobs(int ac, char **av);

/*
** Functions in builtins_dispatcher.c
*/
int				builtins_dispatcher(char **argv);
typedef struct	s_builtins
{
	const char *const	key;
	int		(*const f)(int, char**);
}				t_builtins;

_Bool				prior_builtin(char *str);
struct	s_prior_builtin
{
	const char *const	pbuiltin;
};

extern const t_builtins	g_builtins[];

struct	s_keywords
{
	const char *const	keyword;
};

#endif
