#ifndef VAULT_H
#define VAULT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct vault_s vault_s;

vault_s *vault_create(const char *const vault_name);
void vault_destroy(vault_s *const vault);

const char *vault_get_file_path(const vault_s *const vault);
uint8_t vault_insert(vault_s *const vault, const char *const key, const char *const value);
const char *vault_find(const vault_s *const vault, const char *const key);
const char *vault_find_or_default(const vault_s *const vault, const char *const key, const char *const default_value);
uint8_t vault_update(vault_s *const vault, const char *const key, const char *const value);

uint8_t vault_save(const vault_s *const vault);
uint8_t vault_load(vault_s *const vault);

// Platform specific functions
uint8_t vault_file_exists(const vault_s *const vault);
char *vault_get_path_from_vault_name(const char *const vault_name);
void vault_create_required_directories(const char *const path);

#ifdef DEBUG
void vault_dump(const vault_s *const vault);
#endif

#ifdef __cplusplus
}
#endif

#endif // VAULT_H
