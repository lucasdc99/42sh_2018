/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** options
*/

#include "my.h"

static char *put_space(char *new_str, char *str, int *a, int i)
{
    if (str[i - 1] != ' ') {
        new_str[a[0]] = ' ';
        a[0]++;
    }
    new_str[a[0]] = str[i];
    a[0]++;
    if (str[i + 1] != ' ') {
        new_str[a[0]] = ' ';
        a[0]++;
    }
    return (new_str);
}

char *useless_pipe(char *str)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) + 1));
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            new_str = put_space(new_str, str, &a, i);
        } else {
            new_str[a] = str[i];
            a++;
        }
    }
    new_str[a] = '\0';
    return (new_str);
}

char **add_env(sh_t *sh, int command)
{
    int j = 0;

    for (; sh->env[j] != NULL; j++);
    sh->env[j] = malloc(sizeof(char) * 20);
    sh->env[j] = strcpy(sh->env[j], sh->args[command][1]);
    sh->env[j] = strcat(sh->env[j], "=");
    for (int i = 2; i <= sh->nbr_args[command]; i++)
        sh->env[j] = strcat(sh->env[j], sh->args[command][i]);
    sh->env[j + 1] = 0;
    return (sh->env);
}

static int count_commands_type(char *str, int i, int *counter, int *neighbor)
{
    if (str[i] == '|') {
        if (check_error_pipe(str, i) == 84)
            return (84);
        counter[0]++;
        neighbor[0]++;
    } else {
        if (neighbor[0] == 3)
            return (84);
        else
            neighbor[0] = 0;
    }
    return (0);
}

int count_commands(char *str)
{
    int counter = 1;
    int neighbor = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (count_commands_type(str, i, &counter, &neighbor) == 84)
            return (84);
    }
    return (counter);
}