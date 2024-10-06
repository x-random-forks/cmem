# libcmem (v 0.1)

C Memory Lib

## Download and Use

```bash
$ git clone https://github.com/Arkturius/cmem
$ cd cmem

# Use as static library : compile with libcmem.a
$ make
$ clang -o [your_project] [your_project.c] cmem/libcmem.a -I cmem/include


# Use as dynamic library : compile with linker flags
$ make so
$ clang -o [your_project] [your_project.c] -lcmem -L cmem
```

You just have to include `cmem.h`. Since i'm a 42 student, the whole project is in accordance with The Norm.  
This said, i tried to approach an STB-style (header-only) library except for the header-only part.
You'll have to `#define` `CM_CHUNK_IMPLEMENTATION`, `CM_ARENA_IMPLEMENTATION` and/or `CM_HTABLE_IMPLEMENTATION`
to respectively use chunks, arenas and/or hash tables.  
You can also use `#define CM_INCLUDE_ALL` to get the 3 structures implementations at once.

Those are the typedefs available to work with. They are opaque pointers and are not meant to be de-referenced...
```c
typedef void                    t_cm_chunk;
typedef struct s_cm_iter        t_cm_iterator;

typedef void                    t_cm_arena;

typedef void                    t_cm_htable;
```
BUT if you want to do so, you can cast like this to access struct members
```c
struct s_cm_chunk;
struct s_cm_arena;
struct s_cm_htable

// Example of struct cast
t_cm_chunk  *chunk;

chunk = cm_chunk_init("dummy", 16);

struct s_cm_chunk   *object;
object = (struct s_cm_chunk *)chunk;

// Print chunk capacity
printf("Chunk capacity = %zu\n", object->capacity);

cm_chunk_destroy(chunk);
```

## Data chunks
- Simple Constructor and Destructor.
- Memory-aligned push, pop and alloc.
- Basic iterators for linear traversing.
- **(TODO)** Free list for memory reusage.

### Example
Init a chunk of floats and fill it with multiples of PI

```c
#include <unistd.h>

#define CM_CHUNK_IMPLEMENTATION
#include <cmem.h>

int	main(void)
{
    t_cm_chunk	*floats;
    float	tmp;
    size_t      i;

    // Init the chunk
    floats = cm_chunk_init("floats", sizeof(float));

    i = 0;

    // While the chunk isn't full
    while (i < cm_chunk_max(floats))
    {
        // Compute PI * i
        tmp = 3.14 * i;

        // Push this value into the chunk
        ft_chunk_push(floats, &tmp, sizeof(tmp)))

        i++;
    }

    // Destroy the chunk
    cm_chunk_clear(floats, CM_CHUNK_FREE);
}
```

## **(WIP)** Arenas
- Simple Constructor and Destructor.
- Memory-Aligned push, pop and alloc.
- **(TODO)** Free list for memory reusage.

```c
#define CM_ARENA_IMPLEMENTATION
#include <cmem.h>

int	main(void)
{
    t_cm_arena  *strings;

    // Init the arena
    strings = cm_arena_init();

    // Destroy the arena
    cm_arena_clear(strings, CM_ARENA_FREE);
}
```

## **(WIP)** Hash Table
- Simple Constructor and Destructor.
- Ability to store any kind of data. `-> (void *data)`
- Djb2 hash function.
- **(TODO)** Collision management.

```c
#define CM_HTABLE_IMPLEMENTATION
#include <cmem.h>

int	main(void)
{
    t_cm_htable  *books;

    // Init hash table to store pointers
    books = cm_htable_init(32, sizeof(void *));

    // Destroy the hash table
    cm_htable_clear(books, CM_HTABLE_FREE);
}
```
