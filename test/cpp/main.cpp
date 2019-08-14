
#include <cstdlib>
#include <string>
#include <cstring>
#include <hdf5.h>

#include "../src/phez_cwrappers.hpp"


int main(){

    phez_test_context* handle;
    handle = phez_test_context_start();

    phez_tests_but_is_it_art(handle);

    phez_tests_can_init_and_destroy_a_file(handle);
    phez_tests_can_init_and_destroy_a_group(handle);
    phez_tests_can_init_and_destroy_a_dataset(handle);
    phez_tests_can_init_and_destroy_an_attribute(handle);
    phez_tests_can_init_and_destroy_a_space(handle);

    phez_tests_can_file_link_and_unlink_to_group(handle);
    phez_tests_can_file_link_and_unlink_to_dataset(handle);
    phez_tests_can_file_link_and_unlink_to_attribute(handle);
    phez_tests_can_group_link_and_unlink_to_group(handle);
    phez_tests_can_group_link_and_unlink_to_dataset(handle);
    phez_tests_can_group_link_and_unlink_to_attribute(handle);
    phez_tests_can_dataset_link_and_unlink_to_attribute(handle);

    phez_tests_can_make_any_object(handle);
    phez_tests_can_open_and_close_any_object(handle);
    phez_tests_can_write_any_object(handle);
    phez_tests_can_read_any_object(handle);

    //phez_tests_can_recursively_populate_any_object(handle);
    phez_tests_can_recursively_flush_any_object(handle);
    //phez_tests_can_recursively_close_any_object(handle);
    //phez_tests_can_recursively_forget_any_object(handle);
    //phez_tests_can_recursively_remove_any_object(handle);

    phez_tests_can_hash_then_dehash(handle);
    phez_tests_can_append_to_hash_then_peel_from_hash(handle);
    phez_tests_can_extract_object_with_hash(handle);
    phez_tests_can_appear_any_object_with_hash(handle);

    phez_test_context_stop(handle);

    return(0);
}
