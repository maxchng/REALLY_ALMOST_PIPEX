/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:04:04 by ychng             #+#    #+#             */
/*   Updated: 2023/11/07 14:45:53 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

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

static void	tokenize_cmd(char *cmd, char **envp, char ***cmd_tokens)
{
	*cmd_tokens = ft_split(cmd, " ");
	if (*cmd_tokens == NULL)
	{
		write_error("ft_split function didn't work\n");
		exit(-1);
	}
	(*cmd_tokens)[0] = resolve_cmd_path((*cmd_tokens)[0], envp);
}

static void	setup_pipe_fd(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		write_error("pipe function didn't work\n");
		exit(-1);
	}
}

static int	setup_file_fd(char *file_path, int *file_fd, bool read_only)
{
	mode_t	permission;

	if (read_only == true)
	{
		*file_fd = open(file_path, O_RDONLY);
		if (*file_fd == -1)
		{
			write_error("stdin file doesn't exist\n");
			return (-1);
		}
	}
	else
	{
		permission = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		*file_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, permission);
	}
	return (0);
}

static void	check_exit_status(int status, char *cmd_name)
{
	if (WEXITSTATUS(status) != 0)
	{
		write_error(cmd_name);
		write_error(" command doesn't exist\n");
	}
}

static void	execute_first_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_first_cmd\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(file_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}

static void	execute_last_cmd(int file_fd, int *pipe_fd, char **cmd_tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_last_cmd\n");
		close(file_fd);
		exit(-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(file_fd, STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}

static void	copy_pipe_fd(int *pipe_fd, int *prev_pipe_fd)
{
	prev_pipe_fd[0] = pipe_fd[0];
	prev_pipe_fd[1] = pipe_fd[1];
}

static void	execute_cmd_in_between(int *pipe_fd, char **cmd_tokens)
{
	int		prev_pipe_fd[2];
	pid_t	pid;
	int		status;

	copy_pipe_fd(pipe_fd, prev_pipe_fd);
	setup_pipe_fd(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		write_error("fork function didn't work in execute_cmd_in_between\n");
		exit(-1);
	}
	if (pid == 0)
	{
		close(prev_pipe_fd[1]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
			exit(-1);
	}
	close(prev_pipe_fd[0]);
	close(prev_pipe_fd[1]);
	waitpid(pid, &status, 0);
	check_exit_status(status, cmd_tokens[0]);
}

static size_t	count_argv(char **argv)
{
	size_t	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

static void	execute_cmd(t_execute_cmd params)
{
	int		file_fd;

	if (params.cmd_index == 2)
	{
		if (setup_file_fd(params.argv[1], &file_fd, true) == -1)
			return ;
		execute_first_cmd(file_fd, params.pipe_fd, params.cmd_tokens);
		close(file_fd);
	}
	else if (params.cmd_index == (count_argv(params.argv) - 2))
	{
		setup_file_fd(params.argv[params.cmd_index + 1], &file_fd, false);
		execute_last_cmd(file_fd, params.pipe_fd, params.cmd_tokens);
		close(file_fd);
	}
	else
		execute_cmd_in_between(params.pipe_fd, params.cmd_tokens);
}

static void	free_cmd_tokens(char **cmd_tokens)
{
	size_t	i;

	i = 0;
	while (cmd_tokens[i])
	{
		free(cmd_tokens[i]);
		i++;
	}
	free(cmd_tokens);
}

void	process_cmd(int argc, char **argv, char **envp)
{
	int		cmd_index;
	int		pipe_fd[2];
	char	**cmd_tokens;

	cmd_index = 1;
	setup_pipe_fd(pipe_fd);
	while (++cmd_index <= (argc - 2))
	{
		tokenize_cmd(argv[cmd_index], envp, &cmd_tokens);
		execute_cmd((t_execute_cmd){cmd_index, pipe_fd, argv, cmd_tokens});
		free_cmd_tokens(cmd_tokens);
	}
}
