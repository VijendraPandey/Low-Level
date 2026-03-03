#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "notif.h"

/* Register a new subscriber */
void nfc_register_notif_chain(
    notif_chain_t *nfc,
    notif_chain_elem_t *nfce){

    notif_chain_elem_t *new_nfce =
        calloc(1, sizeof(notif_chain_elem_t));

    memcpy(new_nfce, nfce, sizeof(notif_chain_elem_t));

    glthread_node_init(&new_nfce->glue);

    glthread_add(&nfc->notif_chain_head, &new_nfce->glue);
}

/* Invoke notification */
void nfc_invoke_notif_chain(
    notif_chain_t *nfc,
    nfc_op_t op,
    void *arg,
    size_t arg_size,
    char *key,
    size_t key_size){

    notif_chain_elem_t *nfce = NULL;

    assert(key_size <= MAX_NOTIF_KEY_SIZE);

    ITERATE_GL_THREADS_BEGIN(
        &nfc->notif_chain_head,
        notif_chain_elem_t,
        nfce){

        /* Case 1: subscriber wants all events */
        if(!nfce->is_key_set){
            nfce->app_cb(
                nfce->subs_id,
                op,
                arg,
                arg_size
            );
            continue;
        }

        /* Case 2: key-based subscription */
        if(key &&
           nfce->key_size == key_size &&
           memcmp(nfce->key, key, key_size) == 0){

            nfce->app_cb(
                nfce->subs_id,
                op,
                arg,
                arg_size
            );
        }

    } ITERATE_GL_THREADS_ENDS;
}

/* Create new notification chain */
notif_chain_t *
nfc_create_new_notif_chain(char *notif_chain_name){

    notif_chain_t *nfc =
        calloc(1, sizeof(notif_chain_t));

    if(!nfc)
        return NULL;

    if(notif_chain_name){
        strncpy(nfc->nfc_name,
                notif_chain_name,
                sizeof(nfc->nfc_name) - 1);
    }

    init_glthread(
        &nfc->notif_chain_head,
        offsetof(notif_chain_elem_t, glue)
    );

    return nfc;
}

/* Delete all subscribers */
void
nfc_delete_all_nfce(notif_chain_t *nfc){

    notif_chain_elem_t *nfce = NULL;

    ITERATE_GL_THREADS_BEGIN(
        &nfc->notif_chain_head,
        notif_chain_elem_t,
        nfce){

        glthread_remove(
            &nfc->notif_chain_head,
            &nfce->glue
        );

        free(nfce);

    } ITERATE_GL_THREADS_ENDS;
}

char *nfc_get_str_op_code(nfc_op_t op){

    switch(op){
        case NFC_ADD: return "ADD";
        case NFC_MOD: return "MOD";
        case NFC_DEL: return "DEL";
        default: return "UNKNOWN";
    }
}
