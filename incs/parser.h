/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:21:31 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/30 18:31:59 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libast.h"
# include "libft.h"
# include "parser.h"
# include "lexer.h"
# include "minishell.h"


t_ast_node	*parse_separator(t_vector *tokens, t_token **curr);
t_ast_node	*parse_pipeline(t_vector *tokens, t_token **curr);
t_ast_node	*parse_redirection(t_vector *tokens, t_token **curr);
t_ast_node	*parse_command(t_vector *tokens, t_token **curr);
t_ast_node	*parse_argument(t_vector *tokens, t_token **curr);
bool		consume_token(t_vector *tokens, t_token_type toketype, t_token **curr, char **buff);

#endif