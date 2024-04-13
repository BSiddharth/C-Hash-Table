#include "hashmap.h"
#include "murmurhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *first_name;
  char *last_name;
  char *phone_number;
} User;

bool compare_user(const void *user1, const void *user2) {
  const User *user_1 = (const User *)user1;
  const User *user_2 = (const User *)user2;

  return strcmp(user_1->first_name, user_2->first_name) &&
         strcmp(user_1->last_name, user_2->last_name) &&
         strcmp(user_1->phone_number, user_2->phone_number);
}

int main() {
  printf("Running test now\n");
  User sid = {"Siddharth", "Bisht", "1234567890"};
  User vaish = {"Vaishnavi", "Bisht", "1934767890"};
  hashmap *my_hashmap = create_hashmap(&murmurhash, compare_user);
  insert_in_hash_map(my_hashmap, &sid, sizeof(sid), &vaish, sizeof(vaish));
  printf("Test was succcesful\n");
  return EXIT_SUCCESS;
}
