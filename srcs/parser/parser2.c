#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

t_ast_node* CMDLINE();		//	test all command line production orderwise
t_ast_node* CMDLINE1();		//	<job> ';' <command line>
t_ast_node* CMDLINE2();		//	<job> ';'
t_ast_node* CMDLINE3();		//	<job> '&' <command line>
t_ast_node* CMDLINE4();		//	<job> '&'
t_ast_node* CMDLINE5();		//	<job>

t_ast_node* JOB();			// test all job production in order
t_ast_node* JOB1();			// <command> '|' <job>
t_ast_node* JOB2();			// <command>

t_ast_node* CMD();			// test all command production orderwise
t_ast_node* CMD1();			//	<simple command> '<' <filename>
t_ast_node* CMD2();			//	<simple command> '>' <filename>
t_ast_node* CMD3();			//	<simple command>

t_ast_node* SIMPLECMD();	// test simple cmd production
t_ast_node* SIMPLECMD1();	// <pathname> <token list>

t_ast_node* TOKENLIST();	// test tokenlist production
t_ast_node* TOKENLIST1();	//	<token> <token list>
t_ast_node* TOKENLIST2();	//	EMPTY

// curtok token pointer
t_token	*curtok = NULL;

bool term(t_vector *tokens, t_token_type toketype, char** bufferptr)
{
	if (curtok == NULL)
		return false;
    if (curtok->type == toketype)
    {
		if (bufferptr != NULL) {
			*bufferptr = malloc(strlen(curtok->value) + 1);
			strcpy(*bufferptr, curtok->value);
		}
		curtok = (t_token *)ft_vector_next(tokens, (void *)curtok, 1);;
        return (true);
    }
	curtok = ft_vector_next(tokens, curtok, 1);;
    return (false);
}

t_ast_node* CMDLINE(t_vector *tokens)
{
    t_token *save = curtok;
    t_ast_node* node;

    if ((curtok = save, node = CMDLINE5(tokens)) != NULL)
        return (node);
    return NULL;
}

t_ast_node* CMDLINE1(t_vector *tokens)
{
    t_ast_node* jobNode;
    t_ast_node* cmdlineNode;
    t_ast_node* result;

    if ((jobNode = JOB(tokens)) == NULL)
        return NULL;
    if (!term(tokens, TOKEN_SEMICOLON, NULL)) {
        ast_node_delete(jobNode);
        return NULL;
    }
    if ((cmdlineNode = CMDLINE(tokens)) == NULL) {
        ast_node_delete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_SEQ);
    ast_attach_binary_branch(result, jobNode, cmdlineNode);

    return result;
}

t_ast_node* CMDLINE2(t_vector *tokens)
{
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((jobNode = JOB(tokens)) == NULL)
        return NULL;

	if (!term(tokens, TOKEN_SEMICOLON, NULL)) {
        ast_node_delete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_SEQ);
    ast_attach_binary_branch(result, jobNode, NULL);

    return result;
}

t_ast_node* CMDLINE3(t_vector *tokens)
{
    t_ast_node* jobNode;
    t_ast_node* cmdlineNode;
    t_ast_node* result;

    if ((jobNode = JOB(tokens)) == NULL)
        return NULL;

    if (!term(tokens, TOKEN_AMPERSAND, NULL)) {
        ast_node_delete(jobNode);
        return NULL;
    }

    if ((cmdlineNode = CMDLINE(tokens)) == NULL) {
        ast_node_delete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_BCKGRND);
    ast_attach_binary_branch(result, jobNode, cmdlineNode);

    return result;
}

t_ast_node* CMDLINE4(t_vector *tokens)
{
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((jobNode = JOB(tokens)) == NULL)
        return NULL;

	if (!term(tokens, TOKEN_AMPERSAND, NULL)) {
        ast_node_delete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_BCKGRND);
    ast_attach_binary_branch(result, jobNode, NULL);

    return result;
}

t_ast_node* CMDLINE5(t_vector *tokens)
{
    return JOB(tokens);
}

t_ast_node* JOB(t_vector *tokens)
{
    t_token* save = curtok;
    t_ast_node* node;

    if ((curtok = save, node = JOB2(tokens)) != NULL)
        return node;

    return NULL;
}

