/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:13:00 by ychng             #+#    #+#             */
/*   Updated: 2023/11/09 17:05:55 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// No need to explicitly check the return value of ft_strjoin for NULL, 
// because in case of failure, it will skip the following if statement
// and return NULL.
static char	*check_cmd_in_dir(char *cmd_name, char *dir_path)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(dir_path, cmd_name, "/");
	if (access(cmd_path, F_OK) == 0)
	{
		free(cmd_name);
		return (cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

// This function resolves the command path using the PATH environment variable.
// It iterates through the environment variables, to find the command.
// If found, it returns the full command path; 
// otherwise, it returns the original command name.
static char	*resolve_cmd_path(char *cmd_name, char **envp)
{
	int		i;
	char	*temp_envp;
	char	*dir_path;
	char	*cmd_path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		temp_envp = ft_strdup(envp[i]);
		dir_path = ft_strtok(temp_envp, ":");
		while (dir_path != NULL)
		{
			cmd_path = check_cmd_in_dir(cmd_name, dir_path);
			if (cmd_path != NULL)
			{
				free(temp_envp);
				return (cmd_path);
			}
			dir_path = ft_strtok(NULL, ":");
		}
		free(temp_envp);
	}
	return (cmd_name);
}

void	tokenize_cmd(char *cmd, char **envp, char ***cmd_tokens)
{
	*cmd_tokens = ft_split(cmd, " ");
	if (*cmd_tokens == NULL)
	{
		write_error("ft_split function didn't work\n");
		exit(-1);
	}
	(*cmd_tokens)[0] = resolve_cmd_path((*cmd_tokens)[0], envp);
}
