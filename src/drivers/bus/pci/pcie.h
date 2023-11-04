#ifndef ODI_DRIVERS_BUS_PCI_PCIE_H
#define ODI_DRIVERS_BUS_PCI_PCIE_H

#define ODI_PCIE_CONFIGURATION_SPACE_SIZE 0x1000

typedef struct{
    uint8_t signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
}__attribute__((packed)) odi_acpi_sdt_header_t;

typedef struct{
    uint64_t base_address;
    uint16_t pci_seg_group;
    uint8_t start_bus;
    uint8_t end_bus;
    uint32_t reserved;
}__attribute__((packed)) odi_device_config_t;

typedef struct{
    odi_acpi_sdt_header_t header;
    uint64_t reserved;
    odi_device_config_t configuration_space[];
}__attribute__((packed)) odi_mcfg_header_t;

#endif // ODI_DRIVERS_BUS_PCI_PCIE_H