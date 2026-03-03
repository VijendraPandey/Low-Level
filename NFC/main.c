#include <stdio.h>
#include "notif.h"

void sample_callback(unsigned int id,
                     nfc_op_t op,
                     void *data,
                     size_t size){

    printf("Subscriber %u notified. Op = %d\n", id, op);
}

int main(){

    notif_chain_t *nfc =
        nfc_create_new_notif_chain("TestChain");

    notif_chain_elem_t sub = {0};

    sub.subscriber_id = 1;
    sub.app_cb = sample_callback;
    sub.is_key_set = 0;

    nfc_register_notif_chain(nfc, &sub);

    int value = 100;

    nfc_invoke_notif_chain(
        nfc,
        NFC_ADD,
        &value,
        sizeof(value),
        NULL,
        0
    );

    nfc_delete_all_nfce(nfc);
    free(nfc);

    return 0;
}
