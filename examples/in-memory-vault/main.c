#include "../../include/vault.h"
#include <stdio.h>

int main(void)
{
    Vault *vault = vault_create("in-memory-vault");

    vault_store_entry(vault, "some_name", "some_value");
    vault_store_entry(vault, "some_other_name", "some_other_value");

    printf("%s\n", vault_find_entry(vault, "some_name"));
    printf("%s\n", vault_find_entry(vault, "some_other_name"));

#ifdef DEBUG
    vault_dump_to_stdout(vault);
#endif

    vault_destroy(vault);

    return 0;
}
