/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:06 by tsodre-p          #+#    #+#             */
/*   Updated: 2023/06/07 15:03:46 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_end(char *input, bool n)
{
	if (!input)
	{
		if (n == false)
			printf("\n");
		return (0);
	}
	else
		printf(" ");
	return (1);
}

char	*clean_quotes(char *input)
{
	int	i;
	int	j;
	char	*string;

	i = 0;
	j = 0;
	string = ma;
	/*if (input[0] == '\'')
		input = ft_strtrim(input, "\'");
	else if (input[0] ==  '"')
		input = ft_strtrim(input, "\"");
	return (input);*/
	while (input[i])
	{
		if (input[0] == '\'' || input[0] ==  '"')
		{
			if (input[i] != '\'' || input[i] !=  '"')
			{
				string[j] = input[i];
				j++;
			}
		}
		i++;
	}
	return (string);
}

static void	echo_print(char **input, bool n, int i)
{
	/*verificar que tipo de quotes existem
	depois ver se o numero de quotes e par ou impar:
	- se for impar da erro
	- se nao for impar e nao tiver quotes a volta da string
	simplesmente tira tudo e deixa o texto

	se tiver quotes a volta, 1 inicio e 1 fim:
	imprime tudo, a nao ser que as quotes do meio sejam iguias
	as quotes que estao nas pontas. ai apaga-as*/
	while (input[i])
	{
		//input[i] = ft_strtrim(input[i], "\'\"");
		if (check_strcmp("$?", input[i]))
		{
			printf("%d", g_exit);
			if (!check_end(input[i + 1], n))
				break ;
		}
		else
		{
			input[i] = clean_quotes(input[i]);
			printf("%s", input[i]);
			if (!check_end(input[i + 1], n))
				break ;
		}
		i++;
	}
}

/*
Echo prints text:
-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(t_minishell *ms, char **input)
{
	int		i;
	bool	n;

	n = false;
	if (!input)
	{
		printf("\n");
		return ;
	}
	else if (input[1][0] == '-' && input[1][1] == 'n' && !input[2])
		return ;
	i = 1;
	if (check_strcmp("-n", input[i]))
	{
		n = true;
		i++;
	}
	echo_print(input, n, i);
	free_child(ms, input, 0);
	g_exit = 0;
	exit (0);
}
