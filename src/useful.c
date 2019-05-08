/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** useful
*/

#include "my.h"

void free_command(struct data data, char *str)
{
    for (int i = 0; i < data.nbr_command; i++) {
        free(data.command[i]);
    }
    free(str);
}

int count_lines(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == ':')
            count++;
    }
    count++;
    return (count);
}

int find_line_env(struct data data, int command)
{
    int line = -1;
    char *str = malloc(sizeof(char) * (strlen(data.args[command][1]) + 2));

    str = strcpy(str, data.args[command][1]);
    str[strlen(str)] = '=';
    str[strlen(str) + 1] = 0;
    for (int i = 0; data.env[i] != 0; i++) {
        if (strncmp(data.env[i], str, strlen(str)) == 0)
            line = i;
    }
    return (line);
}

int check_error_path(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '/' && (str[i + 1] == '/' || str[i + 1] == '\0'))
            return (1);
    }
    return (0);
}

char *is_existing(struct data data, char *actual)
{
    char *tmp = NULL;

    if (strcmp("setenv", actual) == 0)
        return (actual);
    if (access(actual, F_OK) == 0) {
        tmp = malloc(sizeof(char) * strlen(actual) + 1);
        tmp = strcpy(tmp, actual);
        return (tmp);
    }
    for (int i = 0; data.path[i] != NULL && data.path[i][0] != 0; i++) {
        tmp = malloc(sizeof(char) * 40);
        tmp = strcpy(tmp, data.path[i]);
        tmp = strcat(tmp, "/");
        tmp = strcat(tmp, actual);
        if (access(tmp, F_OK) == 0 && check_error_path(tmp) == 0)
            return (tmp);
        free(tmp);
    }
    return (NULL);
}