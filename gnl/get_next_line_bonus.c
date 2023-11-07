/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:16:03 by ychng             #+#    #+#             */
/*   Updated: 2023/11/08 03:04:50 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line_bonus.h"

char	*read_file_into_buffer(int fd, char *partial_buffer)
{
	char	*read_buffer;
	int		bytes_read;

	bytes_read = 0;
	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	while (!has_newline_character(partial_buffer))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		read_buffer[bytes_read] = '\0';
		partial_buffer = gnl_strjoin(partial_buffer, read_buffer);
	}
	free(read_buffer);
	if (bytes_read == -1)
		return (NULL);
	return (partial_buffer);
}

char	*extract_before_newline(char *partial_buffer)
{
	int		i;
	char	*result_buffer;

	i = 0;
	if (!partial_buffer || !partial_buffer[i])
		return (NULL);
	while (partial_buffer[i] != '\n' && partial_buffer[i])
		i++;
	result_buffer = malloc(sizeof(char) * (i + 2));
	if (!result_buffer)
		return (NULL);
	i = 0;
	while (partial_buffer[i] != '\n' && partial_buffer[i])
	{
		result_buffer[i] = partial_buffer[i];
		i++;
	}
	if (partial_buffer[i] == '\n')
		result_buffer[i++] = '\n';
	result_buffer[i] = '\0';
	return (result_buffer);
}

char	*extract_after_newline(char *partial_buffer)
{
	int		i;
	char	*remaining_buffer;

	if (!partial_buffer)
		return (NULL);
	i = 0;
	while (partial_buffer[i] != '\n' && partial_buffer[i])
		i++;
	if (!partial_buffer[i])
	{
		free(partial_buffer);
		return (NULL);
	}
	remaining_buffer = malloc(sizeof(char) * (gnl_strlen(partial_buffer) - i));
	if (!remaining_buffer)
	{
		free(partial_buffer);
		return (NULL);
	}
	gnl_strcpy(remaining_buffer, &partial_buffer[i + 1]);
	free(partial_buffer);
	return (remaining_buffer);
}

char	*get_next_line(int fd)
{
	static char	*partial_buffer[1024];
	char		*result_buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	partial_buffer[fd] = read_file_into_buffer(fd, partial_buffer[fd]);
	result_buffer = extract_before_newline(partial_buffer[fd]);
	partial_buffer[fd] = extract_after_newline(partial_buffer[fd]);
	return (result_buffer);
}
