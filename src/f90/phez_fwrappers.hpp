
#ifndef SET_PHEZ_FWRAPPERS_H_
#define SET_PHEZ_FWRAPPERS_H_


#include <cstring>
#include "../phez_cwrappers.hpp"

extern "C" {

    phez_hash_t* phez_current_dataset_get_linked_file_space(phez_context*);
    phez_hash_t* phez_current_dataset_get_linked_memory_space(phez_context*);
    phez_hash_t* phez_current_attribute_get_linked_space(phez_context*);

    size_t phez_internal_get_string_length(void*);
    size_t phez_internal_get_hash_digits(phez_context*);

    void phez_internal_file_set_current_to_null(phez_context*);
    void phez_internal_group_set_current_to_null(phez_context*);
    void phez_internal_dataset_set_current_to_null(phez_context*);
    void phez_internal_attribute_set_current_to_null(phez_context*);
    void phez_internal_space_set_current_to_null(phez_context*);

}

#endif
