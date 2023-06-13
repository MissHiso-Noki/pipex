/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:14 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/13 17:54:48 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//fork, pipe, wait, waitpid, execve, exit, dup, dup2, access
# include <unistd.h>

//perror, strerror
# include <stdio.h>

//malloc, free
# include <stdlib.h>

//open, close, read, write, unlink
# include <fcntl.h>

//waitpid
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile.\n"
# define ERR_OUTFILE "Outfile.\n"
# define ERR_PIPE "Pipe.\n"
# define ERR_CMD "Invalid command.\n"

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		infile;
	int		outfile;
	int		pipe[2];
}				t_pipe;

/* FUNCTIONS */

//ft_split.c
size_t		words_count(char *s, char c);
char		*word(char *s, char c);
char		**free_arr(char **arr, char *s);
char		**worker(char **arr, char *s1, char c, size_t j);
char		**ft_split(char const *s, char c);

//ft_strdup.c
char		*ft_strdup(const char *s);

//ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);

//ft_strlen.c
size_t		ft_strlen(const char *s);

//ft_strncmp.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* SOURCES */
//pipex.c
void		close_pipes(t_pipe *pipex);
char		*find_path(char **envp);

//error.c
int			msg(char *error);
void		msg_perror(char *error);

//child.c
char		*get_cmd(char **paths, char *cmd);
void		first_child(t_pipe pipex, char *argv[], char *envp[]);
void		second_child(t_pipe pipex, char *argv[], char *envp[]);

//free.c
void		parent_free(t_pipe *pipex);
void		child_free(t_pipe *pipex);
#endif
