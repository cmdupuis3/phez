
#include "phez_fwrappers.hpp"

phez_hash_t* phez_current_dataset_get_linked_file_space(phez_context* context){
    return(cwrap_phez_current_dataset_get_linked_file_space(context));
}
phez_hash_t* phez_current_dataset_get_linked_memory_space(phez_context* context){
    return(cwrap_phez_current_dataset_get_linked_memory_space(context));
}
phez_hash_t* phez_current_attribute_get_linked_space(phez_context* context){
    return(cwrap_phez_current_attribute_get_linked_space(context));
}
size_t phez_internal_get_string_length(void* string_in){
    return(strlen((char*)string_in));
}
size_t phez_internal_get_hash_digits(phez_context* context){
    return(cwrap_phez_internal_get_hash_digits(context));
}

void phez_internal_file_set_current_to_null(phez_context* context){
	cwrap_phez_internal_file_set_current_to_null(context);
	return;
}
void phez_internal_group_set_current_to_null(phez_context* context){
	cwrap_phez_internal_group_set_current_to_null(context);
	return;
}
void phez_internal_dataset_set_current_to_null(phez_context* context){
	cwrap_phez_internal_dataset_set_current_to_null(context);
	return;
}
void phez_internal_attribute_set_current_to_null(phez_context* context){
	cwrap_phez_internal_attribute_set_current_to_null(context);
	return;
}
void phez_internal_space_set_current_to_null(phez_context* context){
	cwrap_phez_internal_space_set_current_to_null(context);
	return;
}
