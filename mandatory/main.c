/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:01:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/28 14:34:44 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsing	parsing;
	t_process	process;

	check_arguments(argc);
	parsing_main(&parsing, argc, argv, envp);
	open_files(&parsing, argv, argc);
	transfer_data_to_file2(&parsing, &process, envp);
	wait_child_process(&parsing, &process);
}
