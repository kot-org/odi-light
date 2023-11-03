#include "main.h"

pci_device_array_info_t* pci_device_array = NULL;

#include "pci.c"
#include "pcie.c"
#include "list.c"
#include "device.c"
#include "interface.c"


int odi_drivers_bus_pci_init(void* mcfg_table){
    pci_device_list_info_t* pci_device_list = pci_list_init();

    if(mcfg_table != NULL){
        pcie_init(pci_device_list, mcfg_table);
    }else{
        pci_init(pci_device_list);
    }

    pci_device_array = (pci_device_array_info_t*)odi_dep_malloc(sizeof(pci_device_array_info_t));

    convert_list_to_array(pci_device_list, pci_device_array);
}