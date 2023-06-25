/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:14 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/25 19:42:21 by ccoste           ###   ########.fr       */
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

//strerror
# include <errno.h>
# include <string.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile.\n"
# define ERR_OUTFILE "Outfile.\n"
# define ERR_PIPE "Pipe.\n"
# define ERR_CMD "Invalid command.\n"
# define ERR_FORK "Fork.\n"
# define ERR_PID "Pid.\n"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	int		status;
	int		pipe[2];
	char	*cmd_paths1;
	char	*cmd_paths2;
	char	**cmd1;
	char	**cmd2;
}				t_pipe;

/* FUNCTIONS */

//ft_split.c
char		**free_tab(char **tab);
size_t		count_words(const char *s, char c);
void		get_word(char **next, size_t *len, char c);
char		**ft_split(const char *s, char c);

//ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);

//ft_strlen.c
size_t		ft_strlen(const char *s);

//ft_strncmp.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_substr.c
char		*ft_substr(char const *s, unsigned int start, size_t len);

//ft_calloc.c
void		*ft_calloc(size_t nmemb, size_t size);

//ft_strlcpy.c
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

//ft_bzero.c
void		ft_bzero(void *s, size_t n);

//ft_strlcpy.c
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

//ft_strchr.c
char		*ft_strchr(const char *s, int c);

//ft_putendl_fd.c
void		ft_putendl_fd(char *s, int fd);

//ft_putstr_fd.c
void		ft_putstr_fd(char *s, int fd);

//ft_putchar_fd.c
void		ft_putchar_fd(char c, int fd);

/* SOURCES */

//path.c
char		**find_paths_and_split(char **envp);
char		**paths_add_slash(t_pipe *pipex, char **paths, char *cmd);
char		*cmd_exist(t_pipe *pipex, char	*cmd, char **paths);

//utils.c
char		**get_cmd(char *s);
void		initialize_struct(t_pipe *pipex, char *argv[]);
char		*find_absolut_path(t_pipe *pipex, char **paths, char *cmd);

//error.c
int			msg_error(char *error);
void		error(int ret);
void		child_error(t_pipe *pipex, char *cmd, char **paths);

//child.c
void		first_child(t_pipe *pipex, char *argv[], char *envp[]);
void		second_child(t_pipe *pipex, char *argv[], char *envp[]);
void		parent(t_pipe pipex);

#endif
