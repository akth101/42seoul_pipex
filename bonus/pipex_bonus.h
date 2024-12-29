/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:30:24 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/28 17:15:28 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_parsing {
	char	**cmd_path;
	char	***cmd_argv;
	int		cmd_cnt;
	char	**envp;
	char	**splitted_envp_path;
	int		fd1;
	int		temp_fd1;
	int		fd2;
	int		is_heredoc;
	char	*delimiter;
}	t_parsing;

typedef struct s_process {
	int	pid;
	int	pipe_fd[2];
	int	temp_fd;
	int	*status;
	int	i;
}	t_process;

void	parsing_main(t_parsing *parsing, int argc, char **argv, char **envp);
char	**strjoin_command_with_envp(char **envp_path, char ***commands, \
int cmd_cnt);
char	*ft_getenv(char *name, char **envp);
int		get_here_doc_input(char *delimiter);
int		tmp_file_handling(char *here_doc_input);
int		joined_path(char **envp_path, char ***commands, char **res, int i);
void	first_child_process(int read_end, int write_end, char **argv, \
t_parsing *parsing);
void	middle_child_process(int temp_fd, int read_end, int write_end);
void	last_child_process(int temp_fd, int read_end, int write_end, \
t_parsing *parsing);
void	first_or_middle_or_last_child(t_parsing *parsing, t_process *process, \
char **argv, char **envp);
void	parent(t_parsing *parsing, t_process *process);
void	transfer_data_to_file2(t_parsing *parsing, t_process *process, \
char **argv, char **envp);
void	wait_child_process(t_parsing *parsing, t_process *process);
void	check_arguments(int argc, char **argv);
void	open_files(t_parsing *parsing, char **argv, int argc);

#endif
