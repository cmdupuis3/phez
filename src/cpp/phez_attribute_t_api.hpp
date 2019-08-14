#ifndef SET_PHEZ_ATTRIBUTE_T_API_H_
#define SET_PHEZ_ATTRIBUTE_T_API_H_

// From debug.h...
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <hdf5.h>
#include "phez_types.hpp"
#include "phez_errmacros.hpp"
#include "phez_macros.hpp"

using std::cout;
using std::endl;

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

class hdf5_attributes {

    public:
        // constructor
        hdf5_attributes();
        // destructor
        ~hdf5_attributes();

        // internal API
        phez_attribute_t* initialize();
        void open(hid_t);
        void make(hid_t);

        void read();
        void link_space(phez_space_t*);
        void unlink_space();
        void write();

        void close();
        void destroy();

        phez_attribute_t* lookup_by_name(char*);
        phez_attribute_t* lookup_by_id(hid_t);

        // accessors and mutators
        phez_attribute_t* get_current();
        void set_current(phez_attribute_t*);
        size_t get_num();
        void set_num(size_t);
        void incr_num();
        void decr_num();
        hid_t get_current_id();
        void set_current_id(hid_t);
        char* get_current_name();
        void set_current_name(char*);
        phez_attribute_type_t get_current_type();
        void set_current_type(phez_attribute_type_t);
        phez_attribute_state_t get_current_state();

        nullptr_t* get_current_data();     // apparently templates don't generate
        void set_current_data(nullptr_t*); // nullptr_t functions... go figure.
        /** \brief Get the data pointer of the attribute that hdf5_attributes is currently pointing to. */
        template<typename T> T* get_current_data(){

            if(!this->get_current_is_data_defined()){
                if(this->get_current()->data){
                    PHEZ_FATAL_PREFIX
                    cout << "Cannot retrieve current attribute data because it is not defined." << endl;
                    PHEZ_FATAL_SUFFIX
                }
            }

            return((T*)this->get_current()->data);
        }
        /** \brief Set the data pointer of the attribute that hdf5_attributes is currently pointing to. */
        template<typename T> void set_current_data(T* data_in){
            this->get_current()->data = (void*)data_in;
            this->set_current_is_data_defined(true);
            return;
        }

        // Property lists
        acpl_t get_current_creation_properties();
        void set_current_creation_properties(acpl_t);
        void reset_current_creation_properties();
        void default_current_creation_properties();

        //aapl_t get_current_access_properties();
        //void set_current_access_properties(aapl_t);
        //void reset_current_access_properties();

        // Inward links
        size_t get_current_num_datasets_linking();
        void set_current_num_datasets_linking(size_t);
        void incr_current_num_datasets_linking();
        void decr_current_num_datasets_linking();

        size_t get_current_num_groups_linking();
        void set_current_num_groups_linking(size_t);
        void incr_current_num_groups_linking();
        void decr_current_num_groups_linking();

        size_t get_current_num_files_linking();
        void set_current_num_files_linking(size_t);
        void incr_current_num_files_linking();
        void decr_current_num_files_linking();

        // Outward links
        //size_t get_current_num_linked_spaces();
        //void set_current_num_linked_spaces(size_t);
        //void incr_current_num_linked_spaces();
        //void decr_current_num_linked_spaces();

        phez_space_t* get_current_linked_space();
        void set_current_linked_space(phez_space_t*);

        phez_attribute_t*** get_attribute_list();
        
    private:

        void set_current_state(phez_attribute_state_t);
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

        size_t num_attributes;
        char** attribute_names;
        phez_attribute_t*** attribute_list; /**< List of all attributes */
        phez_attribute_t* current_attribute; /**< Pointer to current attribute */
};

#endif

