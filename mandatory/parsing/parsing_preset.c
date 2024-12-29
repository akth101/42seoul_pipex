/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_preset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:19:47 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/28 17:40:12 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_arguments(int argc)
{
	if (argc != 5)
	{
		perror("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
}

void	open_files(t_parsing *parsing, char **argv, int argc)
{
	parsing->fd1 = open(argv[1], O_RDONLY);
	if (parsing->fd1 == -1)
	{
		perror("failed openning file1\n");
	}
	parsing->fd2 = open(argv[argc - 1], O_RDWR | O_CREAT, 0644);
	if (parsing->fd2 == -1)
	{
		perror("failed openning file2\n");
		exit(1);
	}
}
