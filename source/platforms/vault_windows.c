extern int _make_iso_compilers_happy;

#ifdef __WIN32

#include "../../include/vault.h"
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <shlobj.h>
#include <winnt.h>

char *vault_get_path_from_vault_name(const char *const vault_name)
{
    PWSTR user_data_directory;

    HRESULT user_data_directory_found = SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &user_data_directory);

    if (user_data_directory_found != S_OK)
    {
        fprintf(stderr, "vault::error: Failed to find the user data directory\n");
        return NULL;
    }

    int path_multibyte_length = WideCharToMultiByte(CP_UTF8, 0, user_data_directory, -1, NULL, 0, NULL, NULL);

    if (path_multibyte_length == 0)
    {
        fprintf(stderr, "vault::error: Failed to convert wide string to multi-byte\n");
        CoTaskMemFree(user_data_directory);
        return NULL;
    }

    char *user_data_directory_string = (char *) malloc(path_multibyte_length);

    if (user_data_directory_string == NULL)
    {
        fprintf(stderr, "vault::error: Memory allocation failed\n");
        CoTaskMemFree(user_data_directory);
        return NULL;
    }

    WideCharToMultiByte(
        CP_UTF8,
        0,
        user_data_directory,
        -1,
        user_data_directory_string,
        path_multibyte_length,
        NULL,
        NULL
    );

    const char *path_format = "%s/%s/%s.vault";

    uint16_t path_length = snprintf(NULL, 0, path_format, user_data_directory_string, vault_name, vault_name);

    char *path = (char *) malloc(path_length + 1);

    sprintf(path, path_format, user_data_directory_string, vault_name, vault_name);

    free(user_data_directory_string);
    CoTaskMemFree(user_data_directory);

    return path;
}

void vault_create_required_directories(const char *path)
{
    char *dir_path = (char *) malloc(strlen(path) + 1);
    char *next_sep = strchr(path, '/');

    while (next_sep != NULL)
    {
        int dir_path_len = next_sep - path;
        memcpy(dir_path, path, dir_path_len);
        dir_path[dir_path_len] = '\0';
        mkdir(dir_path);
        next_sep = strchr(next_sep + 1, '/');
    }

    free(dir_path);
}

#endif
