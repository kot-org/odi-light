#include "../odi-light/odi-ocf.c"

void odi_examples_pci(void* mcfg_table){
    /* example of the pci driver implementation */
    odi_pci_handler_t* odi_pci_handler = odi_drivers_bus_pci_init(acpi_find_table(acpi_rsdp, "MCFG"));
    odi_pci_device_info_t odi_pci_device_info = (odi_pci_device_info_t){
        ODI_PCI_SEARCH_NO_PARAMETER, 
        ODI_PCI_SEARCH_NO_PARAMETER, 
        ODI_PCI_SEARCH_NO_PARAMETER,
        ODI_PCI_SEARCH_NO_PARAMETER,
        ODI_PCI_SEARCH_NO_PARAMETER };
    
    size_t odi_pci_device_detected = odi_pci_handler->count_devices(&odi_pci_device_info);

    odi_dep_printf("[module/odi/pci] %d device%s detected\n", odi_pci_device_detected, odi_pci_device_detected > 1 ? "s" : "");

    for(size_t i = 0; i < odi_pci_device_detected; i++){
        odi_pci_device_id_t device_id = odi_pci_handler->find_device(&odi_pci_device_info, i);
        odi_pci_device_info_t device_info;
        assert(!odi_pci_handler->get_info_device(device_id, &device_info));
        odi_dep_printf("[module/odi/pci/device/%d] Vendor : %d, Device ID : %d, Class ID : %d, Subclass ID : %d, Programming Interface Byte : %d\n", i, device_info.vendor_id, device_info.device_id, device_info.class_id, device_info.sub_class_id, device_info.prog_if);
    }

}