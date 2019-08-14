#ifndef SET_PHEZ_CNAMES_H_
#define SET_PHEZ_CNAMES_H_

#include <cstdlib>
#include "phez_context_t_api.hpp"
#include "phez_types.hpp"
#include "phez_hdf5_t_api.hpp"
#include "phez_file_t_api.hpp"
#include "phez_group_t_api.hpp"
#include "phez_dataset_t_api.hpp"
#include "phez_attribute_t_api.hpp"
#include "phez_space_t_api.hpp"

/**************************** PHEZ notes **********************************

    This level serves to assign C names to C++ functions so they can be 
    bound to Fortran. PHEZ object IDs are used at this level to represent
    object pointers at the C++ API level; these IDs are basically strings
    used to represent the object and its ancestry (for existing files) or
    just the object by itself (for new files). This scheme enables us to
    check for and prevent recursive linking (which will create stack overflows
    in hdf5_class routines), as well as condense massive numbers into
    something more manageable.

***************************** PHEZ notes *********************************/




//extern "C" {

    phez_context_t* cwrap_phez_context_start();
    void cwrap_phez_context_stop(phez_context_t*);

    phez_test_context_t* cwrap_phez_test_context_start();
    void cwrap_phez_test_context_stop(phez_test_context_t*);

/******************** PHEZ convenience functions *************************/

    void cwrap_phez_populate(phez_context_t*, phez_hash_t*);
    void cwrap_phez_flush(phez_context_t*, phez_hash_t*); // Users should always call 'link' and 'flush' instead of 'make'
    void cwrap_phez_close(phez_context_t*, phez_hash_t*);
    void cwrap_phez_forget(phez_context_t*, phez_hash_t*);
    void cwrap_phez_remove(phez_context_t*, phez_hash_t*);

    void cwrap_phez_populate_all(phez_context_t*);
    void cwrap_phez_flush_all(phez_context_t*);
    void cwrap_phez_close_all(phez_context_t*);
    void cwrap_phez_forget_all(phez_context_t*);
    void cwrap_phez_remove_all(phez_context_t*);

    phez_hash_t* cwrap_phez_appear(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_extract(phez_context_t*, phez_hash_t*, phez_hdf5_otype_t, char*);
    
    /*void cwrap_phez_reduce_redundant();*/

/******************** PHEZ convenience functions *************************/

/************************ PHEZ file functions ****************************/

    /* Basic routines */
    phez_hash_t* cwrap_phez_file_initialize(phez_context_t*);
    void cwrap_phez_current_file_open(phez_context_t*);
    phez_hash_t* cwrap_phez_current_file_link_group(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_file_link_dataset(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_file_link_attribute(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_file_unlink_attribute(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_file_unlink_dataset(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_file_unlink_group(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_file_close(phez_context_t*);
    void cwrap_phez_current_file_destroy(phez_context_t*);

    /* Set/get basic info */
    phez_hash_t*            cwrap_phez_file_get_current(phez_context_t*);
    void                    cwrap_phez_file_set_current(phez_context_t*, phez_hash_t*);
    size_t                  cwrap_phez_file_get_num(phez_context_t*);
    char*                   cwrap_phez_current_file_get_name(phez_context_t*);
    void                    cwrap_phez_current_file_set_name(phez_context_t*, char*);
    phez_file_action_t       cwrap_phez_current_file_get_action(phez_context_t*);
    void                    cwrap_phez_current_file_set_action(phez_context_t*, phez_file_action_t);

    /* Defend ourselves from wandering property lists */
    void cwrap_phez_current_file_reset_access_properties(phez_context_t*);
    void cwrap_phez_current_file_default_access_properties(phez_context_t*);
    void cwrap_phez_current_file_access_from_memory(phez_context_t*, size_t, bool);
    void cwrap_phez_current_file_reset_creation_properties(phez_context_t*);
    void cwrap_phez_current_file_default_creation_properties(phez_context_t*);

    /* Outward links */
    size_t cwrap_phez_current_file_get_num_linked_attributes(phez_context_t*);
    size_t cwrap_phez_current_file_get_num_linked_datasets(phez_context_t*);
    size_t cwrap_phez_current_file_get_num_linked_groups(phez_context_t*);

/************************ PHEZ file functions ****************************/

/*********************** PHEZ group functions ****************************/

    /* Basic routines */
    phez_hash_t* cwrap_phez_group_initialize(phez_context_t*);
    phez_hash_t* cwrap_phez_current_group_open(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_group_link_group(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_group_link_dataset(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_group_link_attribute(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_group_unlink_attribute(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_group_unlink_dataset(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_group_unlink_group(phez_context_t*, phez_hash_t*);
    //void cwrap_phez_current_group_write();
    void cwrap_phez_current_group_close(phez_context_t*);
    void cwrap_phez_current_group_destroy(phez_context_t*);

    /* Set/get basic info */
    phez_hash_t*    cwrap_phez_group_get_current(phez_context_t*);
    void                    cwrap_phez_group_set_current(phez_context_t*, phez_hash_t*);
    size_t                  cwrap_phez_group_get_num(phez_context_t*);
    char*                   cwrap_phez_current_group_get_name(phez_context_t*);
    void                    cwrap_phez_current_group_set_name(phez_context_t*, char*);
    char*                   cwrap_phez_current_group_get_comment(phez_context_t*);
    void                    cwrap_phez_current_group_set_comment(phez_context_t*, char*);

    /* Defend ourselves from wandering property lists */
    void cwrap_phez_current_group_default_access_properties(phez_context_t*);
    void cwrap_phez_current_group_reset_creation_properties(phez_context_t*);
    void cwrap_phez_current_group_default_creation_properties(phez_context_t*);

    /* Inward links */
    size_t cwrap_phez_current_group_get_num_groups_linking(phez_context_t*);
    size_t cwrap_phez_current_group_get_num_files_linking(phez_context_t*);

    /* Outward links */
    size_t cwrap_phez_current_group_get_num_linked_attributes(phez_context_t*);
    size_t cwrap_phez_current_group_get_num_linked_datasets(phez_context_t*);
    size_t cwrap_phez_current_group_get_num_linked_groups(phez_context_t*);

/*********************** PHEZ group functions ****************************/



/********************** PHEZ dataset functions ***************************/

    /* Basic routines */
    phez_hash_t* cwrap_phez_dataset_initialize(phez_context_t*);
    phez_hash_t* cwrap_phez_current_dataset_open(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_dataset_read(phez_context_t*);
    phez_hash_t* cwrap_phez_current_dataset_link_attribute(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_dataset_link_file_space(phez_context_t*, phez_hash_t*);
    phez_hash_t* cwrap_phez_current_dataset_link_memory_space(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_dataset_unlink_memory_space(phez_context_t*);
    void cwrap_phez_current_dataset_unlink_file_space(phez_context_t*);
    void cwrap_phez_current_dataset_unlink_attribute(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_dataset_write(phez_context_t*);
    void cwrap_phez_current_dataset_close(phez_context_t*);
    void cwrap_phez_current_dataset_destroy(phez_context_t*);

    /* Set/get basic info */
    phez_hash_t*            cwrap_phez_dataset_get_current(phez_context_t*);
    void                    cwrap_phez_dataset_set_current(phez_context_t*, phez_hash_t*);
    size_t                  cwrap_phez_dataset_get_num(phez_context_t*);
    char*                   cwrap_phez_current_dataset_get_name(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_name(phez_context_t*, char*);
    char*                   cwrap_phez_current_dataset_get_comment(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_comment(phez_context_t*, char*);
    phez_dataset_type_t         cwrap_phez_current_dataset_get_type(phez_context_t*);  // clamped to certain H5T native macros

    bool*                   cwrap_phez_current_dataset_get_data_bool(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_data_bool(phez_context_t*, bool*);
    int*                    cwrap_phez_current_dataset_get_data_int(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_data_int(phez_context_t*, int*);
    float*                  cwrap_phez_current_dataset_get_data_float(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_data_float(phez_context_t*, float*);
    double*                 cwrap_phez_current_dataset_get_data_double(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_data_double(phez_context_t*, double*);
    char**                  cwrap_phez_current_dataset_get_data_string(phez_context_t*);
    void                    cwrap_phez_current_dataset_set_data_string(phez_context_t*, char**);

    /* Defend ourselves from wandering property lists */
    void cwrap_phez_current_dataset_reset_access_properties(phez_context_t*);
    void cwrap_phez_current_dataset_default_access_properties(phez_context_t*);
    void cwrap_phez_current_dataset_reset_creation_properties(phez_context_t*);
    void cwrap_phez_current_dataset_default_creation_properties(phez_context_t*);
    void cwrap_phez_current_dataset_default_transfer_properties(phez_context_t*);

    /* Inward links */
    size_t cwrap_phez_current_dataset_get_num_groups_linking(phez_context_t*);
    size_t cwrap_phez_current_dataset_get_num_files_linking(phez_context_t*);

    /* Outward links */
    size_t cwrap_phez_current_dataset_get_num_linked_attributes(phez_context_t*);
    phez_hash_t* cwrap_phez_current_dataset_get_linked_file_space(phez_context_t*);
    phez_hash_t* cwrap_phez_current_dataset_get_linked_memory_space(phez_context_t*);


/********************** PHEZ dataset functions ***************************/



/********************* PHEZ attribute functions **************************/

    /* Basic routines */
    phez_hash_t* cwrap_phez_attribute_initialize(phez_context_t*);
    phez_hash_t* cwrap_phez_current_attribute_open(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_attribute_read(phez_context_t*);
    phez_hash_t* cwrap_phez_current_attribute_link_space(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_attribute_unlink_space(phez_context_t*);
    void cwrap_phez_current_attribute_write(phez_context_t*);
    void cwrap_phez_current_attribute_close(phez_context_t*);
    void cwrap_phez_current_attribute_destroy(phez_context_t*);

    /* Set/get basic info */
    phez_hash_t*            cwrap_phez_attribute_get_current(phez_context_t*);
    void                    cwrap_phez_attribute_set_current(phez_context_t*, phez_hash_t*);
    size_t                  cwrap_phez_attribute_get_num(phez_context_t*);
    char*                   cwrap_phez_current_attribute_get_name(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_name(phez_context_t*, char*);
    phez_attribute_type_t         cwrap_phez_current_attribute_get_type(phez_context_t*); // clamped to certain H5T native macros

    bool*                   cwrap_phez_current_attribute_get_data_bool(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_data_bool(phez_context_t*, bool*);
    int*                    cwrap_phez_current_attribute_get_data_int(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_data_int(phez_context_t*, int*);
    float*                  cwrap_phez_current_attribute_get_data_float(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_data_float(phez_context_t*, float*);
    double*                 cwrap_phez_current_attribute_get_data_double(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_data_double(phez_context_t*, double*);
    char**                  cwrap_phez_current_attribute_get_data_string(phez_context_t*);
    void                    cwrap_phez_current_attribute_set_data_string(phez_context_t*, char**);

    /* Defend ourselves from wandering property lists */
    void cwrap_phez_current_attribute_reset_creation_properties(phez_context_t*);
    void cwrap_phez_current_attribute_default_creation_properties(phez_context_t*);
    /*void cwrap_phez_current_attribute_reset_access_properties(phez_context_t*);*/
    /*void cwrap_phez_current_attribute_default_access_properties(phez_context_t*);*/

    /* Inward links */
    size_t cwrap_phez_current_attribute_get_num_datasets_linking(phez_context_t*);
    size_t cwrap_phez_current_attribute_get_num_groups_linking(phez_context_t*);
    size_t cwrap_phez_current_attribute_get_num_files_linking(phez_context_t*);

    /* Outward links */
    phez_hash_t* cwrap_phez_current_attribute_get_linked_space(phez_context_t*);

/********************* PHEZ attribute functions **************************/



/*********************** PHEZ space functions ****************************/

    /* Basic routines */
    phez_hash_t* cwrap_phez_space_initialize(phez_context_t*);
    phez_hash_t* cwrap_phez_current_space_open(phez_context_t*, phez_hash_t*);
    void cwrap_phez_current_space_close(phez_context_t*);
    void cwrap_phez_current_space_destroy(phez_context_t*);

    /* Set/get basic info */
    phez_hash_t*            cwrap_phez_space_get_current(phez_context_t*);
    void                    cwrap_phez_space_set_current(phez_context_t*, phez_hash_t*);
    size_t                  cwrap_phez_space_get_num(phez_context_t*);
    phez_space_ptype_t        cwrap_phez_current_space_get_ptype(phez_context_t*);
    void                    cwrap_phez_current_space_set_ptype(phez_context_t*, phez_space_ptype_t);
    size_t                  cwrap_phez_current_space_get_size(phez_context_t*);
    void                    cwrap_phez_current_space_set_size(phez_context_t*, size_t);
    size_t*                 cwrap_phez_current_space_get_dims_now(phez_context_t*);
    void                    cwrap_phez_current_space_set_dims_now(phez_context_t*, size_t*);
    size_t*                 cwrap_phez_current_space_get_dims_max(phez_context_t*);
    void                    cwrap_phez_current_space_set_dims_max(phez_context_t*, size_t*);
    phez_space_type_t         cwrap_phez_current_space_get_type(phez_context_t*); // clamped to H5S_TYPE macros
    void                    cwrap_phez_current_space_set_type(phez_context_t*, phez_space_type_t);

    /* Selection operations (unused for now)*/
/*
    void cwrap_phez_current_space_select_all(phez_context_t*);
    void cwrap_phez_current_space_select_none(phez_context_t*);
    void cwrap_phez_current_space_select_inverse(phez_context_t*);
    void cwrap_phez_current_space_add_elements_to_selection(phez_context_t*, size_t, size_t*);
    void cwrap_phez_current_space_subtract_elements_from_selection(phez_context_t*, size_t, size_t*);
    void cwrap_phez_current_space_and_elements_with_selection(phez_context_t*, size_t, size_t*);
    void cwrap_phez_current_space_xor_elements_with_selection(phez_context_t*, size_t, size_t*);
    void cwrap_phez_current_space_add_hyperslabs_to_selection(phez_context_t*, size_t*, size_t*, size_t*, size_t*);
    void cwrap_phez_current_space_subtract_hyperslabs_from_selection(phez_context_t*, size_t*, size_t*, size_t*, size_t*);
    void cwrap_phez_current_space_and_hyperslabs_with_selection(phez_context_t*, size_t*, size_t*, size_t*, size_t*);
    void cwrap_phez_current_space_xor_hyperslabs_with_selection(phez_context_t*, size_t*, size_t*, size_t*, size_t*);
*/

    /* Inward links */
    size_t cwrap_phez_current_space_get_num_datasets_linking(phez_context_t*);
    size_t cwrap_phez_current_space_get_num_attributes_linking(phez_context_t*);

/*********************** PHEZ space functions ****************************/


/*********************** PHEZ unit tests ****************************/

    bool cwrap_phez_tests_but_is_it_art(phez_test_context_t*);

    bool cwrap_phez_tests_can_init_and_destroy_a_file(phez_test_context_t*);
    bool cwrap_phez_tests_can_init_and_destroy_a_group(phez_test_context_t*);
    bool cwrap_phez_tests_can_init_and_destroy_a_dataset(phez_test_context_t*);
    bool cwrap_phez_tests_can_init_and_destroy_an_attribute(phez_test_context_t*);
    bool cwrap_phez_tests_can_init_and_destroy_a_space(phez_test_context_t*);

    bool cwrap_phez_tests_can_file_link_and_unlink_to_group(phez_test_context_t*);
    bool cwrap_phez_tests_can_file_link_and_unlink_to_dataset(phez_test_context_t*);
    bool cwrap_phez_tests_can_file_link_and_unlink_to_attribute(phez_test_context_t*);
    bool cwrap_phez_tests_can_group_link_and_unlink_to_group(phez_test_context_t*);
    bool cwrap_phez_tests_can_group_link_and_unlink_to_dataset(phez_test_context_t*);
    bool cwrap_phez_tests_can_group_link_and_unlink_to_attribute(phez_test_context_t*);
    bool cwrap_phez_tests_can_dataset_link_and_unlink_to_attribute(phez_test_context_t*);

    bool cwrap_phez_tests_can_make_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_open_and_close_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_write_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_read_any_object(phez_test_context_t*);

    bool cwrap_phez_tests_can_recursively_populate_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_recursively_flush_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_recursively_close_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_recursively_forget_any_object(phez_test_context_t*);
    bool cwrap_phez_tests_can_recursively_remove_any_object(phez_test_context_t*);

    bool cwrap_phez_tests_can_hash_then_dehash(phez_test_context_t*);
    bool cwrap_phez_tests_can_append_to_hash_then_peel_from_hash(phez_test_context_t*);
    bool cwrap_phez_tests_can_extract_object_with_hash(phez_test_context_t*);
    bool cwrap_phez_tests_can_appear_any_object_with_hash(phez_test_context_t*);

/*********************** PHEZ unit tests ****************************/

/*********************** PHEZ internal functions ****************************/

    phez_hash_t* cwrap_phez_current_dataset_get_linked_file_space(phez_context_t*);
    phez_hash_t* cwrap_phez_current_dataset_get_linked_memory_space(phez_context_t*);
    phez_hash_t* cwrap_phez_current_attribute_get_linked_space(phez_context_t*);
    size_t cwrap_phez_internal_get_hash_digits(phez_context_t*);

    void cwrap_phez_internal_file_set_current_to_null(phez_context_t*);
    void cwrap_phez_internal_group_set_current_to_null(phez_context_t*);
    void cwrap_phez_internal_dataset_set_current_to_null(phez_context_t*);
    void cwrap_phez_internal_attribute_set_current_to_null(phez_context_t*);
    void cwrap_phez_internal_space_set_current_to_null(phez_context_t*);

/*********************** PHEZ internal functions ****************************/

//}

#endif
