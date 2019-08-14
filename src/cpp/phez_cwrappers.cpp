
#include "phez_cwrappers.hpp"

/********************** PHEZ context functions ***************************/

phez_context* phez_context_start(){
    return((phez_context*)cwrap_phez_context_start());
}
void phez_context_stop(phez_context* context){
    cwrap_phez_context_stop(context);
    return;
}

phez_test_context* phez_test_context_start(){
    return((phez_test_context*)cwrap_phez_test_context_start());
}
void phez_test_context_stop(phez_test_context* context){
    cwrap_phez_test_context_stop(context);
    return;
}

/******************** PHEZ convenience functions *************************/

/*
void phez_populate(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_populate(context, hash_in);
    return;
}
*/
void phez_flush(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_flush(context, hash_in);
    return;
}
/*
void phez_close(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_close(context, hash_in);
    return;
}
*/
/*
void phez_forget(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_forget(context, hash_in);
    return;
}
*/
/*
void phez_remove(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_remove(context, hash_in);
    return;
}
*/
/*
void phez_populate_all(phez_context* context){
    cwrap_phez_populate_all(context);
    return;
}
*/
void phez_flush_all(phez_context* context){
    cwrap_phez_flush_all(context);
    return;
}
/*
void phez_close_all(phez_context* context){
    cwrap_phez_close_all(context);
    return;
}
*/
/*
void phez_forget_all(phez_context* context){
    cwrap_phez_forget_all(context);
    return;
}
*/
/*
void phez_remove_all(phez_context* context){
    cwrap_phez_remove_all(context);
    return;
}
*/
phez_hash_t* phez_appear(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_appear(context, hash_in));
}
phez_hash_t* phez_extract(phez_context*     context,
                          phez_hash_t*          hash_in,
                          phez_hdf5_otype_t     type_in,
                          char*                 name_in){
    return(cwrap_phez_extract(context, hash_in, type_in, name_in));
}

/******************** PHEZ convenience functions *************************/



/************************ PHEZ file functions ****************************/

phez_hash_t* phez_file_initialize(phez_context* context){
    return(cwrap_phez_file_initialize(context));
}
void phez_current_file_open(phez_context* context){
    cwrap_phez_current_file_open(context);
    return;
}
phez_hash_t* phez_current_file_link_group(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_file_link_group(context, hash_in));
}
phez_hash_t* phez_current_file_link_dataset(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_file_link_dataset(context, hash_in));
}
phez_hash_t* phez_current_file_link_attribute(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_file_link_attribute(context, hash_in));
}
void phez_current_file_unlink_attribute(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_current_file_unlink_attribute(context, hash_in);
    return;
}
void phez_current_file_unlink_dataset(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_current_file_unlink_dataset(context, hash_in);
    return;
}
void phez_current_file_unlink_group(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_current_file_unlink_group(context, hash_in);
    return;
}
void phez_current_file_close(phez_context* context){
    cwrap_phez_current_file_close(context);
    return;
}
void phez_current_file_destroy(phez_context* context){
    cwrap_phez_current_file_destroy(context);
    return;
}
phez_hash_t* phez_file_get_current(phez_context* context){
    return(cwrap_phez_file_get_current(context));
}
void phez_file_set_current(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_file_set_current(context, hash_in);
    return;
}
size_t phez_file_get_num(phez_context* context){
    return(cwrap_phez_file_get_num(context));
}
char* phez_current_file_get_name(phez_context* context){
    return(cwrap_phez_current_file_get_name(context));
}
void phez_current_file_set_name(phez_context* context, char* name_in){
    cwrap_phez_current_file_set_name(context, name_in);
    return;
}
phez_file_action_t phez_current_file_get_action(phez_context* context){
    return(cwrap_phez_current_file_get_action(context));
}
void phez_current_file_set_action(phez_context* context, phez_file_action_t action_in){
    cwrap_phez_current_file_set_action(context, action_in);
    return;
}
void phez_current_file_reset_access_properties(phez_context* context){
    cwrap_phez_current_file_reset_access_properties(context);
    return;
}
void phez_current_file_default_access_properties(phez_context* context){
    cwrap_phez_current_file_default_access_properties(context);
    return;
}
void phez_current_file_access_from_memory(phez_context* context,
                                          size_t memory_increment_in,
                                          bool file_writes_to_disk_in){
    cwrap_phez_current_file_access_from_memory(context, memory_increment_in, file_writes_to_disk_in);
    return;
}
void phez_current_file_reset_creation_properties(phez_context* context){
    cwrap_phez_current_file_reset_creation_properties(context);
    return;
}
void phez_current_file_default_creation_properties(phez_context* context){
    cwrap_phez_current_file_default_creation_properties(context);
    return;
}
size_t phez_current_file_get_num_linked_attributes(phez_context* context){
    return(cwrap_phez_current_file_get_num_linked_attributes(context));
}
size_t phez_current_file_get_num_linked_datasets(phez_context* context){
    return(cwrap_phez_current_file_get_num_linked_datasets(context));
}
size_t phez_current_file_get_num_linked_groups(phez_context* context){
    return(cwrap_phez_current_file_get_num_linked_groups(context));
}

