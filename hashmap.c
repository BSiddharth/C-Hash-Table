#include "hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uintmax_t initial_total_buckets = 100;
const uint32_t secret_seed = 20010206;

typedef struct HashMapValue {
  void *key;
  void *data;
  hashmap_value *next; // could be pointing to NULL
} hashmap_value;

typedef struct HashMap {
  uintmax_t total_buckets;
  uint32_t (*hash_func)(const void *item, uint32_t len, uint32_t seed);
  bool (*compare_func)(const void *item1, const void *item2);
  hashmap_value *keys[];
} hashmap;

hashmap *create_hashmap(uint32_t (*hash_func)(const void *item, uint32_t len,
                                              uint32_t seed),
                        bool (*compare_func)(const void *item1,
                                             const void *item2)) {
  // allocating space for hashmap
  hashmap *hashmap_pointer = malloc(
      sizeof(hashmap) + (initial_total_buckets * sizeof(hashmap_value *)));

  if (hashmap_pointer == NULL) {
    printf("Could not allocate space for hashmap, exiting...");
    exit(EXIT_FAILURE);
  }

  // setting up the allocated memory for a new hashmap
  hashmap_pointer->total_buckets = initial_total_buckets;
  hashmap_pointer->hash_func = hash_func; // func are passed as pointers
  hashmap_pointer->compare_func = compare_func;
  for (uintmax_t i = 0; i < initial_total_buckets; i++) {
    hashmap_pointer->keys[i] = NULL; // NULL means the bucket is empty
  }

  return hashmap_pointer;
};

/* Can also be used to update element */
bool insert_in_hash_map(hashmap *hm, void *key, size_t key_size, void *value,
                        size_t value_size) {

  void *value_copy = malloc(value_size);
  if (value_copy == NULL) {
    printf("Insertion: Could not create space for the new value");
    return false;
  }

  int value_copy_status =
      memcpy_s(value_copy, sizeof(value_copy), value, value_size);
  if (value_copy_status == 0) {
    printf("Insertion: Could not copy the new value");
    return false;
  }

  uintmax_t index =
      hm->hash_func(key, key_size, secret_seed) % hm->total_buckets;

  hashmap_value *current_element = hm->keys[index];
  hashmap_value *last_element = NULL;

  while (current_element != NULL) {
    if (hm->compare_func(current_element->key, key)) {
      goto replace;
    }
    current_element = current_element->next;
    last_element = current_element;
  }

  hashmap_value *new_hashmapvalue = malloc(sizeof(hashmap_value));
  if (new_hashmapvalue == NULL) {
    printf("Insertion: Could not create space for the new hashmap_value");
    return false;
  }

  void *key_copy = malloc(key_size);
  if (key_copy == NULL) {
    printf("Insertion: Could not create space for the new key");
    return false;
  }

  int key_copy_status = memcpy_s(key_copy, sizeof(key_copy), key, key_size);
  if (key_copy_status == 0) {
    printf("Insertion: Could not copy the new key");
    return false;
  }
  new_hashmapvalue->key = key_copy;
  new_hashmapvalue->data = value_copy;
  new_hashmapvalue->next = NULL;

  if (last_element == NULL) {
    printf("element addr: %p being saved\n", new_hashmapvalue->key);
    hm->keys[index] = new_hashmapvalue;
  } else {
    last_element->next = new_hashmapvalue;
  }

  return true;

replace:
  free(current_element->data);
  current_element->data = value_copy;
  return true;
}

void remove_from_hash_map(hashmap *hm, char *key);

bool is_in_hash_map(hashmap *hm, void *key, size_t key_size) {
  uintmax_t index =
      hm->hash_func(key, key_size, secret_seed) % hm->total_buckets;
  hashmap_value *current_element = hm->keys[index];
  while (current_element != NULL) {
    printf("Element addr: %p being sent\n", current_element->key);
    if (hm->compare_func(current_element->key, key)) {
      return true;
    }
    current_element = current_element->next;
  }
  return false;
}

/* Always check for that key exists in the HashMap */
void *get_value(hashmap *hm, char *key);
