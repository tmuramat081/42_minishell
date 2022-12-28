#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*** Shell Grammer as given in the assignment question 1 ***/

/**
 *
	<command line>	::=  	<job>
						|	<job> '&'
						| 	<job> '&' <command line>
						|	<job> ';'
						|	<job> ';' <command line>

	<job>			::=		<command>
						|	< job > '|' < command >

	<command>		::=		<simple command>
						|	<simple command> '<' <filename>
						|	<simple command> '>' <filename>

	<simple command>::=		<pathname>
						|	<simple command>  <token>
 *
 *
 *
**/

/*** Shell Grammer for recursive descent parser ***/
/*** Removed left recursion and left factoring ***/

/**
 *
	<command line>	::= 	<job> ';' <command line>
						|	<job> ';'
						| 	<job> '&' <command line>
						|	<job> '&'
							<job>

	<job>			::=		<command> '|' <job>
						|	<command>

	<command>		::=		<simple command> '<' <filename> // this grammer is a bit incorrect, see grammer.llf
						|	<simple command> '>' <filename>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)

 *
 *
 *
**/

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
tok_t* curtok = NULL;

bool term(int toketype, char** bufferptr)
{
	if (curtok == NULL)
		return false;
	
    if (curtok->type == toketype)
    {
		if (bufferptr != NULL) {
			*bufferptr = malloc(strlen(curtok->data) + 1);
			strcpy(*bufferptr, curtok->data);
		}
		curtok = curtok->next;
        return true;
    }

    curtok = curtok->next;
    return false;
}

t_ast_node* CMDLINE()
{
    tok_t* save = curtok;

    t_ast_node* node;

    if ((curtok = save, node = CMDLINE1()) != NULL)
        return node;

    if ((curtok = save, node = CMDLINE2()) != NULL)
        return node;

    if ((curtok = save, node = CMDLINE3()) != NULL)
        return node;

    if ((curtok = save, node = CMDLINE4()) != NULL)
        return node;

    if ((curtok = save, node = CMDLINE5()) != NULL)
        return node;

    return NULL;
}

t_ast_node* CMDLINE1()
{
    t_ast_node* jobNode;
    t_ast_node* cmdlineNode;
    t_ast_node* result;

    if ((jobNode = JOB()) == NULL)
        return NULL;

    if (!term(CHAR_SEMICOLON, NULL)) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    if ((cmdlineNode = CMDLINE()) == NULL) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_SEQ);
    ASTreeAttachBinaryBranch(result, jobNode, cmdlineNode);

    return result;
}

t_ast_node* CMDLINE2()
{
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((jobNode = JOB()) == NULL)
        return NULL;

	if (!term(CHAR_SEMICOLON, NULL)) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_SEQ);
    ASTreeAttachBinaryBranch(result, jobNode, NULL);

    return result;
}

t_ast_node* CMDLINE3()
{
    t_ast_node* jobNode;
    t_ast_node* cmdlineNode;
    t_ast_node* result;

    if ((jobNode = JOB()) == NULL)
        return NULL;

    if (!term(CHAR_AMPERSAND, NULL)) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    if ((cmdlineNode = CMDLINE()) == NULL) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_BCKGRND);
    ASTreeAttachBinaryBranch(result, jobNode, cmdlineNode);

    return result;
}

