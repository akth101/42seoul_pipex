/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_data_to_file2_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:41:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/26 12:46:24 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	transfer_data_to_file2(t_parsing *parsing, t_process *process, \
char **argv, char **envp)
{
	process->i = -1;
	while (++process->i < parsing->cmd_cnt)
	{
		if (pipe(process->pipe_fd) == -1)
		{
			perror("failed opening pipe\n");
			exit(1);
		}
		process->pid = fork();
		if (process->pid == 0)
			first_or_middle_or_last_child(parsing, process, argv, envp);
		else
			parent(parsing, process);
	}
}