#include "../../headers/minishell.h"

/*
Echo prints text:
-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(t_minishell *ms)
{
	//imprimir
	if (!ms->query[1])
	{
		printf("\n");
		return ;
	}
	else if (ms->query[1][0] == '-' && ms->query[1][1] == 'n' && !ms->query[2])
		return ;
	if (!ft_strncmp(ms->query[1], "$?", ft_strlen("$?"))
		&& ft_strlen("$?") == ft_strlen(ms->query[1]))
	{
		printf("%d\n", g_exit);
		return ;
	}
	if (!ft_strncmp(ms->query[1], "-n", ft_strlen("-n"))
		&& (ft_strlen(ms->query[1]) == ft_strlen("-n")))
	{
		handle_quotes(ms->query[2]);
	}
	else
    {
		/*if (count_quotes(ms->query[1]) == 0)
			printf("%s", "Error: unclosed quotes\n");
		else
		{
			//handle_quotes(ms->query[1]);
			printf("%s", ms->query[1]);
        	printf("\n");
		}*/
		handle_quotes(ms->query[1]);
		printf("\n");
    }
}

