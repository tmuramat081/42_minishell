/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:21:31 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 14:29:34 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libast.h"
# include "libft.h"
# include "parser.h"
# include "lexer.h"
# include "minishell.h"


t_ast_node	*parse_command_line(t_vector *tokens, t_token *curr_token);
t_ast_node	*parse_pipe(t_vector *tokens, t_token *curr_token);
t_ast_node	*parse_command(t_vector *tokens, t_token *curr_token);
t_ast_node	*parse_simple_command(t_vector *tokens, t_token *curr_token);
t_ast_node	*parse_token_list(t_vector *tokens, t_token *curr_token);
bool		term(t_vector *tokens, t_token_type toketype, t_token **curr_token, char **buff);

#endif