/************************ PHEZ file functions ****************************/



/*********************** PHEZ group functions ****************************/

phez_hash_t* phez_group_initialize(phez_context* context){
    return(cwrap_phez_group_initialize(context));
}
phez_hash_t* phez_current_group_open(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_group_open(context, hash_in));
}
phez_hash_t* phez_current_group_link_group(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_group_link_group(context, hash_in));
}
phez_hash_t* phez_current_group_link_dataset(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_group_link_dataset(context, hash_in));
}
phez_hash_t* phez_current_group_link_attribute(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_group_link_attribute(context, hash_in));
}
void phez_current_group_unlink_attribute(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_current_group_unlink_attribute(context, hash_in);
    return;
}
void phez_current_group_unlink_dataset(phez_context* context, phez_hash_t* hash_in){
    phez_current_group_unlink_dataset(context, hash_in);
    return;
}
void phez_current_group_unlink_group(phez_context* context, phez_hash_t* hash_in){
    phez_current_group_unlink_group(context, hash_in);
    return;
}
void phez_current_group_close(phez_context* context){
    cwrap_phez_current_group_close(context);
    return;
}
void phez_current_group_destroy(phez_context* context){
    cwrap_phez_current_group_destroy(context);
    return;
}
phez_hash_t* phez_group_get_current(phez_context* context){
    return(cwrap_phez_group_get_current(context));
}
void phez_group_set_current(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_group_set_current(context, hash_in);
    return;
}
size_t phez_group_get_num(phez_context* context){
    return(cwrap_phez_group_get_num(context));
}
char* phez_current_group_get_name(phez_context* context){
    return(cwrap_phez_current_group_get_name(context));
}
void phez_current_group_set_name(phez_context* context, char* name_in){
    cwrap_phez_current_group_set_name(context, name_in);
    return;
}
char* phez_current_group_get_comment(phez_context* context){
    return(cwrap_phez_current_group_get_comment(context));
}
void phez_current_group_set_comment(phez_context* context, char* name_in){
    cwrap_phez_current_group_set_comment(context, name_in);
    return;
}
/*
void phez_current_group_default_access_properties(phez_context* context){
    cwrap_phez_current_group_default_access_properties(context);
    return;
}
*/
void phez_current_group_reset_creation_properties(phez_context* context){
    cwrap_phez_current_group_reset_creation_properties(context);
    return;
}
void phez_current_group_default_creation_properties(phez_context* context){
    cwrap_phez_current_group_default_creation_properties(context);
    return;
}
size_t phez_current_group_get_num_groups_linking(phez_context* context){
    return(cwrap_phez_current_group_get_num_groups_linking(context));
}
size_t phez_current_group_get_num_files_linking(phez_context* context){
    return(cwrap_phez_current_group_get_num_files_linking(context));
}
size_t phez_current_group_get_num_linked_attributes(phez_context* context){
    return(cwrap_phez_current_group_get_num_linked_attributes(context));
}
size_t phez_current_group_get_num_linked_datasets(phez_context* context){
    return(cwrap_phez_current_group_get_num_linked_datasets(context));
}
size_t phez_current_group_get_num_linked_groups(phez_context* context){
    return(cwrap_phez_current_group_get_num_linked_groups(context));
}

/*********************** PHEZ group functions ****************************/



/********************** PHEZ dataset functions ***************************/


