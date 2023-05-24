#include "../../headers/minishell.h"

/*
Echo prints text
	-n flag doesn't output a newline on prompt
or on the file to be outputten
*/
void	do_echo(t_minishell *ms)
{
	if (!ft_strncmp(ms->fq[1], "-n", ft_strlen("-n"))
		&& (ft_strlen(ms->fq[1]) == ft_strlen("-n")))
        	printf("%s", ms->fq[2]);
	else
    {
		printf("%s", ms->fq[1]);
        printf("\n");
    }
}
