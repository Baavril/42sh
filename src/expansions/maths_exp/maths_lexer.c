/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:22:17 by tgouedar          #+#    #+#             */
/*   Updated: 2020/01/08 15:42:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_interne.h"

static size_t	ft_arg_len(char *word)
{
	size_t	i;

	i = 0;
	while ((word[i]) && !(ft_isin(word[i], OPERATOR)))
		i++;
	return (i);
}

void			ft_push_tokens(char *word, t_maths_list **token_list)
{
	size_t			i;
	char			flag;
	t_maths_token	*token;

	token = NULL;
	while (*word)
	{
		ft_putendl(word);
		if (ft_isin(*word, OPERATOR))
		{
			i = ft_op_len(word);
			flag = IS_OP;
		}
		else
		{
			i = ft_arg_len(word);
			flag = IS_ARG;
		}
		token = ft_init_maths_token(word, i, flag);
		ft_putstr("new token: ");
		ft_putendl(token->token);
		ft_lstadd_back((t_list**)token_list, ft_lstnew(token, sizeof(t_maths_token)));
		word += i;
	}
	ft_putendl(NULL);
}

t_maths_list			*ft_maths_lexer(char *expr)
{
	t_maths_list	*token_list;
	char			**words;
	size_t			i;

	i = 0;
	token_list = NULL;
	words = ft_strsplit(expr, IFS);
	while (words[i])
	{
		ft_push_tokens(words[i], &token_list);
		i++;
	}
//	ft_tabfree(words);
	return (token_list);
}
