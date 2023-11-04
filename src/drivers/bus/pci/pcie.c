static void* odi_pcie_map_physical(void* address, size_t size){
    return odi_dep_get_virtual_address(address);
}

void odi_receive_configuration_space_pcie(odi_pci_device_t* device){
    // don't do anything on pci express because it's alread memory mapped
}

void odi_send_configuration_space_pcie(odi_pci_device_t* device){
    // don't do anything on pci express because it's alread memory mapped
}

static void odi_enumerate_function(odi_pci_device_list_info_t* pci_device_list, void* device_address, uint64_t function){
    uint64_t offset = function << 12;

    void* function_address = (void*)((uint64_t)device_address + offset);
    odi_pci_device_header_t* pci_device_header = (odi_pci_device_header_t*)odi_pcie_map_physical(function_address, ODI_PCIE_CONFIGURATION_SPACE_SIZE);

    if(pci_device_header->device_id == 0) return;
    if(pci_device_header->device_id == 0xffff) return;

    odi_pci_device_t* device_info = (odi_pci_device_t*)odi_dep_malloc(sizeof(odi_pci_device_t));
    device_info->is_pcie = true;
    device_info->address = 0; // this is not pci device, it's pcie device
    device_info->configuration_space = pci_device_header;
    device_info->receive_configuration_space = &odi_receive_configuration_space_pcie;
    device_info->send_configuration_space = &odi_send_configuration_space_pcie;

    odi_add_pci_device(pci_device_list, device_info);

    return;
}

static void odi_enumerate_device(odi_pci_device_list_info_t* pci_device_list, void* bus_address, uint64_t device){
    uint64_t offset = device << 15;

    void* device_address = (void*)((uint64_t)bus_address + offset);
    odi_pci_device_header_t* pci_device_header = (odi_pci_device_header_t*)odi_pcie_map_physical(device_address, ODI_PCIE_CONFIGURATION_SPACE_SIZE);

    if(pci_device_header->device_id == 0) return;
    if(pci_device_header->device_id == 0xffff) return;

    if((pci_device_header->header_type & 0x80) != 0){
        for(uint64_t function = 0; function < 8; function++){
            odi_enumerate_function(pci_device_list, device_address, function);
        }
    }else{
        odi_enumerate_function(pci_device_list, device_address, 0);
    }
}

static void odi_enumerate_bus(odi_pci_device_list_info_t* pci_device_list, void* base_address, uint64_t bus){
    uint64_t offset = bus << 20;

    void* bus_address = (void*)((uint64_t)base_address + offset);
    odi_pci_device_header_t* pci_device_header = (odi_pci_device_header_t*)odi_pcie_map_physical(bus_address, ODI_PCIE_CONFIGURATION_SPACE_SIZE);
    if(pci_device_header->device_id == 0) return;
    if(pci_device_header->device_id == 0xffff) return;

    for(uint64_t device = 0; device < 32; device++){
        odi_enumerate_device(pci_device_list, bus_address, device);
    }
}

void odi_pcie_init(odi_pci_device_list_info_t* pci_device_list, void* mcfg_address){
    odi_mcfg_header_t* mcfg = (odi_mcfg_header_t*)mcfg_address;

    size_t entries = ((mcfg->header.length) - sizeof(odi_mcfg_header_t)) / sizeof(odi_device_config_t);

    for(size_t i = 0; i < entries; i++){
        odi_device_config_t* device_config = &mcfg->configuration_space[i];
        for (uint64_t bus = device_config->start_bus; bus < device_config->end_bus; bus++){
            odi_enumerate_bus(pci_device_list, (void*)device_config->base_address, bus);
        }
    }
}