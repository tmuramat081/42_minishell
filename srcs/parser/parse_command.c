/**
 * @file parse_command.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析その4：コマンドパス ex."echo", "./bin/ls*""
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

//	<io_redirect>	::= '>'  filename
//					| 	'>>' filename
//					| 	'<'  filename
//					| 	'<<' here_end
t_redirect	*parse_io_redirect(t_vector *tokens, t_token **curr)
{
	int			type;
	t_redirect	*redirect;

	redirect = ft_xmalloc(sizeof(t_redirect));
	type = (*curr)->type;
	next_token(tokens, curr);
	redirect->dir = type; 
	redirect->file = scan_token(tokens, curr);
	if ((type & TOKEN_RDIR_INPUT) || (type & TOKEN_RDIR_HEREDOC))
		redirect->fd = 0;
	else if ((type & TOKEN_RDIR_OUTPUT) || (type & TOKEN_RDIR_APPEND))
		redirect->fd = 1;
	return (redirect);
}


//	<cmd_suffix>	::= 			 <io_redirect>
//					|	<cmd_suffix> <io_redirect>
//					|				 word
//					|	<cmd_suffix> word

/**
 * @brief 
 * 
 * @param tokens 
 * @param curr 
 * @return t_word* 
 */
t_command *parse_suffix(t_vector *tokens, t_token **curr)
{
	t_command	*command;
	char		*word;
	t_redirect	*redirect;

	command = command_create();
	while (true)
	{
		if ((*curr)->type & TOKEN_STR)
		{
			word = scan_token(tokens, curr);
			append_word(command->arg, word);
		}
		else if ((*curr)->type & TOKEN_RDIR)
		{
			redirect = parse_io_redirect(tokens, curr);
			append_word(command->redirect, redirect);
		}
		else
			break ;
	}
	return (command);
}

/**
 * @brief コマンドの解析
 * 
 * [BNF]
 * <simple_cmd>		::= cmd_name
 *					|	cmd_name <cmd_suffix>
 * [EBNF]
 * cmd_suffix ::= cmd_name | cmd_suffix ?
 * 
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node	*parse_simple_cmd(t_vector *tokens, t_token **curr)
{
	t_ast_node	*node;

	puts("start:command");
	if ((*curr)->type & TOKEN_END)
		return (NULL);
	node = ast_node_create();
	node->data = (t_command *)parse_suffix(tokens, curr);
	ast_node_set_type(node->data, NODE_COMMAND);
	puts("end:command");
	return (node);
}