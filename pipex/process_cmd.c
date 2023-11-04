/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:04 by ychng             #+#    #+#             */
/*   Updated: 2023/11/04 20:08:18 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static char	*get_cmd_path(char *cmd_name, char **envp)
{
	int		i;
	char	*dir_path;
	char	*cmd_path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		dir_path = ft_strtok(envp[i], ":");
		while (dir_path != NULL)
		{
			cmd_path = ft_strjoin(dir_path, cmd_name, "/"); // MIGHT NEED TO HANDLE ERROR
			free(cmd_name); // NOT SURE NEED TO FREE CMD_NAME BECAUSE OF STRJOIN
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			dir_path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

void	process_cmd(int argc, char **argv, char **envp)
{
	int		cmd_index;
	char	**cmd_tokens;
	pid_t	pid;

	cmd_index = 2;
	while (cmd_index < (argc - 2))
	{
		cmd_tokens = ft_split(argv[cmd_index], " "); // MIGHT NEED TO HANDLE ERROR
		cmd_tokens[0] = get_cmd_path(cmd_tokens[0], envp);
		cmd_index++;
	}
}
