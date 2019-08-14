module phez_tests_f
    use phez_f
    use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr, c_bool
    implicit none

    private
    type phez_test_context                                         ! basic class type that simulates OOP
        private
        type(c_ptr) :: obj = c_null_ptr                             ! use obj as C/C++ "this" or Python "self". parameter for all functions
    end type phez_test_context

    interface
    ! bindings for all C functions in Fortran
        function C_phez_test_context_start() result(obj) &
        bind(C, name="phez_test_context_start")
            import
            type(c_ptr)          :: obj                             ! maps to type phez_test_context obj attribute
        end function C_phez_test_context_start

        subroutine C_phez_test_context_stop(obj) &
        bind(C, name="phez_test_context_stop")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
        end subroutine C_phez_test_context_stop

        function C_phez_tests_but_is_it_art(obj) result(success) &
        bind(C, name="phez_tests_but_is_it_art")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_but_is_it_art

        ! Works, but gives erroneous error messages.
        function C_phez_tests_can_init_and_destroy_a_file(obj) result(success) &
        bind(C, name="phez_tests_can_init_and_destroy_a_file")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_init_and_destroy_a_file

        ! Works, but gives erroneous error messages.
        function C_phez_tests_can_init_and_destroy_a_group(obj) result(success) &
        bind(C, name="phez_tests_can_init_and_destroy_a_group")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_init_and_destroy_a_group

        ! Works, but gives erroneous error messages.
        function C_phez_tests_can_init_and_destroy_a_dataset(obj) result(success) &
        bind(C, name="phez_tests_can_init_and_destroy_a_dataset")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_init_and_destroy_a_dataset

        ! Works, but gives erroneous error messages.
        function C_phez_tests_can_init_and_destroy_an_attribute(obj) result(success) &
        bind(C, name="phez_tests_can_init_and_destroy_an_attribute")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_init_and_destroy_an_attribute

        function C_phez_tests_can_init_and_destroy_a_space(obj) result(success) &
        bind(C, name="phez_tests_can_init_and_destroy_a_space")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_init_and_destroy_a_space

        function C_phez_tests_can_file_link_and_unlink_to_group(obj) result(success) &
        bind(C, name="phez_tests_can_file_link_and_unlink_to_group")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_file_link_and_unlink_to_group

        function C_phez_tests_can_file_link_and_unlink_to_dataset(obj) result(success) &
        bind(C, name="phez_tests_can_file_link_and_unlink_to_dataset")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_file_link_and_unlink_to_dataset

        function C_phez_tests_can_file_link_and_unlink_to_attribute(obj) result(success) &
        bind(C, name="phez_tests_can_file_link_and_unlink_to_attribute")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_file_link_and_unlink_to_attribute

        function C_phez_tests_can_group_link_and_unlink_to_group(obj) result(success) &
        bind(C, name="phez_tests_can_group_link_and_unlink_to_group")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_group_link_and_unlink_to_group

        function C_phez_tests_can_group_link_and_unlink_to_dataset(obj) result(success) &
        bind(C, name="phez_tests_can_group_link_and_unlink_to_dataset")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_group_link_and_unlink_to_dataset

        function C_phez_tests_can_group_link_and_unlink_to_attribute(obj) result(success) &
        bind(C, name="phez_tests_can_group_link_and_unlink_to_attribute")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_group_link_and_unlink_to_attribute

        function C_phez_tests_can_dataset_link_and_unlink_to_attribute(obj) result(success) &
        bind(C, name="phez_tests_can_dataset_link_and_unlink_to_attribute")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_dataset_link_and_unlink_to_attribute

        function C_phez_tests_can_make_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_make_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_make_any_object

        function C_phez_tests_can_open_and_close_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_open_and_close_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_open_and_close_any_object

        function C_phez_tests_can_write_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_write_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_write_any_object

        function C_phez_tests_can_read_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_read_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_read_any_object

        function C_phez_tests_can_recursively_flush_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_recursively_flush_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_recursively_flush_any_object

        function C_phez_tests_can_recursively_populate_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_recursively_populate_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_recursively_populate_any_object

        function C_phez_tests_can_recursively_close_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_recursively_close_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_recursively_close_any_object

        function C_phez_tests_can_recursively_forget_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_recursively_forget_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_recursively_forget_any_object

        function C_phez_tests_can_recursively_remove_any_object(obj) result(success) &
        bind(C, name="phez_tests_can_recursively_remove_any_object")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_recursively_remove_any_object

        function C_phez_tests_can_hash_then_dehash(obj) result(success) &
        bind(C, name="phez_tests_can_hash_then_dehash")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_hash_then_dehash

        function C_phez_tests_can_append_to_hash_then_peel_from_hash(obj) result(success) &
        bind(C, name="phez_tests_can_append_to_hash_then_peel_from_hash")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_append_to_hash_then_peel_from_hash

        function C_phez_tests_can_extract_object_with_hash(obj) result(success) &
        bind(C, name="phez_tests_can_extract_object_with_hash")
            import
            type(c_ptr), value          :: obj                             ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_extract_object_with_hash

        function C_phez_tests_can_appear_any_object_with_hash(obj) result(success) &
        bind(C, name="phez_tests_can_appear_any_object_with_hash")
            import
            type(c_ptr), value     :: obj                                  ! maps to type phez_test_context obj attribute
            logical(kind=c_bool) :: success
        end function C_phez_tests_can_appear_any_object_with_hash

    end interface

