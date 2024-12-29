/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:17:53 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:51:41 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
