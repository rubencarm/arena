#include "arena.h"
#include <stdio.h>
#include <stdint.h>
Arena* arena_new()
{
    Arena* a = malloc(sizeof(Arena));
    if (a == NULL){
        return NULL;
    }
    a->beg = malloc(ARENASIZE);
    if(a->beg == NULL){
        return NULL;
    }
    a->end = (char*)  a->beg + ARENASIZE;
    a->curr = a->beg;
    a->next = NULL;
    return a;
}
void a_metadata(Arena* a){
    printf("arena: %p\nbeg: %p\ncurr: %p\nend: %p\nnext: %p\n", a, a->beg, a->curr,a->end, a->next);
}
void* arena_allocate(Arena* a, size_t bytes){
    void* ptr;
    bytes = (bytes / ARENAALIGN + 1) * ARENAALIGN;
    if (bytes > ARENASIZE){
        return NULL;
    }
    if (bytes > (a->end - a->curr)){
        if(a->next != NULL){
            a->next = arena_new();
            ptr = arena_allocate(a->next, bytes);
        }
    } else {
        ptr = a->curr;
        a->curr = (char *) a->curr + bytes;
    }

   return ptr;

}
void* arena_free(Arena* a){
    if (a->next != NULL)
        arena_free(a->next);
    if (a->beg != NULL)
        free(a->beg);
    a->next = a->beg = a->end = a->curr = NULL;
    return NULL;
}
