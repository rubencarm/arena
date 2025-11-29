/* Ruben's super cool arena allocator 
 * okay so basically im making an arena allocaotr
 *
 *
 *
 *
 *
 *
 * */


#include <stdlib.h>
#include <stddef.h>

#define PAGESIZE 4096
#define NUMPAGES 1000
#define ARENASIZE (PAGESIZE * NUMPAGES)
#define ARENAALIGN 8

typedef struct Arena{
    void* beg;
    void* end;
    void* curr;
    struct Arena* next;
}Arena;

Arena *arena_new();
void a_metadata(Arena*);
void* arena_allocate(Arena*, size_t);
void* arena_free(Arena*);

