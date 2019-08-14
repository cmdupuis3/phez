#ifndef SET_PHEZ_FILE_T_API_H_
#define SET_PHEZ_FILE_T_API_H_

// From debug.h...
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <hdf5.h>
#include "phez_types.hpp"
#include "phez_macros.hpp"

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

class hdf5_files {

    public:
        // constructor
        hdf5_files();
        // destructor
        ~hdf5_files();

        // internal API
        phez_file_t* initialize(); // initialize new file_t struct
        void open();
        void make();

        void link_group(phez_group_t*);
        void link_dataset(phez_dataset_t*);
        void link_attribute(phez_attribute_t*);

        void unlink_attribute(phez_attribute_t*);
        void unlink_dataset(phez_dataset_t*);
        void unlink_group(phez_group_t*);
        void close(); // (call close() on all open files in destructor)
        void destroy(); // destroy a file_t struct

        phez_file_t* lookup_by_name(char*);
        phez_file_t* lookup_by_id(hid_t);

        // accessors and mutators
        phez_file_t* get_current();
        void set_current(phez_file_t*);
        size_t get_num();
        void set_num(size_t);
        void incr_num();
        void decr_num();
        hid_t get_current_id();
        void set_current_id(hid_t);
        char* get_current_name();
        void set_current_name(char*);
        phez_file_action_t get_current_action();
        void set_current_action(phez_file_action_t);
        phez_file_state_t get_current_state();

        // Property lists
        fapl_t get_current_access_properties();
        void set_current_access_properties(fapl_t);
        void reset_current_access_properties();
        void default_current_access_properties();

        void access_current_from_memory(size_t, bool);
        //void access_current_from_disk(size_t, size_t, size_t);

        fcpl_t get_current_creation_properties();
        void set_current_creation_properties(fcpl_t);
        void reset_current_creation_properties();
        void default_current_creation_properties();

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

        phez_file_t*** get_file_list();

    private:
        void set_current_state(phez_file_state_t);
        bool get_current_is_name_defined();
        void set_current_is_name_defined(bool);
        bool get_current_is_action_defined();
        void set_current_is_action_defined(bool);

        void check_current_state_can_open();
        void check_current_state_can_make();
        void check_current_state_can_close();
        void update_current_state_opened();
        void update_current_state_made();
        void update_current_state_closed();

        size_t num_files;
        //char*** file_names;
        phez_file_t*** file_list;
        phez_file_t* current_file;
};

#endif

