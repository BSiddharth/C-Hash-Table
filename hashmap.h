#ifndef Hash_Map_H
#define Hash_Map_H
#include <stdbool.h>
#include <stdint.h>

typedef struct HashMapValue hashmap_value;
typedef struct HashMap hashmap;

hashmap *create_hashmap();

void insert_in_hash_map(hashmap *hm, char *key,
                        void *value); // will also work as update element

void remove_from_hash_map(hashmap *hm, char *key);

bool is_in_hash_map(hashmap *hm, char *key);

void *get_value(hashmap *hm,
                char *key); // always check for that key exists in the hashmap

intmax_t hasher(char *input);

#endif // !Hash_Map_H
