#include "../../include/vault.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Vault *vault = vault_create("vault");

    vault_store_entry(vault, "some_name", "some_value");
    vault_store_entry(vault, "some_other_name", "some_other_value");

#ifdef DEBUG
    vault_dump_to_stdout(vault);
#endif

    if (!vault_save_to_file(vault))
    {
        printf("Failed to save vault file.\n");
        vault_destroy(vault);
        return EXIT_FAILURE;
    }

    vault_destroy(vault);

    return EXIT_SUCCESS;
}
