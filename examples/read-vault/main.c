#include "../../include/vault.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Vault *vault = vault_create("vault");

    if (!vault_read_from_file(vault))
    {
        printf("Failed to read vault file.\n");
        vault_destroy(vault);
        return EXIT_FAILURE;
    }

    char *value_of_some_name = vault_find_entry(vault, "some_name");

    if (value_of_some_name)
        printf("The value of 'some_name' is: %s\n", value_of_some_name);

    char *value_of_some_other_name = vault_find_entry(vault, "some_other_name");

    if (value_of_some_other_name)
        printf("The value of 'some_other_name' is: %s\n", value_of_some_other_name);

#ifdef DEBUG
    vault_dump_to_stdout(vault);
#endif

    vault_destroy(vault);

    return EXIT_SUCCESS;
}