phez_hash_t* phez_dataset_initialize(phez_context* context){
    return(cwrap_phez_dataset_initialize(context));
}
phez_hash_t* phez_current_dataset_open(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_dataset_open(context, hash_in));
}
void phez_current_dataset_read(phez_context* context){
    cwrap_phez_current_dataset_read(context);
    return;
}
phez_hash_t* phez_current_dataset_link_attribute(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_dataset_link_attribute(context, hash_in));
}
phez_hash_t* phez_current_dataset_link_file_space(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_dataset_link_file_space(context, hash_in));
}
phez_hash_t* phez_current_dataset_link_memory_space(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_dataset_link_memory_space(context, hash_in));
}
void phez_current_dataset_unlink_memory_space(phez_context* context){
    cwrap_phez_current_dataset_unlink_memory_space(context);
    return;
}
void phez_current_dataset_unlink_file_space(phez_context* context){
    cwrap_phez_current_dataset_unlink_file_space(context);
    return;
}
void phez_current_dataset_unlink_attribute(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_current_dataset_unlink_attribute(context, hash_in);
    return;
}
void phez_current_dataset_write(phez_context* context){
    cwrap_phez_current_dataset_write(context);
    return;
}
void phez_current_dataset_close(phez_context* context){
    cwrap_phez_current_dataset_close(context);
    return;
}
void phez_current_dataset_destroy(phez_context* context){
    cwrap_phez_current_dataset_close(context);
    return;
}
phez_hash_t* phez_dataset_get_current(phez_context* context){
    return(cwrap_phez_dataset_get_current(context));
}
void phez_dataset_set_current(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_dataset_set_current(context, hash_in);
    return;
}
size_t phez_dataset_get_num(phez_context* context){
    return(cwrap_phez_dataset_get_num(context));
}
char* phez_current_dataset_get_name(phez_context* context){
    return(cwrap_phez_current_dataset_get_name(context));
}
void phez_current_dataset_set_name(phez_context* context, char* name_in){
    cwrap_phez_current_dataset_set_name(context, name_in);
    return;
}
char* phez_current_dataset_get_comment(phez_context* context){
    return(cwrap_phez_current_dataset_get_comment(context));
}
void phez_current_dataset_set_comment(phez_context* context, char* comment_in){
    cwrap_phez_current_dataset_set_comment(context, comment_in);
    return;
}
phez_dataset_type_t phez_current_dataset_get_type(phez_context* context){
    return(cwrap_phez_current_dataset_get_type(context));
}
bool* phez_current_dataset_get_data_bool(phez_context* context){
    return(cwrap_phez_current_dataset_get_data_bool(context));
}
void phez_current_dataset_set_data_bool(phez_context* context, bool* data_in){
    cwrap_phez_current_dataset_set_data_bool(context, data_in);
    return;
}
int* phez_current_dataset_get_data_int(phez_context* context){
    return(cwrap_phez_current_dataset_get_data_int(context));
}
void phez_current_dataset_set_data_int(phez_context* context, int* data_in){
    cwrap_phez_current_dataset_set_data_int(context, data_in);
    return;
}
float* phez_current_dataset_get_data_float(phez_context* context){
    return(cwrap_phez_current_dataset_get_data_float(context));
}
void phez_current_dataset_set_data_float(phez_context* context, float* data_in){
    cwrap_phez_current_dataset_set_data_float(context, data_in);
    return;
}
double* phez_current_dataset_get_data_double(phez_context* context){
    return(cwrap_phez_current_dataset_get_data_double(context));
}
void phez_current_dataset_set_data_double(phez_context* context, double* data_in){
    cwrap_phez_current_dataset_set_data_double(context, data_in);
    return;
}
/*
char** phez_current_dataset_get_data_string(phez_context* context){
    return(cwrap_phez_current_dataset_get_data_string(context));
}
*/
/*
void phez_current_dataset_set_data_string(phez_context* context, char** data_in){
    cwrap_phez_current_dataset_set_data_string(context, data_in);
    return;
}
*/
void phez_current_dataset_reset_access_properties(phez_context* context){
    cwrap_phez_current_dataset_reset_access_properties(context);
    return;
}
void phez_current_dataset_default_access_properties(phez_context* context){
    cwrap_phez_current_dataset_default_access_properties(context);
    return;
}
void phez_current_dataset_reset_creation_properties(phez_context* context){
    cwrap_phez_current_dataset_reset_creation_properties(context);
    return;
}
void phez_current_dataset_default_creation_properties(phez_context* context){
    cwrap_phez_current_dataset_default_creation_properties(context);
    return;
}
void phez_current_dataset_default_transfer_properties(phez_context* context){
    cwrap_phez_current_dataset_default_transfer_properties(context);
    return;
}
size_t phez_current_dataset_get_num_groups_linking(phez_context* context){
    return(cwrap_phez_current_dataset_get_num_groups_linking(context));
}
size_t phez_current_dataset_get_num_files_linking(phez_context* context){
    return(cwrap_phez_current_dataset_get_num_files_linking(context));
}
size_t phez_current_dataset_get_num_linked_attributes(phez_context* context){
    return(cwrap_phez_current_dataset_get_num_linked_attributes(context));
}

