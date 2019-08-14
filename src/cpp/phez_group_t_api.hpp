#ifndef SET_PHEZ_GROUP_T_API_H_
#define SET_PHEZ_GROUP_T_API_H_

// From debug.h...
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "phez_types.hpp"

using std::cout;

/************************* HDF5 subclass notes ********************************/
//
//  All HDF5 subclass routines act on the current_... variable, set this pointer
//  to the correct address before calling a routine!
//
//  e.g.,
//      context.hdf5.file.set_current(context.hdf5.file_list[10]);
//      context.hdf5.file.remove();
//
/******************************************************************************/

class hdf5_groups {

    public:
        // constructor
        hdf5_groups();
        // destructor
        ~hdf5_groups();

        // internal API
        phez_group_t* initialize();
        void open(hid_t);
        void make(hid_t);

        //void read();
        void link_group(phez_group_t*);
        void link_dataset(phez_dataset_t*);
        void link_attribute(phez_attribute_t*);

        void unlink_attribute(phez_attribute_t*);
        void unlink_dataset(phez_dataset_t*);
        void unlink_group(phez_group_t*);
        //void write();

        void close();
        void destroy();

        phez_group_t* lookup_by_name(char*);
        phez_group_t* lookup_by_id(hid_t);

        // accessors and mutators
        phez_group_t *get_current();
        void set_current(phez_group_t*);
        size_t get_num();
        void set_num(size_t);
        void incr_num();
        void decr_num();
        hid_t get_current_id();
        void set_current_id(hid_t);
        char* get_current_name();
        void set_current_name(char*);
        char* get_current_comment();
        void set_current_comment(char*);
        phez_group_state_t get_current_state();

        // Property lists
        gapl_t get_current_access_properties();
        void set_current_access_properties(gapl_t);
        void default_current_access_properties();

        gcpl_t get_current_creation_properties();
        void set_current_creation_properties(gcpl_t);
        void reset_current_creation_properties();
        void default_current_creation_properties();

        // Inward links
        size_t get_current_num_groups_linking();
        void set_current_num_groups_linking(size_t);
        size_t get_current_num_files_linking();
        void set_current_num_files_linking(size_t);

        void incr_current_num_groups_linking();
        void decr_current_num_groups_linking();
        void incr_current_num_files_linking();
        void decr_current_num_files_linking();

        // Outward links
        size_t get_current_num_linked_attributes();
        void set_current_num_linked_attributes(size_t);
        void incr_current_num_linked_attributes();
        void decr_current_num_linked_attributes();

        size_t get_current_num_linked_datasets();
        void set_current_num_linked_datasets(size_t);
        void incr_current_num_linked_datasets();
        void decr_current_num_linked_datasets();

        size_t get_current_num_linked_groups();
        void set_current_num_linked_groups(size_t);
        void incr_current_num_linked_groups();
        void decr_current_num_linked_groups();

        phez_attribute_t*** get_current_linked_attributes();
        phez_dataset_t*** get_current_linked_datasets();
        phez_group_t*** get_current_linked_groups();

        phez_group_t*** get_group_list();
        
    private:

        void set_current_state(phez_group_state_t);
        bool get_current_is_name_defined();
        void set_current_is_name_defined(bool);

        void check_current_state_can_open();
        void check_current_state_can_make();
        void check_current_state_can_write();
        void check_current_state_can_close();
        void update_current_state_opened();
        void update_current_state_made();
        // don't need written state
        void update_current_state_closed();

        size_t num_groups;
        char** group_names;
        phez_group_t*** group_list;
        phez_group_t* current_group;
};

#endif

