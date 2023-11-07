/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:16:36 by ychng             #+#    #+#             */
/*   Updated: 2023/11/08 03:16:25 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "sys_headers.h"

// get_next_line_bonus
char	*get_next_line(int fd);

// get_next_line_utils_bonus
char	*has_newline_character(char *s);
int		gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2);
void	gnl_strcpy(char *s1, char *s2);

#endif