/********************** PHEZ dataset functions ***************************/



/********************* PHEZ attribute functions **************************/

phez_hash_t* phez_attribute_initialize(phez_context* context){
    return(cwrap_phez_attribute_initialize(context));
}
phez_hash_t* phez_current_attribute_open(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_attribute_open(context, hash_in));
}
void phez_current_attribute_read(phez_context* context){
    cwrap_phez_current_attribute_read(context);
    return;
}
phez_hash_t* phez_current_attribute_link_space(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_attribute_link_space(context, hash_in));
}
void phez_current_attribute_unlink_space(phez_context* context){
    cwrap_phez_current_attribute_unlink_space(context);
    return;
}
void phez_current_attribute_write(phez_context* context){
    cwrap_phez_current_attribute_write(context);
    return;
}
void phez_current_attribute_close(phez_context* context){
    cwrap_phez_current_attribute_close(context);
    return;
}
void phez_current_attribute_destroy(phez_context* context){
    cwrap_phez_current_attribute_destroy(context);
    return;
}
phez_hash_t* phez_attribute_get_current(phez_context* context){
    return(cwrap_phez_attribute_get_current(context));
}
void phez_attribute_set_current(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_attribute_set_current(context, hash_in);
    return;
}
size_t phez_attribute_get_num(phez_context* context){
    return(cwrap_phez_attribute_get_num(context));
}
char* phez_current_attribute_get_name(phez_context* context){
    return(cwrap_phez_current_attribute_get_name(context));
}
void phez_current_attribute_set_name(phez_context* context, char* name_in){
    cwrap_phez_current_attribute_set_name(context, name_in);
    return;
}
phez_attribute_type_t phez_current_attribute_get_type(phez_context* context){
    return(cwrap_phez_current_attribute_get_type(context));
}
bool* phez_current_attribute_get_data_bool(phez_context* context){
    return(cwrap_phez_current_attribute_get_data_bool(context));
}
void phez_current_attribute_set_data_bool(phez_context* context, bool* data_in){
    cwrap_phez_current_attribute_set_data_bool(context, data_in);
    return;
}
int* phez_current_attribute_get_data_int(phez_context* context){
    return(cwrap_phez_current_attribute_get_data_int(context));
}
void phez_current_attribute_set_data_int(phez_context* context, int* data_in){
    cwrap_phez_current_attribute_set_data_int(context, data_in);
    return;
}
float* phez_current_attribute_get_data_float(phez_context* context){
    return(cwrap_phez_current_attribute_get_data_float(context));
}
void phez_current_attribute_set_data_float(phez_context* context, float* data_in){
    cwrap_phez_current_attribute_set_data_float(context, data_in);
    return;
}
double* phez_current_attribute_get_data_double(phez_context* context){
    return(cwrap_phez_current_attribute_get_data_double(context));
}
void phez_current_attribute_set_data_double(phez_context* context, double* data_in){
    cwrap_phez_current_attribute_set_data_double(context, data_in);
    return;
}
char** phez_current_attribute_get_data_string(phez_context* context){
    return(cwrap_phez_current_attribute_get_data_string(context));
}
/*
void phez_current_attribute_set_data_string(phez_context* context, char** data_in){
    cwrap_phez_current_attribute_set_data_string(context, data_in);
    return;
}
*/

void phez_current_attribute_reset_creation_properties(phez_context* context){
    cwrap_phez_current_attribute_reset_creation_properties(context);
    return;
}
void phez_current_attribute_default_creation_properties(phez_context* context){
    cwrap_phez_current_attribute_default_creation_properties(context);
    return;
}
size_t phez_current_attribute_get_num_datasets_linking(phez_context* context){
    return(cwrap_phez_current_attribute_get_num_datasets_linking(context));
}
size_t phez_current_attribute_get_num_groups_linking(phez_context* context){
    return(cwrap_phez_current_attribute_get_num_groups_linking(context));
}
size_t phez_current_attribute_get_num_files_linking(phez_context* context){
    return(cwrap_phez_current_attribute_get_num_files_linking(context));
}

/********************* PHEZ attribute functions **************************/



/*********************** PHEZ space functions ****************************/

