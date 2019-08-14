
program phez_main_f

    use phez_f
    use phez_tests_f

    logical :: check
    type(phez_test_context) :: test_handle
    type(phez_context) :: handle

    call phez_test_context_start(test_handle)
    !check = phez_tests_but_is_it_art(test_handle)
    !check = phez_tests_can_init_and_destroy_a_file(test_handle)
    !check = phez_tests_can_init_and_destroy_a_group(test_handle)
    !check = phez_tests_can_init_and_destroy_a_dataset(test_handle)
    !check = phez_tests_can_init_and_destroy_an_attribute(test_handle)
    !check = phez_tests_can_init_and_destroy_a_space(test_handle)
    !check = phez_tests_can_file_link_and_unlink_to_group(test_handle)
    !check = phez_tests_can_file_link_and_unlink_to_dataset(test_handle)
    !check = phez_tests_can_file_link_and_unlink_to_attribute(test_handle)
    !check = phez_tests_can_group_link_and_unlink_to_group(test_handle)
    !check = phez_tests_can_group_link_and_unlink_to_dataset(test_handle)
    !check = phez_tests_can_group_link_and_unlink_to_attribute(test_handle)
    !check = phez_tests_can_dataset_link_and_unlink_to_attribute(test_handle)
    !check = phez_tests_can_make_any_object(test_handle)
    !check = phez_tests_can_open_and_close_any_object(test_handle)
    !check = phez_tests_can_write_any_object(test_handle)
    check = phez_tests_can_read_any_object(test_handle)
    !check = phez_tests_can_recursively_populate_any_object(test_handle)
    !check = phez_tests_can_recursively_flush_any_object(test_handle)
    !check = phez_tests_can_recursively_close_any_object(test_handle)
    !check = phez_tests_can_recursively_forget_any_object(test_handle)
    !check = phez_tests_can_recursively_remove_any_object(test_handle)
    !check = phez_tests_can_hash_then_dehash(test_handle)
    !check = phez_tests_can_append_to_hash_then_peel_from_hash(test_handle)
    !check = phez_tests_can_extract_object_with_hash(test_handle)
    !check = phez_tests_can_appear_object_with_hash(test_handle)
    call phez_test_context_stop(test_handle)

    call phez_context_start(handle)
    check = phez_tests_can_pass_string_to_c_and_back(handle)
    check = phez_tests_can_pass_data_to_c_and_back(handle)
    call phez_context_stop(handle)

end program phez_main_f
