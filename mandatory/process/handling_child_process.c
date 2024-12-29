/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_child_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:38:31 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/28 17:14:20 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	if_file1_is_not_readable(t_parsing *parsing)
{
	parsing->temp_fd1 = open("file1_temp.txt", O_CREAT | O_RDONLY, 0644);
	dup2(parsing->temp_fd1, STDIN_FILENO);
	close(parsing->temp_fd1);
	unlink("file1_temp.txt");
}

void	first_child_process(int read_end, int write_end, \
t_parsing *parsing)
{
	close(read_end);
	if (parsing->fd1 != -1)
	{
		dup2(parsing->fd1, STDIN_FILENO);
		close(parsing->fd1);
	}
	else
		if_file1_is_not_readable(parsing);
	dup2(write_end, STDOUT_FILENO);
	close(write_end);
}

void	middle_child_process(int temp_fd, int read_end, int write_end)
{
	close(read_end);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	dup2(write_end, STDOUT_FILENO);
	close(write_end);
}

void	last_child_process(int temp_fd, int read_end, int write_end, \
t_parsing *parsing)
{
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	dup2(parsing->fd2, STDOUT_FILENO);
	close(parsing->fd2);
	close(read_end);
	close(write_end);
}

void	first_or_middle_or_last_child(t_parsing *parsing, t_process *process, \
char **envp)
{
	if (process->i == 0)
	{
		first_child_process(process->pipe_fd[0], process->pipe_fd[1], \
		parsing);
		execve(parsing->cmd_path[process->i], \
		parsing->cmd_argv[process->i], envp);
	}
	else if (process->i > 0 && process->i < parsing->cmd_cnt - 1)
	{
		middle_child_process(process->temp_fd, process->pipe_fd[0], \
		process->pipe_fd[1]);
		execve(parsing->cmd_path[process->i], \
		parsing->cmd_argv[process->i], envp);
	}
	else
	{
		last_child_process(process->temp_fd, process->pipe_fd[0], \
		process->pipe_fd[1], parsing);
		execve(parsing->cmd_path[process->i], \
		parsing->cmd_argv[process->i], envp);
	}
}
