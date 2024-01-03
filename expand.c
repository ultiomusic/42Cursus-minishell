/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:22:03 by ohayek            #+#    #+#             */
/*   Updated: 2024/01/02 21:42:23 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sad(char *str)
{
	int	c;

	c = 1;
	while (str[c] && ft_allvalid(str[c]))
		c++;
	return (c - 1);
}

int	ft_sizeofexpanded(char *str, char **ev, t_global *mini)
{
	int	i;
	int	c;
	int	flag;

	ft_quicklyinitialize(&i, &flag, &c);
	while (str[++i])
	{
		if (str[i] == '$' && flag != 1 && ft_ifvalid(str[i + 1]))
		{
			c += ft_add_dollar(str + i, ev, mini);
			i += ft_sad(str + i);
		}
		else if (ft_check_flag_status(str, i, &flag))
			c++;
	}
	return (c);
}

char	*expander(char *str, char **ev, t_global *mini)
{
	char	*exp;
	int		mem;
	char	*mmm;

	mmm = ft_strdup(str);
	mem = ft_sizeofexpanded(mmm, ev, mini);
	exp = ft_calloc(mem + 2, sizeof(char));
	ft_expandmainly(&exp, str, ev, mini);
	free(mmm);
	return (exp);
}

void	ft_check_delete(t_global *mini, t_lexer *temp)
{
	while (temp)
	{
		if (!temp->str[0] && temp->is_quote == 0)
			ft_delete_node(temp->i, mini);
		temp = temp->next;
	}
}

void	ft_expand(t_global *mini)
{
	t_lexer	*temp;
	char	*to_expand;

	temp = mini->head;
	while (temp)
	{
		to_expand = ft_strdup(temp->str);
		if (temp->str)
			free(temp->str);
		temp->str = expander(to_expand, mini->env, mini);
		free(to_expand);
		temp = temp->next;
	}
	ft_check_delete(mini, mini->head);
}
