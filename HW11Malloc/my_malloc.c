/*
 * CS 2110 Fall 2018
 * Author:
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

/* Our freelist structure - our freelist is represented as two doubly linked lists
 * the address_list orders the free blocks in ascending address
 * the size_list orders the free blocks by size
 */

metadata_t *address_list;
metadata_t *size_list;
metadata_t* left;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

static void removeFromAddressList(metadata_t* curr) {
    if (address_list == curr) {
        address_list = curr -> next_addr;
    }
    
    if (curr -> prev_addr != NULL) {
        curr -> prev_addr -> next_addr = curr -> next_addr;
    }
    
    if (curr -> next_addr != NULL) {
        curr -> next_addr -> prev_addr = curr -> prev_addr;
    }
}

static void removeFromSizeList(metadata_t* curr) {
    if (size_list == curr) {
        size_list = curr -> next_size;
    }
    
    if (curr -> prev_size != NULL) {
        curr -> prev_size -> next_size = curr -> next_size;
    }
    
    if (curr -> next_size != NULL) {
        curr -> next_size -> prev_size = curr -> prev_size;
    }
}

static void removeFromList(metadata_t* curr) {

    removeFromAddressList(curr);
    removeFromSizeList(curr);
    
    curr -> next_addr = NULL;
    curr -> next_size = NULL;
    curr -> prev_addr = NULL;
    curr -> prev_size = NULL;
}

static void set_canary(metadata_t* curr) {
    curr -> canary = ((uintptr_t)curr ^ CANARY_MAGIC_NUMBER) + 1;
    unsigned long *canaryBack = ((unsigned long *)((uint8_t*)curr + curr -> size - sizeof(unsigned long)));
    *canaryBack = ((uintptr_t)curr ^ CANARY_MAGIC_NUMBER) + 1;
}

static void add_to_address_list(metadata_t* add_block) {

    if (address_list == NULL) {
        address_list = add_block;
        return;
    }

    metadata_t *curr = address_list;
    int found = 0;

    while (curr != NULL && found == 0) {

        if ((uintptr_t)(curr) > (uintptr_t)(add_block)) {
            found = 1;
        } else if (curr -> next_addr == NULL) {
            found = 2;
        } else {
            curr = curr -> next_addr;
        }
    }

    if (found == 1) {
        //add to front
        if ((uintptr_t)curr == (uintptr_t)address_list) {
            add_block -> next_addr = curr;
            curr -> prev_addr = add_block;
            add_block -> prev_addr = NULL;
            address_list = add_block;
        //add to middle
        } else {
            add_block -> next_addr = curr;
            add_block -> prev_addr = curr -> prev_addr;
            
            curr -> prev_addr -> next_addr = add_block;

            curr -> prev_addr = add_block;
        }

    //add to back case
    } else {
        curr -> next_addr = add_block;
        add_block -> prev_addr = curr;
        add_block -> next_addr = NULL;
    }

}

static void add_to_size_list(metadata_t* add_block) {

    if (size_list == NULL) {
        size_list = add_block;
        return;
    }

    metadata_t *curr = size_list;
    int found = 0;

    while (curr != NULL && found == 0) {

        if (curr -> size > add_block -> size) {
            found = 1;
        } else if (curr -> next_size == NULL) {
            found = 2;
        } else {
            curr = curr -> next_size;
        }
    }

    if (found == 1) {
        //add to front
        if (curr == size_list) {
            add_block -> next_size = curr;
            curr -> prev_size = add_block;
            add_block -> prev_size = NULL;
            size_list = add_block;
            //add to middle
        } else {
            
            add_block -> next_size = curr;
            add_block -> prev_size = curr -> prev_size;

            curr -> prev_size -> next_size = add_block;
            curr -> prev_size = add_block;
        }

        //add to back case
    } else {
        curr -> next_size = add_block;
        add_block -> prev_size = curr;
        add_block -> next_size = NULL;
    }

}


static metadata_t* find_right(metadata_t* curr) {
    
    uintptr_t *endAddr = (uintptr_t*)((uint8_t*)(curr) + curr -> size);
    
    if ((uintptr_t*)(curr -> next_addr) == endAddr) {
        return curr -> next_addr;
    }
    
    return NULL;
}

static metadata_t* find_left(metadata_t* curr) {
    
    metadata_t* prev = curr -> prev_addr;
    
    if (prev == NULL) {
        return NULL;
    }
    
    uintptr_t *endAddr = (uintptr_t*)((uint8_t*)prev + prev -> size);
    
    if ((uintptr_t *)(curr) == endAddr) {
        return curr -> prev_addr;
    }
    
    return NULL;
}

static void leftMerge(metadata_t* left, metadata_t* curr) {
    removeFromSizeList(left);
    
    left -> size = left -> size + curr -> size;
    add_to_size_list(left);
    
    removeFromAddressList(curr);
    
    curr -> prev_addr = NULL;
    curr -> next_addr = NULL;
    
    curr -> prev_size = NULL;
    curr -> next_size = NULL;

}

static void rightMerge(metadata_t* curr, metadata_t* right) {
    curr -> next_addr = right -> next_addr;
    
    curr -> size = curr -> size + right -> size;
    
//    right -> prev_addr -> next_addr = curr;
    if (right -> next_addr != NULL) {
        right -> next_addr -> prev_addr = curr;
    }
    
    removeFromSizeList(right);
    add_to_size_list(curr);
    
    removeFromAddressList(right);
    
    right -> prev_addr = NULL;
    right -> next_addr = NULL;
    
    right -> prev_size = NULL;
    right -> next_size = NULL;
    
}

