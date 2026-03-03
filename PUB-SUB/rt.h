#ifndef RTABLE_H
#define RTABLE_H

#include <stdbool.h>
#include "../NFC/notif.h"   /* add this include */

typedef struct rt_entry_keys_
{
    char dest[16];
    char mask;
} rt_entry_keys_t;

typedef struct rt_entry_
{
    rt_entry_keys_t rt_entry_keys;

    char gw_ip[16];
    char oif[32];
    struct rt_entry_ *prev;
    struct rt_entry_ *next;

    /* New: notification chain per route entry */
    notif_chain_t *nfc;

} rt_entry_t;

typedef struct rt_table_
{
    rt_entry_t *head;
} rt_table_t;

void rt_init_rt_table(rt_table_t *rt_table);

rt_entry_t* rt_add_or_update_rt_entry(rt_table_t *rt_table,
                                      char *dest_ip,
                                      char mask,
                                      char *gw_ip,
                                      char *oif);

bool rt_delete_rt_entry(rt_table_t *rt_table,
                        char *dest_ip,
                        char mask);

rt_entry_t* rt_lookup_rt_entry(rt_table_t *rt_table,
                               char *dest,
                               char mask);

void rt_dump_rt_table(rt_table_t *rt_table);

void rt_table_register_for_notification(rt_table_t *rt_table, rt_entry_keys_t *keys, size_t key_size, nfc_app_cb app_cb, uint32_t subs_id);

#endif