t_ast_node* JOB1(t_vector *tokens)
{
    t_ast_node* cmdNode;
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((cmdNode = CMD(tokens)) == NULL)
        return NULL;

    if (!term(tokens, TOKEN_PIPELINE, NULL)) {
        ast_node_delete(cmdNode);
        return NULL;
    }

    if ((jobNode = JOB(tokens)) == NULL) {
        ast_node_delete(cmdNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_PIPE);
    ast_attach_binary_branch(result, cmdNode, jobNode);

    return result;
}

t_ast_node* JOB2(t_vector *tokens)
{
    return CMD(tokens);
}

t_ast_node* CMD(t_vector *tokens)
{
    t_token	*save = curtok;
    t_ast_node* node;

    if ((curtok = save, node = CMD3(tokens)) != NULL)
        return node;

    return NULL;
}

t_ast_node* CMD1(t_vector *tokens)
{
    t_ast_node* simplecmdNode;
    t_ast_node* result;

    if ((simplecmdNode = SIMPLECMD(tokens)) == NULL)
        return NULL;

    if (!term(tokens, TOKEN_RDIR, NULL))
	{
		ast_node_delete(simplecmdNode);
		return NULL;
	}

	char* filename;
	if (!term(tokens, TOKEN_NONE, &filename))
	{
		free(filename);
        ast_node_delete(simplecmdNode);
        return NULL;
    }

	result = malloc(sizeof(*result));
	ast_node_set_type(result, NODE_REDIRECT_IN);
	ast_node_set_data(result, filename);
	ast_attach_binary_branch(result, NULL, simplecmdNode);

    return result;
}

t_ast_node* CMD2(t_vector *tokens)
{
    t_ast_node* simplecmdNode;
    t_ast_node* result;

    if ((simplecmdNode = SIMPLECMD(tokens)) == NULL)
        return NULL;

	if (!term(tokens, TOKEN_LDIR, NULL)) {
		ast_node_delete(simplecmdNode);
		return NULL;
	}

	char* filename;
	if (!term(tokens, TOKEN_NONE, &filename)) {
		free(filename);
		ast_node_delete(simplecmdNode);
		return NULL;
	}

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_REDIRECT_OUT);
    ast_node_set_data(result, filename);
	ast_attach_binary_branch(result, NULL, simplecmdNode);

    return result;
}

t_ast_node *CMD3(t_vector *tokens)
{
    return SIMPLECMD(tokens);
}

t_ast_node* SIMPLECMD(t_vector *tokens)
{
    t_token	*save = curtok;
    return SIMPLECMD1(tokens);
}

t_ast_node* SIMPLECMD1(t_vector *tokens)
{
    t_ast_node* tokenListNode;
    t_ast_node* result;

    char* pathname;
    if (!term(tokens, TOKEN_NONE, &pathname))
        return NULL;

    tokenListNode = TOKENLIST(tokens);
    // we don't check whether tokenlistNode is NULL since its a valid grammer

    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_CMDPATH);
    ast_node_set_data(result, pathname);
	ast_attach_binary_branch(result, NULL, tokenListNode);
    return (result);
}

t_ast_node* TOKENLIST(t_vector *tokens)
{
    t_token *save = curtok;
    t_ast_node* node;

    if ((curtok = save, node = TOKENLIST1(tokens)) != NULL)
        return node;
    if ((curtok = save, node = TOKENLIST2(tokens)) != NULL)
        return node;
    return (NULL);
}

t_ast_node* TOKENLIST1(t_vector *tokens)
{
    t_ast_node* tokenListNode;
    t_ast_node* result;

    char* arg;
    if (!term(tokens, TOKEN_NONE, &arg))
        return NULL;

    tokenListNode = TOKENLIST(tokens);
    result = malloc(sizeof(*result));
    ast_node_set_type(result, NODE_ARGUMENT);
    ast_node_set_data(result, arg);
	ast_attach_binary_branch(result, NULL, tokenListNode);

	return (result);
}

t_ast_node	*TOKENLIST2()
{
	return (NULL);
}

int parse(t_vector *tokens)
{
	t_ast	*syntax_tree;

	if (tokens->len == 0)
		return (-1);
	curtok = ft_vector_front(tokens);
	syntax_tree = ast_init();
	syntax_tree->ast = CMDLINE(tokens);
	return (0);
}
