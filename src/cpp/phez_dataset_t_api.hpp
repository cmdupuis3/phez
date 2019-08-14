#ifndef SET_PHEZ_DATASET_T_API_H_
#define SET_PHEZ_DATASET_T_API_H_

// From debug.h...
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <hdf5.h>

#include "phez_types.hpp"
#include "phez_errmacros.hpp"

using std::cout;

/************************* HDF5 subclass notes ********************************/
//
//  All HDF5 subclass routines act on the current_... variable, set this pointer
//  to the correct address before calling a routine!
//
//  e.g.,
//      context.hdf5.file.set_current_file(context.hdf5.file_list[10]);
//      context.hdf5.file.remove();
//
/******************************************************************************/

class hdf5_datasets {

    public:
        // constructor
        hdf5_datasets();
        // destructor
        ~hdf5_datasets();

        // internal API
        phez_dataset_t* initialize();
        void open(hid_t);
        void make(hid_t);

        void read();
        void link_attribute(phez_attribute_t*);
        void link_file_space(phez_space_t*);
        void link_memory_space(phez_space_t*);
        void unlink_memory_space();
        void unlink_file_space();
        void unlink_attribute(phez_attribute_t*);
        void write();

        void close();
        void destroy();

        phez_dataset_t* lookup_by_name(char*);
        phez_dataset_t* lookup_by_id(hid_t);

        // accessors and mutators
        phez_dataset_t* get_current();
        void set_current(phez_dataset_t*);
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
        phez_dataset_type_t get_current_type();
        void set_current_type(phez_dataset_type_t);
        phez_dataset_state_t get_current_state();

        nullptr_t* get_current_data();     // apparently templates don't generate
        void set_current_data(nullptr_t*); // nullptr_t functions... go figure.
        /** \brief Get the data of the dataset that hdf5_datasets is currently pointing to. */
        template<typename T> T* get_current_data(){

            if(!this->get_current_is_data_defined()){
                if(this->get_current()->data){
                    PHEZ_FATAL_PREFIX
                    cout << "Cannot retrieve current dataset data because it is not defined." << endl;
                    PHEZ_FATAL_SUFFIX
                }
            }

            return((T*)this->get_current()->data);
        }
        /** \brief Set the data of the dataset that hdf5_datasets is currently pointing to.*/
        template<typename T> void set_current_data(T* data_in){
            this->get_current()->data = (void*)data_in;
            this->set_current_is_data_defined(true);
            return;
        }

        // Property lists
        dapl_t get_current_access_properties();
        void set_current_access_properties(dapl_t);
        void reset_current_access_properties();
        void default_current_access_properties();

        dcpl_t get_current_creation_properties();
        void set_current_creation_properties(dcpl_t);
        void reset_current_creation_properties();
        void default_current_creation_properties();

        dxpl_t get_current_transfer_properties();
        void set_current_transfer_properties(dxpl_t);
        void default_current_transfer_properties();

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

        //size_t get_current_num_linked_spaces();
        //void set_current_num_linked_spaces(size_t);
        //void incr_current_num_linked_spaces();
        //void decr_current_num_linked_spaces();

        phez_attribute_t*** get_current_linked_attributes();
        phez_space_t* get_current_linked_memory_space();
        void set_current_linked_memory_space(phez_space_t*);
        phez_space_t* get_current_linked_file_space();
        void set_current_linked_file_space(phez_space_t*);

        phez_dataset_t*** get_dataset_list();
        
    private:

        void set_current_state(phez_dataset_state_t);
        bool get_current_is_name_defined();
        void set_current_is_name_defined(bool);
        bool get_current_is_type_defined();
        void set_current_is_type_defined(bool);
        bool get_current_is_data_defined();
        void set_current_is_data_defined(bool);

        void check_current_state_can_open();
        void check_current_state_can_make();
        void check_current_state_can_read();
        void check_current_state_can_write();
        void check_current_state_can_close();
        void update_current_state_opened();
        void update_current_state_made();
        void update_current_state_read();
        void update_current_state_written();
        void update_current_state_closed();

        size_t num_datasets;
        char** dataset_names;
        phez_dataset_t*** dataset_list;
        phez_dataset_t* current_dataset;
};

#endif

