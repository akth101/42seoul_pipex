/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:33:59 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/25 20:46:06 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	***make_command_argv(char **commands, int commands_i, \
int cmd_cnt, int argc)
{
	char	***res;
	int		res_i;

	res_i = 0;
	res = (char ***)malloc(sizeof(char **) * (cmd_cnt + 1));
	if (!res)
	{
		perror("malloc failed - make_command_argv\n");
		exit(1);
	}
	while (commands_i < argc - 1)
	{
		res[res_i] = ft_split(commands[commands_i], ' ');
		res_i++;
		commands_i++;
	}
	res[res_i] = NULL;
	return (res);
}

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
		{
			if (envp[i][j + 1] == '=')
				return (envp[i] + j + 2);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	**strjoin_command_with_envp(char **envp_path, char ***commands, \
int cmd_cnt)
{
	int		i;
	char	**res;

	i = -1;
	res = (char **)malloc(sizeof(char *) * (cmd_cnt + 1));
	if (!res)
	{
		perror("malloc failed - strjoin_command_with_envp\n");
		exit(1);
	}
	while (commands[++i])
	{
		if (!(joined_path(envp_path, commands, res, i)))
		{
			perror("invalid command\n");
			exit(1);
		}
	}
	res[i] = NULL;
	return (res);
}

int	joined_path(char **envp_path, char ***commands, char **res, int i)
{
	char	*slash_path;
	char	*completed_cmd;
	int		j;

	j = -1;
	while (envp_path[++j])
	{
		slash_path = ft_strjoin(envp_path[j], "/");
		completed_cmd = ft_strjoin(slash_path, commands[i][0]);
		if (!slash_path || !completed_cmd)
		{
			perror("strjoin failed - joined_path\n");
			exit(1);
		}
		if (!access(completed_cmd, X_OK))
		{
			res[i] = completed_cmd;
			free(slash_path);
			return (1);
		}
		free(slash_path);
		free(completed_cmd);
	}
	return (0);
}

void	parsing_main(t_parsing *parsing, int argc, char **argv, char **envp)
{
	parsing->splitted_envp_path = ft_split(ft_getenv("PATH", envp), ':');
	parsing->cmd_cnt = 2;
	parsing->cmd_argv = make_command_argv(argv, 2, parsing->cmd_cnt, argc);
	parsing->cmd_path = strjoin_command_with_envp(parsing->splitted_envp_path, \
	parsing->cmd_argv, parsing->cmd_cnt);
}
