#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdbool.h>
#include<memory.h>
#include <stdint.h>
#include "rt.h"
#include "../NFC/notif.h"

void create_subscriber_thread(uint32_t client_id);

extern rt_table_t* publisher_get_rt_table();

static void test_cb(unsigned int client_id,
             nfc_op_t nfc_op_code,
             void *data,
             size_t size)
{
    printf("%s() client : %u, Notified with opcode %s\n", __FUNCTION__, client_id, nfc_get_str_op_code(nfc_op_code));
}

static void* subscriber_thread_fn(void* arg){
    rt_entry_keys_t rt_entry_keys;

    memset(&rt_entry_keys, 0, sizeof(rt_entry_keys_t));
    strncpy(rt_entry_keys.dest, "122.1.1.1", 16);
    rt_entry_keys.mask = 32;

    rt_table_register_for_notification(publisher_get_rt_table(), &rt_entry_keys, sizeof(rt_entry_keys_t), test_cb, (uint32_t)(uintptr_t)arg);

    memset(&rt_entry_keys, 0, sizeof(rt_entry_keys_t));
    strncpy(rt_entry_keys.dest, "122.1.1.5", 16);
    rt_entry_keys.mask = 32;

    rt_table_register_for_notification(publisher_get_rt_table(), &rt_entry_keys, sizeof(rt_entry_keys_t), test_cb, (uint32_t)(uintptr_t)arg);

    memset(&rt_entry_keys, 0, sizeof(rt_entry_keys_t));
    strncpy(rt_entry_keys.dest, "122.1.1.6", 16);
    rt_entry_keys.mask = 32;

    rt_table_register_for_notification(publisher_get_rt_table(), &rt_entry_keys, sizeof(rt_entry_keys_t), test_cb, (uint32_t)(uintptr_t)arg);

    pause();
    return NULL;
}

void create_subscriber_thread(uint32_t client_id){
    pthread_attr_t attr;
    pthread_t subs_thread;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&subs_thread, &attr, subscriber_thread_fn, (void *)(uintptr_t)client_id);

    printf("Subscriber %u Created\n", client_id);
}