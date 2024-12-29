/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:29:11 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:59:12 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	wait_child_process(t_parsing *parsing, t_process *process)
{
	int	i;

	i = 0;
	process->status = NULL;
	while (i < parsing->cmd_cnt)
	{
		wait(process->status);
		i++;
	}
}
