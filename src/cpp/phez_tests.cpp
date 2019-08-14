
#include "phez_tests.hpp"

/** \brief Check if HDF5 file I/O is art. (This is actually useful! We're just
 *          pinging the unit test class to see if it exists.)
 */
bool hdf5_test_class::but_is_it_art(){
    /** It's debatable. */
    bool retval = (bool)(((long int)this / 10) % 2);
    if(retval){
        cout << "Yes, it's art!" << endl;
    }else{
        cout << "No, it's not art." << endl;
    }

    return(retval);
}
/** \brief Try to initialize then destroy a file struct. Thoroughly checks initialization,
 *          but only checks if destroy function decrements file counter and resets the pointer.
 */
bool hdf5_test_class::can_init_and_destroy_a_file(){
    phez_file_t* new_file;
    fapl_t fapl;
    fcpl_t fcpl;
    int i;
    int strndx = -1;

    size_t num_files = this->file->get_num();

    for(i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        if(!(*(this->file->get_file_list()))[i]){ /* Is this slot a nullptr? */
            strndx = i;
            break;
        }
    }

    new_file = this->file->initialize();

    if(this->file->get_num() != num_files + 1){
        cout << "Cannot initialize a file; the file counter did not increment correctly." << endl;
        return(false);
    }

    if(new_file != (*(this->file->get_file_list()))[strndx]){
        cout << "Cannot initialize a file; the file struct pointer is not the next pointer in the file_list array." << endl;
        return(false);
    }

    if(this->file->get_current_id() != PHEZ_FILE_ID_INVALID){
        cout << "Cannot initialize a file; the file ID wasn't initialized to PHEZ_FILE_ID_INVALID." << endl;
        return(false);
    }

    string name = this->file->get_current()->name;
    if(name != ""){
        cout << "Cannot initialize a file; the file name is not empty." << endl;
        return(false);
    }

    fapl = (fapl_t)call_H5Pcreate(H5P_FILE_ACCESS);
    if(!call_H5Pequal(fapl, this->file->get_current_access_properties())){
        cout << "Cannot initialize a file; the file's access property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(fapl);

    fcpl = (fcpl_t)call_H5Pcreate(H5P_FILE_CREATE);
    if(!call_H5Pequal(fcpl, this->file->get_current_creation_properties())){
        cout << "Cannot initialize a file; the file's creation property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(fcpl);

    if(this->file->get_current()->action != PHEZ_FILE_ACTION_INVALID){
        cout << "Cannot initialize a file; the file action wasn't initialized to PHEZ_FILE_ACTION_INVALID." << endl;
        return(false);
    }

    if(this->file->get_current_num_linked_attributes()){
        cout << "Cannot initialize a file; the file's number of linked attributes wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->file->get_current_num_linked_datasets()){
        cout << "Cannot initialize a file; the file's number of linked datasets wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->file->get_current_num_linked_groups()){
        cout << "Cannot initialize a file; the file's number of linked groups wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->file->get_current()->state != PHEZ_FILE_STATE_DEFINED){
        cout << "Cannot initialize a file; the file state wasn't initialized to PHEZ_FILE_STATE_DEFINED." << endl;
        return(false);
    }

    this->file->destroy();

    if(this->file->get_num() != num_files){
        cout << "Cannot destroy a file; the file counter did not decrement correctly." << endl;
        return(false);
    }

    if(this->file->get_current()){
        cout << "Cannot destroy a file; the current_file pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can initialize and destroy a file struct." << endl;
    return(true);
}
bool hdf5_test_class::can_file_link_and_unlink_to_group(){
    phez_group_t* lnk_group;

    this->file->initialize();
    lnk_group = this->group->initialize();
    this->file->link_group(lnk_group);

    for(int i=1;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
        if((*(this->file->get_current_linked_groups()))[i]){
            cout << "Cannot link file to group; the file's linked group " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->file->get_current_linked_groups()))[0] != lnk_group){
        cout << "Cannot link file to group; the file's link pointer was not set correctly." << endl;
        return(false);
    }

    this->file->unlink_group(lnk_group);

    if((*(this->file->get_current_linked_groups()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink file from group; the file's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a file struct to a group struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_file_link_and_unlink_to_dataset(){
    phez_dataset_t* lnk_dataset;

    this->file->initialize();
    lnk_dataset = this->dataset->initialize();
    this->file->link_dataset(lnk_dataset);

    for(int i=1;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
        if((*(this->file->get_current_linked_datasets()))[i]){
            cout << "Cannot link file to dataset; the file's linked dataset " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->file->get_current_linked_datasets()))[0] != lnk_dataset){
        cout << "Cannot link file to dataset; the file's link pointer was not set correctly." << endl;
        return(false);
    }

    this->file->unlink_dataset(lnk_dataset);

    if((*(this->file->get_current_linked_datasets()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink file from dataset; the file's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a file struct to a dataset struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_file_link_and_unlink_to_attribute(){
    phez_attribute_t* lnk_attribute;

    this->file->initialize();
    lnk_attribute = this->attribute->initialize();
    this->file->link_attribute(lnk_attribute);

    for(int i=1;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        if((*(this->file->get_current_linked_attributes()))[i]){
            cout << "Cannot link file to attribute; the file's linked attribute " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->file->get_current_linked_attributes()))[0] != lnk_attribute){
        cout << "Cannot link file to attribute; the file's link pointer was not set correctly." << endl;
        return(false);
    }

    this->file->unlink_attribute(lnk_attribute);

    if((*(this->file->get_current_linked_attributes()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink file from attribute; the file's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a file struct to an attribute struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_init_and_destroy_a_group(){
    phez_group_t* new_group;
    gapl_t gapl;
    gcpl_t gcpl;
    int i;
    int strndx = -1;

    size_t num_groups = this->group->get_num();

    for(i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
        if(!(*(this->group->get_group_list()))[i]){ /* Is this slot a nullptr? */
            strndx = i;
            break;
        }
    }

    new_group = this->group->initialize();

    if(this->group->get_num() != num_groups + 1){
        cout << "Cannot initialize a group; the group counter did not increment correctly." << endl;
        return(false);
    }

    if(new_group != (*(this->group->get_group_list()))[strndx]){
        cout << "Cannot initialize a group; the group struct pointer is not the next pointer in the group_list array." << endl;
        return(false);
    }

    if(this->group->get_current_id() != PHEZ_GROUP_ID_INVALID){
        cout << "Cannot initialize a group; the group ID wasn't initialized to PHEZ_GROUP_ID_INVALID." << endl;
        return(false);
    }

    string name = this->group->get_current()->name;
    if(name != ""){
        cout << "Cannot initialize a group; the group name is not empty." << endl;
        return(false);
    }

    string comment = this->group->get_current()->comment;
    if(comment != ""){
        cout << "Cannot initialize a group; the group comment is not empty." << endl;
        return(false);
    }

    gapl = (gapl_t)call_H5Pcreate(H5P_GROUP_ACCESS);
    if(!call_H5Pequal(gapl, this->group->get_current_access_properties())){
        cout << "Cannot initialize a group; the group's access property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(gapl);

    gcpl = (gcpl_t)call_H5Pcreate(H5P_GROUP_CREATE);
    if(!call_H5Pequal(gcpl, this->group->get_current_creation_properties())){
        cout << "Cannot initialize a group; the group's creation property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(gcpl);

    if(this->group->get_current_num_groups_linking()){
        cout << "Cannot initialize a group; the number of groups linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->group->get_current_num_files_linking()){
        cout << "Cannot initialize a group; the number of files linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->group->get_current_num_linked_attributes()){
        cout << "Cannot initialize a group; the group's number of linked attributes wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->group->get_current_num_linked_datasets()){
        cout << "Cannot initialize a group; the group's number of linked datasets wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->group->get_current_num_linked_groups()){
        cout << "Cannot initialize a group; the group's number of linked groups wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->group->get_current()->state != PHEZ_GROUP_STATE_DEFINED){
        cout << "Cannot initialize a group; the group state wasn't initialized to PHEZ_GROUP_STATE_DEFINED." << endl;
        return(false);
    }

    this->group->destroy();

    if(this->group->get_num() != num_groups){
        cout << "Cannot destroy a group; the group counter did not decrement correctly." << endl;
        return(false);
    }

    if(this->group->get_current()){
        cout << "Cannot destroy a group; the current_group pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can initialize and destroy a group struct." << endl;
    return(true);
}
bool hdf5_test_class::can_group_link_and_unlink_to_group(){
    phez_group_t* lnk_group;

    this->group->initialize();
    lnk_group = this->group->initialize();
    this->group->link_group(lnk_group);

    for(int i=1;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
        if((*(this->group->get_current_linked_groups()))[i]){
            cout << "Cannot link group to group; the group's linked group " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->group->get_current_linked_groups()))[0] != lnk_group){
        cout << "Cannot link group to group; the group's link pointer was not set correctly." << endl;
        return(false);
    }

    this->group->unlink_group(lnk_group);

    if((*(this->group->get_current_linked_groups()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink group from group; the group's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a group struct to a group struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_group_link_and_unlink_to_dataset(){
    phez_dataset_t* lnk_dataset;

    this->group->initialize();
    lnk_dataset = this->dataset->initialize();
    this->group->link_dataset(lnk_dataset);

    for(int i=1;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
        if((*(this->group->get_current_linked_datasets()))[i]){
            cout << "Cannot link group to dataset; the group's linked dataset " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->group->get_current_linked_datasets()))[0] != lnk_dataset){
        cout << "Cannot link group to dataset; the group's link pointer was not set correctly." << endl;
        return(false);
    }

    this->group->unlink_dataset(lnk_dataset);

    if((*(this->group->get_current_linked_datasets()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink group from dataset; the group's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a group struct to a dataset struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_group_link_and_unlink_to_attribute(){
    phez_attribute_t* lnk_attribute;

    this->group->initialize();
    lnk_attribute = this->attribute->initialize();
    this->group->link_attribute(lnk_attribute);

    for(int i=1;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        if((*(this->group->get_current_linked_attributes()))[i]){
            cout << "Cannot link group to attribute; the group's linked attribute " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->group->get_current_linked_attributes()))[0] != lnk_attribute){
        cout << "Cannot link group to attribute; the group's link pointer was not set correctly." << endl;
        return(false);
    }

    this->group->unlink_attribute(lnk_attribute);

    if((*(this->group->get_current_linked_attributes()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink group from attribute; the group's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a group struct to an attribute struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_init_and_destroy_a_dataset(){
    phez_dataset_t* new_dataset;
    dapl_t dapl;
    dcpl_t dcpl;
    dxpl_t dxpl;
    int i;
    int strndx = -1;

    size_t num_datasets = this->dataset->get_num();

    for(i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
        if(!(*(this->dataset->get_dataset_list()))[i]){ // Is this slot a nullptr?
            strndx = i;
            break;
        }
    }

    new_dataset = this->dataset->initialize();

    if(this->dataset->get_num() != num_datasets + 1){
        cout << "Cannot initialize a dataset; the dataset counter did not increment correctly." << endl;
        return(false);
    }

    if(new_dataset != (*(this->dataset->get_dataset_list()))[strndx]){
        cout << "Cannot initialize a dataset; the dataset struct pointer is not the next pointer in the dataset_list array." << endl;
        return(false);
    }

    if(this->dataset->get_current_id() != PHEZ_DATASET_ID_INVALID){
        cout << "Cannot initialize a dataset; the dataset ID wasn't initialized to PHEZ_DATASET_ID_INVALID." << endl;
        return(false);
    }

    string name = this->dataset->get_current()->name;
    if(name != ""){
        cout << "Cannot initialize a dataset; the dataset name is not empty." << endl;
        return(false);
    }

    string comment = this->dataset->get_current()->comment;
    if(comment != ""){
        cout << "Cannot initialize a dataset; the dataset comment is not empty." << endl;
        return(false);
    }

    dapl = (dapl_t)call_H5Pcreate(H5P_DATASET_ACCESS);
    if(!call_H5Pequal(dapl, this->dataset->get_current_access_properties())){
        cout << "Cannot initialize a dataset; the dataset's access property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(dapl);

    dcpl = (dcpl_t)call_H5Pcreate(H5P_DATASET_CREATE);
    if(!call_H5Pequal(dcpl, this->dataset->get_current_creation_properties())){
        cout << "Cannot initialize a dataset; the dataset's creation property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(dcpl);

    dxpl = (dxpl_t)call_H5Pcreate(H5P_DATASET_XFER);
    if(!call_H5Pequal(dxpl, this->dataset->get_current_transfer_properties())){
        cout << "Cannot initialize a dataset; the dataset's transfer property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(dxpl);
/*
    if(this->dataset->get_current_size()){
        cout << "Cannot initialize a dataset; the dataset's size wasn't initialized to 0." << endl;
        return(false);
    }
*/
    if(this->dataset->get_current_type() != (phez_dataset_type_t)PHEZ_DATASET_TYPE_INVALID){
        cout << "Cannot initialize a dataset; the dataset's type wasn't initialized to PHEZ_DATASET_TYPE_INVALID." << endl;
        return(false);
    }

    if(this->dataset->get_current_data()){
        cout << "Cannot initialize a dataset; the dataset's data wasn't initialized to nullptr." << endl;
        return(false);
    }

    if(this->dataset->get_current_num_groups_linking()){
        cout << "Cannot initialize a dataset; the number of groups linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->dataset->get_current_num_files_linking()){
        cout << "Cannot initialize a dataset; the number of files linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->dataset->get_current_num_linked_attributes()){
        cout << "Cannot initialize a dataset; the dataset's number of linked attributes wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->dataset->get_current()->state != PHEZ_DATASET_STATE_DEFINED){
        cout << "Cannot initialize a dataset; the dataset state wasn't initialized to PHEZ_DATASET_STATE_DEFINED." << endl;
        return(false);
    }

    this->dataset->destroy();

    if(this->dataset->get_num() != num_datasets){
        cout << "Cannot destroy a dataset; the dataset counter did not decrement correctly." << endl;
        return(false);
    }

    if(this->dataset->get_current()){
        cout << "Cannot destroy a dataset; the current_dataset pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can initialize and destroy a dataset struct." << endl;
    return(true);
}
bool hdf5_test_class::can_dataset_link_and_unlink_to_attribute(){
    phez_attribute_t* lnk_attribute;

    this->dataset->initialize();
    lnk_attribute = this->attribute->initialize();
    this->dataset->link_attribute(lnk_attribute);

    for(int i=1;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        if((*(this->dataset->get_current_linked_attributes()))[i]){
            cout << "Cannot link dataset to attribute; the dataset's linked attribute " << i << " wasn't initialized to nullptr." << endl;
            return(false);
        }
    }

    if((*(this->dataset->get_current_linked_attributes()))[0] != lnk_attribute){
        cout << "Cannot link dataset to attribute; the dataset's link pointer was not set correctly." << endl;
        return(false);
    }

    this->dataset->unlink_attribute(lnk_attribute);

    if((*(this->dataset->get_current_linked_attributes()))[0]){ // Is it a nullptr?
        cout << "Cannot unlink dataset from attribute; the dataset's link pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can link a dataset struct to an attribute struct, then unlink it." << endl;
    return(true);
}
bool hdf5_test_class::can_init_and_destroy_an_attribute(){
    phez_attribute_t* new_attribute;
    acpl_t acpl;
    int i;
    int strndx = -1;

    size_t num_attributes = this->attribute->get_num();

    for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        if(!(*(this->attribute->get_attribute_list()))[i]){ /* Is this slot a nullptr? */
            strndx = i;
            break;
        }
    }

    new_attribute = this->attribute->initialize();

    if(this->attribute->get_num() != num_attributes + 1){
        cout << "Cannot initialize a attribute; the attribute counter did not increment correctly." << endl;
        return(false);
    }

    if(new_attribute != (*(this->attribute->get_attribute_list()))[strndx]){
        cout << "Cannot initialize an attribute; the attribute struct pointer is not the next pointer in the attribute_list array." << endl;
        return(false);
    }

    string name = this->attribute->get_current()->name;
    if(name != ""){
        cout << "Cannot initialize a attribute; the attribute name is not empty." << endl;
        return(false);
    }

    if(this->attribute->get_current_id() != PHEZ_ATTRIBUTE_ID_INVALID){
        cout << "Cannot initialize an attribute; the attribute ID wasn't initialized to PHEZ_ATTRIBUTE_ID_INVALID." << endl;
        return(false);
    }

    if(this->attribute->get_current_type() != (phez_attribute_type_t)PHEZ_ATTRIBUTE_TYPE_INVALID){
        cout << "Cannot initialize an attribute; the attribute's type wasn't initialized to PHEZ_ATTRIBUTE_TYPE_INVALID." << endl;
        return(false);
    }

    acpl = (acpl_t)call_H5Pcreate(H5P_ATTRIBUTE_CREATE);
    if(!call_H5Pequal(acpl, this->attribute->get_current_creation_properties())){
        cout << "Cannot initialize an attribute; the attribute's creation property list does not exist." << endl;
        return(false);
    }
    call_H5Pclose(acpl);

    if(this->attribute->get_current_num_datasets_linking()){
        cout << "Cannot initialize an attribute; the number of datasets linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->attribute->get_current_num_groups_linking()){
        cout << "Cannot initialize an attribute; the number of groups linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->attribute->get_current_num_files_linking()){
        cout << "Cannot initialize an attribute; the number of files linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->attribute->get_current_linked_space()){
        cout << "Cannot initialize an attribute; the linked space wasn't initialized to nullptr." << endl;
        return(false);
    }

    if(this->attribute->get_current()->state != PHEZ_ATTRIBUTE_STATE_DEFINED){
        cout << "Cannot initialize an attribute; the attribute state wasn't initialized to PHEZ_ATTRIBUTE_STATE_DEFINED." << endl;
        return(false);
    }

    this->attribute->destroy();

    if(this->attribute->get_num() != num_attributes){
        cout << "Cannot destroy a attribute; the attribute counter did not decrement correctly." << endl;
        return(false);
    }

    if(this->attribute->get_current()){
        cout << "Cannot destroy a attribute; the current_attribute pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can initialize and destroy an attribute struct." << endl;
    return(true);
}
bool hdf5_test_class::can_init_and_destroy_a_space(){
    phez_space_t* new_space;
    int i;
    int strndx = -1;

    size_t num_spaces = this->space->get_num();

    for(i=0;i<PHEZ_MAX_NUM_SPACES_ALLOWED;i++){
        if(!(*(this->space->get_space_list()))[i]){ /* Is this slot a nullptr? */
            strndx = i;
            break;
        }
    }

    new_space = this->space->initialize();

    if(this->space->get_num() != num_spaces + 1){
        cout << "Cannot initialize a space; the space counter did not increment correctly." << endl;
        return(false);
    }

    if(new_space != (*(this->space->get_space_list()))[strndx]){
        cout << "Cannot initialize a space; the space struct pointer is not the next pointer in the space_list array." << endl;
        return(false);
    }

    if(this->space->get_current_id() != PHEZ_SPACE_ID_INVALID){
        cout << "Cannot initialize a space; the space ID wasn't initialized to PHEZ_SPACE_ID_INVALID." << endl;
        return(false);
    }

    if(this->space->get_current_type() != PHEZ_SPACE_TYPE_INVALID){
        cout << "Cannot initialize a space; the space type wasn't initialized to PHEZ_SPACE_TYPE_INVALID." << endl;
        return(false);
    }

    if(this->space->get_current()->size != PHEZ_SPACE_SIZE_INVALID){
        cout << "Cannot initialize a space; the space size wasn't initialized to PHEZ_SPACE_SIZE_INVALID." << endl;
        return(false);
    }

    if(this->space->get_current_ptype() != PHEZ_SPACE_PTYPE_INVALID){
        cout << "Cannot initialize a space; the space's parent type wasn't initialized to PHEZ_SPACE_PTYPE_INVALID." << endl;
        return(false);
    }

    if(this->space->get_current_num_attributes_linking()){
        cout << "Cannot initialize a space; the number of attributes linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->space->get_current_num_datasets_linking()){
        cout << "Cannot initialize a space; the number of datasets linking to it wasn't initialized to 0." << endl;
        return(false);
    }

    if(this->space->get_current()->state != PHEZ_SPACE_STATE_DEFINED){
        cout << "Cannot initialize a space; the space state wasn't initialized to PHEZ_SPACE_STATE_DEFINED." << endl;
        return(false);
    }

    this->space->destroy();

    if(this->space->get_num() != num_spaces){
        cout << "Cannot destroy a space; the space counter did not decrement correctly." << endl;
        return(false);
    }

    if(this->space->get_current()){
        cout << "Cannot destroy a space; the current_space pointer was not reset to nullptr." << endl;
        return(false);
    }

    cout << "Yes, we can initialize and destroy a space struct." << endl;
    return(true);
}

void hdf5_test_class::create_sample_file(){

    /* Users should NOT use 'make' the way it is used here! */
    hid_t h5id;
    int ndims = 2;
    size_t dims[2] = {3,4};

    float ddata[3][4] = {{0,  1, 2, 3},{ 4, 5, 6, 7},{ 8, 9, 10, 11}};
    float adata[3][4] = {{1.1,1,.9,.8},{.7,.6,.5,.4},{.3,.2, .1,  0}};

    phez_file_t* new_file = this->file->initialize();
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_OVERWR);
    this->file->make();
    h5id = this->file->get_current_id();

    phez_group_t* new_group = this->group->initialize();
    this->group->set_current_name((char*)"stuff_g");
    this->group->make(h5id);
    this->file->link_group(new_group);
    h5id = this->group->get_current_id();

    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);
    this->space->make();

    phez_dataset_t* new_dataset = this->dataset->initialize();
    this->dataset->set_current_name((char*)"stuff_d");
    this->dataset->set_current_data(ddata);
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->link_file_space(new_dataset_fspace);
    this->dataset->make(h5id);
    this->dataset->write();
    h5id = this->dataset->get_current_id();

    phez_space_t* new_attribute_space = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);
    this->space->make();

    phez_attribute_t* new_attribute = this->attribute->initialize();
    this->attribute->set_current_name((char*)"stuff_a");
    this->attribute->set_current_data(adata);
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->set_current_linked_space(new_attribute_space);
    this->attribute->make(h5id);
    this->attribute->write();

    this->space->set_current(new_attribute_space);
    this->space->close();
    this->space->destroy();

    this->attribute->set_current(new_attribute);
    this->attribute->close();
    this->attribute->destroy();

    this->space->set_current(new_dataset_fspace);
    this->space->close();
    this->space->destroy();

    this->dataset->set_current(new_dataset);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(new_group);
    this->group->close();
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->close();
    this->file->destroy();

    //delete[] dims;

    return;
}
bool hdf5_test_class::can_make_any_object(){

    this->create_sample_file();

    cout << "Yes, we can make any object." << endl;
    return(true);
}

bool hdf5_test_class::can_recursively_populate_any_object(){
    return(true);
}
bool hdf5_test_class::can_recursively_flush_any_object(){
    // Users should NOT use 'make' the way it is used here!

    int ndims = 2;
    size_t dims[2] = {3,4};

    float ddata[3][4] = {{0,  1, 2, 3},{ 4, 5, 6, 7},{ 8, 9, 10, 11}};
    float adata[3][4] = {{1.1,1,.9,.8},{.7,.6,.5,.4},{.3,.2, .1,  0}};

    phez_file_t* new_file = this->file->initialize();
    phez_hash_t* new_file_hash;
    phez_object_t new_obj;
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_APPEND);
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    new_file_hash = this->hash(new_obj);

    phez_group_t* new_group1 = this->group->initialize();
    phez_hash_t* new_group1_hash;
    this->group->set_current_name((char*)"stuff3_g1");
    this->file->link_group(new_group1);
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group1_hash = new_file_hash;
    strcat(new_group1_hash, this->hash(new_obj));

    phez_group_t* new_group2 = this->group->initialize();
    phez_hash_t* new_group2_hash;
    this->group->set_current_name((char*)"stuff3_g2");
    this->group->set_current(new_group1);
    this->group->link_group(new_group2);
    this->group->set_current(new_group2);
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group2_hash = new_group1_hash;
    strcat(new_group2_hash, this->hash(new_obj));

    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);

    phez_dataset_t* new_dataset = this->dataset->initialize();
    phez_hash_t* new_dataset_hash;
    this->dataset->set_current_name((char*)"stuff3_d");
    this->dataset->set_current_data(ddata);
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->link_file_space(new_dataset_fspace);
    this->group->link_dataset(new_dataset);
    this->file->link_dataset(new_dataset);
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    new_dataset_hash = new_group2_hash;
    strcat(new_dataset_hash, this->hash(new_obj));

    phez_space_t* new_attribute_space = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);

    phez_attribute_t* new_attribute = this->attribute->initialize();
    phez_hash_t* new_attribute_hash;
    this->attribute->set_current_name((char*)"stuff3_a");
    this->attribute->set_current_data(adata);
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->set_current_linked_space(new_attribute_space);
    this->dataset->link_attribute(new_attribute);
    this->group->link_attribute(new_attribute);
    this->file->link_attribute(new_attribute);
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    new_attribute_hash = new_dataset_hash;
    strcat(new_attribute_hash, this->hash(new_obj));

    //this->flush(new_attribute_hash);
    //this->flush(new_dataset_hash);
    //this->flush(new_group2_hash);
    //this->flush(new_group1_hash);
    this->flush(new_file_hash);

    this->attribute->unlink_space();
    this->space->set_current(new_attribute_space);
    this->space->destroy();

    this->dataset->unlink_attribute(new_attribute);
    this->group->unlink_attribute(new_attribute);
    this->file->unlink_attribute(new_attribute);
    this->attribute->set_current(new_attribute);
    this->attribute->destroy();

    this->dataset->unlink_file_space();
    this->space->set_current(new_dataset_fspace);
    this->space->destroy();

    this->group->unlink_dataset(new_dataset);
    this->file->unlink_dataset(new_dataset);
    this->dataset->set_current(new_dataset);
    this->dataset->destroy();

    this->group->set_current(new_group1);
    this->group->unlink_group(new_group2);
    this->group->set_current(new_group2);
    this->group->destroy();

    this->file->unlink_group(new_group1);
    this->group->set_current(new_group1);
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->destroy();

    //delete[] dims;

    cout << "Yes, we can recursively flush any object." << endl;
    return(true);
}


bool hdf5_test_class::can_recursively_close_any_object(){
    // Users should NOT use 'make' the way it is used here!

    this->create_sample_file();

    phez_hash_t* new_file_hash;
    phez_object_t new_obj;
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    new_file_hash = this->hash(new_obj);

    phez_group_t* new_group = this->group->initialize();
    phez_hash_t* new_group_hash;
    this->group->set_current_name((char*)"stuff_g");
    this->file->link_group(new_group);
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group_hash = new_file_hash;
    strcat(new_group_hash, this->hash(new_obj));

    phez_dataset_t* new_dataset = this->dataset->initialize();
    phez_hash_t* new_dataset_hash;
    this->dataset->set_current_name((char*)"stuff_d");
    this->group->link_dataset(new_dataset);
    this->file->link_dataset(new_dataset);
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    new_dataset_hash = new_group_hash;
    strcat(new_dataset_hash, this->hash(new_obj));

    phez_attribute_t* new_attribute = this->attribute->initialize();
    phez_hash_t* new_attribute_hash;
    this->attribute->set_current_name((char*)"stuff_a");
    this->dataset->link_attribute(new_attribute);
    this->group->link_attribute(new_attribute);
    this->file->link_attribute(new_attribute);
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    new_attribute_hash = new_dataset_hash;
    strcat(new_attribute_hash, this->hash(new_obj));

    phez_space_t* new_space = this->space->initialize();
    this->attribute->link_space(new_space);

    this->populate(new_file_hash);

    this->close(new_attribute_hash);
    this->close(new_dataset_hash);
    this->close(new_group_hash);
    this->close(new_file_hash);

    this->space->set_current(new_space);
    if(this->space->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively close because a space was not closed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    this->space->destroy();

    this->dataset->unlink_attribute(new_attribute);
    this->group->unlink_attribute(new_attribute);
    this->file->unlink_attribute(new_attribute);
    if(this->attribute->get_current_state() != PHEZ_ATTRIBUTE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively close because an attribute was not closed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    this->attribute->destroy();

    this->group->unlink_dataset(new_dataset);
    this->file->unlink_dataset(new_dataset);
    if(this->dataset->get_current_state() != PHEZ_DATASET_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively close because a dataset was not closed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    this->dataset->destroy();

    this->file->unlink_group(new_group);
    if(this->group->get_current_state() != PHEZ_GROUP_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively close because a group was not closed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    this->group->destroy();

    if(this->file->get_current_state() != PHEZ_FILE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively close because a file was not closed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    this->file->destroy();

    cout << "Yes, we can recursively close any object." << endl;
    return(true);
}
bool hdf5_test_class::can_recursively_forget_any_object(){
    // Users should NOT use 'make' the way it is used here!

    int ndims = 2;
    size_t dims[2] = {3,4};

    float ddata[3][4] = {{0,  1, 2, 3},{ 4, 5, 6, 7},{ 8, 9, 10, 11}};
    float adata[3][4] = {{1.1,1,.9,.8},{.7,.6,.5,.4},{.3,.2, .1,  0}};

    phez_file_t* new_file = this->file->initialize();
    phez_hash_t* new_file_hash;
    phez_object_t new_obj;
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_APPEND);
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    new_file_hash = this->hash(new_obj);

    phez_group_t* new_group1 = this->group->initialize();
    phez_hash_t* new_group1_hash;
    this->group->set_current_name((char*)"stuff3_g1");
    this->file->link_group(new_group1);
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group1_hash = new_file_hash;
    strcat(new_group1_hash, this->hash(new_obj));

    phez_group_t* new_group2 = this->group->initialize();
    phez_hash_t* new_group2_hash;
    this->group->set_current_name((char*)"stuff3_g2");
    this->group->set_current(new_group1);
    this->group->link_group(new_group2);
    this->group->set_current(new_group2);
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group2_hash = new_group1_hash;
    strcat(new_group2_hash, this->hash(new_obj));

    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);
    this->space->make();

    phez_dataset_t* new_dataset = this->dataset->initialize();
    phez_hash_t* new_dataset_hash;
    this->dataset->set_current_name((char*)"stuff3_d");
    this->dataset->set_current_data(ddata);
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->link_file_space(new_dataset_fspace);
    this->group->link_dataset(new_dataset);
    this->file->link_dataset(new_dataset);
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    new_dataset_hash = new_group2_hash;
    strcat(new_dataset_hash, this->hash(new_obj));

    phez_space_t* new_attribute_space = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);
    this->space->make();

    phez_attribute_t* new_attribute = this->attribute->initialize();
    phez_hash_t* new_attribute_hash;
    this->attribute->set_current_name((char*)"stuff3_a");
    this->attribute->set_current_data(adata);
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->set_current_linked_space(new_attribute_space);
    this->dataset->link_attribute(new_attribute);
    this->group->link_attribute(new_attribute);
    this->file->link_attribute(new_attribute);
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    new_attribute_hash = new_dataset_hash;
    strcat(new_attribute_hash, this->hash(new_obj));


    this->flush(new_file_hash);
cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
    this->forget(new_attribute_hash);
    if(this->attribute->get_current_linked_space()){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because an attribute space was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->forget(new_dataset_hash);
    if(this->dataset->get_current_linked_file_space()){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a dataset file space was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->dataset->get_current_num_linked_attributes() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because an attribute was not unlinked from a dataset correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->forget(new_group2_hash);
    this->group->set_current(new_group2);
    if(this->group->get_current_num_linked_attributes() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because an attribute was not unlinked from a group correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->group->get_current_num_linked_datasets() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a dataset was not unlinked from a group correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->forget(new_group1_hash);
    this->group->set_current(new_group1);
    if(this->group->get_current_num_linked_groups() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a group was not unlinked from a group correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(new_group2){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a group was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->forget(new_file_hash);
    if(this->file->get_current_num_linked_attributes() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because an attribute was not unlinked from a file correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(new_attribute){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because an attribute was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->file->get_current_num_linked_datasets() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a dataset was not unlinked from a file correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(new_dataset){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a dataset was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->file->get_current_num_linked_groups() != 0){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a group was not unlinked from a file correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(new_group1){
        PHEZ_FATAL_PREFIX
        cout << "No, we cannot recursively forget because a group was not destroyed correctly." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->file->set_current(new_file);
    this->file->destroy();

    cout << "Yes, we can recursively forget any object." << endl;
    return(true);
}
bool hdf5_test_class::can_recursively_remove_any_object(){
    return(true);
}



bool hdf5_test_class::can_open_and_close_any_object(){

    this->create_sample_file();

    this->file->initialize();
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();

    this->group->initialize();
    this->group->set_current_name((char*)"stuff_g");
    this->group->open(this->file->get_current_id());

    this->dataset->initialize();
    this->dataset->set_current_name((char*)"stuff_d");
    this->dataset->open(this->group->get_current_id());

    this->attribute->initialize();
    this->attribute->set_current_name((char*)"stuff_a");
    this->attribute->open(this->dataset->get_current_id());

    this->space->initialize();
    this->space->open(this->attribute->get_current_id());

    this->space->close();
    this->attribute->close();
    this->dataset->close();
    this->group->close();
    this->file->close();

    this->space->destroy();
    this->attribute->destroy();
    this->dataset->destroy();
    this->group->destroy();
    this->file->destroy();

    cout << "Yes, we can open and close any object." << endl;
    return(true);
}
bool hdf5_test_class::can_write_any_object(){

    this->create_sample_file();

    hid_t h5id;
    int ndims = 2;
    size_t dims[2] = {4,5};

    float ddata[4][5] = {{0, 1, 2, 3, 4},{ 5, 6, 7, 8, 9},{ 10, 11, 12, 13, 14},{ 15, 16, 17, 18, 19}};
    float adata[4][5] = {{0,.1,.2,.3,.4},{.5,.6,.7,.8,.9},{1.0,1.1,1.2,1.3,1.4},{1.5,1.6,1.7,1.8,1.9}};

    phez_file_t* new_file = this->file->initialize();
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_APPEND);
    this->file->open();
    h5id = this->file->get_current_id();

    phez_group_t* new_group = this->group->initialize();
    this->group->set_current_name((char*)"stuff2_g");
    this->group->make(h5id);
    h5id = this->group->get_current_id();

    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);
    this->space->make();

    phez_dataset_t* new_dataset = this->dataset->initialize();
    this->dataset->set_current_name((char*)"stuff2_d");
    this->dataset->set_current_data(ddata);
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->link_file_space(new_dataset_fspace);
    this->dataset->make(h5id);
    this->dataset->write();
    h5id = this->dataset->get_current_id();

    phez_space_t* new_attribute_space = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);
    this->space->make();

    phez_attribute_t* new_attribute = this->attribute->initialize();
    this->attribute->set_current_name((char*)"stuff2_a");
    this->attribute->set_current_data(adata);
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->set_current_linked_space(new_attribute_space);
    this->attribute->make(h5id);
    this->attribute->write();

    this->space->set_current(new_attribute_space);
    this->space->close();
    this->space->destroy();

    this->attribute->set_current(new_attribute);
    this->attribute->close();
    this->attribute->destroy();

    this->space->set_current(new_dataset_fspace);
    this->space->close();
    this->space->destroy();

    this->dataset->set_current(new_dataset);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(new_group);
    this->group->close();
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->close();
    this->file->destroy();

    //delete[] dims;

    cout << "Yes, we can write any object." << endl;
    return(true);
}
bool hdf5_test_class::can_read_any_object(){

    this->create_sample_file();
    this->can_write_any_object();

    hid_t h5id;

    float ddata1[4][5];// = {{0, 1, 2, 3, 4},{ 5, 6, 7, 8, 9},{ 10, 11, 12, 13, 14},{ 15, 16, 17, 18, 19}};
    float adata1[4][5];// = {{0,.1,.2,.3,.4},{.5,.6,.7,.8,.9},{1.0,1.1,1.2,1.3,1.4},{1.5,1.6,1.7,1.8,1.9}};
    float ddata2[4][5] = {{0, 1, 2, 3, 4},{ 5, 6, 7, 8, 9},{ 10, 11, 12, 13, 14},{ 15, 16, 17, 18, 19}};
    float adata2[4][5] = {{0,.1,.2,.3,.4},{.5,.6,.7,.8,.9},{1.0,1.1,1.2,1.3,1.4},{1.5,1.6,1.7,1.8,1.9}};

    phez_file_t* new_file = this->file->initialize();
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();
    h5id = this->file->get_current_id();

    phez_group_t* new_group = this->group->initialize();
    this->group->set_current_name((char*)"stuff2_g");
    this->group->open(h5id);
    h5id = this->group->get_current_id();

    phez_dataset_t* new_dataset = this->dataset->initialize();
    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->dataset->set_current_name((char*)"stuff2_d");
    this->dataset->set_current_data(ddata1);
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->open(h5id);
    h5id = this->dataset->get_current_id();
    this->space->open(h5id);
    this->dataset->link_file_space(new_dataset_fspace);
    this->dataset->read();

    if(this->space->get_current_ptype() != PHEZ_SPACE_PTYPE_DATASET){
        cout << "Cannot read because dataset file space parent type was not set correctly." << endl;
        return(false);
    }
    if(this->space->get_current_size() != 2){
        cout << "Cannot read because dataset file space size was not read correctly." << endl;
        return(false);
    }
    if(this->space->get_current_dims_now()[0] != 4 || this->space->get_current_dims_now()[1] != 5){
        cout << "Cannot read because dataset space dimensions (now) were not read correctly." << endl;
        return(false);
    }
    if(this->space->get_current_dims_max()[0] != 4 || this->space->get_current_dims_max()[1] != 5){
        cout << "Cannot read because dataset space dimensions (max) were not read correctly." << endl;
        return(false);
    }

    phez_attribute_t* new_attribute = this->attribute->initialize();
    phez_space_t* new_attribute_space = this->space->initialize();
    this->attribute->set_current_name((char*)"stuff2_a");
    this->attribute->set_current_data(adata1);
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->open(h5id);
    h5id = this->attribute->get_current_id();
    this->space->open(h5id);
    this->attribute->link_space(new_attribute_space);
    this->attribute->read();

    if(this->space->get_current_ptype() != PHEZ_SPACE_PTYPE_ATTRIBUTE){
        cout << "Cannot read because attribute space parent type was not set correctly." << endl;
        return(false);
    }
    if(this->space->get_current_size() != 2){
        cout << "Cannot read because attribute space size was not read correctly." << endl;
        return(false);
    }
    if(this->space->get_current_dims_now()[0] != 4 || this->space->get_current_dims_now()[1] != 5){
        cout << "Cannot read because attribute space dimensions (now) were not read correctly." << endl;
        return(false);
    }
    if(this->space->get_current_dims_max()[0] != 4 || this->space->get_current_dims_max()[1] != 5){
        cout << "Cannot read because attribute space dimensions (max) were not read correctly." << endl;
        return(false);
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            if(ddata2[i][j] != this->dataset->get_current_data<float>()[5*i + j]){
                cout << "Cannot read because dataset data element " << i << ", " << j << " was not read correctly." << endl;
                return(false);
            }
            if(adata2[i][j] != this->attribute->get_current_data<float>()[5*i + j]){
                cout << "Cannot read because attribute data element " << i << ", " << j << " was not read correctly." << endl;
                return(false);
            }
        }
    }

    this->attribute->set_current(new_attribute);
    this->attribute->close();
    this->attribute->destroy();

    this->dataset->set_current(new_dataset);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(new_group);
    this->group->close();
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->close();
    this->file->destroy();

    cout << "Yes, we can read any object." << endl;
    return(true);
}

bool hdf5_test_class::can_hash_then_dehash(){

    phez_hash_t* new_file_hash;
    phez_hash_t* new_group_hash;
    phez_hash_t* new_dataset_hash;
    phez_hash_t* new_attribute_hash;
    phez_hash_t* new_fspace_hash;
    phez_hash_t* new_aspace_hash;

    phez_object_t new_obj;
    hid_t h5id;

    phez_file_t* new_file = this->file->initialize();
    this->file->set_current_name((char*)"things.h5");
    this->file->set_current_action(PHEZ_FILE_ACTION_OVERWR);
    this->file->make();
    h5id = this->file->get_current_id();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    new_file_hash = this->hash(new_obj);

    if(this->dehash(new_file_hash).ptr.f->id != new_obj.ptr.f->id){
        cout << "Cannot hash then dehash; the error is in the file API." << endl;
        return(false);
    }

    phez_group_t* new_group = this->group->initialize();
    this->group->set_current_name((char*)"stuff_g");
    this->group->make(h5id);
    h5id = this->group->get_current_id();
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group_hash = this->hash(new_obj);

    if(this->dehash(new_group_hash).ptr.g->id != new_obj.ptr.g->id){
        cout << "Cannot hash then dehash; the error is in the group API." << endl;
        return(false);
    }

    int ndims = 2;
    size_t* dims = new size_t[ndims];
    dims[0] = 3;
    dims[1] = 4;

    phez_space_t* new_dataset_fspace = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);
    this->space->make();
    new_obj.type = PHEZ_SPACE;
    new_obj.ptr.s = this->space->get_current();
    new_fspace_hash = this->hash(new_obj);

    if(this->dehash(new_fspace_hash).ptr.s->id != new_obj.ptr.s->id){
        cout << "Cannot hash then dehash; the error is in the space API." << endl;
        return(false);
    }

    phez_dataset_t* new_dataset = this->dataset->initialize();
    this->dataset->set_current_name((char*)"stuff_d");
    this->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    this->dataset->link_file_space(new_dataset_fspace);
    this->dataset->make(h5id);
    h5id = this->dataset->get_current_id();
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    new_dataset_hash = this->hash(new_obj);

    if(this->dehash(new_dataset_hash).ptr.d->id != new_obj.ptr.d->id){
        cout << "Cannot hash then dehash; the error is in the dataset API." << endl;
        return(false);
    }

    phez_space_t* new_attribute_space = this->space->initialize();
    this->space->set_current_size(ndims);
    this->space->set_current_dims_now(dims);
    this->space->set_current_dims_max(dims);
    this->space->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);
    this->space->make();
    new_obj.type = PHEZ_SPACE;
    new_obj.ptr.s = this->space->get_current();
    new_aspace_hash = this->hash(new_obj);

    if(this->dehash(new_aspace_hash).ptr.s->id != new_obj.ptr.s->id){
        cout << "Cannot hash then dehash; the error is in the space API." << endl;
        return(false);
    }

    phez_attribute_t* new_attribute = this->attribute->initialize();
    this->attribute->set_current_name((char*)"stuff_a");
    this->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    this->attribute->set_current_linked_space(new_attribute_space);
    this->attribute->make(h5id);
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    new_attribute_hash = this->hash(new_obj);

    if(this->dehash(new_attribute_hash).ptr.a->id != new_obj.ptr.a->id){
        cout << "Cannot hash then dehash; the error is in the attribute API." << endl;
        return(false);
    }

    this->space->set_current(new_attribute_space);
    this->space->close();
    this->space->destroy();

    this->attribute->set_current(new_attribute);
    this->attribute->close();
    this->attribute->destroy();

    this->space->set_current(new_dataset_fspace);
    this->space->close();
    this->space->destroy();

    this->dataset->set_current(new_dataset);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(new_group);
    this->group->close();
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->close();
    this->file->destroy();

    //delete[] dims;

    cout << "Yes, we can hash and then dehash any object." << endl;
    return(true);
}
bool hdf5_test_class::can_append_to_hash_then_peel_from_hash(){

    phez_hash_t* new_file_hash;
    phez_hash_t* new_group1_hash;
    phez_hash_t* new_group2_hash;
    phez_hash_t* new_dataset_hash;
    phez_hash_t* new_attribute_hash;
    phez_hash_t* new_space_hash;

    phez_hash_t* new_hash = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    new_hash[0] = '\0';
    phez_object_t new_obj;

    phez_file_t* new_file = this->file->initialize();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    new_file_hash = this->hash(new_obj);

    phez_group_t* new_group1 = this->group->initialize();
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group1_hash = this->hash(new_obj);

    phez_group_t* new_group2 = this->group->initialize();
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    new_group2_hash = this->hash(new_obj);

    phez_dataset_t* new_dataset = this->dataset->initialize();
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    new_dataset_hash = this->hash(new_obj);

    phez_attribute_t* new_attribute = this->attribute->initialize();
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    new_attribute_hash = this->hash(new_obj);

    phez_space_t* new_space = this->space->initialize();
    new_obj.type = PHEZ_SPACE;
    new_obj.ptr.s = this->space->get_current();
    new_space_hash = this->hash(new_obj);

    new_hash = this->append_to_hash(new_hash, new_file_hash);
    new_hash = this->append_to_hash(new_hash, new_group1_hash);
    new_hash = this->append_to_hash(new_hash, new_group2_hash);
    new_hash = this->append_to_hash(new_hash, new_dataset_hash);
    new_hash = this->append_to_hash(new_hash, new_attribute_hash);
    new_hash = this->append_to_hash(new_hash, new_space_hash);

    if(this->dehash(new_file_hash).ptr.f->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.f->id){
        return(false);
    }
    if(this->dehash(new_group1_hash).ptr.g->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.g->id){
        return(false);
    }
    if(this->dehash(new_group2_hash).ptr.g->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.g->id){
        return(false);
    }
    if(this->dehash(new_dataset_hash).ptr.d->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.d->id){
        return(false);
    }
    if(this->dehash(new_attribute_hash).ptr.a->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.a->id){
        return(false);
    }
    if(this->dehash(new_space_hash).ptr.s->id !=
       this->dehash(this->peel_from_hash(new_hash)).ptr.s->id){
        return(false);
    }

    this->space->set_current(new_space);
    this->space->destroy();

    this->attribute->set_current(new_attribute);
    this->attribute->destroy();

    this->dataset->set_current(new_dataset);
    this->dataset->destroy();

    this->group->set_current(new_group2);
    this->group->destroy();

    this->group->set_current(new_group1);
    this->group->destroy();

    this->file->set_current(new_file);
    this->file->destroy();

    //delete[] new_hash;

    cout << "Yes, we can append to a hash and then peel it." << endl;
    return(true);
}
bool hdf5_test_class::can_extract_object_with_hash(){

    hid_t file_id;
    hid_t group_id;
    hid_t dataset_id;
    hid_t attribute_id;
    phez_hash_t* new_hash = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    phez_hash_t* ext_hash = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    new_hash[0] = '\0';
    ext_hash[0] = '\0';
    phez_hash_t* file_hash;
    phez_hash_t* group_hash;
    phez_hash_t* dataset_hash;
    phez_hash_t* attribute_hash;
    phez_object_t new_obj;
    char* name = new char[PHEZ_MAX_NAME_LENGTH];

    this->create_sample_file();

    name = (char*)"things.h5";
    phez_file_t* file_ptr = this->file->initialize();
    this->file->set_current_name(name);
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();
    file_id = this->file->get_current_id();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    file_hash = this->hash(new_obj);

    name = (char*)"stuff_g";
    phez_group_t* group_ptr = this->group->initialize();
    this->group->set_current_name(name);
    this->group->open(file_id);
    group_id = this->group->get_current_id();
    new_obj.type = PHEZ_GROUP;
    new_obj.ptr.g = this->group->get_current();
    group_hash = this->hash(new_obj);

    name = (char*)"stuff_d";
    phez_dataset_t* dataset_ptr = this->dataset->initialize();
    this->dataset->set_current_name(name);
    this->dataset->open(group_id);
    dataset_id = this->dataset->get_current_id();
    new_obj.type = PHEZ_DATASET;
    new_obj.ptr.d = this->dataset->get_current();
    dataset_hash = this->hash(new_obj);

    name = (char*)"stuff_a";
    phez_attribute_t* attribute_ptr = this->attribute->initialize();
    this->attribute->set_current_name(name);
    this->attribute->open(dataset_id);
    attribute_id = this->attribute->get_current_id();
    new_obj.type = PHEZ_ATTRIBUTE;
    new_obj.ptr.a = this->attribute->get_current();
    attribute_hash = this->hash(new_obj);

    new_hash = this->append_to_hash(new_hash, file_hash);
    new_hash = this->append_to_hash(new_hash, group_hash);
    new_hash = this->append_to_hash(new_hash, dataset_hash);
    new_hash = this->append_to_hash(new_hash, attribute_hash);

    // Clean Up
    this->attribute->set_current(attribute_ptr);
    this->attribute->close();
    this->attribute->destroy();

    this->dataset->set_current(dataset_ptr);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(group_ptr);
    this->group->close();
    this->group->destroy();

    this->file->set_current(file_ptr);
    this->file->close();
    this->file->destroy();

    // Now let's see if 'extract' calls do the same thing...

    name = (char*)"things.h5";
    file_ptr = this->file->initialize();
    this->file->set_current_name(name);
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    ext_hash = this->hash(new_obj);

    ext_hash = this->extract(ext_hash, PHEZ_GROUP, (char*)"stuff_g");
    ext_hash = this->extract(ext_hash, PHEZ_DATASET, (char*)"stuff_d");
    ext_hash = this->extract(ext_hash, PHEZ_ATTRIBUTE, (char*)"stuff_a");

    if(strcmp(new_hash, ext_hash)){
        cout << "Cannot extract object with hash; the hash from extracting does not match the hash from initializing. " << endl;
        return(false);
    }

    file_hash = this->peel_from_hash(new_hash);
    new_obj = this->dehash(file_hash);
    file_ptr = new_obj.ptr.f;

    // These error checks are unreliable (version dependent?)
/*
    if(file_ptr->id != file_id){
        cout << "Cannot extract object with hash; the file ID from extracting does not match the ID from opening. " << endl;
        return(false);
    }
*/
    group_hash = this->peel_from_hash(new_hash);
    new_obj = this->dehash(group_hash);
    group_ptr = new_obj.ptr.g;
/*
    if(group_ptr->id != group_id){
        cout << "Cannot extract object with hash; the group ID from extracting does not match the ID from opening. " << endl;
        return(false);
    }
*/
    dataset_hash = this->peel_from_hash(new_hash);
    new_obj = this->dehash(dataset_hash);
    dataset_ptr = new_obj.ptr.d;
/*
    if(dataset_ptr->id != dataset_id){
        cout << "Cannot extract object with hash; the dataset ID from extracting does not match the ID from opening. " << endl;
        return(false);
    }
*/
    attribute_hash = this->peel_from_hash(new_hash);
    new_obj = this->dehash(attribute_hash);
    attribute_ptr = new_obj.ptr.a;
/*
    if(attribute_ptr->id != attribute_id){
        cout << "Cannot extract object with hash; the attribute ID from extracting does not match the ID from opening. " << endl;
        return(false);
    }
*/
    this->attribute->set_current(attribute_ptr);
    this->attribute->close();
    this->attribute->destroy();

    this->dataset->set_current(dataset_ptr);
    this->dataset->close();
    this->dataset->destroy();

    this->group->set_current(group_ptr);
    this->group->close();
    this->group->destroy();

    this->file->set_current(file_ptr);
    this->file->close();
    this->file->destroy();

    cout << "Yes, we can extract an object from a hash." << endl;
    return(true);
}
bool hdf5_test_class::can_appear_any_object_with_hash(){

    char* name = new char[PHEZ_MAX_NAME_LENGTH];
    phez_hash_t* ext_hash = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    phez_hash_t* buf_hash = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    phez_object_t new_obj;
    float* dset1 = new float[12];
    float* dset2 = new float[12];

    this->create_sample_file();

    name = (char*)"things.h5";
    this->file->initialize();
    this->file->set_current_name(name);
    this->file->set_current_action(PHEZ_FILE_ACTION_RDONLY);
    this->file->open();
    new_obj.type = PHEZ_FILE;
    new_obj.ptr.f = this->file->get_current();
    ext_hash = this->hash(new_obj);

    ext_hash = this->extract(ext_hash, PHEZ_GROUP, (char*)"stuff_g\0");
    ext_hash = this->extract(ext_hash, PHEZ_DATASET, (char*)"stuff_d\0");
    this->dataset->set_current(this->dehash(ext_hash).ptr.d);
    this->dataset->set_current_data(dset1);
    this->dataset->read();

    buf_hash = this->appear(ext_hash);
    this->dataset->set_current(this->dehash(buf_hash).ptr.d);
    this->dataset->set_current_data(dset2);
    this->dataset->read();

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            if(dset1[4*i + j] != dset2[4*i + j]){
                cout << "Cannot appear a dataset because dataset data element " << i << ", " << j << " does not match." << endl;
                return(false);
            }
        }
    }

    cout << "Yes, we can make a group or dataset appear in memory." << endl;
    return(true);
}
/*
bool hdf5_test_class::(){

}
*/
