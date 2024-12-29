/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:01:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:55:04 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsing	parsing;
	t_process	process;

	check_arguments(argc, argv);
	parsing_main(&parsing, argc, argv, envp);
	open_files(&parsing, argv, argc);
	transfer_data_to_file2(&parsing, &process, argv, envp);
	wait_child_process(&parsing, &process);
}
