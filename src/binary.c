/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** binary
*/

#include "my.h"

static int do_pipe_first(sh_t *sh, int i, int pipes[], int out)
{
    if (sh->command[i + 1] != NULL)
        dup2(pipes[1], 1);
    else {
        if (sh->redirection != 0)
            dup2(out, 1);
    }
    close(pipes[0]);
    if (is_builtin(sh, i) == 1)
        return (out);
    if (strncmp(sh->command[i], "./", 2) == 0)
        do_binary(sh, i);
    else {
        if (execve(sh->command[i], sh->args[i], sh->env) < 0) {
            if (errno != 2) {
                my_putstr_err(sh->command[0]);
                my_putstr_err(": Permission denied.\n");
            }
        }
    }
    return (out);
}

static int close_fd_pipes(int out, int pipes[], int fd_in, sh_t *sh)
{
    int status;

    close(out);
    close(pipes[0]);
    close(fd_in);
    for (int i = 0; i < sh->nbr_command; i++) {
        if (wait(&status) < 0)
            exit(84);
    }
    sh->exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status) == 1) {
        sh->exit_status = status;
        print_error(status);
    }
    status = check_exit(sh);
    if (sh->not_found == 1)
        return (1);
    if (status > 0)
        return (status);
    return (sh->exit_status);
}

void do_pipe(sh_t *sh, int i)
{
    int pipes[2];
    int out = open_type(sh->redirection, sh->redirection_name);
    static int fd_in = 0;

    pipe(pipes);
    if (fork() == 0) {
        dup2(fd_in, 0);
        out = do_pipe_first(sh, i, pipes, out);
        exit(0);
    } else {
        close(pipes[1]);
        fd_in = pipes[0];
        if (sh->command[i + 1] == NULL) {
            sh->exit_status = close_fd_pipes(out, pipes, fd_in, sh);
            exit(sh->exit_status);
        }
    }
}

void do_binary(sh_t *sh, int command)
{
    sh->command[command] += 2;
    if (execve(sh->command[command], sh->args[command], sh->env) <= 0) {
        my_putstr_err("./");
        my_putstr_err(sh->command[command]);
        my_putstr_err(": Exec format error. Wrong Architecture.\n");
    }
    exit(0);
}

void check_binary(sh_t *sh)
{
    for (int i = 0; i < sh->nbr_command; i++) {
        if (strncmp(sh->command[i], "./", 2) == 0)
            do_binary(sh, i);
    }
}