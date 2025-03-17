/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_create_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:43:53 by tcosta-f          #+#    #+#             */
/*   Updated: 2025/03/17 18:56:52 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*ft_create_cmd_node(t_token *token);
t_node	*ft_create_operator_node(t_token *token, t_node *left, t_node *right);
t_node	*ft_create_cmd(t_token *tokens, int *i);

/**
 * @brief  Creates a new command node in the AST.
 * 
 * @param  token  Token associated with the command node.
 * @return t_node* Pointer to the created command node.
 */
t_node	*ft_create_cmd_node(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd_ready = NULL;
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	node->prev = NULL;
	node->file = false;
	node->file_unlink = false;
	node->heredoc_stops = NULL;
	return (node);
}

/**
 * @brief  Creates a new operator node in the AST.
 * 
 * @param  token  Token associated with the operator node.
 * @param  left   Pointer to the left child node.
 * @param  right  Pointer to the right child node.
 * @return t_node* Pointer to the created operator node.
 */
t_node	*ft_create_operator_node(t_token *token, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd_ready = NULL;
	node->token = token;
	node->left = left;
	node->right = right;
	node->prev = NULL;
	node->file = false;
	node->file_unlink = false;
	node->heredoc_stops = NULL;
	return (node);
}

/**
 * @brief Creates a command node from the tokens array.
 * 
 * @param tokens      Array of tokens to parse.
 * @param i           Pointer to the current index in tokens.
 * @return t_node*    Created command node.
 */
t_node	*ft_create_cmd(t_token *tokens, int *i)
{
	t_node	*cmd_node;

	if (tokens[*i].type == TKN_BLTIN || tokens[*i].type == TKN_CMD)
		cmd_node = ft_group_command_tokens(tokens, i);
	else
	{
		cmd_node = ft_create_cmd_node(&tokens[*i]);
		(*i)++;
	}
	return (cmd_node);
}
