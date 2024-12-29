/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:16:51 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:57:58 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	get_here_doc_input(char *delimiter)
{
	char	*res;
	char	*res_tmp;
	char	*line;
	char	*trans_delimiter;

	trans_delimiter = ft_strjoin(delimiter, "\n");
	res = (char *)malloc(sizeof(char));
	*res = '\0';
	line = get_next_line(0);
	while (ft_strncmp(line, trans_delimiter, ft_strlen(trans_delimiter) + 1))
	{
		res_tmp = ft_strjoin(res, line);
		free(res);
		free(line);
		res = res_tmp;
		line = get_next_line(0);
	}
	free(trans_delimiter);
	free(line);
	return (tmp_file_handling(res));
}

int	tmp_file_handling(char *here_doc_input)
{
	int	tmp_fd;

	tmp_fd = open("temp.txt", O_CREAT | O_WRONLY, 0644);
	write(tmp_fd, here_doc_input, ft_strlen(here_doc_input));
	close(tmp_fd);
	tmp_fd = open("temp.txt", O_RDONLY, 0644);
	return (tmp_fd);
}
