#ifdef ODI_ENABLE_PCI_DRIVER

#include "main.h"

odi_pci_device_array_info_t* pci_device_array = NULL;

#include "pci.c"
#include "pcie.c"
#include "list.c"
#include "device.c"
#include "interface.c"


odi_pci_handler_t* odi_drivers_bus_pci_init(void* mcfg_table){
    odi_pci_device_list_info_t* pci_device_list = odi_pci_list_init();

    if(mcfg_table != NULL){
        odi_pcie_init(pci_device_list, mcfg_table);
    }else{
        odi_pci_init(pci_device_list);
    }

    pci_device_array = (odi_pci_device_array_info_t*)odi_dep_malloc(sizeof(odi_pci_device_array_info_t));

    odi_convert_list_to_array(pci_device_list, pci_device_array);

    return odi_interface_init();
}

#endif // ODI_ENABLE_PCI_DRIVER