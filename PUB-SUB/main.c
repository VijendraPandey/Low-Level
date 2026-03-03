#include "rt.h"

int main(){

    rt_table_t table;
    rt_init_rt_table(&table);

    rt_add_or_update_rt_entry(&table,
                              "192.168.1.0", 24,
                              "10.0.0.1",
                              "eth0");

    rt_add_or_update_rt_entry(&table,
                              "10.0.0.0", 8,
                              "10.0.0.254",
                              "eth1");

    rt_dump_rt_table(&table);

    rt_delete_rt_entry(&table,
                       "192.168.1.0", 24);

    rt_dump_rt_table(&table);

    return 0;
}
