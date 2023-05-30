/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:41:39 by ccoste            #+#    #+#             */
/*   Updated: 2023/05/30 13:26:02 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg(ERR_INPUT));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		msg_error(ERR_INFILE);
//O_TRUNC : Cette option est utilisée pour tronquer (vider) le fichier s'il existe déjà. Si le fichier n'existe pas, cette option est ignorée.
//O_CREAT : Cette option est utilisée pour créer le fichier s'il n'existe pas déjà.
//O_RDWR : Cette option est utilisée pour ouvrir le fichier en lecture et en écriture.
//0 : Spécifie que les permissions seront définies en utilisant les chiffres octaux suivants.
//00644 : Spécifie que le propriétaire du fichier a les permissions de lecture et d'écriture, tandis que les autres utilisateurs ont uniquement la permission de lecture.
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		msg_error(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
// Si la valeur de retour est négative, cela indique qu'une erreur s'est produite lors de l'appel à fork.
// Si la valeur de retour est zéro, cela signifie que le code s'exécute dans le processus enfant.
// Si la valeur de retour est positive, cela indique l'ID du processus enfant dans le processus parent.
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
//0 = attendre n'importe lequel des processus fils dont le GID du processus est égal à celui du processus appelant.
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
