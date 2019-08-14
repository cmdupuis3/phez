#ifndef SET_PHEZ_SPACE_T_API_H_
#define SET_PHEZ_SPACE_T_API_H_

// From debug.h...
#include <cstdlib>
#include <iostream>

#include <hdf5.h>
#include "phez_types.hpp"

using std::cout;
using std::size_t;

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

class hdf5_spaces {

    public:
        // constructor
        hdf5_spaces();
        // destructor
        ~hdf5_spaces();

        // internal API
        phez_space_t* initialize();
        void open(hid_t);
        void make();
        void close();
        void destroy();

        // selection functions
        void select_all();      // select everything
        void select_none();     // select nothing
        void select_inverse();  // H5S_SELECT_NOTA with a dummy hyperslab
                                // covering the entire space

        void add_elements_to_selection(size_t, size_t*);        // (H5S_SELECT_APPEND)
        void subtract_elements_from_selection(size_t, size_t*); // invert -> H5S_SELECT_APPEND -> invert
        void and_elements_with_selection(size_t, size_t*);      // invert -> xor_elements -> invert
        void xor_elements_with_selection(size_t, size_t*);      // H5S_SELECT_XOR with dummy hyperslabs
                                                                // for single points

        void add_hyperslabs_to_selection(size_t*, size_t*, size_t*, size_t*);        // (H5S_SELECT_OR)
        void subtract_hyperslabs_from_selection(size_t*, size_t*, size_t*, size_t*); // (H5S_SELECT_NOTB)
        void and_hyperslabs_with_selection(size_t*, size_t*, size_t*, size_t*);      // (H5S_SELECT_AND)
        void xor_hyperslabs_with_selection(size_t*, size_t*, size_t*, size_t*);      // (H5S_SELECT_XOR)

        // accessors and mutators
        phez_space_t* get_current();
        void set_current(phez_space_t*);
        size_t get_num();
        void set_num(size_t);
        void incr_num();
        void decr_num();
        hid_t get_current_id();
        void set_current_id(hid_t);
        phez_space_ptype_t get_current_ptype();
        void set_current_ptype(phez_space_ptype_t);
        int get_current_size();
        void set_current_size(int);
        size_t* get_current_dims_now();
        void set_current_dims_now(size_t*);
        size_t* get_current_dims_max();
        void set_current_dims_max(size_t*);
        phez_space_type_t get_current_type();
        void set_current_type(phez_space_type_t);
        phez_space_state_t get_current_state();

        // Inward links
        size_t get_current_num_datasets_linking();
        void set_current_num_datasets_linking(size_t);
        void incr_current_num_datasets_linking();
        void decr_current_num_datasets_linking();

        size_t get_current_num_attributes_linking();
        void set_current_num_attributes_linking(size_t);
        void incr_current_num_attributes_linking();
        void decr_current_num_attributes_linking();

        phez_space_t*** get_space_list();

    private:
        void set_current_state(phez_space_state_t);
        bool get_current_is_size_defined();
        void set_current_is_size_defined(bool);
        bool get_current_is_dims_now_defined();
        void set_current_is_dims_now_defined(bool);
        bool get_current_is_dims_max_defined();
        void set_current_is_dims_max_defined(bool);
        bool get_current_is_ptype_defined();
        void set_current_is_ptype_defined(bool);

        void check_current_state_can_open();
        void check_current_state_can_make();
        void check_current_state_can_close();
        void update_current_state_opened();
        void update_current_state_made();
        void update_current_state_closed();

        size_t num_spaces;
        phez_space_t*** space_list;
        phez_space_t* current_space;
};

#endif
