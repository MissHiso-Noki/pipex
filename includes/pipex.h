/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:16:02 by ccoste            #+#    #+#             */
/*   Updated: 2023/05/30 11:24:15 by ccoste           ###   ########.fr       */
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

//ft_bzero.c

void			ft_bzero(void *s, size_t n);

//ft_calloc.c

void			*ft_calloc(size_t nmemb, size_t size);

//ft_split.c
char			**free_tab(char **tab);
size_t			count_words(const char *s, char c);
void			get_word(char **next, size_t *len, char c);
char			**ft_split(const char *s, char c);

//ft_strdup.c
char			*ft_strdup(const char *s);

//ft_strjoin.c
char			*ft_strjoin(char const *s1, char const *s2);

//ft_strlcpy
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

//ft_strncmp.c
int				ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_strlen.c
size_t			ft_strlen(const char *s);

//error.c
int				msg(char *err);
void			msg_error(char *err);

//free.c
void			child_free(t_pipex *pipex);
void			parent_free(t_pipex *pipex);

//childs.c
char			*get_cmd(char **paths, char *cmd);
void			first_child(t_pipex pipex, char *argv[], char *envp[]);
void			second_child(t_pipex pipex, char *argv[], char *envp[]);

//pipex.c
char			*find_path(char **envp);
void			close_pipes(t_pipex *pipex);

#endif
