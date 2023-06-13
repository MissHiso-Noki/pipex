/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:12:55 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/13 17:38:39 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//itère sur les chemins fournis, concatène le nom de la commande avec chaque chemin, vérifie si le fichier existe
// et est accessible, puis retourne le chemin complet de la commande si elle est trouvée avec succès.
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
//concaténer le chemin actuel *paths avec le caractère '/' pour former un nouveau chemin temporaire tmp.
		tmp = ft_strjoin(*paths, "/");
//concaténer le chemin temporaire tmp avec le nom de la commande cmd pour obtenir le chemin complet de la command.
		command = ft_strjoin(tmp, cmd);
//libère la mémoire allouée pour le chemin temporaire tmp car il n'est plus nécessaire.
		free(tmp);
//vérifier si le fichier correspondant au chemin de la commande command existe et est
//accessible. Si c'est le cas (valeur de retour égale à 0).
		if (access(command, 0) == 0)
//elle retourne le chemin complet de la commande command.
			return (command);
//Sinon, elle libère la mémoire allouée pour le chemin de la commande command.
		free(command);
		paths++;
	}
	return (NULL);
}

//pipe[0] : C'est le descripteur de fichier (fd) de l'extrémité de lecture (read end) du pipe.
//pipe[1] : C'est le descripteur de fichier (fd) de l'extrémité d'écriture (write end) du pipe.

void	first_child(t_pipe pipex, char *argv[], char *envp[])
{
//rediriger la sortie standard (1) vers l'extrémité d'écriture du tube (pipex.pipe[1]). Cela signifie que
//tout ce qui serait normalement écrit sur la sortie standard sera maintenant écrit dans le tube.
	dup2(pipex.pipe[1], 1);
//ferme l'extrémité de lecture du tube (pipex.pipe[0]) dans le processus fils, car il ne va pas lire à
//partir de cette extrémité.
	close(pipex.pipe[0]);
//rediriger l'entrée standard (0) vers le descripteur de fichier pipex.infile. Cela signifie que le
//processus fils lira à partir du fichier spécifié par pipex.infile au lieu de lire depuis l'entrée standard.
	dup2(pipex.infile, 0);
//diviser la chaîne argv[2] en sous-chaines, Ces sous-chaînes seront ensuite stockées dans un tableau pipex.cmd_args.
	pipex.cmd_args = ft_split(argv[2], ' ');
//Elle est utilisée pour rechercher et obtenir le chemin complet de la commande à exécuter en fonction de
//son nom (pipex.cmd_args[0]). La variable pipex.cmd est alors mise à jour avec le chemin complet de la commande.
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(EXIT_FAILURE);
	}
// est utilisée pour exécuter la commande spécifiée avec les arguments correspondants et l'environnement
//fourni, en remplaçant le processus actuel par le nouveau programme exécuté.
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipe pipex, char *argv[], char *envp[])
{
//rediriger l'entrée standard (0) vers l'extrémité de lecture du tube (pipex.pipe[0]).
//Cela signifie que le processus fils va maintenant lire à partir du tube plutôt que de l'entrée standard.
	dup2(pipex.pipe[0], 0);
//ferme l'extrémité d'écriture du tube (pipex.pipe[1]) dans le processus fils, car il ne va pas écrire
//dans cette extrémité.
	close(pipex.pipe[1]);
//rediriger la sortie standard (1) vers le descripteur de fichier pipex.infile. Cela signifie que le processus
//fils va écrire dans le fichier spécifié par pipex.infile au lieu d'écrire sur la sortie standard.
	dup2(pipex.outfile, 1);
//diviser la chaîne argv[3] en sous-chaines, Ces sous-chaînes seront ensuite stockées dans un tableau pipex.cmd_args.
	pipex.cmd_args = ft_split(argv[3], ' ');
//Elle est utilisée pour rechercher et obtenir le chemin complet de la commande à exécuter en fonction de
//son nom (pipex.cmd_args[0]). La variable pipex.cmd est alors mise à jour avec le chemin complet de la commande.
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(EXIT_FAILURE);
	}
// est utilisée pour exécuter la commande spécifiée avec les arguments correspondants et l'environnement
//fourni, en remplaçant le processus actuel par le nouveau programme exécuté.
	execve(pipex.cmd, pipex.cmd_args, envp);
}