! interfaces to easily access wrapper functions and bound C functions without weird names and types
    interface phez_test_context_start
        module procedure fwrap_phez_test_context_start
    end interface phez_test_context_start

    interface phez_test_context_stop
        module procedure fwrap_phez_test_context_stop
    end interface phez_test_context_stop

    interface phez_tests_but_is_it_art
        module procedure fwrap_phez_tests_but_is_it_art
    end interface phez_tests_but_is_it_art

    interface phez_tests_can_init_and_destroy_a_file
        module procedure fwrap_phez_tests_can_init_and_destroy_a_file
    end interface phez_tests_can_init_and_destroy_a_file

    interface phez_tests_can_init_and_destroy_a_group
        module procedure fwrap_phez_tests_can_init_and_destroy_a_group
    end interface phez_tests_can_init_and_destroy_a_group

    interface phez_tests_can_init_and_destroy_a_dataset
        module procedure fwrap_phez_tests_can_init_and_destroy_a_dataset
    end interface phez_tests_can_init_and_destroy_a_dataset

    interface phez_tests_can_init_and_destroy_an_attribute
        module procedure fwrap_phez_tests_can_init_and_destroy_an_attribute
    end interface phez_tests_can_init_and_destroy_an_attribute

    interface phez_tests_can_init_and_destroy_a_space
        module procedure fwrap_phez_tests_can_init_and_destroy_a_space
    end interface phez_tests_can_init_and_destroy_a_space

    interface phez_tests_can_file_link_and_unlink_to_group
        module procedure fwrap_phez_tests_can_file_link_and_unlink_to_group
    end interface phez_tests_can_file_link_and_unlink_to_group

    interface phez_tests_can_file_link_and_unlink_to_dataset
        module procedure fwrap_phez_tests_can_file_link_and_unlink_to_dataset
    end interface phez_tests_can_file_link_and_unlink_to_dataset

    interface phez_tests_can_file_link_and_unlink_to_attribute
        module procedure fwrap_phez_tests_can_file_link_and_unlink_to_attribute
    end interface phez_tests_can_file_link_and_unlink_to_attribute

    interface phez_tests_can_group_link_and_unlink_to_group
        module procedure fwrap_phez_tests_can_group_link_and_unlink_to_group
    end interface phez_tests_can_group_link_and_unlink_to_group

    interface phez_tests_can_group_link_and_unlink_to_dataset
        module procedure fwrap_phez_tests_can_group_link_and_unlink_to_dataset
    end interface phez_tests_can_group_link_and_unlink_to_dataset

    interface phez_tests_can_group_link_and_unlink_to_attribute
        module procedure fwrap_phez_tests_can_group_link_and_unlink_to_attribute
    end interface phez_tests_can_group_link_and_unlink_to_attribute

    interface phez_tests_can_dataset_link_and_unlink_to_attribute
        module procedure fwrap_phez_tests_can_dataset_link_and_unlink_to_attribute
    end interface phez_tests_can_dataset_link_and_unlink_to_attribute

    interface phez_tests_can_make_any_object
        module procedure fwrap_phez_tests_can_make_any_object
    end interface phez_tests_can_make_any_object

    interface phez_tests_can_open_and_close_any_object
        module procedure fwrap_phez_tests_can_open_and_close_any_object
    end interface phez_tests_can_open_and_close_any_object

    interface phez_tests_can_write_any_object
        module procedure fwrap_phez_tests_can_write_any_object
    end interface phez_tests_can_write_any_object

    interface phez_tests_can_read_any_object
        module procedure fwrap_phez_tests_can_read_any_object
    end interface phez_tests_can_read_any_object

    interface phez_tests_can_recursively_populate_any_object
        module procedure fwrap_phez_tests_can_recursively_populate_any_object
    end interface phez_tests_can_recursively_populate_any_object

    interface phez_tests_can_recursively_flush_any_object
        module procedure fwrap_phez_tests_can_recursively_flush_any_object
    end interface phez_tests_can_recursively_flush_any_object

    interface phez_tests_can_recursively_close_any_object
        module procedure fwrap_phez_tests_can_recursively_close_any_object
    end interface phez_tests_can_recursively_close_any_object

    interface phez_tests_can_recursively_forget_any_object
        module procedure fwrap_phez_tests_can_recursively_forget_any_object
    end interface phez_tests_can_recursively_forget_any_object

    interface phez_tests_can_recursively_remove_any_object
        module procedure fwrap_phez_tests_can_recursively_remove_any_object
    end interface phez_tests_can_recursively_remove_any_object

    interface phez_tests_can_hash_then_dehash
        module procedure fwrap_phez_tests_can_hash_then_dehash
    end interface phez_tests_can_hash_then_dehash

    interface phez_tests_can_append_to_hash_then_peel_from_hash
        module procedure fwrap_phez_tests_can_append_to_hash_then_peel_from_hash
    end interface phez_tests_can_append_to_hash_then_peel_from_hash

    interface phez_tests_can_extract_object_with_hash
        module procedure fwrap_phez_tests_can_extract_object_with_hash
    end interface phez_tests_can_extract_object_with_hash

    interface phez_tests_can_appear_object_with_hash
        module procedure fwrap_phez_tests_can_appear_object_with_hash
    end interface phez_tests_can_appear_object_with_hash

    public ::   phez_test_context, &
                phez_test_context_start,  &
                phez_test_context_stop,  &
                phez_tests_but_is_it_art,  &
                phez_tests_can_init_and_destroy_a_file,  &
                phez_tests_can_init_and_destroy_a_group, &
                phez_tests_can_init_and_destroy_a_dataset, &
                phez_tests_can_init_and_destroy_an_attribute, &
                phez_tests_can_init_and_destroy_a_space,  &
                phez_tests_can_file_link_and_unlink_to_group, &
                phez_tests_can_file_link_and_unlink_to_dataset,  &
                phez_tests_can_file_link_and_unlink_to_attribute, &
                phez_tests_can_group_link_and_unlink_to_group,  &
                phez_tests_can_group_link_and_unlink_to_dataset, &
                phez_tests_can_group_link_and_unlink_to_attribute,  &
                phez_tests_can_dataset_link_and_unlink_to_attribute, &
                phez_tests_can_make_any_object,  &
                phez_tests_can_open_and_close_any_object,  &
                phez_tests_can_write_any_object,  &
                phez_tests_can_read_any_object, &
                phez_tests_can_recursively_populate_any_object,  &
                phez_tests_can_recursively_flush_any_object,  &
                phez_tests_can_recursively_close_any_object,  &
                phez_tests_can_recursively_forget_any_object,  &
                phez_tests_can_recursively_remove_any_object,  &
                phez_tests_can_hash_then_dehash,  &
                phez_tests_can_append_to_hash_then_peel_from_hash,  &
                phez_tests_can_extract_object_with_hash, &
                phez_tests_can_appear_object_with_hash, &
                phez_tests_can_pass_string_to_c_and_back, &
                phez_tests_can_pass_data_to_c_and_back

