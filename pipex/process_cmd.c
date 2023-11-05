/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:04 by ychng             #+#    #+#             */
/*   Updated: 2023/11/05 20:52:51 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

// No need to explicitly check the return value of ft_strjoin for NULL, 
// because in case of failure, it will return NULL and we handle it 
// in the following if statement.
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
			cmd_path = ft_strjoin(dir_path, cmd_name, "/");
			if (access(cmd_path, F_OK) == 0)
			{
				free(cmd_name);
				free(temp_envp);
				return (cmd_path);
			}
			dir_path = ft_strtok(NULL, ":");
		}
	}
	free(temp_envp);
	return (NULL);
}

static void	tokenize_cmd(char *cmd, char **envp, char ***cmd_tokens)
{
	*cmd_tokens = ft_split(cmd, " ");
	if (*cmd_tokens == NULL)
	{
		perror("ft_splt function didn't work.\n");
		exit(-1);
	}
	(*cmd_tokens)[0] = resolve_cmd_path((*cmd_tokens)[0], envp);
}

static void	setup_pipe_fd(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe function didn't work.\n");
		exit(-1);
	}
}

static void	setup_file_fd(char *file_path, int *file_fd)
{
	*file_fd = open(file_path, O_RDONLY);
	if (*file_fd == -1)
	{
		perror("stdin file doesn't exist.\n");
		exit(-1);
	}
}

static void execute_first_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork function didn't work.\n");
		perror("can't create child process.\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(file_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(cmd_tokens[0], cmd_tokens, NULL);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

static void	execute_last_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork function didn't work.\n");
		perror("can't create child process.\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		execve(cmd_tokens[0], cmd_tokens, NULL);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
}

static void	execute_cmd_in_between(int *pipe_fd, char **cmd_tokens)
{
	int		prev_pipe_fd[2];
	pid_t	pid;

	prev_pipe_fd[0] = pipe_fd[0];
	prev_pipe_fd[1] = pipe_fd[1];
	setup_pipe_fd(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork function didn't work.\n");
		exit(-1);
	}
	if (pid == 0)
	{
		close(prev_pipe_fd[1]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(cmd_tokens[0], cmd_tokens, NULL);
		exit(0);
	}
	close(prev_pipe_fd[0]);
	close(prev_pipe_fd[1]);
	waitpid(pid, NULL, 0);
}

static void	execute_cmd(int cmd_index, int argc, char **argv, char **cmd_tokens)
{
	int		pipe_fd[2];
	int		file_fd;

	if (cmd_index == 2)
	{
		setup_pipe_fd(pipe_fd);
		setup_file_fd(argv[1], &file_fd);
		execute_first_cmd(file_fd, pipe_fd, cmd_tokens);
		close(file_fd);
	}
	else if (cmd_index == (argc - 2))
	{
		file_fd = open(argv[cmd_index + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IROTH | S_IRGRP | S_IRGRP);
		execute_last_cmd(file_fd, pipe_fd, cmd_tokens);
		close(file_fd);
	}
	else
		execute_cmd_in_between(pipe_fd, cmd_tokens);
}

void	process_cmd(int argc, char **argv, char **envp)
{
	int		cmd_index;
	char	**cmd_tokens;

	cmd_index = 1;
	while (++cmd_index <= (argc - 2))
	{
		tokenize_cmd(argv[cmd_index], envp, &cmd_tokens);
		execute_cmd(cmd_index, argc, argv, cmd_tokens);
	}
}
