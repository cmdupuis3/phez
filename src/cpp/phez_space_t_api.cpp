
#include "phez_space_t_api.hpp"
#include "phez_macros.hpp"

//using namespace std;

/*************************** HDF5 space functions *****************************/
/** \brief HDF5 spaces class constructor */
hdf5_spaces::hdf5_spaces(){
    /** Initialize number of active spaces to zero.*/
    this->set_num(0);
    this->set_current((phez_space_t*)nullptr);

    /** Malloc space for space_list and set pointers to nullptr. */
    this->space_list = new phez_space_t**;
    *(this->space_list) = new phez_space_t*[PHEZ_MAX_NUM_SPACES_ALLOWED];
    for(int i=0;i<PHEZ_MAX_NUM_SPACES_ALLOWED;i++){
        (*(this->space_list))[i] = nullptr;
    }

    PHEZ_NOTE_PREFIX
    cout << "hdf5_spaces was created" << endl;
}
/** \brief HDF5 spaces class destructor */
hdf5_spaces::~hdf5_spaces(){
    // demalloc stuff
    if(this->get_space_list()){
        for(int i=0;i<PHEZ_MAX_NUM_SPACES_ALLOWED;i++){
            if((*(this->get_space_list()))[i]){
                this->set_current((*(this->get_space_list()))[i]);
                this->destroy();
                (*(this->space_list))[i] = nullptr;
            }
        }

        delete[] *(this->space_list);
    }

    // free current_ pointer
    delete this->current_space;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_spaces was destroyed" << endl;
}

/** \brief Get the address of the space that hdf5_spaces is currently pointing to. */
phez_space_t* hdf5_spaces::get_current(){
    return(this->current_space);
}
/** \brief Set the address of the space that hdf5_spaces will point to. */
void hdf5_spaces::set_current(phez_space_t* current_space_in){
    this->current_space = current_space_in;
    return;
}
/** \brief Get the num_spaces of hdf5_spaces currently in use. */
size_t hdf5_spaces::get_num(){
    return(this->num_spaces);
}
/** \brief Set the num_spaces of hdf5_spaces currently in use.*/
void hdf5_spaces::set_num(size_t num_spaces_in){
    this->num_spaces = num_spaces_in;
    return;
}
/** \brief Increment the num_spaces of hdf5_spaces currently in use. */
void hdf5_spaces::incr_num(){
    this->num_spaces++;
    return;
}
/** \brief Decrement the num_spaces of hdf5_spaces currently in use. */
void hdf5_spaces::decr_num(){
    this->num_spaces--;
    return;
}
/** \brief Get the ID of the space that hdf5_spaces is currently pointing to. */
hid_t hdf5_spaces::get_current_id(){
    return(this->get_current()->id);
}
/** \brief Set the ID of the space that hdf5_spaces is currently pointing to.*/
void hdf5_spaces::set_current_id(hid_t id_in){
    this->get_current()->id = id_in;
    return;
}
/** \brief Get the type of object able to link to the space that hdf5_spaces is currently pointing to. */
phez_space_ptype_t hdf5_spaces::get_current_ptype(){
    return(this->get_current()->ptype);
}
/** \brief Set the type of object able to link to the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::set_current_ptype(phez_space_ptype_t ptype_in){

    switch(ptype_in){
        case(PHEZ_SPACE_PTYPE_INVALID):
            break;
        case(PHEZ_SPACE_PTYPE_ATTRIBUTE):
            break;
        case(PHEZ_SPACE_PTYPE_DATASET):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Attempted to update current space ptype to something other than ";
            cout << "PHEZ_SPACE_PTYPE_ATTRIBUTE or PHEZ_SPACE_PTYPE_DATASET." << endl;
            PHEZ_FATAL_SUFFIX
    }

    this->get_current()->ptype = ptype_in;
    this->set_current_is_ptype_defined(true);

    return;
}
/** \brief Get the data_size of the space that hdf5_spaces is currently pointing to. */
int hdf5_spaces::get_current_size(){

    if(!this->get_current_is_size_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current space size because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->size);
}
/** \brief Set the data_size of the space that hdf5_spaces is currently pointing to.*/
void hdf5_spaces::set_current_size(int size_in){
    this->get_current()->size = size_in;
    this->set_current_is_size_defined(true);
    return;
}