phez_hash_t* phez_space_initialize(phez_context* context){
    return(cwrap_phez_space_initialize(context));
}
phez_hash_t* phez_current_space_open(phez_context* context, phez_hash_t* hash_in){
    return(cwrap_phez_current_space_open(context, hash_in));
}
void phez_current_space_close(phez_context* context){
    cwrap_phez_current_space_close(context);
    return;
}
void phez_current_space_destroy(phez_context* context){
    cwrap_phez_current_space_destroy(context);
    return;
}
phez_hash_t* phez_space_get_current(phez_context* context){
    return(cwrap_phez_space_get_current(context));
}
void phez_space_set_current(phez_context* context, phez_hash_t* hash_in){
    cwrap_phez_space_set_current(context, hash_in);
    return;
}
size_t phez_space_get_num(phez_context* context){
    return(cwrap_phez_space_get_num(context));
}
size_t phez_current_space_get_size(phez_context* context){
    return(cwrap_phez_current_space_get_size(context));
}
void phez_current_space_set_size(phez_context* context, size_t size_in){
    cwrap_phez_current_space_set_size(context, size_in);
    return;
}
phez_space_ptype_t phez_current_space_get_ptype(phez_context* context){
    return(cwrap_phez_current_space_get_ptype(context));
}
void phez_current_space_set_ptype(phez_context* context, phez_space_ptype_t ptype_in){
    cwrap_phez_current_space_set_ptype(context, ptype_in);
    return;
}
size_t* phez_current_space_get_dims_now(phez_context* context){
    return(cwrap_phez_current_space_get_dims_now(context));
}
void phez_current_space_set_dims_now(phez_context* context, size_t* dims_now){
    cwrap_phez_current_space_set_dims_now(context, dims_now);
    return;
}
size_t* phez_current_space_get_dims_max(phez_context* context){
    return(cwrap_phez_current_space_get_dims_max(context));
}
void phez_current_space_set_dims_max(phez_context* context, size_t* dims_max){
    cwrap_phez_current_space_set_dims_max(context, dims_max);
    return;
}
phez_space_type_t phez_current_space_get_type(phez_context* context){
    return(cwrap_phez_current_space_get_type(context));
}
void phez_current_space_set_type(phez_context* context, phez_space_type_t type_in){
    cwrap_phez_current_space_set_type(context, type_in);
    return;
}
/*
void phez_current_space_select_all(phez_context* context){
    cwrap_phez_current_space_select_all(context);
    return;
}
void phez_current_space_select_none(phez_context* context){
    cwrap_phez_current_space_select_none(context);
    return;
}
void phez_current_space_select_inverse(phez_context* context){
    cwrap_phez_current_space_select_inverse(context);
    return;
}
void phez_current_space_add_elements_to_selection(phez_context* context,
                                                  size_t nelements_in,
                                                  size_t* coords_in){
    cwrap_phez_current_space_add_elements_to_selection(context, nelements_in, coords_in);
    return;
}
void phez_current_space_subtract_elements_from_selection(phez_context* context,
                                                         size_t nelements_in,
                                                         size_t* coords_in){
    cwrap_phez_current_space_subtract_elements_from_selection(context, nelements_in, coords_in);
    return;
}
void phez_current_space_and_elements_with_selection(phez_context* context,
                                                    size_t nelements_in,
                                                    size_t* coords_in){
    cwrap_phez_current_space_and_elements_with_selection(context, nelements_in, coords_in);
    return;
}
void phez_current_space_xor_elements_with_selection(phez_context* context,
                                                    size_t nelements_in,
                                                    size_t* coords_in){
    cwrap_phez_current_space_xor_elements_with_selection(context, nelements_in, coords_in);
    return;
}
void phez_current_space_add_hyperslabs_to_selection(phez_context* context,
                                                    size_t* start_in,
                                                    size_t* stride_in,
                                                    size_t* count_in,
                                                    size_t* block_in){
    cwrap_phez_current_space_add_hyperslabs_to_selection(context, start_in, stride_in, count_in, block_in);
    return;
}
void phez_current_space_subtract_hyperslabs_from_selection(phez_context* context,
                                                           size_t* start_in,
                                                           size_t* stride_in,
                                                           size_t* count_in,
                                                           size_t* block_in){
    cwrap_phez_current_space_subtract_hyperslabs_from_selection(context, start_in, stride_in, count_in, block_in);
    return;
}
void phez_current_space_and_hyperslabs_with_selection(phez_context* context,
                                                      size_t* start_in,
                                                      size_t* stride_in,
                                                      size_t* count_in,
                                                      size_t* block_in){
    cwrap_phez_current_space_and_hyperslabs_with_selection(context, start_in, stride_in, count_in, block_in);
    return;
}
void phez_current_space_xor_hyperslabs_with_selection(phez_context* context,
                                                      size_t* start_in,
                                                      size_t* stride_in,
                                                      size_t* count_in,
                                                      size_t* block_in){
    cwrap_phez_current_space_xor_hyperslabs_with_selection(context, start_in, stride_in, count_in, block_in);
    return;
}
*/

