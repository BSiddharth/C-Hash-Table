#include "hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const intmax_t hash_map_len = 100;

typedef struct HashMapValue {
  size_t data_size;
  void *data;
  hashmap_value *next; // could be pointing to NULL
} hashmap_value;

typedef struct HashMap {
  intmax_t hashmap_length;
  hashmap_value *hashmap_keys[];
} hashmap;

hashmap *create_hashmap() {

  // allocating space for hashmap
  hashmap *hashmap_pointer =
      malloc(sizeof(hashmap) + (hash_map_len * sizeof(hashmap_value *)));

  if (hashmap_pointer == NULL) {
    printf("Could not allocate space for hashmap, exiting...");
    exit(EXIT_FAILURE);
  }

  // setting up the allocated memory for a new hashmap
  hashmap_pointer->hashmap_length = hash_map_len;
  for (intmax_t i = 0; i < hash_map_len; i++) {
    hashmap_pointer->hashmap_keys[i] = NULL; // NULL means the bucket is empty
  }

  return hashmap_pointer;
};

/* Can also be used to update element */
void insert_in_hash_map(hashmap *hm, char *key, void *value);

void remove_from_hash_map(hashmap *hm, char *key);

bool is_in_hash_map(hashmap *hm, char *key);

/* Always check for that key exists in the HashMap */
void *get_value(hashmap *hm, char *key);
