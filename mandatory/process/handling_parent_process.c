/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_parent_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:12:44 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:51:14 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parent(t_parsing *parsing, t_process *process)
{
	if (process->i != 0)
		close(process->temp_fd);
	if (process->i != parsing->cmd_cnt - 1)
		process->temp_fd = dup(process->pipe_fd[0]);
	close(process->pipe_fd[0]);
	close(process->pipe_fd[1]);
}
