#ifndef Hash_Map_H
#define Hash_Map_H

typedef struct HashMap;

void insert_in_hash_map(HashMap *hm,char *key, void *value); // will also work as update element
void remove_from_hash_map(HashMap *hm,char *key);
bool is_in_hash_map(HashMap *hm, char *key);
void *get_value(HashMap *hm, char *key); // always check for that key exists in the HashMap

#endif // !Hash_Map_H