size_t phez_current_space_get_num_datasets_linking(phez_context* context){
    return(cwrap_phez_current_space_get_num_datasets_linking(context));
}
size_t phez_current_space_get_num_attributes_linking(phez_context* context){
    return(cwrap_phez_current_space_get_num_attributes_linking(context));
}

/*********************** PHEZ space functions ****************************/


/*********************** PHEZ unit tests ****************************/


bool phez_tests_but_is_it_art(phez_test_context* context){
    return(cwrap_phez_tests_but_is_it_art(context));
}
bool phez_tests_can_init_and_destroy_a_file(phez_test_context* context){
    return(cwrap_phez_tests_can_init_and_destroy_a_file(context));
}
bool phez_tests_can_init_and_destroy_a_group(phez_test_context* context){
    return(cwrap_phez_tests_can_init_and_destroy_a_group(context));
}
bool phez_tests_can_init_and_destroy_a_dataset(phez_test_context* context){
    return(cwrap_phez_tests_can_init_and_destroy_a_dataset(context));
}
bool phez_tests_can_init_and_destroy_an_attribute(phez_test_context* context){
    return(cwrap_phez_tests_can_init_and_destroy_an_attribute(context));
}
bool phez_tests_can_init_and_destroy_a_space(phez_test_context* context){
    return(cwrap_phez_tests_can_init_and_destroy_a_space(context));
}
bool phez_tests_can_file_link_and_unlink_to_group(phez_test_context* context){
    return(cwrap_phez_tests_can_file_link_and_unlink_to_group(context));
}
bool phez_tests_can_file_link_and_unlink_to_dataset(phez_test_context* context){
    return(cwrap_phez_tests_can_file_link_and_unlink_to_dataset(context));
}
bool phez_tests_can_file_link_and_unlink_to_attribute(phez_test_context* context){
    return(cwrap_phez_tests_can_file_link_and_unlink_to_attribute(context));
}
bool phez_tests_can_group_link_and_unlink_to_group(phez_test_context* context){
    return(cwrap_phez_tests_can_group_link_and_unlink_to_group(context));
}
bool phez_tests_can_group_link_and_unlink_to_dataset(phez_test_context* context){
    return(cwrap_phez_tests_can_group_link_and_unlink_to_dataset(context));
}
bool phez_tests_can_group_link_and_unlink_to_attribute(phez_test_context* context){
    return(cwrap_phez_tests_can_group_link_and_unlink_to_attribute(context));
}
bool phez_tests_can_dataset_link_and_unlink_to_attribute(phez_test_context* context){
    return(cwrap_phez_tests_can_dataset_link_and_unlink_to_attribute(context));
}
bool phez_tests_can_make_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_make_any_object(context));
}
bool phez_tests_can_open_and_close_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_open_and_close_any_object(context));
}
bool phez_tests_can_write_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_write_any_object(context));
}
bool phez_tests_can_read_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_read_any_object(context));
}
bool phez_tests_can_recursively_populate_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_recursively_populate_any_object(context));
}
bool phez_tests_can_recursively_flush_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_recursively_flush_any_object(context));
}
bool phez_tests_can_recursively_close_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_recursively_close_any_object(context));
}
bool phez_tests_can_recursively_forget_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_recursively_forget_any_object(context));
}
bool phez_tests_can_recursively_remove_any_object(phez_test_context* context){
    return(cwrap_phez_tests_can_recursively_remove_any_object(context));
}
bool phez_tests_can_hash_then_dehash(phez_test_context* context){
    return(cwrap_phez_tests_can_hash_then_dehash(context));
}
bool phez_tests_can_append_to_hash_then_peel_from_hash(phez_test_context* context){
    return(cwrap_phez_tests_can_append_to_hash_then_peel_from_hash(context));
}
bool phez_tests_can_extract_object_with_hash(phez_test_context* context){
    return(cwrap_phez_tests_can_extract_object_with_hash(context));
}
bool phez_tests_can_appear_any_object_with_hash(phez_test_context* context){
    return(cwrap_phez_tests_can_appear_any_object_with_hash(context));
}
