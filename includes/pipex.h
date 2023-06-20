/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:14 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/20 13:22:03 by ccoste           ###   ########.fr       */
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
size_t		check_str(char const *s, char c);
void		ft_free(char **spl, size_t i);
char		*ft_strndup(char const *str, size_t size);
char		**ft_create_str(char **spl, char const *s, char c, int i);
char		**ft_split(char const *s, char c);

//ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);

//ft_strlen.c
size_t		ft_strlen(const char *s);

//ft_strncmp.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_substr.c
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* SOURCES */

//path.c
char		**find_paths_and_split(char **envp);
char		**paths_add_slash(char **paths);
char		*cmd_exist(char	*cmd, char **paths);

//utils.c
char		**get_cmd(char *s);
void		cmd_not_found(char *path_cmd, char	**cmd);
void		initialize_struct(t_pipe *pipex, char *argv[]);

//error.c
int			msg_error(char *error);
void		msg_perror(char *error);
void		error(int ret);

//child.c
void		first_child(t_pipe pipex, char *envp[]);
void		second_child(t_pipe pipex, char *envp[]);
void		parent(t_pipe pipex);

#endif
