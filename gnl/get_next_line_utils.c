/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:01:28 by ychng             #+#    #+#             */
/*   Updated: 2023/11/08 03:05:01 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

char	*has_newline_character(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (s + i);
		i++;
	}
	return (NULL);
}

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined_buffer;
	int		i;
	int		j;

	joined_buffer = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!joined_buffer)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		joined_buffer[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined_buffer[i++] = s2[j++];
	joined_buffer[i] = '\0';
	free(s1);
	return (joined_buffer);
}

void	gnl_strcpy(char *s1, char *s2)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[j] = s2[j];
		j++;
	}
	s1[j] = '\0';
}