static void double_merge(metadata_t* left, metadata_t* middle, metadata_t* right) {
    
    left -> next_addr = right -> next_addr;
    
    left -> size = left -> size + middle -> size + right -> size;

    if (right -> next_addr != NULL) {
        right -> next_addr -> prev_addr = left;
    }
    
    removeFromSizeList(right);
    removeFromSizeList(left);
    
    add_to_size_list(left);
    
    removeFromAddressList(middle);
    removeFromAddressList(right);
    
    middle -> prev_addr = NULL;
    middle -> next_addr = NULL;
    
    middle -> prev_size = NULL;
    middle -> next_size = NULL;
    
    right -> prev_addr = NULL;
    right -> next_addr = NULL;
    
    right -> prev_size = NULL;
    right -> next_size = NULL;
    
}

/* MALLOC
 * See my_malloc.h for documentation
 */
void *my_malloc(size_t size) {
    
    if (size <= 0) {
        my_malloc_errno = NO_ERROR;
        return NULL;
    }
    
    size_t sizeRequired = TOTAL_METADATA_SIZE + size;
    
    if (SBRK_SIZE < sizeRequired) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }
    
    metadata_t *curr = size_list;
    int found = 0;
    
    //    struct metadata *prev_addr;
    //    struct metadata *next_addr;
    //    struct metadata *prev_size;
    //    struct metadata *next_size;
    //    unsigned long size; // size of the whole block in number of bytes
    //    unsigned long canary;
    
    while (curr != NULL && found == 0) {
        if (curr -> size == sizeRequired || curr -> size >= sizeRequired + MIN_BLOCK_SIZE) {
            found = 1;
        } else {
            curr = curr -> next_size;
        }
    }
    
    if (found == 1) {
        
        my_malloc_errno = NO_ERROR;

        //Case with same size
        if (curr -> size == sizeRequired) {
            
            removeFromList(curr);
            set_canary(curr);
            
            curr -> next_addr = NULL;
            curr -> next_size = NULL;
            curr -> prev_addr = NULL;
            curr -> prev_size = NULL;
            
            return curr + 1;
        //Case where block is bigger than requested size
        } else {
            metadata_t *newMeta = (metadata_t *)((uint8_t*)curr + curr -> size - sizeRequired);

            //Reenter new curr into size list
            removeFromSizeList(curr);
            curr -> size = curr -> size - sizeRequired;
            add_to_size_list(curr);
            
            //Initialize values
            newMeta -> size = sizeRequired;
            newMeta -> next_addr = NULL;
            newMeta -> next_size = NULL;
            newMeta -> prev_addr = NULL;
            newMeta -> prev_size = NULL;
            
            //Set canaries for new
            set_canary(newMeta);
            
            return newMeta + 1;
            
        }
    } else {
        
        metadata_t *curr = my_sbrk(SBRK_SIZE);
        if (curr == NULL) {
            my_malloc_errno = OUT_OF_MEMORY;
            return NULL; 
        }
        
        curr -> next_addr = NULL;
        curr -> next_size = NULL;
        curr -> prev_addr = NULL;
        curr -> prev_size = NULL;
        
        curr -> size = SBRK_SIZE;
        
        add_to_address_list(curr);
        
        metadata_t* right = find_right(curr);
        metadata_t* left = find_left(curr);
        
        if (right != NULL && left != NULL) {
            
            double_merge(left, curr, right);
            
        } else if (right != NULL) {
            rightMerge(curr, right);
        } else if (left != NULL) {
            leftMerge(left, curr);
        } else {
            add_to_size_list(curr);
        }
        
        my_malloc_errno = NO_ERROR;
        
        return my_malloc(size);
    }
    
	return (NULL);
}


/* REALLOC
 * See my_malloc.h for documentation
 */
void *my_realloc(void *ptr, size_t size) {
	
    
    if (ptr == NULL) {
        my_malloc_errno = NO_ERROR;
        return my_malloc(size);
    }
    
    my_malloc_errno = NO_ERROR;

    if (size == 0) {
        my_free(ptr);
        return NULL;
    }
    
    
    my_free(ptr);
    
    if (my_malloc_errno != NO_ERROR) {
        return NULL;
    }
    
    void *reallocated = my_malloc(size);
    
    metadata_t *curr = (metadata_t *)(ptr) - 1;
    
    if (curr -> size > size) {
        memcpy(reallocated, ptr, size);
    } else {
        memcpy(reallocated, ptr, curr -> size);
    }
    

    return reallocated;
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    void *allocated = my_malloc(nmemb * size);
    if (allocated == NULL) {
        return NULL;
    }
    allocated = memset(allocated, 0, nmemb * size);
    return allocated;
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void *ptr) {
    
    if (ptr == NULL) {
        my_malloc_errno = NO_ERROR;
        return;
    }

    metadata_t *curr = (metadata_t*)(ptr) - 1;

    unsigned long *canaryBack = ((unsigned long *)((uint8_t*)curr + curr -> size - sizeof(unsigned long)));

    if (curr -> canary != (((uintptr_t)curr ^ CANARY_MAGIC_NUMBER) + 1) || *canaryBack != (((uintptr_t)curr ^ CANARY_MAGIC_NUMBER) + 1)) {
        my_malloc_errno = CANARY_CORRUPTED;
        return;
    }
    
    add_to_address_list(curr);
    
    metadata_t* right = find_right(curr);
    metadata_t* left = find_left(curr);
    
    if (right != NULL && left != NULL) {
        
        double_merge(left, curr, right);

    } else if (right != NULL) {
        rightMerge(curr, right);
    } else if (left != NULL) {
        leftMerge(left, curr);
    } else {
        add_to_size_list(curr);
    }
    
    my_malloc_errno = NO_ERROR;
    
    
}







