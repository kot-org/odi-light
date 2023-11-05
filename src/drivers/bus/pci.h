#ifdef ODI_ENABLE_PCI_DRIVER

#ifndef ODI_DRIVERS_BUS_PCI_H
#define ODI_DRIVERS_BUS_PCI_H

#include "pci/main.h"

#define ODI_PCI_BAR_TYPE_NULL           0x0
#define ODI_PCI_BAR_TYPE_IO             0x1
#define ODI_PCI_BAR_TYPE_32             0x2
#define ODI_PCI_BAR_TYPE_64             0x3

#define ODI_PCI_SEARCH_NO_PARAMETER     0xFFFF

#define ODI_PCI_MSI_VERSION             0x1
#define ODI_PCI_MSIX_VERSION            0x2

typedef uint64_t odi_pci_device_id_t;

typedef struct {
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t class_id;
    uint16_t sub_class_id;
    uint16_t prog_if;
} odi_pci_device_info_t;

typedef struct {
    void* address;
    size_t size;
    uint8_t type;
} odi_pci_bar_info_t;

typedef struct{
    size_t (*count_devices)(odi_pci_device_info_t*); // arg 0: info | return count
    odi_pci_device_id_t (*find_device)(odi_pci_device_info_t*, uint64_t); // arg 0: info | arg 1: index | return id
    int (*get_info_device)(odi_pci_device_id_t, odi_pci_device_info_t*); // arg 0: id | arg1: info pointer | return result
    int (*get_bar_device)(odi_pci_device_id_t, uint8_t, odi_pci_bar_info_t*); // arg 0: id | arg1: bar index | arg2: info pointer | return result
    int (*bind_msi)(odi_pci_device_id_t, uint8_t, uint8_t, uint16_t, uint64_t*); // arg 0: id | arg1: interrupt vector | arg2: processor | arg3: local device vector | arg4: version pointer | return result
    int (*unbind_msi)(odi_pci_device_id_t, uint16_t); // arg 0: id | arg1: local device vector | return result
    int (*config_read_word)(odi_pci_device_id_t, uint16_t, uint16_t*); // arg 0: id | arg1: offset | arg2: value pointer | return result
    int (*config_write_word)(odi_pci_device_id_t, uint16_t, uint16_t); // arg 0: id | arg1: offset | arg2: value | return result
} odi_pci_handler_t;

odi_pci_handler_t* odi_drivers_bus_pci_init(void* mcfg);

size_t odi_drivers_bus_pci_count_devices(odi_pci_device_info_t* info);
odi_pci_device_id_t odi_drivers_bus_pci_find_device(odi_pci_device_info_t* info, size_t index);
int odi_drivers_bus_pci_get_info_device(odi_pci_device_id_t id, odi_pci_device_info_t* info);
int odi_drivers_bus_pci_get_bar_device(odi_pci_device_id_t id, uint8_t bar_index, odi_pci_bar_info_t* info);
int odi_drivers_bus_pci_bind_msi(odi_pci_device_id_t id, uint8_t interrupt_vector, uint8_t processor, uint16_t local_device_vector, uint64_t* version);
int odi_drivers_bus_pci_unbind_msi(odi_pci_device_id_t id, uint16_t local_device_vector);
int odi_drivers_bus_pci_config_read_word(odi_pci_device_id_t id, uint16_t offset, uint16_t* value);
int odi_drivers_bus_pci_config_write_word(odi_pci_device_id_t id, uint16_t offset, uint16_t value);

#endif // ODI_DRIVERS_BUS_PCI_H

#endif // ODI_ENABLE_PCI_DRIVER