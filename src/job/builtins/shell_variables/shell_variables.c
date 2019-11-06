/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:07:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

int	append_shvar(const char *const name, const char *const content)
{
	struct s_shvar		*tmp;

	tmp = g_shellvar;
	while (tmp->next_var)
	{
		tmp = tmp->next_var;
	}
	tmp->next_var = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp)
		return (e_cannot_allocate_memory);
	tmp = tmp->next_var;
	tmp->value = ft_strdup(name);
	tmp->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp->next_content)
		return (e_cannot_allocate_memory);
	tmp->next_content->value = ft_strdup(content);
	tmp->index = 0;
	tmp->next_var = NULL;
	return (e_success);
}

static int	assign_array(char *name, char **tokens)
{
	(void)name;
	(void)tokens;
	return (e_success);
}

static struct s_shvar	*find_root_of_var(const char *const name)
{
	struct s_shvar	*lookup;

	lookup = g_shellvar;
	if (g_shellvar)
	{
		while (lookup && ft_strcmp(name, lookup->value))
			lookup = lookup->next_var;
		if (lookup)
			return (lookup);
	}
	return (NULL);
}

static int insert_node(char *name, char *content, int index)
{
	struct s_shvar	*node;
	struct s_shvar	*previous;
	struct s_shvar	*next;
	struct s_shvar	*leaf;
	
	next = NULL;
	node = g_shellvar;
	previous = g_shellvar;
	while (node && ft_strcmp(node->value, name) < 0)
	{
		previous = node;
		node = node->next_var;
	}
	leaf = create_shvar_node(content, NULL, NULL, index);
	if (!leaf)
		return (e_cannot_allocate_memory);
	if (next)
		next = node;
	if (previous)
	{
		ft_printf("previous %s\n", name);
		previous->next_var = create_shvar_node(name, leaf, next, 0);
		if (!previous->next_var)
			return (e_cannot_allocate_memory);
	}
	else
	{
		g_shellvar = create_shvar_node(name, leaf, NULL, 0);
		if (!g_shellvar)
			return (e_cannot_allocate_memory);
	}
	return (e_success);
}

static int	assign_at_index(char *name, char *content, int index)
{
	struct s_shvar	*root;
	
	root = find_root_of_var(name);
	if (!root)
		insert_node(name, content, index);
	else /* the var exists, replace or add index */
	{
		return (e_success);
	}
	return (e_success);
}

static int	assign_shvar(char *name, char *content, int index, _Bool has_array_subscript)
{
	char *str;
	char *end;
	char **tok;

	tok = NULL;
	end = content;
	while (*end)
		++end;
	--end;
	if (index == -1)
	{
		if (has_array_subscript)
		{
			*end = '\0';
			++content;
			tok = ft_strsplit(content, ' ');
			if (!tok)
				return (e_cannot_allocate_memory);
			else
				return (assign_array(name, tok));
		}
		else
			return (assign_at_index(name, content, index));
	}
	else
	{
		if (has_array_subscript)
		{
			str = name;
			while (*str)
			{
				++str;
			}
			*str = '[';
			while (*str && *str != '=')
				++str;
			if (*str == '=')
				*str = '\0';
			psherror(e_cannot_assign_list_to_array_member, name, e_cmd_type);
			return (e_cannot_assign_list_to_array_member);
		}
		else
		{
			assign_at_index(name, content, index);
			return (e_success);
		}
		
	}
}

int	shellvar_assignement(const char *const str)
{ /* parsing of str containing a shell variable assignement */
	char 	*content;
	char 	*name;
	int		index;
	int		ret;
	_Bool	has_array_subscript;
	
	name = ft_strdup(str);
	if (!name)
		return (e_cannot_allocate_memory);
	content = ft_strstr(name, "=");
	*content = '\0';
	++content;
	index = get_index(name);
	has_array_subscript = contains_array_subscript(content);
	if (index != -1 && has_array_subscript)
	{
		psherror(e_cannot_assign_list_to_array_member, name, e_cmd_type);
		return (e_cannot_assign_list_to_array_member);
	}
	ret = assign_shvar(name, content, index, has_array_subscript);
	ft_memdel((void**)&name);
	return (ret);
}