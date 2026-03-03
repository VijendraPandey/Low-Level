#ifndef __GLTHREADS__
#define __GLTHREADS__

#include <stddef.h>

/* Doubly linked list node */
typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t;

/* List controller */
typedef struct glthread_ {
    glthread_node_t *head;
    size_t offset;
} glthread_t;

/* API functions */
void glthread_add(glthread_t *lst, glthread_node_t *glnode);
void glthread_remove(glthread_t *lst, glthread_node_t *glnode);
void init_glthread(glthread_t *glthread, size_t offset);

/* Node initializer */
#define glthread_node_init(glnode) \
    (glnode)->left = NULL;         \
    (glnode)->right = NULL;

/* Iterator macros */
#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr)      \
{                                                               \
    glthread_node_t *_glnode = NULL, *_next = NULL;             \
    for(_glnode = (lstptr)->head; _glnode; _glnode = _next){    \
        _next = _glnode->right;                                 \
        ptr = (struct_type *)((char *)_glnode - (lstptr)->offset);

#define ITERATE_GL_THREADS_ENDS }}

/* Convert glthread node to parent struct */
#define GLTHREAD_TO_STRUCT(fn_name, struct_type, field_name) \
static inline struct_type *                                  \
fn_name(glthread_node_t *glnode){                            \
    return (struct_type *)((char *)glnode -                  \
        offsetof(struct_type, field_name));                  \
}

#endif /* __GLTHREADS__ */
