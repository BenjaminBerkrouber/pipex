/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:19:26 by bberkrou          #+#    #+#             */
/*   Updated: 2023/11/26 11:47:28 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Executes the specified command using execve. It splits the command into
** arguments, finds the executable path, and then executes the command.
**
** @param  cmd        The command to execute, including its arguments.
** @param  envp       The environment variables.
** @return            None. Exits the program in case of failure.
*/
void ft_exec(char *cmd, char **envp)
{
    char **cmd_args;
    char *path;

    cmd_args = ft_split(cmd, ' ');
    path = ft_get_path(cmd_args[0], envp);
    if (path == NULL || execve(path, cmd_args, envp) == -1)
    {
        ft_free_tab(cmd_args);
        if (path)
            free(path);
        ft_error("Error: Command not found\n");
    }
    ft_free_tab(cmd_args);
    free(path);
}

/*
** Executes the specified command using execve. It splits the command into
** arguments, finds the executable path, and then executes the command.
**
** @param  cmd        The command to execute, including its arguments.
** @param  envp       The environment variables.
** @return            None. Exits the program in case of failure.
*/
void ft_child(int *fd, char **argv, char **envp)
{
    int file_in;

    file_in = open_file(argv[1], 0);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    dup2(file_in, STDIN_FILENO);
    close(file_in);
    ft_exec(argv[2], envp);
    exit(EXIT_SUCCESS);
}

/*
** Manages the parent process in the pipex program. It redirects the standard
** output to the output file, reads input from the pipe, and executes the
** second specified command.
**
** @param  fd         File descriptors for the pipe.
** @param  argv       Command line arguments.
** @param  envp       The environment variables.
** @return            None. Waits for the child process to complete.
*/
void ft_parent(int *fd, char **argv, char **envp)
{
    int file_out;

    file_out = open_file(argv[4], 1);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    dup2(file_out, STDOUT_FILENO);
    close(file_out);
    ft_exec(argv[3], envp);
    wait(NULL);
}

/*
** Main function for the pipex program. It validates the arguments, sets up
** the pipe, and forks to create child and parent processes.
**
** @param  argc       The number of command line arguments.
** @param  argv       The command line arguments.
** @param  envp       The environment variables.
** @return            None. Exits the program in case of failure.
*/
void ft_pipex(int argc, char **argv, char **envp)
{
    int fd[2];
    int pid;

    if (argc != 5)
        ft_error("Error: Wrong number of arguments\n");
    if (pipe(fd) == -1)
        ft_error("Error: Pipe failed\n");
    
    pid = fork();
    if (pid == -1)
        ft_error("Error: Fork failed\n");
    if (pid == 0)
        ft_child(fd, argv, envp);
    else
        ft_parent(fd, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    ft_pipex(argc, argv, envp);
    return (0);
}


