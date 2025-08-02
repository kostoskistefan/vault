extern int _make_iso_compilers_happy;

#ifdef __linux__

#include "../../include/vault.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *vault_get_path_from_vault_name(const char *const vault_name)
{
    char *home_directory = getenv("HOME");

    if (home_directory == NULL)
    {
        home_directory = getpwuid(getuid())->pw_dir;
    }

    const char *path_format = "%s/.config/%s/%s.vault";

    uint16_t path_length = snprintf(NULL, 0, path_format, home_directory, vault_name, vault_name);

    char *path = (char *) malloc(path_length + 1);

    sprintf(path, path_format, home_directory, vault_name, vault_name);

    return path;
}

void vault_create_required_directories(const char *const path)
{
    char *dir_path = (char *) malloc(strlen(path) + 1);
    char *next_sep = strchr(path, '/');

    while (next_sep != NULL)
    {
        int dir_path_len = next_sep - path;
        memcpy(dir_path, path, dir_path_len);
        dir_path[dir_path_len] = '\0';
        mkdir(dir_path, S_IRWXU | S_IRWXG | S_IROTH);
        next_sep = strchr(next_sep + 1, '/');
    }

    free(dir_path);
}

#endif