t_ast_node* CMDLINE4()
{
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((jobNode = JOB()) == NULL)
        return NULL;

	if (!term(CHAR_AMPERSAND, NULL)) {
        t_ast_nodeDelete(jobNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_BCKGRND);
    ASTreeAttachBinaryBranch(result, jobNode, NULL);

    return result;
}

t_ast_node* CMDLINE5()
{
    return JOB();
}

t_ast_node* JOB()
{
    tok_t* save = curtok;

    t_ast_node* node;

    if ((curtok = save, node = JOB1()) != NULL)
        return node;

    if ((curtok = save, node = JOB2()) != NULL)
        return node;

    return NULL;
}

t_ast_node* JOB1()
{
    t_ast_node* cmdNode;
    t_ast_node* jobNode;
    t_ast_node* result;

    if ((cmdNode = CMD()) == NULL)
        return NULL;

    if (!term(CHAR_PIPE, NULL)) {
        t_ast_nodeDelete(cmdNode);
        return NULL;
    }

    if ((jobNode = JOB()) == NULL) {
        t_ast_nodeDelete(cmdNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_PIPE);
    ASTreeAttachBinaryBranch(result, cmdNode, jobNode);

    return result;
}

t_ast_node* JOB2()
{
    return CMD();
}

t_ast_node* CMD()
{
    tok_t* save = curtok;

    t_ast_node* node;

    if ((curtok = save, node = CMD1()) != NULL)
        return node;

    if ((curtok = save, node = CMD2()) != NULL)
        return node;

    if ((curtok = save, node = CMD3()) != NULL)
        return node;

    return NULL;
}

t_ast_node* CMD1()
{
    t_ast_node* simplecmdNode;
    t_ast_node* result;

    if ((simplecmdNode = SIMPLECMD()) == NULL)
        return NULL;

    if (!term(CHAR_LESSER, NULL)) {
		t_ast_nodeDelete(simplecmdNode);
		return NULL;
	}
	
	char* filename;
	if (!term(TOKEN, &filename)) {
		free(filename);
        t_ast_nodeDelete(simplecmdNode);
        return NULL;
    }

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_REDIRECT_IN);
    t_ast_nodeSetData(result, filename);
    ASTreeAttachBinaryBranch(result, NULL, simplecmdNode);

    return result;
}

t_ast_node* CMD2()
{
    t_ast_node* simplecmdNode;
    t_ast_node* result;

    if ((simplecmdNode = SIMPLECMD()) == NULL)
        return NULL;

	if (!term(CHAR_GREATER, NULL)) {
		t_ast_nodeDelete(simplecmdNode);
		return NULL;
	}
	
	char* filename;
	if (!term(TOKEN, &filename)) {
		free(filename);
		t_ast_nodeDelete(simplecmdNode);
		return NULL;
	}

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_REDIRECT_OUT);
    t_ast_nodeSetData(result, filename);
	ASTreeAttachBinaryBranch(result, NULL, simplecmdNode);

    return result;
}

t_ast_node* CMD3()
{
    return SIMPLECMD();
}

t_ast_node* SIMPLECMD()
{
    tok_t* save = curtok;
    return SIMPLECMD1();
}

t_ast_node* SIMPLECMD1()
{
    t_ast_node* tokenListNode;
    t_ast_node* result;

    char* pathname;
    if (!term(TOKEN, &pathname))
        return NULL;

    tokenListNode = TOKENLIST();
    // we don't check whether tokenlistNode is NULL since its a valid grammer

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_CMDPATH);
    t_ast_nodeSetData(result, pathname);
	ASTreeAttachBinaryBranch(result, NULL, tokenListNode);

    return result;
}

t_ast_node* TOKENLIST()
{
    tok_t* save = curtok;

    t_ast_node* node;

    if ((curtok = save, node = TOKENLIST1()) != NULL)
        return node;

    if ((curtok = save, node = TOKENLIST2()) != NULL)
        return node;

    return NULL;
}

t_ast_node* TOKENLIST1()
{
    t_ast_node* tokenListNode;
    t_ast_node* result;

    char* arg;
    if (!term(TOKEN, &arg))
        return NULL;

    tokenListNode = TOKENLIST();
    // we don't check whether tokenlistNode is NULL since its a valid grammer

    result = malloc(sizeof(*result));
    t_ast_nodeSetType(result, NODE_ARGUMENT);
    t_ast_nodeSetData(result, arg);
	ASTreeAttachBinaryBranch(result, NULL, tokenListNode);

    return result;
}

t_ast_node* TOKENLIST2()
{
    return NULL;
}

int parse(lexer_t* lexbuf, t_ast_node** syntax_tree)
{
	if (lexbuf->ntoks == 0)
		return -1;
	
	curtok = lexbuf->llisttok;
    *syntax_tree = CMDLINE();
	
    if (curtok != NULL && curtok->type != 0)
    {
        printf("Syntax Error near: %s\n", curtok->data);
        return -1;
    }
	return 0;
}

int main (void)
{

    return (0);
}