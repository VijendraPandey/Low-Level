#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "rt.h"
#include "../NFC/notif.h" /* add this include */

/* Initialize routing table */
void rt_init_rt_table(rt_table_t *rt_table)
{
    rt_table->head = NULL;
}

/* Lookup route entry */
rt_entry_t *rt_lookup_rt_entry(rt_table_t *rt_table,
                               char *dest,
                               char mask)
{

    rt_entry_t *curr = rt_table->head;

    while (curr)
    {
        if (strcmp(curr->rt_entry_keys.dest, dest) == 0 &&
            curr->rt_entry_keys.mask == mask)
        {
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

/* Add or update route entry */
rt_entry_t *rt_add_or_update_rt_entry(rt_table_t *rt_table,
                                      char *dest_ip,
                                      char mask,
                                      char *gw_ip,
                                      char *oif)
{

    /* Check if entry already exists */
    rt_entry_t *entry =
        rt_lookup_rt_entry(rt_table, dest_ip, mask);

    if (entry)
    {
        /* Update existing entry */
        strncpy(entry->gw_ip, gw_ip, sizeof(entry->gw_ip) - 1);
        strncpy(entry->oif, oif, sizeof(entry->oif) - 1);
        return entry;
    }

    /* Create new entry */
    entry = calloc(1, sizeof(rt_entry_t));
    if (!entry)
        return NULL;

    strncpy(entry->rt_entry_keys.dest,
            dest_ip,
            sizeof(entry->rt_entry_keys.dest) - 1);

    entry->rt_entry_keys.mask = mask;

    if (gw_ip)
    strncpy(entry->gw_ip, gw_ip, sizeof(entry->gw_ip) - 1);

if (oif)
    strncpy(entry->oif, oif, sizeof(entry->oif) - 1);


    /* NEW: create notification chain for this entry */
    entry->nfc = nfc_create_new_notif_chain(NULL);

    /* Insert at head */
    entry->next = rt_table->head;
    entry->prev = NULL;

    if (rt_table->head)
    {
        rt_table->head->prev = entry;
    }

    rt_table->head = entry;

    if (gw_ip && oif)
{
    nfc_invoke_notif_chain(
        entry->nfc,
        NFC_ADD,
        (void *)entry,
        sizeof(rt_entry_t),
        NULL,
        0);
}


    return entry;
}

/* Delete route entry */
bool rt_delete_rt_entry(rt_table_t *rt_table,
                        char *dest_ip,
                        char mask)
{
    rt_entry_t *entry =
        rt_lookup_rt_entry(rt_table, dest_ip, mask);

    if (!entry)
        return false;

    /* Step 1: Notify subscribers before deletion */
    if (entry->nfc)
    {
        nfc_invoke_notif_chain(
            entry->nfc,
            NFC_DEL,
            (void *)entry,
            sizeof(rt_entry_t),
            NULL,
            0);
    }

    /* Step 2: Destroy notification chain */
    if (entry->nfc)
    {
        nfc_delete_all_nfce(entry->nfc);
        free(entry->nfc);
        entry->nfc = NULL;
    }

    /* Step 3: Unlink from routing table */
    if (entry->prev)
    {
        entry->prev->next = entry->next;
    }
    else
    {
        /* entry is head */
        rt_table->head = entry->next;
    }

    if (entry->next)
    {
        entry->next->prev = entry->prev;
    }

    /* Step 4: Free entry */
    free(entry);

    return true;
}

/* Dump routing table */
void rt_dump_rt_table(rt_table_t *rt_table)
{

    rt_entry_t *curr = rt_table->head;

    printf("Routing Table:\n");
    printf("-----------------------------\n");

    while (curr)
    {
        printf("Dest: %s/%d | GW: %s | OIF: %s\n",
               curr->rt_entry_keys.dest,
               curr->rt_entry_keys.mask,
               curr->gw_ip,
               curr->oif);

        curr = curr->next;
    }

    printf("-----------------------------\n");
}

void rt_table_register_for_notification(rt_table_t *rt_table, rt_entry_keys_t *keys, size_t key_size, nfc_app_cb app_cb, uint32_t subs_id)
{
    bool new_entry_created;
    rt_entry_t *rt_entry;
    notif_chain_elem_t nfce;

    new_entry_created = false;

    rt_entry = rt_lookup_rt_entry(rt_table, keys->dest, keys->mask);

    if (!rt_entry)
    {
        rt_entry = rt_add_or_update_rt_entry(rt_table, keys->dest, keys->mask, 0, 0);
        new_entry_created = true;
    }

    memset(&nfce, 0, sizeof(notif_chain_elem_t));

    assert(key_size <= MAX_NOTIF_KEY_SIZE);

    nfce.app_cb = app_cb;
    nfce.subs_id = subs_id;
    nfc_register_notif_chain(rt_entry->nfc, &nfce);

    if (!new_entry_created)
    {
        app_cb(
            subs_id,
            NFC_ADD,
            (void *)rt_entry,
            sizeof(rt_entry_t));
    }
}