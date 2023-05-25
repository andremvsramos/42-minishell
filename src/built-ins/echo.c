#include "../../headers/minishell.h"

//Check how many single quotes there is int the string
int	count_quotes(char *input, char quote)
{
	int	i;
	int	num_quotes;

	i = 0;
	num_quotes = 0;
	while (input[i])
	{
		if (input[i] == quote)
			num_single_quotes++;
		i++;
	}
	/*if (num_double_quotes % 2 != 0 || num_single_quotes != 0)
		return (0);*/
	return (1);
}

/*
Echo prints text:
-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(t_minishell *ms)
{
	if (!ft_strncmp(ms->fq[1], "-n", ft_strlen("-n"))
		&& (ft_strlen(ms->fq[1]) == ft_strlen("-n")))
	{
		if (ms->fq[1][i] == '\'' && ms->fq[1][i] == '\'' && )
			if (count_quotes(ms->fq[2], '\'') == 0)
				printf("%s", "Error: unclosed quotes\n");
			 
		/*else
		{
			handle_quotes(ms->fq[1]);
		}*/	
	}
	else
    {
		if (count_quotes(ms->fq[1]) == 0)
			printf("%s", "Error: unclosed quotes\n");
		else
		{
			//handle_quotes(ms->fq[1]);
			printf("%s", ms->fq[1]);
        	printf("\n");
		}
    }
}