contains
! wrappers for type conversion from Fortran to C

    subroutine fwrap_phez_test_context_start(this)
        implicit none
        type(phez_test_context), intent(out) :: this
        this%obj = C_phez_test_context_start()
    end subroutine fwrap_phez_test_context_start

    subroutine fwrap_phez_test_context_stop(this)
        implicit none
        type(phez_test_context), intent(inout) :: this
        call C_phez_test_context_stop(this%obj)
        this%obj = c_null_ptr
    end subroutine fwrap_phez_test_context_stop

    function fwrap_phez_tests_but_is_it_art(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_but_is_it_art(this%obj)
    end function fwrap_phez_tests_but_is_it_art

    function fwrap_phez_tests_can_init_and_destroy_a_file(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_init_and_destroy_a_file(this%obj)
    end function fwrap_phez_tests_can_init_and_destroy_a_file

    function fwrap_phez_tests_can_init_and_destroy_a_group(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_init_and_destroy_a_group(this%obj)
    end function fwrap_phez_tests_can_init_and_destroy_a_group

    function fwrap_phez_tests_can_init_and_destroy_a_dataset(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_init_and_destroy_a_dataset(this%obj)
    end function fwrap_phez_tests_can_init_and_destroy_a_dataset

    function fwrap_phez_tests_can_init_and_destroy_an_attribute(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_init_and_destroy_an_attribute(this%obj)
    end function fwrap_phez_tests_can_init_and_destroy_an_attribute

    function fwrap_phez_tests_can_init_and_destroy_a_space(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_init_and_destroy_a_space(this%obj)
    end function fwrap_phez_tests_can_init_and_destroy_a_space

    function fwrap_phez_tests_can_file_link_and_unlink_to_group(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_file_link_and_unlink_to_group(this%obj)
    end function fwrap_phez_tests_can_file_link_and_unlink_to_group

    function fwrap_phez_tests_can_file_link_and_unlink_to_dataset(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_file_link_and_unlink_to_dataset(this%obj)
    end function fwrap_phez_tests_can_file_link_and_unlink_to_dataset

    function fwrap_phez_tests_can_file_link_and_unlink_to_attribute(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_file_link_and_unlink_to_attribute(this%obj)
    end function fwrap_phez_tests_can_file_link_and_unlink_to_attribute

    function fwrap_phez_tests_can_group_link_and_unlink_to_group(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_group_link_and_unlink_to_group(this%obj)
    end function fwrap_phez_tests_can_group_link_and_unlink_to_group

    function fwrap_phez_tests_can_group_link_and_unlink_to_dataset(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_group_link_and_unlink_to_dataset(this%obj)
    end function fwrap_phez_tests_can_group_link_and_unlink_to_dataset

    function fwrap_phez_tests_can_group_link_and_unlink_to_attribute(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_group_link_and_unlink_to_attribute(this%obj)
    end function fwrap_phez_tests_can_group_link_and_unlink_to_attribute

    function fwrap_phez_tests_can_dataset_link_and_unlink_to_attribute(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_dataset_link_and_unlink_to_attribute(this%obj)
    end function fwrap_phez_tests_can_dataset_link_and_unlink_to_attribute

    function fwrap_phez_tests_can_make_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_make_any_object(this%obj)
    end function fwrap_phez_tests_can_make_any_object

    function fwrap_phez_tests_can_open_and_close_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_open_and_close_any_object(this%obj)
    end function fwrap_phez_tests_can_open_and_close_any_object

    function fwrap_phez_tests_can_write_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_write_any_object(this%obj)
    end function fwrap_phez_tests_can_write_any_object

    function fwrap_phez_tests_can_read_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_read_any_object(this%obj)
    end function fwrap_phez_tests_can_read_any_object

    function fwrap_phez_tests_can_recursively_populate_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_recursively_populate_any_object(this%obj)
    end function fwrap_phez_tests_can_recursively_populate_any_object

    function fwrap_phez_tests_can_recursively_flush_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_recursively_flush_any_object(this%obj)
    end function fwrap_phez_tests_can_recursively_flush_any_object

    function fwrap_phez_tests_can_recursively_close_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_recursively_close_any_object(this%obj)
    end function fwrap_phez_tests_can_recursively_close_any_object

    function fwrap_phez_tests_can_recursively_forget_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_recursively_forget_any_object(this%obj)
    end function fwrap_phez_tests_can_recursively_forget_any_object

    function fwrap_phez_tests_can_recursively_remove_any_object(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_recursively_remove_any_object(this%obj)
    end function fwrap_phez_tests_can_recursively_remove_any_object

    function fwrap_phez_tests_can_hash_then_dehash(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_hash_then_dehash(this%obj)
    end function fwrap_phez_tests_can_hash_then_dehash

    function fwrap_phez_tests_can_append_to_hash_then_peel_from_hash(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_append_to_hash_then_peel_from_hash(this%obj)
    end function fwrap_phez_tests_can_append_to_hash_then_peel_from_hash

    function fwrap_phez_tests_can_extract_object_with_hash(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_extract_object_with_hash(this%obj)
    end function fwrap_phez_tests_can_extract_object_with_hash

    function fwrap_phez_tests_can_appear_object_with_hash(this) result(success)
        implicit none
        type(phez_test_context), intent(in) :: this
        logical                              :: success
        success = C_phez_tests_can_appear_any_object_with_hash(this%obj)
    end function fwrap_phez_tests_can_appear_object_with_hash

    function phez_tests_can_pass_string_to_c_and_back(this) result(success)
        implicit none
        type(phez_context), intent(in) :: this
        logical                      :: success
        character(len=:),allocatable :: fhash, ghash, dhash, ahash
        character(len=:),allocatable :: fname_in, gname_in, dname_in, aname_in
        character(len=:),allocatable :: fname_out, gname_out, dname_out, aname_out
        character(len=:),allocatable :: gcomment_in, dcomment_in
        character(len=:),allocatable :: gcomment_out, dcomment_out

        fname_in = "filename"
        gname_in = "groupname"
        gcomment_in = "groupcomment"
        dname_in = "dataname"
        dcomment_in = "datacomment"
        aname_in = "attrname"

        fhash = phez_file_initialize(this)
        ghash = phez_group_initialize(this)
        dhash = phez_dataset_initialize(this)
        ahash = phez_attribute_initialize(this)

        call phez_current_file_set_name(this, fname_in)
        fname_out = phez_current_file_get_name(this)
        if(fname_in .ne. fname_out) then
            print *, "Cannot pass a file name to C and back."
            return
        endif

        call phez_current_group_set_name(this, gname_in)
        gname_out = phez_current_group_get_name(this)
        if(gname_in .ne. gname_out) then
            print *,  "Cannot pass a group name to C and back."
            return
        endif

        call phez_current_dataset_set_name(this, dname_in)
        dname_out = phez_current_dataset_get_name(this)
        if(dname_in .ne. dname_out) then
            print *,  "Cannot pass a dataset name to C and back."
            return
        endif

        call phez_current_attribute_set_name(this, aname_in)
        aname_out = phez_current_attribute_get_name(this)
        if(aname_in .ne. aname_out) then
            print *,  "Cannot pass an attribute name to C and back."
            return
        endif

        call phez_current_group_set_comment(this, gcomment_in)
        gcomment_out = phez_current_group_get_comment(this)
        if(gcomment_in .ne. gcomment_out) then
            print *,  "Cannot pass a group comment to C and back."
            return
        endif

        call phez_current_dataset_set_comment(this, dcomment_in)
        dcomment_out = phez_current_dataset_get_comment(this)
        if(dcomment_in .ne. dcomment_out) then
            print *,  "Cannot pass a dataset comment to C and back."
            return
        endif

        print *, "Yes, names and comments can be passed from Fortran to C and back."

    end function phez_tests_can_pass_string_to_c_and_back

    function phez_tests_can_pass_data_to_c_and_back(this) result(success)
        implicit none
        type(phez_context), intent(in)       :: this
        logical                                 :: success
        character                               :: fstring
        real,allocatable                        :: adata(:,:)
        real,allocatable                        :: ddata(:,:)
        real                                    :: acheck(3,4)
        real                                    :: dcheck(3,4)
        integer :: i,j

        character(len=:),allocatable :: fhash, ghash, dhash, ahash
        character(len=:),allocatable :: fname, gname, dname, aname
        character(len=:),allocatable :: phash
        integer                      :: f_action, gtype, dtype, atype

        !acheck = (/ (/  /)



        fname = "things.h5"
        gname = "stuff_g"
        dname = "stuff_d"
        aname = "stuff_a"
        gtype = 14
        dtype = 13
        atype = 12

        f_action = 500

        fhash = phez_file_initialize(this)
        call phez_current_file_set_name(this, fname)
        call phez_current_file_set_action(this, f_action)
        call phez_current_file_open(this)

        ghash = phez_extract(this, trim(fhash), gtype, gname)
        dhash = phez_extract(this, trim(ghash), dtype, dname)
        ahash = phez_extract(this, trim(dhash), atype, aname)

        !call phez_current_attribute_set_data(this, adata)
        call phez_current_attribute_read(this)
        call phez_current_attribute_get_data(this, adata)

        do i = 1,3
            do j = 1,4
                print *, NINT(adata(i,j)*10), NINT(acheck(i,j)*10)
                !if(NINT(adata(i,j)*10) .ne. NINT(acheck(i,j)*10)) then
                !    print *,  "Cannot pass an array from C to Fortran."
                !    return
                !end if
            end do
        end do

        allocate(ddata(3,4))
        call phez_current_dataset_set_data(this, ddata)
        call phez_current_dataset_read(this)
        call phez_current_dataset_get_data(this, ddata)

        do i = 1,3
            do j = 1,4
                if(NINT(ddata(i,j)*10) .ne. NINT(dcheck(i,j)*10)) then
                    print *,  "Cannot pass an array from Fortran to C and back."
                    return
                end if
            end do
        end do

    end function phez_tests_can_pass_data_to_c_and_back


end module phez_tests_f
