module phez_f
    use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr, c_loc, c_f_pointer
    use, intrinsic :: iso_c_binding, only: c_bool, c_int, c_size_t, c_float, c_double
    use, intrinsic :: iso_c_binding, only: c_char, c_null_char, c_associated
    implicit none

    private
    type phez_context                                         ! basic class type that simulates OOP
        private
        type(c_ptr) :: obj = c_null_ptr                             ! use obj as C/C++ "this" or Python "self". parameter for all functions
    end type phez_context

    type phez_hash
        private
        character(len=1, kind=c_char) :: hash
    end type phez_hash

    type phez_hdf5_otype
        private
        integer :: otype
    end type phez_hdf5_otype

    type phez_h5f_action
        private
        integer :: action
    end type phez_h5f_action

    type phez_h5d_type
        private
        integer :: dtype
    end type phez_h5d_type

    type phez_h5a_type
        private
        integer :: atype
    end type phez_h5a_type

    type phez_h5s_ptype
        private
        integer :: ptype
    end type phez_h5s_ptype

    type phez_h5s_type
        private
        integer :: stype
    end type phez_h5s_type

    interface
        ! bindings for all C functions in Fortran
        function C_phez_context_start() result(obj) &
        bind(C, name="phez_context_start")
            import
            type(c_ptr)          :: obj
        end function C_phez_context_start

        subroutine C_phez_context_stop(obj) &
        bind(C, name="phez_context_stop")
            import
            type(c_ptr), value          :: obj
        end subroutine C_phez_context_stop

!        subroutine C_phez_populate(obj, hash) &
!        bind(C, name="phez_populate")
!            import
!            type(c_ptr), value          :: obj
!            character(kind=c_char)      :: hash(*)
!        end subroutine C_phez_populate

        subroutine C_phez_flush(obj, hash) &
        bind(C, name="phez_flush")
            import
            type(c_ptr), value          :: obj
            character(kind=c_char)      :: hash(*)
        end subroutine C_phez_flush

!        subroutine C_phez_close(obj, hash) &
!        bind(C, name="phez_close")
!            import
!            type(c_ptr), value          :: obj
!            character(kind=c_char)      :: hash(*)
!        end subroutine C_phez_close

!        subroutine C_phez_forget(obj, hash) &
!        bind(C, name="phez_forget")
!            import
!            type(c_ptr), value          :: obj
!            character(kind=c_char)      :: hash(*)
!        end subroutine C_phez_forget

!        subroutine C_phez_remove(obj, hash) &
!        bind(C, name="phez_remove")
!            import
!            type(c_ptr), value          :: obj
!            character(kind=c_char)      :: hash(*)
!        end subroutine C_phez_remove

!        subroutine C_phez_populate_all(obj) &
!        bind(C, name="phez_populate_all")
!            import
!            type(c_ptr), value          :: obj
!        end subroutine C_phez_populate_all

        subroutine C_phez_flush_all(obj) &
        bind(C, name="phez_flush_all")
            import
            type(c_ptr), value          :: obj
        end subroutine C_phez_flush_all

!        subroutine C_phez_close_all(obj) &
!        bind(C, name="phez_close_all")
!            import
!            type(c_ptr), value          :: obj
!        end subroutine C_phez_close_all

!        subroutine C_phez_forget_all(obj) &
!        bind(C, name="phez_forget_all")
!            import
!            type(c_ptr), value          :: obj
!        end subroutine C_phez_forget_all