/** \brief Get the dimensions of the space that hdf5_spaces is currently pointing to. */
size_t* hdf5_spaces::get_current_dims_now(){

    if(!this->get_current_is_dims_now_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current space dimension (now) because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->dims_now);
}
/** \brief Get the dimensions of the space that hdf5_spaces is currently pointing to.
 *          Will only loop through the first current_size elements of dims_now_in, so
 *          use responsibly. */
void hdf5_spaces::set_current_dims_now(size_t* dims_now_in){

    if(!dims_now_in){
        /** If input is nullptr, set to nullptr and unset the 'defined' flag. */
        this->get_current()->dims_now = nullptr;
        this->set_current_is_dims_now_defined(false);
    }else{
        /** Otherwise, copy input dims_now to array. */
        size_t* cpy = new size_t[this->get_current_size()];
        for(int i = 0; i < this->get_current_size(); i++){
            cpy[i] = dims_now_in[i];
        }
        this->get_current()->dims_now = cpy;
        this->set_current_is_dims_now_defined(true);
    }

    return;
}
/** \brief Get the maximum size of the dimensions of the space that hdf5_spaces is currently pointing to. */
size_t* hdf5_spaces::get_current_dims_max(){

    if(!this->get_current_is_dims_max_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current space dimension (maximum) because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->dims_max);
}
/** \brief Get the maximum size of the dimensions of the space that hdf5_spaces is currently pointing to.
 *          Will only loop through the first current_size elements of dims_now_in, so
 *          use responsibly. */
