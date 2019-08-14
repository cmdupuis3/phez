
#ifndef SET_PHEZ_TESTS_H_
#define SET_PHEZ_TESTS_H_

#include <string>
#include "phez_hdf5_t_api.hpp"

using std::string;

/** \class phez_context_t phez_context_t_api.h
 *  \brief The context is a version of the base clase for PHEZ I/O that includes unit tests
 *  \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
class hdf5_test_class : hdf5_class {
    public:
        hdf5_test_class(){

        }

        bool but_is_it_art();

        bool can_init_and_destroy_a_file();
        bool can_init_and_destroy_a_group();
        bool can_init_and_destroy_a_dataset();
        bool can_init_and_destroy_an_attribute();
        bool can_init_and_destroy_a_space();

        bool can_file_link_and_unlink_to_group();
        bool can_file_link_and_unlink_to_dataset();
        bool can_file_link_and_unlink_to_attribute();
        bool can_group_link_and_unlink_to_group();
        bool can_group_link_and_unlink_to_dataset();
        bool can_group_link_and_unlink_to_attribute();
        bool can_dataset_link_and_unlink_to_attribute();
        //bool can_dataset_link_and_unlink_to_spaces();
        //bool can_attribute_link_and_unlink_to_space();

        bool can_make_any_object();
        bool can_open_and_close_any_object();
        bool can_write_any_object();
        bool can_read_any_object();

        bool can_recursively_populate_any_object();
        bool can_recursively_flush_any_object();
        bool can_recursively_close_any_object();
        bool can_recursively_forget_any_object();
        bool can_recursively_remove_any_object();

        bool can_hash_then_dehash();
        bool can_append_to_hash_then_peel_from_hash();
        bool can_extract_object_with_hash();
        bool can_appear_any_object_with_hash();

        void create_sample_file(); // should be private

};

#endif
