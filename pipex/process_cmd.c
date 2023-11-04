/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:04 by ychng             #+#    #+#             */
/*   Updated: 2023/11/04 21:48:39 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

// No need to explicitly check the return value of ft_strjoin for NULL, 
// because in case of failure, it will return NULL and we handle it 
// in the following if statement.
static char	*resolve_cmd_path(char *cmd_name, char **envp)
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
			cmd_path = ft_strjoin(dir_path, cmd_name, "/");
			if (access(cmd_path, F_OK) == 0)
			{
				free(cmd_name);
				return (cmd_path);
			}
			dir_path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

static char	**tokenize_cmd(char *cmd, char **envp, char ***cmd_tokens)
{
	*cmd_tokens = ft_split(cmd, " ");
	if (*cmd_tokens != NULL)
		(*cmd_tokens)[0] = resolve_cmd_path((*cmd_tokens)[0], envp);
}

static void	execute_cmd(int cmd_index, char **cmd_tokens)
{
	pid_t	pid;
	int		status;

	pid = fork(); // NEED TO HANDLE ERROR
	if (pid == 0)
	{
		
	}
	waitpid(pid, &status, 0);
}

void	process_cmd(int argc, char **argv, char **envp)
{
	int		cmd_index;
	char	**cmd_tokens;

	cmd_index = 1;
	while (++cmd_index < (argc - 2))
	{
		tokenize_cmd(argv[cmd_index], envp, &cmd_tokens); // NEED TO HANDLE ERROR
		execute_cmd(cmd_index, cmd_tokens);
	}
}
