/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:21:31 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/29 11:09:53 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define STR_RDIR ">"
# define STR_RRDIR ">>"
# define STR_LDIR "<"
# define STR_LLDIR "<<"
# define STR_SPACE " "
# define STR_PIPELINE "|"
# define STR_AMPERSAND "&"
# define STR_SEMICOLON ";"


# include "libast.h"
# include "libft.h"

typedef enum e_token_type {
	TOKEN_NONE,
	TOKEN_STR,
	TOKEN_RDIR,
	TOKEN_RRDIR,
	TOKEN_LDIR,
	TOKEN_LLDIR,
	TOKEN_SPACE,
	TOKEN_PIPELINE,
	TOKEN_AMPERSAND,
	TOKEN_SEMICOLON,
	TOKEN_NULL,
	TOKEN_END
}	t_token_type;

void		print_nodes(t_ast_node *tokens);

#endif