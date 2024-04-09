#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Running test now\n");
  hashmap *my_hashmap = create_hashmap();
  printf("Test was succcesful\n");
  return EXIT_SUCCESS;
}
