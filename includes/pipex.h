/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:16:02 by ccoste            #+#    #+#             */
/*   Updated: 2023/04/29 13:28:26 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

//ft_split.c
static char	    **free_tab(char **tab);
static size_t	count_words(const char *s, char c);
static void	    get_word(char **next, size_t *len, char c);
char	        **ft_split(const char *s, char c);

//ft_strdup.c
char	        *ft_strdup(const char *s);

//ft_strjoin.c
char	        *ft_strjoin(char const *s1, char const *s2);

//ft_strncmp.c
int	            ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_strlen.c
size_t	        ft_strlen(const char *s);

//error.c
int	            msg(char *err);
void	        msg_error(char *err);

#endif