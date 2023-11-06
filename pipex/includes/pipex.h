/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychng <ychng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:07:18 by ychng             #+#    #+#             */
/*   Updated: 2023/11/06 12:57:19 by ychng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "sys_headers.h"
# include "libft.h"

void	write_error(char *msg);
void	process_cmd(int argc, char **argv, char **envp);

#endif