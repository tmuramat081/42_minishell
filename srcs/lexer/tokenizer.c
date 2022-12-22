/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:57:12 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/22 08:57:14 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

#define INIT_SIZE 36

bool	is_separator(char c)
{
	if (c == ' ' || c == '&' || c == '<' || c == '>'
		|| c == '|' || c == ';' || c == '\0')
		return (true);
	return (false);
}

char	*get_next_token(t_tokenizer *tokenizer)
{
	char	*startptr = tokenizer->pos;
	char	*endptr;
	char	*token;

	if (!tokenizer)
		return (NULL);
	if (tokenizer->pos == '\0')
		return (NULL);
	if (is_separator(*startptr) == true)
	{
		if (*startptr == '\0')
			return (NULL);
		token = (char *)malloc(2);
		token[0] = *startptr;
		token[1] = '\0';
		tokenizer->pos++;
		return (token);
	}
	if (*startptr == '\0')
		return (NULL);
	endptr = startptr;
	while (true)
	{
		if (is_separator(*(endptr + 1)) == true)
		{
			token = (char *)malloc((endptr - startptr) + 2);
			memcpy(token, startptr, (endptr - startptr) + 1);
			token[(endptr - startptr) + 1] = '\0';
			tokenizer->pos = endptr + 1;
			while (isspace(*tokenizer->pos))
				tokenizer->pos++;
			return (token);
		}
		endptr++;
	}
	return (NULL);
}

t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tk;

	tk = malloc(sizeof(t_tokenizer));
	tk->str = line;
	tk->pos = line;
	return (tk);
}

void	tokenizer(char *line)
{
	t_tokenizer	*tk;
	t_vector	*vec;
	char		*token;

	tk = init_tokenizer(line);
	vec = ft_vector_init(sizeof(char *), 10);
	while (true)
	{
		token = get_next_token(&tk);
		if (!token)
			break ;
		ft_vector_push_back(vec, token);
		free(token);
	}
	ft_vector_foreach(vec, print_token);
	//token = tokenizer(str);
}
