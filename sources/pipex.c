/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:36:48 by ccoste            #+#    #+#             */
/*   Updated: 2023/06/13 11:35:24 by ccoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    *find_path(char **envp)
{
//PATH : Cette variable contient une liste de répertoires dans lesquels le système d'exploitation recherche les exécutables lorsqu'une commande est saisie dans la ligne de commande.
    while(ft_strncmp("PATH", *envp, 4))
    {
        envp++;
    }
//PATH + 5 : passe les 5 premier caractère.
    return(*envp + 5);
}

void    close_pipes(t_pipe *pipex)
{
//pipe[0] : C'est le descripteur de fichier (fd) de l'extrémité de lecture (read end) du pipe.
//pipe[1] : C'est le descripteur de fichier (fd) de l'extrémité d'écriture (write end) du pipe.
    close(pipex->pipe[0]);
    close(pipex->pipe[1]);
}
//char *envp[] : C'est un tableau de pointeurs vers des chaînes de caractères qui contiennent les variables d'environnement.
//Une variable d'environnement est une valeur associée à une clé spécifique qui est utilisée par le système d'exploitation pour configurer le comportement d'un programme ou pour stocker des informations système.
int main(int argc, char *argv[], char *envp[])
{
    t_pipe pipex;

    if (argc != 5 )
    {
        msg(ERR_INPUT);
        exit(EXIT_FAILURE);
    }
//O_RDONLY : Ouvrir le fichier en lecture seule.
    pipex.infile = open(argv[1], O_RDONLY);
    if (argv[1] == NULL)
    {
        msg_perror(ERR_INFILE);
    }
//argv(argc[argc - 1]) : le derniere argument de la ligne de commande.
//O_TRUNC : Cette option est utilisée pour tronquer (vider) le fichier s'il existe déjà. Si le fichier n'existe pas, cette option est ignorée.
//O_CREAT : Cette option est utilisée pour créer le fichier s'il n'existe pas déjà.
//O_RDWR : Cette option est utilisée pour ouvrir le fichier en lecture et en écriture.
//0644 : Spécifie que le propriétaire du fichier a les permissions de lecture et d'écriture, tandis que les autres utilisateurs ont uniquement la permission de lecture.
    pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (argv[argc - 1] == NULL)
    {
        msg_perror(ERR_OUTFILE);
    }
    if (pipe(pipex.pipe) < 0)
    {
        msg_perror(ERR_PIPE);
    }
    pipex.path = find_path(envp);
    pipex.cmd_paths = ft_split(pipex.path, ':');
//fork retourne une valeur négative, cela signifie qu'une erreur s'est produite lors de la création du processus enfant.
//fork retourne 0, cela signifie que vous êtes dans le processus enfant.
//fork retourne une valeur positive, cela signifie que vous êtes dans le processus parent et la valeur retournée est l'identifiant du processus enfant.
    pipex.pid1 = fork();
    if (pipex.pid1 == 0)
    {
        first_child(pipex, argv, envp);
    }
    pipex.pid2 = fork();
    if (pipex.pid2 == 0)
    {
        second_child(pipex, argv, envp);
    }
    close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
    return(0);
}
