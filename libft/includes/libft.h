/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:00:36 by ychng             #+#    #+#             */
/*   Updated: 2023/10/31 19:14:40 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "sys_headers.h"

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2, const char *delim);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *str, const char *delim);

#endif