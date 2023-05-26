/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:50 by marvin            #+#    #+#             */
/*   Updated: 2023/05/26 14:53:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	do_heredoc(t_minishell *ms)
{
	int		temp_file;
	//char	*buffer;

	(void)ms;
	temp_file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
	if (!temp_file)
		{/*DO ERROR*/}
	while(1)
	{
		//buffer = readline(">");
		/* if (!buffer)
		{ */
			/*DO ERROR*/
		/* } */
		/*FAZER MERDAS*/
		/* if (ft_strrchr(buffer, '$'))
			{DO EXPANDER FOR FILE CLOSER} */
		break ;
	}
	//free(buffer);
	close(temp_file);
}