!        subroutine C_phez_remove_all(obj) &
!        bind(C, name="phez_remove_all")
!            import
!            type(c_ptr), value          :: obj
!        end subroutine C_phez_remove_all

        function C_phez_appear(obj, hash) result(result_hash) &
        bind(C, name="phez_appear")
            import
            type(c_ptr), value          :: obj
            character(kind=c_char)      :: hash(*)
            type(c_ptr)                 :: result_hash
        end function C_phez_appear

        function C_phez_extract(obj, hash, otype, chname) result(result_hash) &
        bind(C, name="phez_extract")
            import
            type(c_ptr), value          :: obj
            character(kind=c_char)      :: hash(*)
            integer(kind=c_int), value       :: otype
            character(kind=c_char)      :: chname(*)
            type(c_ptr)                 :: result_hash
        end function C_phez_extract

    !******************** PHEZ convenience functions *************************/


    !************************ PHEZ file functions ****************************/

    !* Basic routines */
        function C_phez_file_initialize(obj) result(hash) &
        bind(C, name="phez_file_initialize")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_file_initialize

        subroutine C_phez_current_file_open(obj) &
        bind(C, name="phez_current_file_open")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_current_file_open

        function C_phez_current_file_link_group(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_file_link_group")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_file_link_group

        function C_phez_current_file_link_dataset(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_file_link_dataset")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_file_link_dataset

        function C_phez_current_file_link_attribute(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_file_link_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_file_link_attribute

        subroutine C_phez_current_file_unlink_attribute(obj, hash) &
        bind(C, name="phez_current_file_unlink_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_file_unlink_attribute

        subroutine C_phez_current_file_unlink_dataset(obj, hash) &
        bind(C, name="phez_current_file_unlink_dataset")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_file_unlink_dataset

        subroutine C_phez_current_file_unlink_group(obj, hash) &
        bind(C, name="phez_current_file_unlink_group")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_file_unlink_group

        subroutine C_phez_current_file_close(obj) &
        bind(C, name="phez_current_file_close")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_current_file_close

        subroutine C_phez_current_file_destroy(obj) &
        bind(C, name="phez_current_file_destroy")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_current_file_destroy

    !* Set/get basic info */

        function C_phez_file_get_current(obj) result(hash) &
        bind(C, name="phez_file_get_current")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_file_get_current

        subroutine C_phez_file_set_current(obj, hash) &
        bind(C, name="phez_file_set_current")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_file_set_current

        function C_phez_file_get_num(obj) result(size_t) &
        bind(C, name="phez_file_get_num")
            import
            type(c_ptr), value            :: obj
            integer(kind=c_size_t)             :: size_t
        end function C_phez_file_get_num

        function C_phez_current_file_get_name(obj) result(fname) &
        bind(C, name="phez_current_file_get_name")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: fname
        end function C_phez_current_file_get_name

        subroutine C_phez_current_file_set_name(obj, fname) &
        bind(C, name="phez_current_file_set_name")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: fname(*)
        end subroutine C_phez_current_file_set_name

        function C_phez_current_file_get_action(obj) result(action) &
        bind(C, name="phez_current_file_get_action")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int)             :: action
        end function C_phez_current_file_get_action

        subroutine C_phez_current_file_set_action(obj, action) &
        bind(C, name="phez_current_file_set_action")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int), value             :: action
        end subroutine C_phez_current_file_set_action

    !* Defend ourselves from wandering property lists */

        subroutine C_phez_current_file_reset_access_properties(obj) &
        bind(C, name="phez_current_file_reset_access_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_file_reset_access_properties

        subroutine C_phez_current_file_default_access_properties(obj) &
        bind(C, name="phez_current_file_default_access_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_file_default_access_properties

        subroutine C_phez_current_file_access_from_memory(obj, size_t, bool) &
        bind(C, name="phez_current_file_access_from_memory")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t), value   :: size_t
            logical(kind=c_bool), value     :: bool
        end subroutine C_phez_current_file_access_from_memory

        subroutine C_phez_current_file_reset_creation_properties(obj) &
        bind(C, name="phez_current_file_reset_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_file_reset_creation_properties

        subroutine C_phez_current_file_default_creation_properties(obj) &
        bind(C, name="phez_current_file_default_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_file_default_creation_properties

    !* Outward links */

        function C_phez_current_file_get_num_linked_attributes(obj) result(size_t) &
        bind(C, name="phez_current_file_get_num_linked_attributes")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_file_get_num_linked_attributes

        function C_phez_current_file_get_num_linked_datasets(obj) result(size_t) &
        bind(C, name="phez_current_file_get_num_linked_datasets")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_file_get_num_linked_datasets

        function C_phez_current_file_get_num_linked_groups(obj) result(size_t) &
        bind(C, name="phez_current_file_get_num_linked_groups")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_file_get_num_linked_groups

    !************************ PHEZ file functions ****************************/


    !*********************** PHEZ group functions ****************************/

    !* Basic routines */
        function C_phez_group_initialize(obj) result(hash) &
        bind(C, name="phez_group_initialize")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_group_initialize

        function C_phez_current_group_open(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_group_open")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_group_open

        function C_phez_current_group_link_group(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_group_link_group")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_group_link_group

        function C_phez_current_group_link_dataset(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_group_link_dataset")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_group_link_dataset

        function C_phez_current_group_link_attribute(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_group_link_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_group_link_attribute

        subroutine C_phez_current_group_unlink_attribute(obj, hash) &
        bind(C, name="phez_current_group_unlink_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_group_unlink_attribute

        subroutine C_phez_current_group_unlink_dataset(obj, hash) &
        bind(C, name="phez_current_group_unlink_dataset")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_group_unlink_dataset

        subroutine C_phez_current_group_unlink_group(obj, hash) &
        bind(C, name="phez_current_group_unlink_group")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_group_unlink_group

        subroutine C_phez_current_group_close(obj) &
        bind(C, name="phez_current_group_close")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_group_close

        subroutine C_phez_current_group_destroy(obj) &
        bind(C, name="phez_current_group_destroy")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_group_destroy

    !* Set/get basic info */

        function C_phez_group_get_current(obj) result(hash) &
        bind(C, name="phez_group_get_current")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_group_get_current

        subroutine C_phez_group_set_current(obj, hash) &
        bind(C, name="phez_group_set_current")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_group_set_current

        function C_phez_group_get_num(obj) result(size_t) &
        bind(C, name="phez_group_get_num")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_group_get_num

        function C_phez_current_group_get_name(obj) result(gname) &
        bind(C, name="phez_current_group_get_name")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: gname
        end function C_phez_current_group_get_name

        subroutine C_phez_current_group_set_name(obj, gname) &
        bind(C, name="phez_current_group_set_name")
            import
            type(c_ptr), value         :: obj
            character(kind=c_char)     :: gname(*)
        end subroutine C_phez_current_group_set_name

        function C_phez_current_group_get_comment(obj) result(gcomment) &
        bind(C, name="phez_current_group_get_comment")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: gcomment
        end function C_phez_current_group_get_comment

        subroutine C_phez_current_group_set_comment(obj, gcomment) &
        bind(C, name="phez_current_group_set_comment")
            import
            type(c_ptr), value         :: obj
            character(kind=c_char)     :: gcomment(*)
        end subroutine C_phez_current_group_set_comment

    !* Defend ourselves from wandering property lists */

!        subroutine C_phez_current_group_default_access_properties(obj) &
!        bind(C, name="phez_current_group_default_access_properties")
!            import
!            type(c_ptr), value         :: obj
!        end subroutine C_phez_current_group_default_access_properties

        subroutine C_phez_current_group_reset_creation_properties(obj) &
        bind(C, name="phez_current_group_reset_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_group_reset_creation_properties

        subroutine C_phez_current_group_default_creation_properties(obj) &
        bind(C, name="phez_current_group_default_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_group_default_creation_properties

    !* Inward links */

        function C_phez_current_group_get_num_groups_linking(obj) result(size_t) &
        bind(C, name="phez_current_group_get_num_groups_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_group_get_num_groups_linking

        function C_phez_current_group_get_num_files_linking(obj) result(size_t) &
        bind(C, name="phez_current_group_get_num_files_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_group_get_num_files_linking

    !* Outward links */

        function C_phez_current_group_get_num_linked_attributes(obj) result(size_t) &
        bind(C, name="phez_current_group_get_num_linked_attributes")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_group_get_num_linked_attributes

        function C_phez_current_group_get_num_linked_datasets(obj) result(size_t) &
        bind(C, name="phez_current_group_get_num_linked_datasets")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_group_get_num_linked_datasets

        function C_phez_current_group_get_num_linked_groups(obj) result(size_t) &
        bind(C, name="phez_current_group_get_num_linked_groups")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_group_get_num_linked_groups

    !*********************** PHEZ group functions ****************************/


    !********************** PHEZ dataset functions ***************************/

    !* Basic routines */

        function C_phez_dataset_initialize(obj) result(hash) &
        bind(C, name="phez_dataset_initialize")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_dataset_initialize

        function C_phez_current_dataset_open(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_dataset_open")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_dataset_open

        subroutine C_phez_current_dataset_read(obj) &
        bind(C, name="phez_current_dataset_read")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_read

        function C_phez_current_dataset_link_attribute(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_dataset_link_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_dataset_link_attribute

        function C_phez_current_dataset_link_file_space(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_dataset_link_file_space")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_dataset_link_file_space

        function C_phez_current_dataset_link_memory_space(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_dataset_link_memory_space")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_dataset_link_memory_space

        subroutine C_phez_current_dataset_unlink_memory_space(obj) &
        bind(C, name="phez_current_dataset_unlink_memory_space")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_unlink_memory_space

        subroutine C_phez_current_dataset_unlink_file_space(obj) &
        bind(C, name="phez_current_dataset_unlink_file_space")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_unlink_file_space

        subroutine C_phez_current_dataset_unlink_attribute(obj, hash) &
        bind(C, name="phez_current_dataset_unlink_attribute")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_current_dataset_unlink_attribute

        subroutine C_phez_current_dataset_write(obj) &
        bind(C, name="phez_current_dataset_write")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_write

        subroutine C_phez_current_dataset_close(obj) &
        bind(C, name="phez_current_dataset_close")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_close

        subroutine C_phez_current_dataset_destroy(obj) &
        bind(C, name="phez_current_dataset_destroy")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_destroy

    !* Set/get basic info */

        function C_phez_dataset_get_current(obj) result(hash) &
        bind(C, name="phez_dataset_get_current")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_dataset_get_current

        subroutine C_phez_dataset_set_current(obj, hash) &
        bind(C, name="phez_dataset_set_current")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_dataset_set_current

        function C_phez_dataset_get_num(obj) result(size_t) &
        bind(C, name="phez_dataset_get_num")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_dataset_get_num

        function C_phez_current_dataset_get_name(obj) result(dname) &
        bind(C, name="phez_current_dataset_get_name")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: dname
        end function C_phez_current_dataset_get_name

        subroutine C_phez_current_dataset_set_name(obj, dname) &
        bind(C, name="phez_current_dataset_set_name")
            import
            type(c_ptr), value         :: obj
            character(kind=c_char)     :: dname(*)
        end subroutine C_phez_current_dataset_set_name

        function C_phez_current_dataset_get_comment(obj) result(dcomment) &
        bind(C, name="phez_current_dataset_get_comment")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: dcomment
        end function C_phez_current_dataset_get_comment

        subroutine C_phez_current_dataset_set_comment(obj, dcomment) &
        bind(C, name="phez_current_dataset_set_comment")
            import
            type(c_ptr), value         :: obj
            character(kind=c_char)     :: dcomment(*)
        end subroutine C_phez_current_dataset_set_comment

        function C_phez_current_dataset_get_type(obj) result(datatype) &
        bind(C, name="phez_current_dataset_get_type")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int) :: datatype
        end function C_phez_current_dataset_get_type

        function C_phez_current_dataset_get_data_bool(obj) result(data) &
        bind(C, name="phez_current_dataset_get_data_bool")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_dataset_get_data_bool

        subroutine C_phez_current_dataset_set_data_bool(obj, data) &
        bind(C, name="phez_current_dataset_set_data_bool")
            import
            type(c_ptr), value         :: obj
            logical(kind=c_bool),dimension(*) :: data
        end subroutine C_phez_current_dataset_set_data_bool

        function C_phez_current_dataset_get_data_int(obj) result(data) &
        bind(C, name="phez_current_dataset_get_data_int")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_dataset_get_data_int

        subroutine C_phez_current_dataset_set_data_int(obj, data) &
        bind(C, name="phez_current_dataset_set_data_int")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int),dimension(*) :: data
        end subroutine C_phez_current_dataset_set_data_int

        function C_phez_current_dataset_get_data_float(obj) result(data) &
        bind(C, name="phez_current_dataset_get_data_float")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_dataset_get_data_float

        subroutine C_phez_current_dataset_set_data_float(obj, data) &
        bind(C, name="phez_current_dataset_set_data_float")
            import
            type(c_ptr), value         :: obj
            real(kind=c_float),dimension(*) :: data
        end subroutine C_phez_current_dataset_set_data_float

        function C_phez_current_dataset_get_data_double(obj) result(data) &
        bind(C, name="phez_current_dataset_get_data_double")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_dataset_get_data_double

        subroutine C_phez_current_dataset_set_data_double(obj, data) &
        bind(C, name="phez_current_dataset_set_data_double")
            import
            type(c_ptr), value         :: obj
            real(kind=c_double),dimension(*) :: data
        end subroutine C_phez_current_dataset_set_data_double

!        function C_phez_current_dataset_get_data_string(obj) result(data) &
!        bind(C, name="phez_current_dataset_get_data_string")
!            import
!            type(c_ptr), value         :: obj
!            type(c_ptr)                :: data
!        end function C_phez_current_dataset_get_data_string

!        subroutine C_phez_current_dataset_set_data_string(obj, data) &
!        bind(C, name="phez_current_dataset_set_data_string")
!            import
!            type(c_ptr), value         :: obj
!            type(c_ptr), value         :: data
!        end subroutine C_phez_current_dataset_set_data_string

    !* Defend ourselves from wandering property lists */

        subroutine C_phez_current_dataset_reset_access_properties(obj) &
        bind(C, name="phez_current_dataset_reset_access_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_reset_access_properties

        subroutine C_phez_current_dataset_default_access_properties(obj) &
        bind(C, name="phez_current_dataset_default_access_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_default_access_properties

        subroutine C_phez_current_dataset_reset_creation_properties(obj) &
        bind(C, name="phez_current_dataset_reset_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_reset_creation_properties

        subroutine C_phez_current_dataset_default_creation_properties(obj) &
        bind(C, name="phez_current_dataset_default_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_dataset_default_creation_properties

!        subroutine C_phez_current_dataset_default_transfer_properties(obj) &
!        bind(C, name="phez_current_dataset_default_transfer_properties")
!            import
!            type(c_ptr), value         :: obj
!        end subroutine C_phez_current_dataset_default_transfer_properties

    !* Inward links */

        function C_phez_current_dataset_get_num_groups_linking(obj) result(size_t) &
        bind(C, name="phez_current_dataset_get_num_groups_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_dataset_get_num_groups_linking

        function C_phez_current_dataset_get_num_files_linking(obj) result(size_t) &
        bind(C, name="phez_current_dataset_get_num_files_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_dataset_get_num_files_linking

    !* Outward links */

        function C_phez_current_dataset_get_num_linked_attributes(obj) result(size_t) &
        bind(C, name="phez_current_dataset_get_num_linked_attributes")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_dataset_get_num_linked_attributes

        function C_phez_current_dataset_get_linked_file_space(obj) result(hash) &
        bind(C, name="phez_current_dataset_get_linked_file_space")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: hash
        end function C_phez_current_dataset_get_linked_file_space

        function C_phez_current_dataset_get_linked_memory_space(obj) result(hash) &
        bind(C, name="phez_current_dataset_get_linked_memory_space")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: hash
        end function C_phez_current_dataset_get_linked_memory_space

    !********************** PHEZ dataset functions ***************************/


    !********************* PHEZ attribute functions **************************/

    !* Basic routines */

        function C_phez_attribute_initialize(obj) result(hash) &
        bind(C, name="phez_attribute_initialize")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_attribute_initialize

        function C_phez_current_attribute_open(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_attribute_open")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_attribute_open

        subroutine C_phez_current_attribute_read(obj) &
        bind(C, name="phez_current_attribute_read")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_read

        function C_phez_current_attribute_link_space(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_attribute_link_space")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_attribute_link_space

        subroutine C_phez_current_attribute_unlink_space(obj) &
        bind(C, name="phez_current_attribute_unlink_space")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_unlink_space

        subroutine C_phez_current_attribute_write(obj) &
        bind(C, name="phez_current_attribute_write")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_write

        subroutine C_phez_current_attribute_close(obj) &
        bind(C, name="phez_current_attribute_close")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_close

        subroutine C_phez_current_attribute_destroy(obj) &
        bind(C, name="phez_current_attribute_destroy")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_destroy

    !* Set/get basic info */

        function C_phez_attribute_get_current(obj) result(hash) &
        bind(C, name="phez_attribute_get_current")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_attribute_get_current

        subroutine C_phez_attribute_set_current(obj, hash) &
        bind(C, name="phez_attribute_set_current")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_attribute_set_current

        function C_phez_attribute_get_num(obj) result(attrsize) &
        bind(C, name="phez_attribute_get_num")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t)          :: attrsize
        end function C_phez_attribute_get_num

        function C_phez_current_attribute_get_name(obj) result(aname) &
        bind(C, name="phez_current_attribute_get_name")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: aname
        end function C_phez_current_attribute_get_name

        subroutine C_phez_current_attribute_set_name(obj, aname) &
        bind(C, name="phez_current_attribute_set_name")
            import
            type(c_ptr), value         :: obj
            character(kind=c_char)     :: aname(*)
        end subroutine C_phez_current_attribute_set_name

        function C_phez_current_attribute_get_type(obj) result(datatype) &
        bind(C, name="phez_current_attribute_get_type")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int) :: datatype
        end function C_phez_current_attribute_get_type

        function C_phez_current_attribute_get_size(obj) result(size_t) &
        bind(C, name="phez_current_attribute_get_size")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_attribute_get_size

        function C_phez_current_attribute_get_data_bool(obj) result(data) &
        bind(C, name="phez_current_attribute_get_data_bool")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_attribute_get_data_bool

        subroutine C_phez_current_attribute_set_data_bool(obj, data) &
        bind(C, name="phez_current_attribute_set_data_bool")
            import
            type(c_ptr), value         :: obj
            logical(kind=c_bool),dimension(*) :: data
        end subroutine C_phez_current_attribute_set_data_bool

        function C_phez_current_attribute_get_data_int(obj) result(data) &
        bind(C, name="phez_current_attribute_get_data_int")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_attribute_get_data_int

        subroutine C_phez_current_attribute_set_data_int(obj, data) &
        bind(C, name="phez_current_attribute_set_data_int")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int),dimension(*) :: data
        end subroutine C_phez_current_attribute_set_data_int

        function C_phez_current_attribute_get_data_float(obj) result(data) &
        bind(C, name="phez_current_attribute_get_data_float")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_attribute_get_data_float

        subroutine C_phez_current_attribute_set_data_float(obj, data) &
        bind(C, name="phez_current_attribute_set_data_float")
            import
            type(c_ptr), value         :: obj
            real(kind=c_float),dimension(*) :: data
        end subroutine C_phez_current_attribute_set_data_float

        function C_phez_current_attribute_get_data_double(obj) result(data) &
        bind(C, name="phez_current_attribute_get_data_double")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: data
        end function C_phez_current_attribute_get_data_double

        subroutine C_phez_current_attribute_set_data_double(obj, data) &
        bind(C, name="phez_current_attribute_set_data_double")
            import
            type(c_ptr), value         :: obj
            real(kind=c_double),dimension(*) :: data
        end subroutine C_phez_current_attribute_set_data_double

!        function C_phez_current_attribute_get_data_string(obj) result(data) &
!        bind(C, name="phez_current_attribute_get_data_string")
!            import
!            type(c_ptr), value         :: obj
!            type(c_ptr)                :: data
!        end function C_phez_current_attribute_get_data_string

!        subroutine C_phez_current_attribute_set_data_string(obj, data) &
!        bind(C, name="phez_current_attribute_set_data_string")
!            import
!            type(c_ptr), value         :: obj
!            type(c_ptr), value         :: data
!        end subroutine C_phez_current_attribute_set_data_string

    !* Defend ourselves from wandering property lists */

        subroutine C_phez_current_attribute_reset_creation_properties(obj) &
        bind(C, name="phez_current_attribute_reset_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_reset_creation_properties

        subroutine C_phez_current_attribute_default_creation_properties(obj) &
        bind(C, name="phez_current_attribute_default_creation_properties")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_attribute_default_creation_properties

    !* Inward links */

        function C_phez_current_attribute_get_num_datasets_linking(obj) result(size_t) &
        bind(C, name="phez_current_attribute_get_num_datasets_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_attribute_get_num_datasets_linking

        function C_phez_current_attribute_get_num_groups_linking(obj) result(size_t) &
        bind(C, name="phez_current_attribute_get_num_groups_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_attribute_get_num_groups_linking

        function C_phez_current_attribute_get_num_files_linking(obj) result(size_t) &
        bind(C, name="phez_current_attribute_get_num_files_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_attribute_get_num_files_linking

        function C_phez_current_attribute_get_linked_space(obj) result(hash) &
        bind(C, name="phez_current_attribute_get_linked_space")
            import
            type(c_ptr), value         :: obj
            type(c_ptr)                :: hash
        end function C_phez_current_attribute_get_linked_space

    !********************* PHEZ attribute functions **************************/


    !*********************** PHEZ space functions ****************************/

        function C_phez_space_initialize(obj) result(hash) &
        bind(C, name="phez_space_initialize")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_space_initialize

        function C_phez_current_space_open(obj, hash_in) result(hash_out) &
        bind(C, name="phez_current_space_open")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash_in(*)
            type(c_ptr)                   :: hash_out
        end function C_phez_current_space_open

        subroutine C_phez_current_space_close(obj) &
        bind(C, name="phez_current_space_close")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_space_close

        subroutine C_phez_current_space_destroy(obj) &
        bind(C, name="phez_current_space_destroy")
            import
            type(c_ptr), value         :: obj
        end subroutine C_phez_current_space_destroy

        function C_phez_space_get_current(obj) result(hash) &
        bind(C, name="phez_space_get_current")
            import
            type(c_ptr), value            :: obj
            type(c_ptr)                   :: hash
        end function C_phez_space_get_current

        subroutine C_phez_space_set_current(obj, hash) &
        bind(C, name="phez_space_set_current")
            import
            type(c_ptr), value            :: obj
            character(kind=c_char)        :: hash(*)
        end subroutine C_phez_space_set_current

        function C_phez_space_get_num(obj) result(size_t) &
        bind(C, name="phez_space_get_num")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_space_get_num

        function C_phez_current_space_get_ptype(obj) result(ptype) &
        bind(C, name="phez_current_space_get_ptype")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int) :: ptype
        end function C_phez_current_space_get_ptype

        subroutine C_phez_current_space_set_ptype(obj, ptype) &
        bind(C, name="phez_current_space_set_ptype")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int), value :: ptype
        end subroutine C_phez_current_space_set_ptype

        function C_phez_current_space_get_size(obj) result(size_t) &
        bind(C, name="phez_current_space_get_size")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_space_get_size

        subroutine C_phez_current_space_set_size(obj, size_t) &
        bind(C, name="phez_current_space_set_size")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t), value :: size_t
        end subroutine C_phez_current_space_set_size

        function C_phez_current_space_get_dims_now(obj) result(size_t) &
        bind(C, name="phez_current_space_get_dims_now")
            import
            type(c_ptr), value         :: obj
            type(c_ptr) :: size_t
        end function C_phez_current_space_get_dims_now

        subroutine C_phez_current_space_set_dims_now(obj, size_t) &
        bind(C, name="phez_current_space_set_dims_now")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t),dimension(*) :: size_t
        end subroutine C_phez_current_space_set_dims_now

        function C_phez_current_space_get_dims_max(obj) result(size_t) &
        bind(C, name="phez_current_space_get_dims_max")
            import
            type(c_ptr), value         :: obj
            type(c_ptr) :: size_t
        end function C_phez_current_space_get_dims_max

        subroutine C_phez_current_space_set_dims_max(obj, size_t) &
        bind(C, name="phez_current_space_set_dims_max")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t),dimension(*) :: size_t
        end subroutine C_phez_current_space_set_dims_max

        function C_phez_current_space_get_type(obj) result(type_t) &
        bind(C, name="phez_current_space_get_type")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int) :: type_t
        end function C_phez_current_space_get_type

        subroutine C_phez_current_space_set_type(obj, type_t) &
        bind(C, name="phez_current_space_set_type")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_int), value :: type_t
        end subroutine C_phez_current_space_set_type

    !* Inward links */

        function C_phez_current_space_get_num_datasets_linking(obj) result(size_t) &
        bind(C, name="phez_current_space_get_num_datasets_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_space_get_num_datasets_linking

        function C_phez_current_space_get_num_attributes_linking(obj) result(size_t) &
        bind(C, name="phez_current_space_get_num_attributes_linking")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_current_space_get_num_attributes_linking

    !*********************** PHEZ space functions ****************************/


    !*********************** PHEZ etc functions ******************************/

        function C_phez_internal_get_string_length(cstring) result(size_t) &
        bind(C, name="phez_internal_get_string_length")
            import
            type(c_ptr),intent(in), value         :: cstring
            integer(kind=c_size_t) :: size_t
        end function C_phez_internal_get_string_length

        function C_phez_internal_get_hash_digits(obj) result(size_t) &
        bind(C, name="phez_internal_get_hash_digits")
            import
            type(c_ptr), value         :: obj
            integer(kind=c_size_t) :: size_t
        end function C_phez_internal_get_hash_digits


        subroutine C_phez_internal_file_set_current_to_null(obj) &
        bind(C, name="phez_internal_file_set_current_to_null")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_internal_file_set_current_to_null

        subroutine C_phez_internal_group_set_current_to_null(obj) &
        bind(C, name="phez_internal_group_set_current_to_null")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_internal_group_set_current_to_null

        subroutine C_phez_internal_dataset_set_current_to_null(obj) &
        bind(C, name="phez_internal_dataset_set_current_to_null")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_internal_dataset_set_current_to_null

        subroutine C_phez_internal_attribute_set_current_to_null(obj) &
        bind(C, name="phez_internal_attribute_set_current_to_null")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_internal_attribute_set_current_to_null

        subroutine C_phez_internal_space_set_current_to_null(obj) &
        bind(C, name="phez_internal_space_set_current_to_null")
            import
            type(c_ptr), value            :: obj
        end subroutine C_phez_internal_space_set_current_to_null

    end interface



! interfaces to easily access wrapper functions and bound C functions without weird names and types


    interface phez_context_start
        module procedure fwrap_phez_context_start
    end interface phez_context_start

    interface phez_context_stop
        module procedure fwrap_phez_context_stop
    end interface phez_context_stop

!    interface phez_populate
!        module procedure fwrap_phez_populate
!    end interface phez_populate

    interface phez_flush
        module procedure fwrap_phez_flush
    end interface phez_flush

!    interface phez_close
!        module procedure fwrap_phez_close
!    end interface phez_close

!    interface phez_forget
!        module procedure fwrap_phez_forget
!    end interface phez_forget

!    interface phez_remove
!        module procedure fwrap_phez_remove
!    end interface phez_remove

!    interface phez_populate_all
!        module procedure fwrap_phez_populate_all
!    end interface phez_populate_all

    interface phez_flush_all
        module procedure fwrap_phez_flush_all
    end interface phez_flush_all

!    interface phez_close_all
!        module procedure fwrap_phez_close_all
!    end interface phez_close_all

!    interface phez_forget_all
!        module procedure fwrap_phez_forget_all
!    end interface phez_forget_all

!    interface phez_remove_all
!        module procedure fwrap_phez_remove_all
!    end interface phez_remove_all

    interface phez_appear
        module procedure fwrap_phez_appear
    end interface phez_appear

    interface phez_extract
        module procedure fwrap_phez_extract
    end interface phez_extract

    interface phez_file_initialize
        module procedure fwrap_phez_file_initialize
    end interface phez_file_initialize

    interface phez_current_file_open
        module procedure fwrap_phez_current_file_open
    end interface phez_current_file_open

    interface phez_current_file_link_group
        module procedure fwrap_phez_current_file_link_group
    end interface phez_current_file_link_group

    interface phez_current_file_link_dataset
        module procedure fwrap_phez_current_file_link_dataset
    end interface phez_current_file_link_dataset

    interface phez_current_file_link_attribute
        module procedure fwrap_phez_current_file_link_attribute
    end interface phez_current_file_link_attribute

    interface phez_current_file_unlink_attribute
        module procedure fwrap_phez_current_file_unlink_attribute
    end interface phez_current_file_unlink_attribute

    interface phez_current_file_unlink_dataset
        module procedure fwrap_phez_current_file_unlink_dataset
    end interface phez_current_file_unlink_dataset

    interface phez_current_file_unlink_group
        module procedure fwrap_phez_current_file_unlink_group
    end interface phez_current_file_unlink_group

    interface phez_current_file_close
        module procedure fwrap_phez_current_file_close
    end interface phez_current_file_close

    interface phez_current_file_destroy
        module procedure fwrap_phez_current_file_destroy
    end interface phez_current_file_destroy

    interface phez_file_get_current
        module procedure fwrap_phez_file_get_current
    end interface phez_file_get_current

    interface phez_file_set_current
        module procedure fwrap_phez_file_set_current
    end interface phez_file_set_current

    interface phez_file_get_num
        module procedure fwrap_phez_file_get_num
    end interface phez_file_get_num

    interface phez_current_file_get_name
        module procedure fwrap_phez_current_file_get_name
    end interface phez_current_file_get_name

    interface phez_current_file_set_name
        module procedure fwrap_phez_current_file_set_name
    end interface phez_current_file_set_name

    interface phez_current_file_get_action
        module procedure fwrap_phez_current_file_get_action
    end interface phez_current_file_get_action

    interface phez_current_file_set_action
        module procedure fwrap_phez_current_file_set_action
    end interface phez_current_file_set_action

    interface phez_current_file_reset_access_properties
        module procedure fwrap_phez_current_file_reset_access_properties
    end interface phez_current_file_reset_access_properties

    interface phez_current_file_default_access_properties
        module procedure fwrap_phez_current_file_default_access_properties
    end interface phez_current_file_default_access_properties

    interface phez_current_file_access_from_memory
        module procedure fwrap_phez_current_file_access_from_memory
    end interface phez_current_file_access_from_memory

    interface phez_current_file_reset_creation_properties
        module procedure fwrap_phez_current_file_reset_creation_properties
    end interface phez_current_file_reset_creation_properties

    interface phez_current_file_default_creation_properties
        module procedure fwrap_phez_current_file_default_creation_properties
    end interface phez_current_file_default_creation_properties

    interface phez_current_file_get_num_linked_attributes
        module procedure fwrap_phez_current_file_get_num_linked_attributes
    end interface phez_current_file_get_num_linked_attributes

    interface phez_current_file_get_num_linked_datasets
        module procedure fwrap_phez_current_file_get_num_linked_datasets
    end interface phez_current_file_get_num_linked_datasets

    interface phez_current_file_get_num_linked_groups
        module procedure fwrap_phez_current_file_get_num_linked_groups
    end interface phez_current_file_get_num_linked_groups

    interface phez_group_initialize
        module procedure fwrap_phez_group_initialize
    end interface phez_group_initialize

    interface phez_current_group_open
        module procedure fwrap_phez_current_group_open
    end interface phez_current_group_open

    interface phez_current_group_link_group
        module procedure fwrap_phez_current_group_link_group
    end interface phez_current_group_link_group

    interface phez_current_group_link_dataset
        module procedure fwrap_phez_current_group_link_dataset
    end interface phez_current_group_link_dataset

    interface phez_current_group_link_attribute
        module procedure fwrap_phez_current_group_link_attribute
    end interface phez_current_group_link_attribute

    interface phez_current_group_unlink_attribute
        module procedure fwrap_phez_current_group_unlink_attribute
    end interface phez_current_group_unlink_attribute

    interface phez_current_group_unlink_dataset
        module procedure fwrap_phez_current_group_unlink_dataset
    end interface phez_current_group_unlink_dataset

    interface phez_current_group_unlink_group
        module procedure fwrap_phez_current_group_unlink_group
    end interface phez_current_group_unlink_group

    interface phez_current_group_close
        module procedure fwrap_phez_current_group_close
    end interface phez_current_group_close

    interface phez_current_group_destroy
        module procedure fwrap_phez_current_group_destroy
    end interface phez_current_group_destroy

    interface phez_group_get_current
        module procedure fwrap_phez_group_get_current
    end interface phez_group_get_current

    interface phez_group_set_current
        module procedure fwrap_phez_group_set_current
    end interface phez_group_set_current

    interface phez_group_get_num
        module procedure fwrap_phez_group_get_num
    end interface phez_group_get_num

    interface phez_current_group_get_name
        module procedure fwrap_phez_current_group_get_name
    end interface phez_current_group_get_name

    interface phez_current_group_set_name
        module procedure fwrap_phez_current_group_set_name
    end interface phez_current_group_set_name

    interface phez_current_group_get_comment
        module procedure fwrap_phez_current_group_get_comment
    end interface phez_current_group_get_comment

    interface phez_current_group_set_comment
        module procedure fwrap_phez_current_group_set_comment
    end interface phez_current_group_set_comment

!    interface phez_current_group_default_access_properties
!        module procedure fwrap_phez_current_group_default_access_properties
!    end interface phez_current_group_default_access_properties

    interface phez_current_group_reset_creation_properties
        module procedure fwrap_phez_current_group_reset_creation_properties
    end interface phez_current_group_reset_creation_properties

    interface phez_current_group_default_creation_properties
        module procedure fwrap_phez_current_group_default_creation_properties
    end interface phez_current_group_default_creation_properties

    interface phez_current_group_get_num_groups_linking
        module procedure fwrap_phez_current_group_get_num_groups_linking
    end interface phez_current_group_get_num_groups_linking

    interface phez_current_group_get_num_files_linking
        module procedure fwrap_phez_current_group_get_num_files_linking
    end interface phez_current_group_get_num_files_linking

    interface phez_current_group_get_num_linked_attributes
        module procedure fwrap_phez_current_group_get_num_linked_attributes
    end interface phez_current_group_get_num_linked_attributes

    interface phez_current_group_get_num_linked_datasets
        module procedure fwrap_phez_current_group_get_num_linked_datasets
    end interface phez_current_group_get_num_linked_datasets

    interface phez_current_group_get_num_linked_groups
        module procedure fwrap_phez_current_group_get_num_linked_groups
    end interface phez_current_group_get_num_linked_groups

    interface phez_dataset_initialize
        module procedure fwrap_phez_dataset_initialize
    end interface phez_dataset_initialize

    interface phez_current_dataset_open
        module procedure fwrap_phez_current_dataset_open
    end interface phez_current_dataset_open

    interface phez_current_dataset_read
        module procedure fwrap_phez_current_dataset_read
    end interface phez_current_dataset_read

    interface phez_current_dataset_link_attribute
        module procedure fwrap_phez_current_dataset_link_attribute
    end interface phez_current_dataset_link_attribute

    interface phez_current_dataset_link_file_space
        module procedure fwrap_phez_current_dataset_link_file_space
    end interface phez_current_dataset_link_file_space

    interface phez_current_dataset_link_memory_space
        module procedure fwrap_phez_current_dataset_link_memory_space
    end interface phez_current_dataset_link_memory_space

    interface phez_current_dataset_unlink_memory_space
        module procedure fwrap_phez_current_dataset_unlink_memory_space
    end interface phez_current_dataset_unlink_memory_space

    interface phez_current_dataset_unlink_file_space
        module procedure fwrap_phez_current_dataset_unlink_file_space
    end interface phez_current_dataset_unlink_file_space

    interface phez_current_dataset_unlink_attribute
        module procedure fwrap_phez_current_dataset_unlink_attribute
    end interface phez_current_dataset_unlink_attribute

    interface phez_current_dataset_write
        module procedure fwrap_phez_current_dataset_write
    end interface phez_current_dataset_write

    interface phez_current_dataset_close
        module procedure fwrap_phez_current_dataset_close
    end interface phez_current_dataset_close

    interface phez_current_dataset_destroy
        module procedure fwrap_phez_current_dataset_destroy
    end interface phez_current_dataset_destroy

    interface phez_dataset_get_current
        module procedure fwrap_phez_dataset_get_current
    end interface phez_dataset_get_current

    interface phez_dataset_set_current
        module procedure fwrap_phez_dataset_set_current
    end interface phez_dataset_set_current

    interface phez_dataset_get_num
        module procedure fwrap_phez_dataset_get_num
    end interface phez_dataset_get_num

    interface phez_current_dataset_get_name
        module procedure fwrap_phez_current_dataset_get_name
    end interface phez_current_dataset_get_name

    interface phez_current_dataset_set_name
        module procedure fwrap_phez_current_dataset_set_name
    end interface phez_current_dataset_set_name

    interface phez_current_dataset_get_comment
        module procedure fwrap_phez_current_dataset_get_comment
    end interface phez_current_dataset_get_comment

    interface phez_current_dataset_set_comment
        module procedure fwrap_phez_current_dataset_set_comment
    end interface phez_current_dataset_set_comment

    interface phez_current_dataset_get_type
        module procedure fwrap_phez_current_dataset_get_type
    end interface phez_current_dataset_get_type

    interface phez_current_dataset_get_data
        module procedure fwrap_phez_current_dataset_get_data_bool_1D
        module procedure fwrap_phez_current_dataset_get_data_bool_2D
        module procedure fwrap_phez_current_dataset_get_data_bool_3D
        module procedure fwrap_phez_current_dataset_get_data_bool_4D
        module procedure fwrap_phez_current_dataset_get_data_bool_5D

        module procedure fwrap_phez_current_dataset_get_data_int_1D
        module procedure fwrap_phez_current_dataset_get_data_int_2D
        module procedure fwrap_phez_current_dataset_get_data_int_3D
        module procedure fwrap_phez_current_dataset_get_data_int_4D
        module procedure fwrap_phez_current_dataset_get_data_int_5D

        module procedure fwrap_phez_current_dataset_get_data_float_1D
        module procedure fwrap_phez_current_dataset_get_data_float_2D
        module procedure fwrap_phez_current_dataset_get_data_float_3D
        module procedure fwrap_phez_current_dataset_get_data_float_4D
        module procedure fwrap_phez_current_dataset_get_data_float_5D

        module procedure fwrap_phez_current_dataset_get_data_double_1D
        module procedure fwrap_phez_current_dataset_get_data_double_2D
        module procedure fwrap_phez_current_dataset_get_data_double_3D
        module procedure fwrap_phez_current_dataset_get_data_double_4D
        module procedure fwrap_phez_current_dataset_get_data_double_5D

!        module procedure fwrap_phez_current_dataset_get_data_string_1D
!        module procedure fwrap_phez_current_dataset_get_data_string_2D
!        module procedure fwrap_phez_current_dataset_get_data_string_3D
!        module procedure fwrap_phez_current_dataset_get_data_string_4D
!        module procedure fwrap_phez_current_dataset_get_data_string_5D
    end interface phez_current_dataset_get_data

    interface phez_current_dataset_set_data
        module procedure fwrap_phez_current_dataset_set_data_bool_1D
        module procedure fwrap_phez_current_dataset_set_data_bool_2D
        module procedure fwrap_phez_current_dataset_set_data_bool_3D
        module procedure fwrap_phez_current_dataset_set_data_bool_4D
        module procedure fwrap_phez_current_dataset_set_data_bool_5D

        module procedure fwrap_phez_current_dataset_set_data_int_1D
        module procedure fwrap_phez_current_dataset_set_data_int_2D
        module procedure fwrap_phez_current_dataset_set_data_int_3D
        module procedure fwrap_phez_current_dataset_set_data_int_4D
        module procedure fwrap_phez_current_dataset_set_data_int_5D

        module procedure fwrap_phez_current_dataset_set_data_float_1D
        module procedure fwrap_phez_current_dataset_set_data_float_2D
        module procedure fwrap_phez_current_dataset_set_data_float_3D
        module procedure fwrap_phez_current_dataset_set_data_float_4D
        module procedure fwrap_phez_current_dataset_set_data_float_5D

        module procedure fwrap_phez_current_dataset_set_data_double_1D
        module procedure fwrap_phez_current_dataset_set_data_double_2D
        module procedure fwrap_phez_current_dataset_set_data_double_3D
        module procedure fwrap_phez_current_dataset_set_data_double_4D
        module procedure fwrap_phez_current_dataset_set_data_double_5D

!        module procedure fwrap_phez_current_dataset_set_data_string_1D
!        module procedure fwrap_phez_current_dataset_set_data_string_2D
!        module procedure fwrap_phez_current_dataset_set_data_string_3D
!        module procedure fwrap_phez_current_dataset_set_data_string_4D
!        module procedure fwrap_phez_current_dataset_set_data_string_5D
    end interface phez_current_dataset_set_data

    interface phez_current_dataset_reset_access_properties
        module procedure fwrap_phez_current_dataset_reset_access_properties
    end interface phez_current_dataset_reset_access_properties

    interface phez_current_dataset_default_access_properties
        module procedure fwrap_phez_current_dataset_default_access_properties
    end interface phez_current_dataset_default_access_properties

    interface phez_current_dataset_reset_creation_properties
        module procedure fwrap_phez_current_dataset_reset_creation_properties
    end interface phez_current_dataset_reset_creation_properties

    interface phez_current_dataset_default_creation_properties
        module procedure fwrap_phez_current_dataset_default_creation_properties
    end interface phez_current_dataset_default_creation_properties

!    interface phez_current_dataset_default_transfer_properties
!        module procedure fwrap_phez_current_dataset_default_transfer_properties
!    end interface phez_current_dataset_default_transfer_properties

    interface phez_current_dataset_get_num_groups_linking
        module procedure fwrap_phez_current_dataset_get_num_groups_linking
    end interface phez_current_dataset_get_num_groups_linking

    interface phez_current_dataset_get_num_files_linking
        module procedure fwrap_phez_current_dataset_get_num_files_linking
    end interface phez_current_dataset_get_num_files_linking

    interface phez_current_dataset_get_num_linked_attributes
        module procedure fwrap_phez_current_dataset_get_num_linked_attributes
    end interface phez_current_dataset_get_num_linked_attributes

    interface phez_current_dataset_get_linked_file_space
        module procedure fwrap_phez_current_dataset_get_linked_file_space
    end interface phez_current_dataset_get_linked_file_space

    interface phez_current_dataset_get_linked_memory_space
        module procedure fwrap_phez_current_dataset_get_linked_memory_space
    end interface phez_current_dataset_get_linked_memory_space

    interface phez_attribute_initialize
        module procedure fwrap_phez_attribute_initialize
    end interface phez_attribute_initialize

    interface phez_current_attribute_open
        module procedure fwrap_phez_current_attribute_open
    end interface phez_current_attribute_open

    interface phez_current_attribute_read
        module procedure fwrap_phez_current_attribute_read
    end interface phez_current_attribute_read

    interface phez_current_attribute_link_space
        module procedure fwrap_phez_current_attribute_link_space
    end interface phez_current_attribute_link_space

    interface phez_current_attribute_unlink_space
        module procedure fwrap_phez_current_attribute_unlink_space
    end interface phez_current_attribute_unlink_space

    interface phez_current_attribute_write
        module procedure fwrap_phez_current_attribute_write
    end interface phez_current_attribute_write

    interface phez_current_attribute_close
        module procedure fwrap_phez_current_attribute_close
    end interface phez_current_attribute_close

    interface phez_current_attribute_destroy
        module procedure fwrap_phez_current_attribute_destroy
    end interface phez_current_attribute_destroy

    interface phez_attribute_get_current
        module procedure fwrap_phez_attribute_get_current
    end interface phez_attribute_get_current

    interface phez_attribute_set_current
        module procedure fwrap_phez_attribute_set_current
    end interface phez_attribute_set_current

    interface phez_attribute_get_num
        module procedure fwrap_phez_attribute_get_num
    end interface phez_attribute_get_num

    interface phez_current_attribute_get_name
        module procedure fwrap_phez_current_attribute_get_name
    end interface phez_current_attribute_get_name

    interface phez_current_attribute_set_name
        module procedure fwrap_phez_current_attribute_set_name
    end interface phez_current_attribute_set_name

    interface phez_current_attribute_get_type
        module procedure fwrap_phez_current_attribute_get_type
    end interface phez_current_attribute_get_type

    interface phez_current_attribute_get_data
        module procedure fwrap_phez_current_attribute_get_data_bool_1D
        module procedure fwrap_phez_current_attribute_get_data_bool_2D
        module procedure fwrap_phez_current_attribute_get_data_bool_3D
        module procedure fwrap_phez_current_attribute_get_data_bool_4D
        module procedure fwrap_phez_current_attribute_get_data_bool_5D

        module procedure fwrap_phez_current_attribute_get_data_int_1D
        module procedure fwrap_phez_current_attribute_get_data_int_2D
        module procedure fwrap_phez_current_attribute_get_data_int_3D
        module procedure fwrap_phez_current_attribute_get_data_int_4D
        module procedure fwrap_phez_current_attribute_get_data_int_5D

        module procedure fwrap_phez_current_attribute_get_data_float_1D
        module procedure fwrap_phez_current_attribute_get_data_float_2D
        module procedure fwrap_phez_current_attribute_get_data_float_3D
        module procedure fwrap_phez_current_attribute_get_data_float_4D
        module procedure fwrap_phez_current_attribute_get_data_float_5D

        module procedure fwrap_phez_current_attribute_get_data_double_1D
        module procedure fwrap_phez_current_attribute_get_data_double_2D
        module procedure fwrap_phez_current_attribute_get_data_double_3D
        module procedure fwrap_phez_current_attribute_get_data_double_4D
        module procedure fwrap_phez_current_attribute_get_data_double_5D

!        module procedure fwrap_phez_current_attribute_get_data_string_1D
!        module procedure fwrap_phez_current_attribute_get_data_string_2D
!        module procedure fwrap_phez_current_attribute_get_data_string_3D
!        module procedure fwrap_phez_current_attribute_get_data_string_4D
!        module procedure fwrap_phez_current_attribute_get_data_string_5D
    end interface phez_current_attribute_get_data

    interface phez_current_attribute_set_data
        module procedure fwrap_phez_current_attribute_set_data_bool_1D
        module procedure fwrap_phez_current_attribute_set_data_bool_2D
        module procedure fwrap_phez_current_attribute_set_data_bool_3D
        module procedure fwrap_phez_current_attribute_set_data_bool_4D
        module procedure fwrap_phez_current_attribute_set_data_bool_5D

        module procedure fwrap_phez_current_attribute_set_data_int_1D
        module procedure fwrap_phez_current_attribute_set_data_int_2D
        module procedure fwrap_phez_current_attribute_set_data_int_3D
        module procedure fwrap_phez_current_attribute_set_data_int_4D
        module procedure fwrap_phez_current_attribute_set_data_int_5D

        module procedure fwrap_phez_current_attribute_set_data_float_1D
        module procedure fwrap_phez_current_attribute_set_data_float_2D
        module procedure fwrap_phez_current_attribute_set_data_float_3D
        module procedure fwrap_phez_current_attribute_set_data_float_4D
        module procedure fwrap_phez_current_attribute_set_data_float_5D

        module procedure fwrap_phez_current_attribute_set_data_double_1D
        module procedure fwrap_phez_current_attribute_set_data_double_2D
        module procedure fwrap_phez_current_attribute_set_data_double_3D
        module procedure fwrap_phez_current_attribute_set_data_double_4D
        module procedure fwrap_phez_current_attribute_set_data_double_5D

!        module procedure fwrap_phez_current_attribute_set_data_string_1D
!        module procedure fwrap_phez_current_attribute_set_data_string_2D
!        module procedure fwrap_phez_current_attribute_set_data_string_3D
!        module procedure fwrap_phez_current_attribute_set_data_string_4D
!        module procedure fwrap_phez_current_attribute_set_data_string_5D
    end interface phez_current_attribute_set_data

    interface phez_current_attribute_reset_creation_properties
        module procedure fwrap_phez_current_attribute_reset_creation_properties
    end interface phez_current_attribute_reset_creation_properties

    interface phez_current_attribute_default_creation_properties
        module procedure fwrap_phez_current_attribute_default_creation_properties
    end interface phez_current_attribute_default_creation_properties

    interface phez_current_attribute_get_num_datasets_linking
        module procedure fwrap_phez_current_attribute_get_num_datasets_linking
    end interface phez_current_attribute_get_num_datasets_linking

    interface phez_current_attribute_get_num_groups_linking
        module procedure fwrap_phez_current_attribute_get_num_groups_linking
    end interface phez_current_attribute_get_num_groups_linking

    interface phez_current_attribute_get_num_files_linking
        module procedure fwrap_phez_current_attribute_get_num_files_linking
    end interface phez_current_attribute_get_num_files_linking

    interface phez_current_attribute_get_linked_space
        module procedure fwrap_phez_current_attribute_get_linked_space
    end interface phez_current_attribute_get_linked_space

    interface phez_space_initialize
        module procedure fwrap_phez_space_initialize
    end interface phez_space_initialize

    interface phez_current_space_open
        module procedure fwrap_phez_current_space_open
    end interface phez_current_space_open

    interface phez_current_space_close
        module procedure fwrap_phez_current_space_close
    end interface phez_current_space_close

    interface phez_current_space_destroy
        module procedure fwrap_phez_current_space_destroy
    end interface phez_current_space_destroy

    interface phez_space_get_current
        module procedure fwrap_phez_space_get_current
    end interface phez_space_get_current

    interface phez_space_set_current
        module procedure fwrap_phez_space_set_current
    end interface phez_space_set_current

    interface phez_space_get_num
        module procedure fwrap_phez_space_get_num
    end interface phez_space_get_num

    interface phez_current_space_get_ptype
        module procedure fwrap_phez_current_space_get_ptype
    end interface phez_current_space_get_ptype

    interface phez_current_space_set_ptype
        module procedure fwrap_phez_current_space_set_ptype
    end interface phez_current_space_set_ptype

    interface phez_current_space_get_size
        module procedure fwrap_phez_current_space_get_size
    end interface phez_current_space_get_size

    interface phez_current_space_set_size
        module procedure fwrap_phez_current_space_set_size
    end interface phez_current_space_set_size

    interface phez_current_space_get_dims_now
        module procedure fwrap_phez_current_space_get_dims_now
    end interface phez_current_space_get_dims_now

    interface phez_current_space_set_dims_now
        module procedure fwrap_phez_current_space_set_dims_now
    end interface phez_current_space_set_dims_now

    interface phez_current_space_get_dims_max
        module procedure fwrap_phez_current_space_get_dims_max
    end interface phez_current_space_get_dims_max

    interface phez_current_space_set_dims_max
        module procedure fwrap_phez_current_space_set_dims_max
    end interface phez_current_space_set_dims_max

    interface phez_current_space_get_type
        module procedure fwrap_phez_current_space_get_type
    end interface phez_current_space_get_type

    interface phez_current_space_set_type
        module procedure fwrap_phez_current_space_set_type
    end interface phez_current_space_set_type

    interface phez_current_space_get_num_datasets_linking
        module procedure fwrap_phez_current_space_get_num_datasets_linking
    end interface phez_current_space_get_num_datasets_linking

    interface phez_current_space_get_num_attributes_linking
        module procedure fwrap_phez_current_space_get_num_attributes_linking
    end interface phez_current_space_get_num_attributes_linking

    public ::   phez_context,        &
                phez_context_start,     &
                phez_context_stop,      &
!                phez_populate,          &
                phez_flush,             &
!                phez_close,             &
!                phez_forget,            &
!                phez_remove,            &
!                phez_populate_all,      &
                phez_flush_all,         &
!                phez_close_all,         &
!                phez_forget_all,        &
!                phez_remove_all,        &
                phez_appear,            &
                phez_extract,           &
                phez_file_initialize,                               &
                phez_current_file_open,                             &
                phez_current_file_link_group,                       &
                phez_current_file_link_dataset,                     &
                phez_current_file_link_attribute,                   &
                phez_current_file_unlink_attribute,                 &
                phez_current_file_unlink_dataset,                   &
                phez_current_file_unlink_group,                     &
                phez_current_file_close,                            &
                phez_current_file_destroy,                          &
                phez_file_get_current,                              &
                phez_file_set_current,                              &
                phez_file_get_num,                                  &
                phez_current_file_get_name,                         &
                phez_current_file_set_name,                         &
                phez_current_file_get_action,                       &
                phez_current_file_set_action,                       &
                phez_current_file_reset_access_properties,          &
                phez_current_file_default_access_properties,        &
                phez_current_file_access_from_memory,               &
                phez_current_file_reset_creation_properties,        &
                phez_current_file_default_creation_properties,      &
                phez_current_file_get_num_linked_attributes,        &
                phez_current_file_get_num_linked_datasets,          &
                phez_current_file_get_num_linked_groups,            &
                phez_group_initialize,                              &
                phez_current_group_open,                            &
                phez_current_group_link_group,                      &
                phez_current_group_link_dataset,                    &
                phez_current_group_link_attribute,                  &
                phez_current_group_unlink_attribute,                &
                phez_current_group_unlink_dataset,                  &
                phez_current_group_unlink_group,                    &
                phez_current_group_close,                           &
                phez_current_group_destroy,                         &
                phez_group_get_current,                             &
                phez_group_set_current,                             &
                phez_group_get_num,                                 &
                phez_current_group_get_name,                        &
                phez_current_group_set_name,                        &
                phez_current_group_get_comment,                     &
                phez_current_group_set_comment,                     &
!                phez_current_group_default_access_properties,       &
                phez_current_group_reset_creation_properties,       &
                phez_current_group_default_creation_properties,     &
                phez_current_group_get_num_groups_linking,          &
                phez_current_group_get_num_files_linking,           &
                phez_current_group_get_num_linked_attributes,       &
                phez_current_group_get_num_linked_datasets,         &
                phez_current_group_get_num_linked_groups,           &
                phez_dataset_initialize,                            &
                phez_current_dataset_open,                          &
                phez_current_dataset_read,                          &
                phez_current_dataset_link_attribute,                &
                phez_current_dataset_link_file_space,               &
                phez_current_dataset_link_memory_space,             &
                phez_current_dataset_unlink_memory_space,           &
                phez_current_dataset_unlink_file_space,             &
                phez_current_dataset_unlink_attribute,              &
                phez_current_dataset_write,                         &
                phez_current_dataset_close,                         &
                phez_current_dataset_destroy,                       &
                phez_dataset_get_current,                           &
                phez_dataset_set_current,                           &
                phez_dataset_get_num,                               &
                phez_current_dataset_get_name,                      &
                phez_current_dataset_set_name,                      &
                phez_current_dataset_get_comment,                   &
                phez_current_dataset_set_comment,                   &
                phez_current_dataset_get_type,                      &
                phez_current_dataset_get_data,                      &
                phez_current_dataset_set_data,                      &
                phez_current_dataset_reset_access_properties,       &
                phez_current_dataset_default_access_properties,     &
                phez_current_dataset_reset_creation_properties,     &
                phez_current_dataset_default_creation_properties,   &
!                phez_current_dataset_default_transfer_properties,   &
                phez_current_dataset_get_num_groups_linking,        &
                phez_current_dataset_get_num_files_linking,         &
                phez_current_dataset_get_num_linked_attributes,     &
                phez_current_dataset_get_linked_file_space,         &
                phez_current_dataset_get_linked_memory_space,       &
                phez_attribute_initialize,                          &
                phez_current_attribute_open,                        &
                phez_current_attribute_read,                        &
                phez_current_attribute_link_space,                  &
                phez_current_attribute_unlink_space,                &
                phez_current_attribute_write,                       &
                phez_current_attribute_close,                       &
                phez_current_attribute_destroy,                     &
                phez_attribute_get_current,                         &
                phez_attribute_set_current,                         &
                phez_attribute_get_num,                             &
                phez_current_attribute_get_name,                    &
                phez_current_attribute_set_name,                    &
                phez_current_attribute_get_type,                    &
                phez_current_attribute_get_data,                    &
                phez_current_attribute_set_data,                    &
                phez_current_attribute_reset_creation_properties,   &
                phez_current_attribute_default_creation_properties, &
                phez_current_attribute_get_num_datasets_linking,    &
                phez_current_attribute_get_num_groups_linking,      &
                phez_current_attribute_get_num_files_linking,       &
                phez_current_attribute_get_linked_space,            &
                phez_space_initialize,                              &
                phez_current_space_open,                            &
                phez_current_space_close,                           &
                phez_current_space_destroy,                         &
                phez_space_get_current,                             &
                phez_space_set_current,                             &
                phez_space_get_num,                                 &
                phez_current_space_get_ptype,                       &
                phez_current_space_set_ptype,                       &
                phez_current_space_get_size,                        &
                phez_current_space_set_size,                        &
                phez_current_space_get_dims_now,                    &
                phez_current_space_set_dims_now,                    &
                phez_current_space_get_dims_max,                    &
                phez_current_space_set_dims_max,                    &
                phez_current_space_get_type,                        &
                phez_current_space_set_type,                        &
                phez_current_space_get_num_datasets_linking,        &
                phez_current_space_get_num_attributes_linking

contains


    subroutine fwrap_phez_context_start(this)
        implicit none
        type(phez_context), intent(out) :: this
        this%obj = C_phez_context_start()
    end subroutine fwrap_phez_context_start

    subroutine fwrap_phez_context_stop(this)
        implicit none
        type(phez_context), intent(inout) :: this
        call C_phez_context_stop(this%obj)
        this%obj = c_null_ptr
    end subroutine fwrap_phez_context_stop

!    subroutine fwrap_phez_populate(this, hash)
!        implicit none
!        type(phez_context), intent(in) :: this
!        character(len=*), intent(inout)  :: hash
!        call C_phez_populate(this%obj, phez_internal_as_c_string(hash))
!    end subroutine fwrap_phez_populate

    subroutine fwrap_phez_flush(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_flush(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_flush

!    subroutine fwrap_phez_close(this, hash)
!        implicit none
!        type(phez_context), intent(in) :: this
!        character(len=*), intent(inout), target  :: hash
!        call C_phez_close(this%obj, phez_internal_as_c_string(hash))
!    end subroutine fwrap_phez_close

!    subroutine fwrap_phez_forget(this, hash)
!        implicit none
!        type(phez_context), intent(in) :: this
!        character(len=*), intent(inout), target  :: hash
!        call C_phez_forget(this%obj, phez_internal_as_c_string(hash))
!    end subroutine fwrap_phez_forget

!    subroutine fwrap_phez_remove(this, hash)
!        implicit none
!        type(phez_context), intent(in) :: this
!        character(len=*), intent(inout), target  :: hash
!        call C_phez_remove(this%obj, phez_internal_as_c_string(hash))
!    end subroutine fwrap_phez_remove

!    subroutine fwrap_phez_populate_all(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_populate_all(this%obj)
!    end subroutine fwrap_phez_populate_all

    subroutine fwrap_phez_flush_all(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_flush_all(this%obj)
    end subroutine fwrap_phez_flush_all

!    subroutine fwrap_phez_close_all(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_close_all(this%obj)
!    end subroutine fwrap_phez_close_all

!    subroutine fwrap_phez_forget_all(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_forget_all(this%obj)
!    end subroutine fwrap_phez_forget_all

!    subroutine fwrap_phez_remove_all(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_remove_all(this%obj)
!    end subroutine fwrap_phez_remove_all

    function fwrap_phez_appear(this, hash) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=*),target                    :: hash
        character(len=:),allocatable        :: result_hash
        result_hash = phez_internal_get_string(C_phez_appear(this%obj, phez_internal_as_c_string(hash)))
    end function fwrap_phez_appear

    function fwrap_phez_extract(this, hash, otype, oname) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=*),target             :: hash
        integer(kind=c_int), intent(in)          :: otype
        character(len=*),target             :: oname
        character(len=:),allocatable        :: result_hash
        type(c_ptr) :: result_hash_ptr
        integer :: rhash_len

        rhash_len = len(hash)+phez_internal_get_hash_digits(this)
        allocate(character(len=rhash_len) :: result_hash)

        result_hash_ptr = C_phez_extract(this%obj,&
                                         phez_internal_as_c_string(hash),&
                                         otype,&
                                         phez_internal_as_c_string(oname))
        result_hash = phez_internal_get_string(result_hash_ptr)
    end function fwrap_phez_extract

    !******************** PHEZ convenience functions *************************/


    !************************ PHEZ file functions ****************************/

    !* Basic routines */
    function fwrap_phez_file_initialize(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_file_initialize(this%obj))
    end function fwrap_phez_file_initialize

    subroutine fwrap_phez_current_file_open(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_open(this%obj)
    end subroutine fwrap_phez_current_file_open

    function fwrap_phez_current_file_link_group(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_file_link_group(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_file_link_group

    function fwrap_phez_current_file_link_dataset(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_file_link_dataset(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_file_link_dataset

    function fwrap_phez_current_file_link_attribute(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_file_link_attribute(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_file_link_attribute

    subroutine fwrap_phez_current_file_unlink_attribute(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_file_unlink_attribute(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_file_unlink_attribute

    subroutine fwrap_phez_current_file_unlink_dataset(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_file_unlink_dataset(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_file_unlink_dataset

    subroutine fwrap_phez_current_file_unlink_group(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_file_unlink_group(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_file_unlink_group

    subroutine fwrap_phez_current_file_close(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_close(this%obj)
    end subroutine fwrap_phez_current_file_close

    subroutine fwrap_phez_current_file_destroy(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_destroy(this%obj)
    end subroutine fwrap_phez_current_file_destroy

    !* Set/get basic info */

    function fwrap_phez_file_get_current(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_current_file_get_name(this%obj))
    end function fwrap_phez_file_get_current

    subroutine fwrap_phez_file_set_current(this, hash)
        implicit none
        type(phez_context), intent(in)       :: this
        character(len=*), intent(in), target    :: hash

        if(hash .eq. "") then
            call C_phez_internal_file_set_current_to_null(this%obj)
        else
            call C_phez_file_set_current(this%obj, phez_internal_as_c_string(hash))
        endif
    end subroutine fwrap_phez_file_set_current

    function fwrap_phez_file_get_num(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_file_get_num(this%obj)
    end function fwrap_phez_file_get_num

    function fwrap_phez_current_file_get_name(this) result(fname)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: fname
        fname = phez_internal_get_string(C_phez_current_file_get_name(this%obj))
    end function fwrap_phez_current_file_get_name

    subroutine fwrap_phez_current_file_set_name(this, fname)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: fname
        call C_phez_current_file_set_name(this%obj, phez_internal_as_c_string(fname))
    end subroutine fwrap_phez_current_file_set_name

    function fwrap_phez_current_file_get_action(this) result(action)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int) :: action
        action = C_phez_current_file_get_action(this%obj)
    end function fwrap_phez_current_file_get_action

    subroutine fwrap_phez_current_file_set_action(this, action)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int), intent(in) :: action
        call C_phez_current_file_set_action(this%obj, action)
    end subroutine fwrap_phez_current_file_set_action

    !* Defend ourselves from wandering property lists */

    subroutine fwrap_phez_current_file_reset_access_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_reset_access_properties(this%obj)
    end subroutine fwrap_phez_current_file_reset_access_properties

    subroutine fwrap_phez_current_file_default_access_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_default_access_properties(this%obj)
    end subroutine fwrap_phez_current_file_default_access_properties

    subroutine fwrap_phez_current_file_access_from_memory(this, size_t, bool)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t), intent(in) :: size_t
        logical(kind=c_bool), intent(in)   :: bool
        call C_phez_current_file_access_from_memory(this%obj, size_t, bool)
    end subroutine fwrap_phez_current_file_access_from_memory

    subroutine fwrap_phez_current_file_reset_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_reset_creation_properties(this%obj)
    end subroutine fwrap_phez_current_file_reset_creation_properties

    subroutine fwrap_phez_current_file_default_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_file_default_creation_properties(this%obj)
    end subroutine fwrap_phez_current_file_default_creation_properties

    !* Outward links */

    function fwrap_phez_current_file_get_num_linked_attributes(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_file_get_num_linked_attributes(this%obj)
    end function fwrap_phez_current_file_get_num_linked_attributes

    function fwrap_phez_current_file_get_num_linked_datasets(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_file_get_num_linked_datasets(this%obj)
    end function fwrap_phez_current_file_get_num_linked_datasets

    function fwrap_phez_current_file_get_num_linked_groups(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_file_get_num_linked_groups(this%obj)
    end function fwrap_phez_current_file_get_num_linked_groups

    !************************ PHEZ file functions ****************************/


    !*********************** PHEZ group functions ****************************/

    !* Basic routines */
    function fwrap_phez_group_initialize(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_group_initialize(this%obj))
    end function fwrap_phez_group_initialize

    function fwrap_phez_current_group_open(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_group_open(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_group_open

    function fwrap_phez_current_group_link_group(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_group_link_group(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_group_link_group

    function fwrap_phez_current_group_link_dataset(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_group_link_dataset(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_group_link_dataset

    function fwrap_phez_current_group_link_attribute(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_group_link_attribute(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_group_link_attribute

    subroutine fwrap_phez_current_group_unlink_attribute(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_group_unlink_attribute(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_group_unlink_attribute

    subroutine fwrap_phez_current_group_unlink_dataset(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_group_unlink_dataset(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_group_unlink_dataset

    subroutine fwrap_phez_current_group_unlink_group(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_group_unlink_group(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_group_unlink_group

    subroutine fwrap_phez_current_group_close(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_group_close(this%obj)
    end subroutine fwrap_phez_current_group_close

    subroutine fwrap_phez_current_group_destroy(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_group_destroy(this%obj)
    end subroutine fwrap_phez_current_group_destroy

    !* Set/get basic info */

    function fwrap_phez_group_get_current(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_group_get_current(this%obj))
    end function fwrap_phez_group_get_current

    subroutine fwrap_phez_group_set_current(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash

        if(hash .eq. "") then
            call C_phez_internal_group_set_current_to_null(this%obj)
        else
            call C_phez_group_set_current(this%obj, phez_internal_as_c_string(hash))
        endif
    end subroutine fwrap_phez_group_set_current

    function fwrap_phez_group_get_num(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_group_get_num(this%obj)
    end function fwrap_phez_group_get_num

    function fwrap_phez_current_group_get_name(this) result(gname)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: gname
        gname = phez_internal_get_string(C_phez_current_group_get_name(this%obj))
    end function fwrap_phez_current_group_get_name

    subroutine fwrap_phez_current_group_set_name(this, gname)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: gname
        call C_phez_current_group_set_name(this%obj, phez_internal_as_c_string(gname))
    end subroutine fwrap_phez_current_group_set_name

    function fwrap_phez_current_group_get_comment(this) result(gcomment)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: gcomment
        gcomment = phez_internal_get_string(C_phez_current_group_get_comment(this%obj))
    end function fwrap_phez_current_group_get_comment

    subroutine fwrap_phez_current_group_set_comment(this, gcomment)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: gcomment
        call C_phez_current_group_set_comment(this%obj, phez_internal_as_c_string(gcomment))
    end subroutine fwrap_phez_current_group_set_comment

    !* Defend ourselves from wandering property lists */

!    subroutine fwrap_phez_current_group_default_access_properties(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_current_group_default_access_properties(this%obj)
!    end subroutine fwrap_phez_current_group_default_access_properties

    subroutine fwrap_phez_current_group_reset_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_group_reset_creation_properties(this%obj)
    end subroutine fwrap_phez_current_group_reset_creation_properties

    subroutine fwrap_phez_current_group_default_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_group_default_creation_properties(this%obj)
    end subroutine fwrap_phez_current_group_default_creation_properties

    !* Inward links */

    function fwrap_phez_current_group_get_num_groups_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_group_get_num_groups_linking(this%obj)
    end function fwrap_phez_current_group_get_num_groups_linking

    function fwrap_phez_current_group_get_num_files_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_group_get_num_files_linking(this%obj)
    end function fwrap_phez_current_group_get_num_files_linking

    !* Outward links */

    function fwrap_phez_current_group_get_num_linked_attributes(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_group_get_num_linked_attributes(this%obj)
    end function fwrap_phez_current_group_get_num_linked_attributes

    function fwrap_phez_current_group_get_num_linked_datasets(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_group_get_num_linked_datasets(this%obj)
    end function fwrap_phez_current_group_get_num_linked_datasets

    function fwrap_phez_current_group_get_num_linked_groups(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_group_get_num_linked_groups(this%obj)
    end function fwrap_phez_current_group_get_num_linked_groups

    !*********************** PHEZ group functions ****************************/


    !********************** PHEZ dataset functions ***************************/

    !* Basic routines */
    function fwrap_phez_dataset_initialize(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_dataset_initialize(this%obj))
    end function fwrap_phez_dataset_initialize

    function fwrap_phez_current_dataset_open(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_dataset_open(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_dataset_open

    subroutine fwrap_phez_current_dataset_read(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_read(this%obj)
    end subroutine fwrap_phez_current_dataset_read

    function fwrap_phez_current_dataset_link_attribute(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_dataset_link_attribute(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_dataset_link_attribute

    function fwrap_phez_current_dataset_link_file_space(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_dataset_link_file_space(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_dataset_link_file_space

    function fwrap_phez_current_dataset_link_memory_space(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_dataset_link_memory_space(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_dataset_link_memory_space

    subroutine fwrap_phez_current_dataset_unlink_memory_space(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_unlink_memory_space(this%obj)
    end subroutine fwrap_phez_current_dataset_unlink_memory_space

    subroutine fwrap_phez_current_dataset_unlink_file_space(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_unlink_file_space(this%obj)
    end subroutine fwrap_phez_current_dataset_unlink_file_space

    subroutine fwrap_phez_current_dataset_unlink_attribute(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash
        call C_phez_current_dataset_unlink_attribute(this%obj, phez_internal_as_c_string(hash))
    end subroutine fwrap_phez_current_dataset_unlink_attribute

    subroutine fwrap_phez_current_dataset_write(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_write(this%obj)
    end subroutine fwrap_phez_current_dataset_write

    subroutine fwrap_phez_current_dataset_close(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_close(this%obj)
    end subroutine fwrap_phez_current_dataset_close

    subroutine fwrap_phez_current_dataset_destroy(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_destroy(this%obj)
    end subroutine fwrap_phez_current_dataset_destroy

    !* Set/get basic info */

    function fwrap_phez_dataset_get_current(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_dataset_get_current(this%obj))
    end function fwrap_phez_dataset_get_current

    subroutine fwrap_phez_dataset_set_current(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash

        if(hash .eq. "") then
            call C_phez_internal_dataset_set_current_to_null(this%obj)
        else
            call C_phez_dataset_set_current(this%obj, phez_internal_as_c_string(hash))
        endif
    end subroutine fwrap_phez_dataset_set_current

    function fwrap_phez_dataset_get_num(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_dataset_get_num(this%obj)
    end function fwrap_phez_dataset_get_num

    function fwrap_phez_current_dataset_get_name(this) result(dname)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: dname
        dname = phez_internal_get_string(C_phez_current_dataset_get_name(this%obj))
    end function fwrap_phez_current_dataset_get_name

    subroutine fwrap_phez_current_dataset_set_name(this, dname)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: dname
        call C_phez_current_dataset_set_name(this%obj, phez_internal_as_c_string(dname))
    end subroutine fwrap_phez_current_dataset_set_name

    function fwrap_phez_current_dataset_get_comment(this) result(dcomment)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: dcomment
        dcomment = phez_internal_get_string(C_phez_current_dataset_get_comment(this%obj))
    end function fwrap_phez_current_dataset_get_comment

    subroutine fwrap_phez_current_dataset_set_comment(this, dcomment)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: dcomment
        call C_phez_current_dataset_set_comment(this%obj, phez_internal_as_c_string(dcomment))
    end subroutine fwrap_phez_current_dataset_set_comment

    function fwrap_phez_current_dataset_get_type(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int) :: size_t
        size_t = C_phez_current_dataset_get_type(this%obj)
    end function fwrap_phez_current_dataset_get_type

    subroutine fwrap_phez_current_dataset_get_data_bool_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_dataset_get_data_bool_1D

    subroutine fwrap_phez_current_dataset_get_data_bool_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_bool_2D

    subroutine fwrap_phez_current_dataset_get_data_bool_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_bool_3D

    subroutine fwrap_phez_current_dataset_get_data_bool_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_bool_4D

    subroutine fwrap_phez_current_dataset_get_data_bool_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_bool_5D

    subroutine fwrap_phez_current_dataset_set_data_bool_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:)
        call C_phez_current_dataset_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_bool_1D

    subroutine fwrap_phez_current_dataset_set_data_bool_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:)
        call C_phez_current_dataset_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_bool_2D

    subroutine fwrap_phez_current_dataset_set_data_bool_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:)
        call C_phez_current_dataset_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_bool_3D

    subroutine fwrap_phez_current_dataset_set_data_bool_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_dataset_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_bool_4D

    subroutine fwrap_phez_current_dataset_set_data_bool_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_dataset_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_bool_5D

    subroutine fwrap_phez_current_dataset_get_data_int_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:)
        integer(kind=c_int),pointer     :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_dataset_get_data_int_1D

    subroutine fwrap_phez_current_dataset_get_data_int_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_int_2D

    subroutine fwrap_phez_current_dataset_get_data_int_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_int_3D

    subroutine fwrap_phez_current_dataset_get_data_int_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_int_4D

    subroutine fwrap_phez_current_dataset_get_data_int_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_int_5D

    subroutine fwrap_phez_current_dataset_set_data_int_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:)
        call C_phez_current_dataset_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_int_1D

    subroutine fwrap_phez_current_dataset_set_data_int_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:)
        call C_phez_current_dataset_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_int_2D

    subroutine fwrap_phez_current_dataset_set_data_int_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:)
        call C_phez_current_dataset_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_int_3D

    subroutine fwrap_phez_current_dataset_set_data_int_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_dataset_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_int_4D

    subroutine fwrap_phez_current_dataset_set_data_int_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_dataset_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_int_5D

    subroutine fwrap_phez_current_dataset_get_data_float_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:)
        real(kind=c_float),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_dataset_get_data_float_1D

    subroutine fwrap_phez_current_dataset_get_data_float_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i1, i2)
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_float_2D

    subroutine fwrap_phez_current_dataset_get_data_float_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_float_3D

    subroutine fwrap_phez_current_dataset_get_data_float_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_float_4D

    subroutine fwrap_phez_current_dataset_get_data_float_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_float_5D

    subroutine fwrap_phez_current_dataset_set_data_float_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:)
        call C_phez_current_dataset_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_float_1D

    subroutine fwrap_phez_current_dataset_set_data_float_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:)
        call C_phez_current_dataset_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_float_2D

    subroutine fwrap_phez_current_dataset_set_data_float_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:)
        call C_phez_current_dataset_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_float_3D

    subroutine fwrap_phez_current_dataset_set_data_float_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_dataset_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_float_4D

    subroutine fwrap_phez_current_dataset_set_data_float_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_dataset_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_float_5D

    subroutine fwrap_phez_current_dataset_get_data_double_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:)
        real(kind=c_double),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data))  allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_dataset_get_data_double_1D

    subroutine fwrap_phez_current_dataset_get_data_double_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_double_2D

    subroutine fwrap_phez_current_dataset_get_data_double_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_double_3D

    subroutine fwrap_phez_current_dataset_get_data_double_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_double_4D

    subroutine fwrap_phez_current_dataset_get_data_double_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_dataset_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_dataset_get_data_double_5D

    subroutine fwrap_phez_current_dataset_set_data_double_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:)
        call C_phez_current_dataset_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_double_1D

    subroutine fwrap_phez_current_dataset_set_data_double_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:)
        call C_phez_current_dataset_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_double_2D

    subroutine fwrap_phez_current_dataset_set_data_double_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:)
        call C_phez_current_dataset_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_double_3D

    subroutine fwrap_phez_current_dataset_set_data_double_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_dataset_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_double_4D

    subroutine fwrap_phez_current_dataset_set_data_double_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_dataset_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_dataset_set_data_double_5D

    !subroutine fwrap_phez_current_dataset_get_data_string(this, data)
    !    implicit none
    !    type(phez_context), intent(in) :: this
    !    type(c_ptr) :: data
    !    data = C_phez_current_dataset_get_data_string(this%obj)
    !end subroutine fwrap_phez_current_dataset_get_data_string

    !subroutine fwrap_phez_current_dataset_set_data_string(this, data)
    !    implicit none
    !    type(phez_context), intent(in) :: this
    !    type(c_ptr), intent(in) :: data
    !    call C_phez_current_dataset_set_data_string(this%obj, data)
    !end subroutine fwrap_phez_current_dataset_set_data_string

    !* Defend ourselves from wandering property lists */

    subroutine fwrap_phez_current_dataset_reset_access_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_reset_access_properties(this%obj)
    end subroutine fwrap_phez_current_dataset_reset_access_properties

    subroutine fwrap_phez_current_dataset_default_access_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_default_access_properties(this%obj)
    end subroutine fwrap_phez_current_dataset_default_access_properties

    subroutine fwrap_phez_current_dataset_reset_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_reset_creation_properties(this%obj)
    end subroutine fwrap_phez_current_dataset_reset_creation_properties

    subroutine fwrap_phez_current_dataset_default_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_dataset_default_creation_properties(this%obj)
    end subroutine fwrap_phez_current_dataset_default_creation_properties

!    subroutine fwrap_phez_current_dataset_default_transfer_properties(this)
!        implicit none
!        type(phez_context), intent(in) :: this
!        call C_phez_current_dataset_default_transfer_properties(this%obj)
!    end subroutine fwrap_phez_current_dataset_default_transfer_properties

    !* Inward links */

    function fwrap_phez_current_dataset_get_num_groups_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_dataset_get_num_groups_linking(this%obj)
    end function fwrap_phez_current_dataset_get_num_groups_linking

    function fwrap_phez_current_dataset_get_num_files_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_dataset_get_num_files_linking(this%obj)
    end function fwrap_phez_current_dataset_get_num_files_linking

    !* Outward links */

    function fwrap_phez_current_dataset_get_num_linked_attributes(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_dataset_get_num_linked_attributes(this%obj)
    end function fwrap_phez_current_dataset_get_num_linked_attributes

    function fwrap_phez_current_dataset_get_linked_file_space(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_current_dataset_get_linked_file_space(this%obj))
    end function fwrap_phez_current_dataset_get_linked_file_space

    function fwrap_phez_current_dataset_get_linked_memory_space(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_current_dataset_get_linked_memory_space(this%obj))
    end function fwrap_phez_current_dataset_get_linked_memory_space

    !********************** PHEZ dataset functions ***************************/



    !********************* PHEZ attribute functions **************************/

    !* Basic routines */
    function fwrap_phez_attribute_initialize(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_attribute_initialize(this%obj))
    end function fwrap_phez_attribute_initialize

    function fwrap_phez_current_attribute_open(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_attribute_open(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_attribute_open

    subroutine fwrap_phez_current_attribute_read(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_read(this%obj)
    end subroutine fwrap_phez_current_attribute_read

    function fwrap_phez_current_attribute_link_space(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_attribute_link_space(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_attribute_link_space

    subroutine fwrap_phez_current_attribute_unlink_space(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_unlink_space(this%obj)
    end subroutine fwrap_phez_current_attribute_unlink_space

    subroutine fwrap_phez_current_attribute_write(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_write(this%obj)
    end subroutine fwrap_phez_current_attribute_write

    subroutine fwrap_phez_current_attribute_close(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_close(this%obj)
    end subroutine fwrap_phez_current_attribute_close

    subroutine fwrap_phez_current_attribute_destroy(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_destroy(this%obj)
    end subroutine fwrap_phez_current_attribute_destroy

    !* Set/get basic info */

    function fwrap_phez_attribute_get_current(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_attribute_get_current(this%obj))
    end function fwrap_phez_attribute_get_current

    subroutine fwrap_phez_attribute_set_current(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash

        if(hash .eq. "") then
            call C_phez_internal_attribute_set_current_to_null(this%obj)
        else
            call C_phez_attribute_set_current(this%obj, phez_internal_as_c_string(hash))
        endif
    end subroutine fwrap_phez_attribute_set_current

    function fwrap_phez_attribute_get_num(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_attribute_get_num(this%obj)
    end function fwrap_phez_attribute_get_num

    function fwrap_phez_current_attribute_get_name(this) result(aname)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: aname
        aname = phez_internal_get_string(C_phez_current_attribute_get_name(this%obj))
    end function fwrap_phez_current_attribute_get_name

    subroutine fwrap_phez_current_attribute_set_name(this, aname)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: aname
        call C_phez_current_attribute_set_name(this%obj, phez_internal_as_c_string(aname))
    end subroutine fwrap_phez_current_attribute_set_name

    function fwrap_phez_current_attribute_get_type(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int) :: size_t
        size_t = C_phez_current_attribute_get_type(this%obj)
    end function fwrap_phez_current_attribute_get_type

    subroutine fwrap_phez_current_attribute_get_data_bool_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_attribute_get_data_bool_1D

    subroutine fwrap_phez_current_attribute_get_data_bool_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_bool_2D

    subroutine fwrap_phez_current_attribute_get_data_bool_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_bool_3D

    subroutine fwrap_phez_current_attribute_get_data_bool_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_bool_4D

    subroutine fwrap_phez_current_attribute_get_data_bool_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        logical(kind=c_bool),allocatable  :: data(:,:,:,:,:)
        logical(kind=c_bool),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "bool")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_bool_5D

    subroutine fwrap_phez_current_attribute_set_data_bool_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:)
        call C_phez_current_attribute_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_bool_1D

    subroutine fwrap_phez_current_attribute_set_data_bool_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:)
        call C_phez_current_attribute_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_bool_2D

    subroutine fwrap_phez_current_attribute_set_data_bool_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:)
        call C_phez_current_attribute_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_bool_3D

    subroutine fwrap_phez_current_attribute_set_data_bool_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_attribute_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_bool_4D

    subroutine fwrap_phez_current_attribute_set_data_bool_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        logical(kind=c_bool),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_attribute_set_data_bool(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_bool_5D

    subroutine fwrap_phez_current_attribute_get_data_int_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:)
        integer(kind=c_int),pointer     :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_attribute_get_data_int_1D

    subroutine fwrap_phez_current_attribute_get_data_int_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_int_2D

    subroutine fwrap_phez_current_attribute_get_data_int_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_int_3D

    subroutine fwrap_phez_current_attribute_get_data_int_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_int_4D

    subroutine fwrap_phez_current_attribute_get_data_int_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        integer(kind=c_int),allocatable :: data(:,:,:,:,:)
        integer(kind=c_int),pointer     :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "integer")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_int_5D

    subroutine fwrap_phez_current_attribute_set_data_int_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:)
        call C_phez_current_attribute_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_int_1D

    subroutine fwrap_phez_current_attribute_set_data_int_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:)
        call C_phez_current_attribute_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_int_2D

    subroutine fwrap_phez_current_attribute_set_data_int_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:)
        call C_phez_current_attribute_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_int_3D

    subroutine fwrap_phez_current_attribute_set_data_int_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_attribute_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_int_4D

    subroutine fwrap_phez_current_attribute_set_data_int_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_attribute_set_data_int(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_int_5D

    subroutine fwrap_phez_current_attribute_get_data_float_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:)
        real(kind=c_float),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_attribute_get_data_float_1D

    subroutine fwrap_phez_current_attribute_get_data_float_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i1, i2)
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_float_2D

    subroutine fwrap_phez_current_attribute_get_data_float_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_float_3D

    subroutine fwrap_phez_current_attribute_get_data_float_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_float_4D

    subroutine fwrap_phez_current_attribute_get_data_float_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_float),allocatable  :: data(:,:,:,:,:)
        real(kind=c_float),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "float")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_float_5D

    subroutine fwrap_phez_current_attribute_set_data_float_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:)
        call C_phez_current_attribute_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_float_1D

    subroutine fwrap_phez_current_attribute_set_data_float_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:)
        call C_phez_current_attribute_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_float_2D

    subroutine fwrap_phez_current_attribute_set_data_float_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:)
        call C_phez_current_attribute_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_float_3D

    subroutine fwrap_phez_current_attribute_set_data_float_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_attribute_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_float_4D

    subroutine fwrap_phez_current_attribute_set_data_float_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_float),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_attribute_set_data_float(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_float_5D

    subroutine fwrap_phez_current_attribute_get_data_double_1D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:)
        real(kind=c_double),pointer      :: data_f_ptr(:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims)

        do i1 = 1,dims(1)
            data(i1) = data_f_ptr(i1)
        end do

    end subroutine fwrap_phez_current_attribute_get_data_double_1D

    subroutine fwrap_phez_current_attribute_get_data_double_2D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
            data(i1, i2) = data_f_ptr(i2, i1)
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_double_2D

    subroutine fwrap_phez_current_attribute_get_data_double_3D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
            data(i1, i2, i3) = data_f_ptr(i3, i2, i1)
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_double_3D

    subroutine fwrap_phez_current_attribute_get_data_double_4D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
            data(i1, i2, i3, i4) = data_f_ptr(i4, i3, i2, i1)
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_double_4D

    subroutine fwrap_phez_current_attribute_get_data_double_5D(this, data)
        implicit none
        type(phez_context), intent(in)   :: this
        integer                         :: ndims
        integer,allocatable             :: dims(:)
        real(kind=c_double),allocatable  :: data(:,:,:,:,:)
        real(kind=c_double),pointer      :: data_f_ptr(:,:,:,:,:)
        type(c_ptr)                     :: data_c_ptr
        integer                         :: i1, i2, i3, i4, i5

        data_c_ptr = phez_internal_attribute_get_data_c_ptr(this, ndims, dims, "double")
        if(.not. allocated(data)) allocate(data(dims(1),dims(2),dims(3),dims(4),dims(5)))
        call c_f_pointer(data_c_ptr, data_f_ptr, dims(ndims:1:-1))

        do i1 = 1,dims(1)
        do i2 = 1,dims(2)
        do i3 = 1,dims(3)
        do i4 = 1,dims(4)
        do i5 = 1,dims(5)
            data(i1, i2, i3, i4, i5) = data_f_ptr(i5, i4, i3, i2, i1)
        end do
        end do
        end do
        end do
        end do

    end subroutine fwrap_phez_current_attribute_get_data_double_5D

    subroutine fwrap_phez_current_attribute_set_data_double_1D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:)
        call C_phez_current_attribute_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_double_1D

    subroutine fwrap_phez_current_attribute_set_data_double_2D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:)
        call C_phez_current_attribute_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_double_2D

    subroutine fwrap_phez_current_attribute_set_data_double_3D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:)
        call C_phez_current_attribute_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_double_3D

    subroutine fwrap_phez_current_attribute_set_data_double_4D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:,:)
        call C_phez_current_attribute_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_double_4D

    subroutine fwrap_phez_current_attribute_set_data_double_5D(this, data)
        implicit none
        type(phez_context), intent(in) :: this
        real(kind=c_double),intent(in),target     :: data(:,:,:,:,:)
        call C_phez_current_attribute_set_data_double(this%obj, data)
    end subroutine fwrap_phez_current_attribute_set_data_double_5D

    !subroutine fwrap_phez_current_attribute_get_data_string(this, data)
    !    implicit none
    !    type(phez_context), intent(in) :: this
    !    type(c_ptr) :: data
    !    data = C_phez_current_attribute_get_data_string(this%obj)
    !end subroutine fwrap_phez_current_attribute_get_data_string

    !subroutine fwrap_phez_current_attribute_set_data_string(this, data)
    !    implicit none
    !    type(phez_context), intent(in) :: this
    !    type(c_ptr), intent(in) :: data
    !    call C_phez_current_attribute_set_data_string(this%obj, data)
    !end subroutine fwrap_phez_current_attribute_set_data_string

    !* Defend ourselves from wandering property lists */

    subroutine fwrap_phez_current_attribute_reset_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_reset_creation_properties(this%obj)
    end subroutine fwrap_phez_current_attribute_reset_creation_properties

    subroutine fwrap_phez_current_attribute_default_creation_properties(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_attribute_default_creation_properties(this%obj)
    end subroutine fwrap_phez_current_attribute_default_creation_properties

    !* Inward links */

    function fwrap_phez_current_attribute_get_num_datasets_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_attribute_get_num_datasets_linking(this%obj)
    end function fwrap_phez_current_attribute_get_num_datasets_linking

    function fwrap_phez_current_attribute_get_num_groups_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_attribute_get_num_groups_linking(this%obj)
    end function fwrap_phez_current_attribute_get_num_groups_linking

    function fwrap_phez_current_attribute_get_num_files_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_attribute_get_num_files_linking(this%obj)
    end function fwrap_phez_current_attribute_get_num_files_linking

    function fwrap_phez_current_attribute_get_linked_space(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_current_attribute_get_linked_space(this%obj))
    end function fwrap_phez_current_attribute_get_linked_space

    !********************* PHEZ attribute functions **************************/



    !*********************** PHEZ space functions ****************************/

    !* Basic routines */

    function fwrap_phez_space_initialize(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_space_initialize(this%obj))
    end function fwrap_phez_space_initialize

    function fwrap_phez_current_space_open(this, hash_in) result(hash_out)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash_in
        character(len=:), allocatable  :: hash_out
        hash_out = phez_internal_get_string(C_phez_current_space_open(this%obj, phez_internal_as_c_string(hash_in)))
    end function fwrap_phez_current_space_open

    subroutine fwrap_phez_current_space_close(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_space_close(this%obj)
    end subroutine fwrap_phez_current_space_close

    subroutine fwrap_phez_current_space_destroy(this)
        implicit none
        type(phez_context), intent(in) :: this
        call C_phez_current_space_destroy(this%obj)
    end subroutine fwrap_phez_current_space_destroy

    !* Set/get basic info */

    function fwrap_phez_space_get_current(this) result(result_hash)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=:),allocatable  :: result_hash
        result_hash = phez_internal_get_string(C_phez_space_get_current(this%obj))
    end function fwrap_phez_space_get_current

    subroutine fwrap_phez_space_set_current(this, hash)
        implicit none
        type(phez_context), intent(in) :: this
        character(len=*), intent(inout), target  :: hash

        if(hash .eq. "") then
            call C_phez_internal_space_set_current_to_null(this%obj)
        else
            call C_phez_space_set_current(this%obj, phez_internal_as_c_string(hash))
        endif
    end subroutine fwrap_phez_space_set_current

    function fwrap_phez_space_get_num(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_space_get_num(this%obj)
    end function fwrap_phez_space_get_num

    function fwrap_phez_current_space_get_ptype(this) result(ptype)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int) :: ptype
        ptype = C_phez_current_space_get_ptype(this%obj)
    end function fwrap_phez_current_space_get_ptype

    subroutine fwrap_phez_current_space_set_ptype(this, ptype)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_int), intent(in) :: ptype
        call C_phez_current_space_set_ptype(this%obj, ptype)
    end subroutine fwrap_phez_current_space_set_ptype

    function fwrap_phez_current_space_get_size(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_space_get_size(this%obj)
    end function fwrap_phez_current_space_get_size

    subroutine fwrap_phez_current_space_set_size(this, ssize)
        implicit none
        type(phez_context), intent(in) :: this
        integer, intent(in) :: ssize
        integer(kind=c_size_t) :: ssize_t
        ssize_t = ssize
        call C_phez_current_space_set_size(this%obj, ssize_t)
    end subroutine fwrap_phez_current_space_set_size

    function fwrap_phez_current_space_get_dims_now(this) result(dims)
        implicit none
        type(phez_context), intent(in)   :: this
        integer(kind=c_size_t),allocatable,target          :: dims(:)
        integer(kind=c_size_t),pointer                     :: dims_f_ptr(:)
        type(c_ptr)                         :: dims_c_ptr
        integer                             :: ndims
        integer :: i

        ndims = fwrap_phez_current_space_get_size(this)
        allocate(dims(ndims))
        dims_c_ptr = C_phez_current_space_get_dims_now(this%obj)
        dims_f_ptr => NULL()
        call c_f_pointer(dims_c_ptr, dims_f_ptr, [ndims])
        do i = 1,ndims
            dims(i) = dims_f_ptr(i)
        end do

    end function fwrap_phez_current_space_get_dims_now

    subroutine fwrap_phez_current_space_set_dims_now(this, dims)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t),intent(in),target :: dims(:)
        call C_phez_current_space_set_dims_now(this%obj, dims)
    end subroutine fwrap_phez_current_space_set_dims_now

    function fwrap_phez_current_space_get_dims_max(this) result(dims)
        implicit none
        type(phez_context), intent(in)   :: this
        integer(kind=c_size_t),allocatable,target          :: dims(:)
        integer(kind=c_size_t),pointer                     :: dims_f_ptr(:)
        type(c_ptr)                         :: dims_c_ptr
        integer                             :: ndims
        integer :: i

        ndims = fwrap_phez_current_space_get_size(this)
        allocate(dims(ndims))
        dims_c_ptr = C_phez_current_space_get_dims_max(this%obj)
        dims_f_ptr => NULL()
        call c_f_pointer(dims_c_ptr, dims_f_ptr, [ndims])
        do i = 1,ndims
            dims(i) = dims_f_ptr(i)
        end do

    end function fwrap_phez_current_space_get_dims_max

    subroutine fwrap_phez_current_space_set_dims_max(this, dims)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t),intent(in),target :: dims(:)
        call C_phez_current_space_set_dims_max(this%obj, dims)
    end subroutine fwrap_phez_current_space_set_dims_max

    function fwrap_phez_current_space_get_type(this) result(phez_h5s_type_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(c_int) :: phez_h5s_type_t
        phez_h5s_type_t = C_phez_current_space_get_type(this%obj)
    end function fwrap_phez_current_space_get_type

    subroutine fwrap_phez_current_space_set_type(this, phez_h5s_type_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(c_int), intent(in) :: phez_h5s_type_t
        call C_phez_current_space_set_type(this%obj, phez_h5s_type_t)
    end subroutine fwrap_phez_current_space_set_type

    !* Inward links */

    function fwrap_phez_current_space_get_num_datasets_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_space_get_num_datasets_linking(this%obj)
    end function fwrap_phez_current_space_get_num_datasets_linking

    function fwrap_phez_current_space_get_num_attributes_linking(this) result(size_t)
        implicit none
        type(phez_context), intent(in) :: this
        integer(kind=c_size_t) :: size_t
        size_t = C_phez_current_space_get_num_attributes_linking(this%obj)
    end function fwrap_phez_current_space_get_num_attributes_linking

    !*********************** PHEZ etc functions ******************************/

    function phez_internal_get_hash_digits(this) result(hash_digits)
        implicit none
        type(phez_context), intent(in)   :: this
        integer(kind=c_size_t) :: hash_digits_c
        integer :: hash_digits
        hash_digits_c = C_phez_internal_get_hash_digits(this%obj)
        hash_digits = hash_digits_c
    end function phez_internal_get_hash_digits

    function phez_internal_get_string(cstring_c_ptr) result(fstring)
        implicit none
        type(c_ptr)                                         :: cstring_c_ptr
        integer(kind=c_size_t)                              :: cstring_len
        character(kind=c_char,len=1),dimension(:),pointer   :: cstring_f_ptr
        character(len=:),allocatable                        :: fstring
        integer                                             :: i

        if(c_associated(cstring_c_ptr)) then
            cstring_len = C_phez_internal_get_string_length(cstring_c_ptr)
            !print *, cstring_len
            call c_f_pointer(cstring_c_ptr,cstring_f_ptr,[cstring_len])
            allocate(character(len=cstring_len) :: fstring)

            do i = 1, cstring_len
                fstring(i:i) = cstring_f_ptr(i)
            end do

            cstring_c_ptr = c_null_ptr
            cstring_f_ptr => NULL()
        else
            fstring = ""
        endif

    end function phez_internal_get_string

!    function phez_internal_get_dims(carray_c_ptr) result(farray)
!        implicit none
!        type(c_ptr)                                         :: carray_c_ptr
!        integer(kind=c_size_t)                                   :: carray_len
!        integer(kind=c_int),dimension(:),pointer            :: carray_f_ptr
!        integer,dimension(:),allocatable                    :: farray
!        integer                                             :: i
!
!        if(c_associated(carray_c_ptr)) then
!            carray_len = C_phez_internal_get_string_length(carray_c_ptr)
!            call c_f_pointer(carray_c_ptr,carray_f_ptr,[carray_len])
!            allocate(farray(carray_len))
!
!            do i = 1, carray_len
!                farray(i:i) = carray_f_ptr(i)
!            end do
!
!            carray_c_ptr = c_null_ptr
!            carray_f_ptr => NULL()
!        else
!            !fatal
!        endif
!
!    end function phez_internal_get_dims

    function phez_internal_as_c_string(fstring) result(cstring)
        implicit none
        character(len=*), intent(in)   :: fstring
        integer                                             :: fstring_len
        character(len=:,kind=c_char),allocatable, target    :: cstring
        integer                                             :: i

        if(fstring .eq. "") then
            allocate(character(len=1) :: cstring)
            cstring = c_null_char
        else
            fstring_len = len(fstring)
            allocate(character(len=fstring_len+1) :: cstring)
            do i = 1, fstring_len
                cstring(i:i) = fstring(i:i)
            end do
            cstring(i:i) = c_null_char
        end if

    end function phez_internal_as_c_string

    function phez_internal_attribute_get_data_c_ptr(this, ndims, dims, type) result(data_c_ptr)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=*), intent(in)        :: type
        character(len=:),allocatable        :: curra_hash
        character(len=:),allocatable        :: currs_hash
        character(len=:),allocatable        :: space_hash
        integer, intent(inout)              :: ndims
        integer,allocatable, intent(inout)  :: dims(:)
        type(c_ptr)                         :: data_c_ptr
        integer :: i

        currs_hash = fwrap_phez_space_get_current(this)
        curra_hash = fwrap_phez_attribute_get_current(this)
        space_hash = fwrap_phez_current_attribute_get_linked_space(this)
        call fwrap_phez_space_set_current(this, space_hash)
        ndims = fwrap_phez_current_space_get_size(this)
        dims = fwrap_phez_current_space_get_dims_now(this)

        if(type .eq. "bool") then
            data_c_ptr = C_phez_current_attribute_get_data_bool(this%obj)
        else if(type .eq. "integer") then
            data_c_ptr = C_phez_current_attribute_get_data_int(this%obj)
        else if(type .eq. "float") then
            data_c_ptr = C_phez_current_attribute_get_data_float(this%obj)
        else if(type .eq. "double") then
            data_c_ptr = C_phez_current_attribute_get_data_double(this%obj)
        !else if(type .eq. "string") then
        !    data_c_ptr = C_phez_current_attribute_get_data_string(this%obj)
        else
            print *, "womp womp"
        end if

        call fwrap_phez_space_set_current(this, currs_hash)

    end function phez_internal_attribute_get_data_c_ptr

    function phez_internal_dataset_get_data_c_ptr(this, ndims, dims, type) result(data_c_ptr)
        implicit none
        type(phez_context), intent(in)   :: this
        character(len=*), intent(in)        :: type
        character(len=:),allocatable        :: currd_hash
        character(len=:),allocatable        :: currs_hash
        character(len=:),allocatable        :: space_hash
        integer, intent(inout)              :: ndims
        integer,allocatable, intent(inout)  :: dims(:)
        type(c_ptr)                         :: data_c_ptr

        currs_hash = fwrap_phez_space_get_current(this)
        currd_hash = fwrap_phez_dataset_get_current(this)
        space_hash = fwrap_phez_current_dataset_get_linked_file_space(this)
        call fwrap_phez_space_set_current(this, space_hash)
        ndims = fwrap_phez_current_space_get_size(this)
        dims = fwrap_phez_current_space_get_dims_now(this)

        if(type .eq. "bool") then
            data_c_ptr = C_phez_current_dataset_get_data_bool(this%obj)
        else if(type .eq. "integer") then
            data_c_ptr = C_phez_current_dataset_get_data_int(this%obj)
        else if(type .eq. "float") then
            data_c_ptr = C_phez_current_dataset_get_data_float(this%obj)
        else if(type .eq. "double") then
            data_c_ptr = C_phez_current_dataset_get_data_double(this%obj)
        !else if(type .eq. "string") then
        !    data_c_ptr = C_phez_current_dataset_get_data_string(this%obj)
        else
            print *, "womp womp"
        end if

        call fwrap_phez_space_set_current(this, currs_hash)

    end function phez_internal_dataset_get_data_c_ptr



end module phez_f
