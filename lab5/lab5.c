#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size) {
      return curr->id;
    }
    curr = curr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t bestsize = 0;
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size) {
      if (best_fit_id = -1 || curr->size < bestsize) {
        best_fit_id = curr->id;
        bestsize = curr->size;
      }
    }
    curr = curr->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worstsize = 0;
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size) {
      if (worst_fit_id == -1 || curr->size > worstsize) {
        worst_fit_id = curr->id;
        worstsize = curr->size;
      }
    }
    curr = curr->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for First-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for First-Fit algorithm is: %d\n", worst_fit_id);

  return 0;
}

// Pseudocode for Part 2
// memory order: a,b,c,d,m,z,n,f,g,h
// Free b,m,n
// Allocated: a,c,d,f,g,h
// Each block's end address is (address of block) + block->size
//
// remove_from_list(target){
//      if head == target:
//         head = target->next;
//      else:
//         prev = head
//         while prev->next != target:
//             prev = prev->next
//         prev->next = target->next
//
// coalesce(new_block):
//      newstart = address of the new_block
//      newend = new_start + new_block->size
//      before and after = NULL //freeing blocks ending at new_start and starting at new_end
//
//      curr = head
//      while curr is not NULL:
//           if curr + curr->size == newstart:
//             before=curr
//           if curr == newend:
//             after = curr
//           curr = curr->next
//
//      //Merge w/ the block after by removing it from the list
//      if after != NULL:
//         remove_from_list(after);
//         new_block->size += after->size
//
//      //now merge with the block before
//      if before != NULL:
//         before->size += new_block->size
//      else:
//         new_block->next = head
//         head = new_block
