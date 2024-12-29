/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_preset_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:37:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/28 17:33:27 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	check_arguments(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		exit(1);
	}
	if (argc < 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		perror("Usage: ./pipex here_doc DELIMETER cmd1 cmd2 ... cmdn file2\n");
		exit(1);
	}
}

void	open_files(t_parsing *parsing, char **argv, int argc)
{
	if (!parsing->is_heredoc)
	{
		parsing->fd1 = open(argv[1], O_RDONLY);
		if (parsing->fd1 == -1)
			perror("failed openning file1\n");
		parsing->fd2 = open(argv[argc - 1], O_RDWR | O_CREAT, 0644);
	}
	else
		parsing->fd2 = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	if (parsing->fd2 == -1)
	{
		perror("failed openning file2\n");
		exit(1);
	}
}
