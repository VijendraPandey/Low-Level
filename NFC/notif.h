#ifndef NOTIF_CHAIN
#define NOTIF_CHAIN

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "../GLTHREADS/glthreads.h"

#define MAX_NOTIF_KEY_SIZE 64

/* Operation type enum */
typedef enum
{
    NFC_UNKNOWN,
    NFC_ADD,
    NFC_MOD,
    NFC_DEL,
} nfc_op_t;

/* Callback signature:
 * subscriber_id → who is being notified
 * op            → type of operation
 * data          → event data
 * data_size     → size of event data
 */
typedef void (*nfc_app_cb)(
    unsigned int subs_id,
    nfc_op_t op,
    void *data,
    size_t data_size
);


/* Notification chain element (subscriber) */
typedef struct notif_chain_elem
{

    unsigned int subs_id;

    char key[MAX_NOTIF_KEY_SIZE];
    size_t key_size;
    bool_t is_key_set;

    nfc_app_cb app_cb;

    glthread_node_t glue;

} notif_chain_elem_t;

/* Convert glue node back to nfce */
GLTHREAD_TO_STRUCT(
    glthread_glue_to_notif_chain_elem,
    notif_chain_elem_t,
    glue);

/* Notification chain (publisher) */
typedef struct notif_chain_
{
    char nfc_name[64];
    glthread_t notif_chain_head;
} notif_chain_t;

/* APIs */
void nfc_register_notif_chain(
    notif_chain_t *nfc,
    notif_chain_elem_t *nfce);

void nfc_invoke_notif_chain(
    notif_chain_t *nfc,
    nfc_op_t op,
    void *arg,
    size_t arg_size,
    char *key,
    size_t key_size);

notif_chain_t *
nfc_create_new_notif_chain(char *notif_chain_name);

void nfc_delete_all_nfce(notif_chain_t *nfc);

char *nfc_get_str_op_code(nfc_op_t op);

#endif