void hdf5_spaces::set_current_dims_max(size_t* dims_max_in){

    if(!dims_max_in){
        /** If input is nullptr, set to nullptr and unset the 'defined' flag. */
        this->get_current()->dims_max = nullptr;
        this->set_current_is_dims_max_defined(false);
    }else{
        /** Otherwise, copy input dims_now to array. */
        size_t* cpy = new size_t[this->get_current_size()];
        for(int i = 0; i < this->get_current_size(); i++){
            cpy[i] = dims_max_in[i];
        }
        this->get_current()->dims_max = cpy;
        this->set_current_is_dims_max_defined(true);
    }

    return;
}
/** \brief Get the type of the space that hdf5_spaces is currently pointing to. */
phez_space_type_t hdf5_spaces::get_current_type(){
    return(this->get_current()->type);
}
/** \brief Set the type of the space that hdf5_spaces is currently pointing to.*/
void hdf5_spaces::set_current_type(phez_space_type_t type_in){

    switch(type_in){
        case(PHEZ_SPACE_TYPE_SIMPLE):
            break;
        case(PHEZ_SPACE_TYPE_SCALAR):
            break;
        case(PHEZ_SPACE_TYPE_NULL):
            break;
        case(PHEZ_SPACE_TYPE_INVALID):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Attempted to update current space type to something other than ";
            cout << "PHEZ_SPACE_TYPE_SIMPLE, PHEZ_SPACE_TYPE_SCALAR, or PHEZ_SPACE_TYPE_NULL." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->type = type_in;
    return;
}
/** \brief Get the comment of the group that hdf5_spaces is currently pointing to. */
phez_space_state_t hdf5_spaces::get_current_state(){
    return(this->get_current()->state);
}
/** \brief Set the comment of the group that hdf5_spaces is currently pointing to.*/
void hdf5_spaces::set_current_state(phez_space_state_t state_in){

    switch(state_in){
        case(PHEZ_SPACE_STATE_DEFINED):
            break;
        case(PHEZ_SPACE_STATE_OPENED):
            break;
        case(PHEZ_SPACE_STATE_MADE):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot set current space state; state is invalid." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->state = state_in;
    return;
}
/** \brief Get whether the size of the space that hdf5_spaces is currently pointing to is defined. */
bool hdf5_spaces::get_current_is_size_defined(){
    return(this->get_current()->state_size);
}
/** \brief Set whether the size of the space that hdf5_spaces is currently pointing to is defined. */
void hdf5_spaces::set_current_is_size_defined(bool state_size_in){
    this->get_current()->state_size = state_size_in;
    return;
}
/** \brief Get whether the dimensions (now) of the space that hdf5_spaces is currently pointing to is defined. */
bool hdf5_spaces::get_current_is_dims_now_defined(){
    return(this->get_current()->state_dims_now);
}
/** \brief Set whether the dimensions (now) of the space that hdf5_spaces is currently pointing to is defined. */
void hdf5_spaces::set_current_is_dims_now_defined(bool state_dims_now_in){
    this->get_current()->state_dims_now = state_dims_now_in;
    return;
}
/** \brief Get whether the dimensions (maximum) of the space that hdf5_spaces is currently pointing to is defined. */
bool hdf5_spaces::get_current_is_dims_max_defined(){
    return(this->get_current()->state_dims_max);
}
/** \brief Set whether the dimensions (maximum) of the space that hdf5_spaces is currently pointing to is defined. */
void hdf5_spaces::set_current_is_dims_max_defined(bool state_dims_max_in){
    this->get_current()->state_dims_max = state_dims_max_in;
    return;
}
/** \brief Get whether the parent object's type of the space that hdf5_spaces is currently pointing to is defined. */
bool hdf5_spaces::get_current_is_ptype_defined(){
    return(this->get_current()->state_ptype);
}
/** \brief Set whether the parent object's type of the space that hdf5_spaces is currently pointing to is defined. */
void hdf5_spaces::set_current_is_ptype_defined(bool state_ptype_in){
    this->get_current()->state_ptype = state_ptype_in;
    return;
}
/** \brief Set the num_attributes_linking of the space that hdf5_spaces is currently pointing to. */
size_t hdf5_spaces::get_current_num_attributes_linking(){
    return(this->get_current()->num_attributes_linking);
}
/** \brief Get the num_attributes_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::set_current_num_attributes_linking(size_t num_attributes_linking_in){
    this->get_current()->num_attributes_linking = num_attributes_linking_in;
    return;
}
/** \brief Set the num_datasets_linking of the space that hdf5_spaces is currently pointing to. */
size_t hdf5_spaces::get_current_num_datasets_linking(){
    return(this->get_current()->num_datasets_linking);
}
/** \brief Get the num_datasets_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::set_current_num_datasets_linking(size_t num_datasets_linking_in){
    this->get_current()->num_datasets_linking = num_datasets_linking_in;
    return;
}
/** \brief Increment the num_attributes_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::incr_current_num_attributes_linking(){
    this->get_current()->num_attributes_linking++;
    return;
}
/** \brief Decrement the num_attributes_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::decr_current_num_attributes_linking(){
    this->get_current()->num_attributes_linking--;
    return;
}
/** \brief Increment the num_datasets_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::incr_current_num_datasets_linking(){
    this->get_current()->num_datasets_linking++;
    return;
}
/** \brief Decrement the num_datasets_linking of the space that hdf5_spaces is currently pointing to. */
void hdf5_spaces::decr_current_num_datasets_linking(){
    this->get_current()->num_datasets_linking--;
    return;
}
/** \brief Get the space list. */
phez_space_t*** hdf5_spaces::get_space_list(){
    return(this->space_list);
}
/** \brief Creates a new hdf5_dataset struct and returns its address. */
phez_space_t* hdf5_spaces::initialize(){
    /** Fail immediately if it would exceed the maximum number
         of active spaces allowed */
    if(this->get_num() >= PHEZ_MAX_NUM_SPACES_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot initialize another space struct; the maximum is " << PHEZ_MAX_NUM_SPACES_ALLOWED << endl;
        PHEZ_FATAL_SUFFIX
        return(nullptr);
    }else{
        /*Local variables*/
        int i;

        /** Find empty pointer in the dataset_list.*/
        for(i=0;i<PHEZ_MAX_NUM_SPACES_ALLOWED;i++){
            if(!(*(this->space_list))[i]){
                phez_space_t* sstruct = new phez_space_t;
                (*(this->space_list))[i] = sstruct;
                this->set_current((*(this->space_list))[i]);
                break;
            }
        }

        /** Set id to be invalid.*/
        this->set_current_id(PHEZ_SPACE_ID_INVALID);
        
        /** Set type to be invalid. */
        this->set_current_type(PHEZ_SPACE_TYPE_INVALID);

        /** Set size to be invalid. */
        this->set_current_size(PHEZ_SPACE_SIZE_INVALID);

        /** Set parent type to be invalid. */
        this->set_current_ptype(PHEZ_SPACE_PTYPE_INVALID);

        /** Set inward link count to zero */
        this->set_current_num_attributes_linking(0);
        this->set_current_num_datasets_linking(0);

        /** Set state to default (all needed vars undefined) */
        this->set_current_state(PHEZ_SPACE_STATE_DEFINED);
        this->set_current_is_size_defined(false);
        this->set_current_is_dims_now_defined(false);
        this->set_current_is_dims_max_defined(false);
        this->set_current_is_ptype_defined(false);

        /** Increment the number of spaces. */
        this->incr_num();
        return(this->get_current());
    }
}

/** \brief Open a space (in practice, it copies the space to a new ID). Returns the file space for datasets. */
void hdf5_spaces::open(hid_t o_id){

    this->check_current_state_can_open();

    hid_t spcid;
    H5I_type_t itype;
    size_t* dims_now_tmp;
    size_t* dims_max_tmp;

    itype = call_H5Iget_type(o_id);
    switch(itype){
        case(H5I_DATASET):
            spcid = call_H5Dget_space(o_id);
            this->set_current_ptype(PHEZ_SPACE_PTYPE_DATASET);
            break;
        case(H5I_ATTR):
            spcid = call_H5Aget_space(o_id);
            this->set_current_ptype(PHEZ_SPACE_PTYPE_ATTRIBUTE);
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot open a space for this object because the object is not an attribute or dataset." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->set_current_id(spcid);
    this->set_current_size(call_H5Sget_simple_extent_ndims(this->get_current_id()));

    dims_now_tmp = new size_t[this->get_current_size()];
    dims_max_tmp = new size_t[this->get_current_size()];
    call_H5Sget_simple_extent_dims(spcid,
                                   (hsize_t*)dims_now_tmp,
                                   (hsize_t*)dims_max_tmp);
    this->set_current_dims_now(dims_now_tmp);
    this->set_current_dims_max(dims_max_tmp);

    switch(call_H5Sget_simple_extent_type(this->get_current_id())){
        case(H5S_SIMPLE):
            this->set_current_type(PHEZ_SPACE_TYPE_SIMPLE);
            break;
        case(H5S_SCALAR):
            this->set_current_type(PHEZ_SPACE_TYPE_SCALAR);
            break;
        case(H5S_NULL):
            this->set_current_type(PHEZ_SPACE_TYPE_NULL);
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "HDF5 returned an unsupported space type." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    delete[] dims_now_tmp;
    delete[] dims_max_tmp;

    /** Set initial state to DEFINED_NONE. */
    this->set_current_state(PHEZ_SPACE_STATE_DEFINED);

    this->update_current_state_opened();

    return;
}
/** \brief Make a new HDF5 space */
void hdf5_spaces::make(){

    this->check_current_state_can_make();

    hid_t spcid;
    spcid = call_H5Screate_simple(this->get_current_size(),
                                  (const hsize_t*)this->get_current_dims_now(),
                                  (const hsize_t*)this->get_current_dims_max());
    this->set_current_id(spcid);

    this->update_current_state_made();

    return;
}

/** \brief Close current space */
void hdf5_spaces::close(){

    this->check_current_state_can_close();

    call_H5Sclose(this->get_current_id());

    /** Set id to be invalid.*/
    this->set_current_id(PHEZ_SPACE_ID_INVALID);

    /** Return state to defined */
    this->update_current_state_closed();

    return;
}

/** \brief Destroy current space struct */
void hdf5_spaces::destroy(){

    if(!this->get_current()){
        PHEZ_FATAL_PREFIX
        cout << "Trying to destroy a nonexistent space." << endl;
        PHEZ_FATAL_SUFFIX
    }else{

        if(this->get_current()->dims_now){
            //delete[] this->get_current()->dims_now;
            this->get_current()->dims_now = nullptr;
        }

        if(this->get_current()->dims_max){
            //delete[] this->get_current()->dims_max;
            this->get_current()->dims_max = nullptr;
        }

        this->set_current_size(0);
        this->get_current()->type = (phez_space_type_t)0;
        this->get_current()->ptype = (phez_space_ptype_t)0;

        /** Set inward link count to zero */
        this->set_current_num_attributes_linking(0);
        this->set_current_num_datasets_linking(0);

        /** Set id to be zero.*/
        this->set_current_id(0);

        /** Set state to zero. */
        this->get_current()->state = (phez_space_state_t)0;
        this->set_current_is_size_defined(false);
        this->set_current_is_dims_now_defined(false);
        this->set_current_is_dims_max_defined(false);
        this->set_current_is_ptype_defined(false);

        /** Free the phez_space_t object. */
        delete this->current_space;

        /** Set the space_list slot to nullptr. */
        for(int i=0;i<PHEZ_MAX_NUM_SPACES_ALLOWED;i++){
            if((*(this->get_space_list()))[i]){
                if((*(this->get_space_list()))[i] == this->get_current()){
                    (*(this->get_space_list()))[i] = nullptr;
                }
            }
        }

        /** Set current_ pointer to nullptr. */
        this->set_current((phez_space_t*)nullptr);

        /** Decrement the number of spaces. */
        this->decr_num();
    }

    return;
}

/** \brief Add all elements to current selection */
void hdf5_spaces::select_all(){
    call_H5Sselect_all(this->get_current_id());
    return;
}

/** \brief Remove all elements from current selection. */
void hdf5_spaces::select_none(){
    call_H5Sselect_none(this->get_current_id());
    return;
}

/** \brief Invert current selection. */
void hdf5_spaces::select_inverse(){
    size_t* start;
    size_t* stride;
    size_t* count;
    size_t* block;

    /** Set a dummy hyperslab by including entire dataset. */
    start = new size_t[this->get_current_size()];
    stride = new size_t[this->get_current_size()];
    count = new size_t[this->get_current_size()];
    block = this->get_current_dims_now();

    for(int i = 0; i < (int)this->get_current_size(); i++){
        start[i] = 0;
        stride[i] = 1;
        count[i] = 1;
    }

    /** Invert selection by selecting the dummy hyperslab with H5S_SELECT_NOTA. */
    call_H5Sselect_hyperslab(this->get_current_id(),
                             H5S_SELECT_NOTA,
                             (hsize_t*)start,
                             (hsize_t*)stride,
                             (hsize_t*)count,
                             (hsize_t*)block);

    /** Clean up. */
    for(int i = 0; i < (int)this->get_current_size(); i++){
        start[i] = 0;
        stride[i] = 0;
        count[i] = 0;
    }

    delete[] start;
    delete[] stride;
    delete[] count;

    block = nullptr;
    delete block;

    return;
}

/** \brief Add new elements (by coordinates) to existing selection. */
void hdf5_spaces::add_elements_to_selection(size_t nelements_in, /**< Total number of elements to add */
                                            size_t* coords_in){  /**< 2-D array of element coordinates */

    call_H5Sselect_elements(this->get_current_id(),
                            H5S_SELECT_APPEND,
                            (hsize_t)nelements_in,
                            (hsize_t*)coords_in);

    return;
}

/** \brief Subtract new elements (by coordinates) from existing selection. */
void hdf5_spaces::subtract_elements_from_selection(size_t nelements_in, /**< Total number of elements to add */
                                                   size_t* coords_in){  /**< 2-D array of element coordinates */

    /** Invert selection so we can "add" the elements. */
    this->select_inverse();

    /** Add the elements to subtract to the inverted selection. */
    this->add_elements_to_selection(nelements_in,
                                    coords_in);

    /** Invert selection again to get the original with the new elements subtracted. */
    this->select_inverse();

    return;
}

/** \brief Logical XOR new elements (by coordinates) with existing selection. */
void hdf5_spaces::xor_elements_with_selection(size_t nelements_in,  /**< Total number of elements to add */
                                              size_t* coords_in){  /**< 2-D array of element coordinates */
    size_t* start;
    size_t* stride;
    size_t* count;
    size_t* block;

    /** Set a dummy hyperslab by including only a single element. */
    start = new size_t[this->get_current_size()];
    stride = new size_t[this->get_current_size()];
    count = new size_t[this->get_current_size()];
    block = new size_t[this->get_current_size()];

    for(int i = 0; i < (int)this->get_current_size(); i++){
        stride[i] = 1;
        count[i] = 1;
        block[i] = 1;
    }

    /** Logical XOR each inputted element with selection. */
    for(int i = 0; i < (int)nelements_in; i++){
        for(int j = 0; j < (int)this->get_current_size(); j++){
            start[j] = coords_in[j + i*this->get_current_size()];
        }

        call_H5Sselect_hyperslab(this->get_current_id(),
                                 H5S_SELECT_XOR,
                                 (hsize_t*)start,
                                 (hsize_t*)stride,
                                 (hsize_t*)count,
                                 (hsize_t*)block);
    }

    /** Clean up. */
    for(int i = 0; i < (int)this->get_current_size(); i++){
        start[i] = 0;
        stride[i] = 0;
        count[i] = 0;
    }

    delete[] start;
    delete[] stride;
    delete[] count;
    delete[] block;

    return;
}

/** \brief Logical AND new elements (by coordinates) with existing selection. */
void hdf5_spaces::and_elements_with_selection(size_t nelements_in, /**< Total number of elements to add */
                                              size_t* coords_in){  /**< 2-D array of element coordinates */

    /** Invert selection. */
    this->select_inverse();

    /** Logical XOR each inputted element with inverted selection. */
    this->xor_elements_with_selection(nelements_in,
                                      coords_in);

    /** Invert selection again. */
    this->select_inverse();

    return;
}

/** \brief Add hyperslabs to current selection. */
void hdf5_spaces::add_hyperslabs_to_selection(size_t* start_in,     /**<  Offset of start of hyperslab */
                                              size_t* stride_in,    /**< Number of blocks included in hyperslab */
                                              size_t* count_in,     /**< Hyperslab stride */
                                              size_t* block_in){    /**< Size of block in hyperslab */

    call_H5Sselect_hyperslab(this->get_current_id(),
                             H5S_SELECT_OR,
                             (hsize_t*)start_in,
                             (hsize_t*)stride_in,
                             (hsize_t*)count_in,
                             (hsize_t*)block_in);

    return;
}

/** \brief Subtract hyperslabs from current selection. */
void hdf5_spaces::subtract_hyperslabs_from_selection(size_t* start_in,  /**<  Offset of start of hyperslab */
                                                     size_t* stride_in, /**< Number of blocks included in hyperslab */
                                                     size_t* count_in,  /**< Hyperslab stride */
                                                     size_t* block_in){ /**< Size of block in hyperslab */

    call_H5Sselect_hyperslab(this->get_current_id(),
                             H5S_SELECT_NOTB,
                             (hsize_t*)start_in,
                             (hsize_t*)stride_in,
                             (hsize_t*)count_in,
                             (hsize_t*)block_in);

    return;
}

/** \brief Logical AND hyperslabs with current selection. */
void hdf5_spaces::and_hyperslabs_with_selection(size_t* start_in,     /**<  Offset of start of hyperslab */
                                                size_t* stride_in,    /**< Number of blocks included in hyperslab */
                                                size_t* count_in,     /**< Hyperslab stride */
                                                size_t* block_in){    /**< Size of block in hyperslab */

    call_H5Sselect_hyperslab(this->get_current_id(),
                             H5S_SELECT_AND,
                             (hsize_t*)start_in,
                             (hsize_t*)stride_in,
                             (hsize_t*)count_in,
                             (hsize_t*)block_in);

    return;
}

/** \brief Logical XOR hyperslabs with current selection. */
void hdf5_spaces::xor_hyperslabs_with_selection(size_t* start_in,     /**<  Offset of start of hyperslab */
                                                size_t* stride_in,    /**< Number of blocks included in hyperslab */
                                                size_t* count_in,     /**< Hyperslab stride */
                                                size_t* block_in){    /**< Size of block in hyperslab */

    call_H5Sselect_hyperslab(this->get_current_id(),
                             H5S_SELECT_XOR,
                             (hsize_t*)start_in,
                             (hsize_t*)stride_in,
                             (hsize_t*)count_in,
                             (hsize_t*)block_in);

    return;
}
/** \brief Trap open calls if some of the parameters it needs are undefined. */
void hdf5_spaces::check_current_state_can_open(){

    /* All states can open for now, so we just return */
    /*
    switch(this->get_current_state()){
        case(PHEZ_SPACE_STATE_DEFINED):
        case(PHEZ_SPACE_STATE_OPENED):
        case(PHEZ_SPACE_STATE_MADE):
    }
    */

    return;
}
/** \brief Trap make calls if some of the parameters it needs are undefined. */
void hdf5_spaces::check_current_state_can_make(){


    if(!this->get_current_is_size_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make space because the size is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_dims_now_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make space because the dimensions (now) are undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_dims_max_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make space because the dimensions (maximum) are undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_ptype_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make space because the parent type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){

        case(PHEZ_SPACE_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make space because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_SPACE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make space because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}

/** \brief Trap close calls if nothing is open. */
void hdf5_spaces::check_current_state_can_close(){

    if(this->get_current_state() == PHEZ_SPACE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot close space because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_spaces::update_current_state_opened(){

    if(this->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current space state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->set_current_state(PHEZ_SPACE_STATE_OPENED);

    return;
}
void hdf5_spaces::update_current_state_made(){

    if(this->get_current_state() == PHEZ_SPACE_STATE_DEFINED &&
       this->get_current_is_size_defined()                 &&
       this->get_current_is_dims_now_defined()             &&
       this->get_current_is_dims_max_defined()             &&
       this->get_current_is_ptype_defined()){

        this->set_current_state(PHEZ_SPACE_STATE_MADE);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current space state to made,";
        cout << " when the original state is not allowed to make. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_spaces::update_current_state_closed(){

    if(this->get_current_state() == PHEZ_SPACE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current space state to closed,";
        cout << " when the original state is not allowed to close. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->set_current_state(PHEZ_SPACE_STATE_DEFINED);

    return;
}
