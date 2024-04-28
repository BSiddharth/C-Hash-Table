#ifndef Hash_Map_H
#define Hash_Map_H
#include <stdbool.h>
#include <stdint.h>

typedef struct HashMapValue hashmap_value;
typedef struct HashMap hashmap;

hashmap *create_hashmap(uint32_t (*hash_func)(const void *item, uint32_t len,
                                              uint32_t seed),
                        bool (*compare_func)(const void *item1,
                                             const void *item2));

bool insert_in_hash_map(hashmap *hm, void *key, size_t key_size, void *value,
                        size_t value_size); // will also work as update element

void remove_from_hash_map(hashmap *hm, char *key);

bool is_in_hash_map(hashmap *hm, void *key, size_t key_size);

void *get_value(hashmap *hm, void *key, size_t key_size);
#endif // !Hash_Map_H
