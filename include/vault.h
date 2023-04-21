#ifndef VAULT_H
#define VAULT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct Vault Vault;

extern Vault *vault_create(const char *vault_name);
extern void vault_destroy(Vault *vault);

extern char *vault_get_file_path(Vault *vault);
extern uint8_t vault_insert(Vault *vault, const char *key, const char *value);
extern char   *vault_find(Vault *vault, const char *key, char *default_value);
extern uint8_t vault_update(Vault *vault, const char *key, const char *value);

extern uint8_t vault_save(Vault *vault);
extern uint8_t vault_load(Vault *vault);

extern void vault_dump(Vault *vault);

extern uint8_t vault_file_exists(Vault *vault);
extern char *vault_get_path_from_vault_name(const char *vault_name);
extern void vault_create_required_directories(const char *path);

#ifdef __cplusplus
}
#endif

#endif // VAULT_H
