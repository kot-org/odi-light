odi_pci_device_list_info_t* odi_pci_list_init(void){
    odi_pci_device_list_info_t* return_value = (odi_pci_device_list_info_t*)odi_dep_malloc(sizeof(odi_pci_device_list_info_t));
    return_value->devices = odi_vector_create();
    return return_value;
}

void odi_add_pci_device(odi_pci_device_list_info_t* devices_list, odi_pci_device_t* device){
    // setup command register
    odi_pci_device_header_t* header = (odi_pci_device_header_t*)device->configuration_space;
    device->send_configuration_space(device);

    // add device to list
    odi_vector_push(devices_list->devices, device);
}

void odi_convert_list_to_array(odi_pci_device_list_info_t* devices_list, odi_pci_device_array_info_t* devices_array){
    devices_array->devices_count = 1; // 0 is invalid index
    devices_array->devices = (odi_pci_device_t**)odi_dep_malloc((devices_list->devices->length + 1) * sizeof(odi_pci_device_t*));
    for(size_t i = 0; i < devices_list->devices->length; i++){
        devices_array->devices[devices_array->devices_count] = (odi_pci_device_t*)odi_vector_get(devices_list->devices, i);
        devices_array->devices_count++;
    }
}
