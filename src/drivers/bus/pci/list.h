#ifndef ODI_DRIVERS_BUS_PCI_LIST_H
#define ODI_DRIVERS_BUS_PCI_LIST_H

odi_pci_device_list_info_t* odi_pci_list_init(void);

void odi_add_pci_device(odi_pci_device_list_info_t* devices_list, odi_pci_device_t* device);

void odi_convert_list_to_array(odi_pci_device_list_info_t* devices_list, odi_pci_device_array_info_t* devices_array);

#endif