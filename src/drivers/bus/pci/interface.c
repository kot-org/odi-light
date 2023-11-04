odi_pci_handler_t odi_pci_internal_handler;

size_t odi_drivers_bus_pci_count_devices(odi_pci_device_info_t* info){
    return odi_device_search(pci_device_array, info->vendor_id, info->device_id, info->class_id, info->sub_class_id, info->prog_if);
}

odi_pci_device_id_t odi_drivers_bus_pci_find_device(odi_pci_device_info_t* info, size_t index){
    return odi_device_find(pci_device_array, info->vendor_id, info->device_id, info->class_id, info->sub_class_id, info->prog_if, index);
}

int odi_drivers_bus_pci_get_info_device(odi_pci_device_id_t id, odi_pci_device_info_t* info){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    odi_pci_device_header_t* header = (odi_pci_device_header_t*)device_info->configuration_space;
    info->vendor_id = header->vendor_id;
    info->device_id = header->device_id;
    info->class_id = header->class_id;
    info->sub_class_id = header->sub_class_id;
    info->prog_if = header->prog_if;
    
    return 0;
}

int odi_drivers_bus_pci_get_bar_device(odi_pci_device_id_t id, uint8_t bar_index, odi_pci_bar_info_t* info){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    info->address = odi_device_get_bar_address(device_info, bar_index);
    info->size = odi_device_get_bar_size(device_info, bar_index);
    info->type = odi_device_get_bar_type(device_info, bar_index);

    return 0;
}

int odi_drivers_bus_pci_bind_msi(odi_pci_device_id_t id, uint8_t interrupt_vector, uint8_t processor, uint16_t local_device_vector, uint64_t* version){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    return odi_device_bind_msi(device_info, interrupt_vector, processor, local_device_vector, version);
}

int odi_drivers_bus_pci_unbind_msi(odi_pci_device_id_t id, uint16_t local_device_vector){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    return odi_device_unbind_msi(device_info, local_device_vector);
}

int odi_drivers_bus_pci_config_read_word(odi_pci_device_id_t id, uint16_t offset, uint16_t* value){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    return odi_device_config_read_word(device_info, offset, value);
}

int odi_drivers_bus_pci_config_write_word(odi_pci_device_id_t id, uint16_t offset, uint16_t value){
    if(!odi_device_check(pci_device_array, id)) return EINVAL;

    odi_pci_device_t* device_info = odi_device_get_from_index(pci_device_array, id);
    return odi_device_config_write_word(device_info, offset, value);
}

odi_pci_handler_t* odi_interface_init(void){
    odi_pci_internal_handler.count_devices = &odi_drivers_bus_pci_count_devices;
    odi_pci_internal_handler.find_device = &odi_drivers_bus_pci_find_device;
    odi_pci_internal_handler.get_info_device = &odi_drivers_bus_pci_get_info_device;
    odi_pci_internal_handler.get_bar_device = &odi_drivers_bus_pci_get_bar_device;
    odi_pci_internal_handler.bind_msi = &odi_drivers_bus_pci_bind_msi;
    odi_pci_internal_handler.unbind_msi = &odi_drivers_bus_pci_unbind_msi;
    odi_pci_internal_handler.config_read_word = &odi_drivers_bus_pci_config_read_word;
    odi_pci_internal_handler.config_write_word = &odi_drivers_bus_pci_config_write_word;
    return &odi_pci_internal_handler;
}