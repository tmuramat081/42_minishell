/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:21:31 by tmuramat          #+#    #+#             */
/*   Updated: 2023/01/12 00:08:42 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libast.h"
# include "libft.h"
# include "ft_vector.h"
# include "ft_deque.h"
# include "minishell.h"

typedef struct s_command
{
	t_deque *arg;
	t_deque *redirect;
}   t_command;

t_ast		*parser(t_vector *tokens, t_shell *msh);
t_ast_node	*parse_separator(t_vector *tokens, t_token **curr);
t_ast_node	*parse_pipeline(t_vector *tokens, t_token **curr);
t_ast_node	*parse_simple_cmd(t_vector *tokens, t_token **curr);
t_ast_node	*parse_redirect(t_vector *tokens, t_token **curr);
t_ast_node	*parse_command(t_vector *tokens, t_token **curr);
t_ast_node	*parse_argument(t_vector *tokens, t_token **curr);
bool		consume_token(t_vector *tokens, t_token_type toketype, t_token **curr, char **buff);

#endif