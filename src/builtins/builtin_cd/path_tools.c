/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:20:22 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/22 20:46:20 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_have_acces_right()
{


}

int		ft_is_valid_path()
{

}

int		ft_concatenate(char *pwd, char *target)
{


}

int		ft_treat_path(char *new_pwd, int opt_p)
{
	if (!new_pwd)
		return (ERROR);
	if (*new_pwd != '/')
	{
		if (new_pwd[0] == '.'
		&& (new_pwd[1] == '/' || (new_pwd[1] == '.' && new_pwd[2] == '/')))
			ft_concatenate(PWD, new_pwd);
//		else if (getenv(CD_PATH))
//		{
//			split = ft_str_split(CD_PATH);
//			while (split++)
//			{
//				tmp = concatenate(*split, new_pwd)
//				if (is_valid_dir())
//				{
//					free(new_pwd);
//					new_pwd = tmp;
//					break ;
//				}
//			}
//			ft_tabdel(&split);
//		}
		else
			ft_concatenate(PWD, new_pwd);
	}
	if (!opt_p)
		ft_simplify_path(&new_pwd);
//	if (!ft_have_acces_right(new_pwd))
		//Pemission denied/is file;
	return (ft_update_pwd());
}
