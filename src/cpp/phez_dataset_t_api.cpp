
#include "phez_dataset_t_api.hpp"
#include "phez_macros.hpp"

//using namespace std;

/************************* HDF5 dataset functions *****************************/
/** \brief HDF5 datasets class constructor */
hdf5_datasets::hdf5_datasets(){

    /** Initialize number of active datasets to zero.*/
    this->set_num(0);
    this->set_current((phez_dataset_t*)nullptr);

    /** Malloc space for dataset_list and set pointers to nullptr. */
    this->dataset_list = new phez_dataset_t**;
    *(this->dataset_list) = new phez_dataset_t*[PHEZ_MAX_NUM_DATASETS_ALLOWED];
    for(int i = 0; i < PHEZ_MAX_NUM_DATASETS_ALLOWED; i++){
        (*(this->dataset_list))[i] = nullptr;
    }

    PHEZ_NOTE_PREFIX
    cout << "hdf5_datasets was created" << endl;
}
/** \brief HDF5 datasets class destructor */
hdf5_datasets::~hdf5_datasets(){
    // demalloc stuff

    if(this->get_dataset_list()){
        for(int i = 0; i < PHEZ_MAX_NUM_DATASETS_ALLOWED; i++){
            if((*(this->get_dataset_list()))[i]){
                this->set_current((*(this->get_dataset_list()))[i]);
                switch(this->get_current_state()){
                    case (PHEZ_DATASET_STATE_OPENED):
                        this->close();
                        break;
                    case (PHEZ_DATASET_STATE_MADE):
                        this->close();
                        break;
                    case (PHEZ_DATASET_STATE_READ):
                        this->close();
                        break;
                    case (PHEZ_DATASET_STATE_WRITTEN):
                        this->close();
                        break;
                    default:
                        break;
                }

                this->destroy();
                (*(this->dataset_list))[i] = nullptr;
            }
        }

        delete[] *(this->dataset_list);
    }

    // free current_ pointer
    delete this->current_dataset;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_datasets was destroyed" << endl;
}

/** \brief Get the address of the dataset that hdf5_datasets is currently pointing to. */
phez_dataset_t* hdf5_datasets::get_current(){
    return(this->current_dataset);
}
/** \brief Set the address of the dataset that hdf5_datasets will point to. */
void hdf5_datasets::set_current(phez_dataset_t* current_dataset_in){
    this->current_dataset = current_dataset_in;
    return;
}
/** \brief Get the num_datasets of hdf5_datasets currently in use. */
size_t hdf5_datasets::get_num(){
    return(this->num_datasets);
}
/** \brief Set the num_datasets of hdf5_datasets currently in use. */
void hdf5_datasets::set_num(size_t num_datasets_in){
    this->num_datasets = num_datasets_in;
    return;
}
/** \brief Increment the num_datasets of hdf5_datasets currently in use. */
void hdf5_datasets::incr_num(){
    this->num_datasets++;
    return;
}
/** \brief Decrement the num_datasets of hdf5_datasets currently in use. */
void hdf5_datasets::decr_num(){
    this->num_datasets--;
    return;
}
/** \brief Get the ID of the dataset that hdf5_datasets is currently pointing to. */
hid_t hdf5_datasets::get_current_id(){
    return(this->get_current()->id);
}
/** \brief Set the ID of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_id(hid_t id_in){
    this->get_current()->id = id_in;
    return;
}
/** \brief Get the name of the dataset that hdf5_datasets is currently pointing to. */
char* hdf5_datasets::get_current_name(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current dataset name because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->name);
}
/** \brief Set the name of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_name(char* name_in){
    strcpy(this->get_current()->name, name_in);
    this->set_current_is_name_defined(true);
    return;
}
/** \brief Get the comment of the dataset that hdf5_datasets is currently pointing to. */
char* hdf5_datasets::get_current_comment(){
    return(this->get_current()->comment);
}
/** \brief Set the comment of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::set_current_comment(char* comment_in){
    strcpy(this->get_current()->comment, comment_in);
    return;
}
/** \brief Get the access properties of the dataset that hdf5_datasets is currently pointing to. */
dapl_t hdf5_datasets::get_current_access_properties(){
    return(this->get_current()->dapl);
}
/** \brief Set the access properties of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_access_properties(dapl_t dapl_in){
    this->get_current()->dapl = dapl_in;
    return;
}
/** \brief Reset the access properties of the dataset that hdf5_datasets is currently pointing to to H5P_DEFAULT. */
void hdf5_datasets::default_current_access_properties(){
    call_H5Pclose(this->get_current_access_properties()); // don't leak memory
    this->set_current_access_properties( (dapl_t)call_H5Pcreate(H5P_DATASET_ACCESS) );
    return;
}
/** \brief Set the access properties of the dataset that hdf5_datasets is currently pointing to to the value on the HDF5 side. */
void hdf5_datasets::reset_current_access_properties(){
    call_H5Pclose(this->get_current_access_properties()); // don't leak memory
    this->set_current_access_properties( (dapl_t)call_H5Dget_access_plist(this->get_current_id()));
    return;
}
/** \brief Get the creation properties of the dataset that hdf5_datasets is currently pointing to. */
dcpl_t hdf5_datasets::get_current_creation_properties(){
    return(this->get_current()->dcpl);
}
/** \brief Set the creation properties of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_creation_properties(dcpl_t dcpl_in){
    this->get_current()->dcpl = dcpl_in;
    return;
}
/** \brief Reset the creation properties of the dataset that hdf5_datasets is currently pointing to to the value on the HDF5 side. */
void hdf5_datasets::reset_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties(
        call_H5Dget_create_plist(this->get_current_id()));
    return;
}
/** \brief Set the creation properties of the dataset that hdf5_datasets is currently pointing to to H5P_DEFAULT */
void hdf5_datasets::default_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( (dcpl_t)call_H5Pcreate(H5P_DATASET_CREATE) );
    return;
}
/** \brief Get the transfer properties of the dataset that hdf5_datasets is currently pointing to. */
dxpl_t hdf5_datasets::get_current_transfer_properties(){
    return(this->get_current()->dxpl);
}
/** \brief Set the transfer properties of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_transfer_properties(dxpl_t dxpl_in){
    this->get_current()->dxpl = dxpl_in;
    return;
}
/** \brief Set the transfer properties of the dataset that hdf5_datasets is currently pointing to to H5P_DEFAULT. */
void hdf5_datasets::default_current_transfer_properties(){
    call_H5Pclose(this->get_current_transfer_properties()); // don't leak memory
    this->set_current_transfer_properties( (dxpl_t)call_H5Pcreate(H5P_DATASET_XFER) );
    return;
}
/** \brief Get the data of the dataset that hdf5_datasets is currently pointing to. */
nullptr_t* hdf5_datasets::get_current_data(){
    return(nullptr); // Can't do it the normal way, C++ is stupid sometimes.
}
/** \brief Set the data of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_data(nullptr_t* data_in){
    this->get_current()->data = data_in;
    this->set_current_is_name_defined(false);
    return;
}
/** \brief Get the type of the dataset that hdf5_datasets is currently pointing to. */
phez_dataset_type_t hdf5_datasets::get_current_type(){

    if(!this->get_current_is_type_defined()){
        if(this->get_current()->type != PHEZ_DATASET_TYPE_INVALID){
            PHEZ_FATAL_PREFIX
            cout << "Cannot retrieve current dataset type because it is not defined." << endl;
            PHEZ_FATAL_SUFFIX
        }
    }

    return(this->get_current()->type);
}
/** \brief Set the type of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_type(phez_dataset_type_t type_in){
    if(this->get_current()->type != PHEZ_DATASET_TYPE_INVALID){
        //call_H5Tclose((hid_t)this->get_current_type());
    }

    this->get_current()->type = type_in;

    if(type_in == PHEZ_DATASET_TYPE_INVALID){
        this->set_current_is_type_defined(false);
    }else{
        this->set_current_is_type_defined(true);
    }

    return;
}
/** \brief Get the comment of the group that hdf5_datasets is currently pointing to. */
phez_dataset_state_t hdf5_datasets::get_current_state(){
    return(this->get_current()->state);
}
/** \brief Set the comment of the group that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_state(phez_dataset_state_t state_in){

    switch(state_in){
        case(PHEZ_DATASET_STATE_DEFINED):
            break;
        case(PHEZ_DATASET_STATE_OPENED):
            break;
        case(PHEZ_DATASET_STATE_MADE):
            break;
        case(PHEZ_DATASET_STATE_READ):
            break;
        case(PHEZ_DATASET_STATE_WRITTEN):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot set current dataset state; state is invalid." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->state = state_in;
    return;
}
/** \brief Get whether the name of the dataset that hdf5_datasets is currently pointing to is defined. */
bool hdf5_datasets::get_current_is_name_defined(){
    return(this->get_current()->state_name);
}
/** \brief Set whether the name of the dataset that hdf5_datasets is currently pointing to is defined. */
void hdf5_datasets::set_current_is_name_defined(bool state_name_in){
    this->get_current()->state_name = state_name_in;
    return;
}
/** \brief Get whether the type of the dataset that hdf5_datasets is currently pointing to is defined. */
bool hdf5_datasets::get_current_is_type_defined(){
    return(this->get_current()->state_type);
}
/** \brief Set whether the type of the dataset that hdf5_datasets is currently pointing to is defined. */
void hdf5_datasets::set_current_is_type_defined(bool state_type_in){
    this->get_current()->state_type = state_type_in;
    return;
}
/** \brief Get whether the data of the dataset that hdf5_datasets is currently pointing to is defined. */
bool hdf5_datasets::get_current_is_data_defined(){
    return(this->get_current()->state_data);
}
/** \brief Set whether the data of the dataset that hdf5_datasets is currently pointing to is defined. */
void hdf5_datasets::set_current_is_data_defined(bool state_data_in){
    this->get_current()->state_data = state_data_in;
    return;
}
/** \brief Get the num_linked_attributes of the dataset that hdf5_datasets is currently pointing to. */
size_t hdf5_datasets::get_current_num_linked_attributes(){
    return(this->get_current()->num_linked_attributes);
}
/** \brief Set the num_linked_attributes of the dataset that hdf5_datasets is currently pointing to.*/
void hdf5_datasets::set_current_num_linked_attributes(size_t num_linked_attributes_in){
    this->get_current()->num_linked_attributes = num_linked_attributes_in;
    return;
}
/** \brief Increment the num_linked_attributes of hdf5_dataset currently in use. */
void hdf5_datasets::incr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes++;
    return;
}
/** \brief Decrement the num_linked_attributes of hdf5_dataset currently in use. */
void hdf5_datasets::decr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes--;
    return;
}
/** \brief Set the num_groups_linking of the dataset that hdf5_datasets is currently pointing to. */
size_t hdf5_datasets::get_current_num_groups_linking(){
    return(this->get_current()->num_groups_linking);
}
/** \brief Get the num_groups_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::set_current_num_groups_linking(size_t num_groups_linking_in){
    this->get_current()->num_groups_linking = num_groups_linking_in;
    return;
}
/** \brief Set the num_files_linking of the dataset that hdf5_datasets is currently pointing to. */
size_t hdf5_datasets::get_current_num_files_linking(){
    return(this->get_current()->num_files_linking);
}
/** \brief Get the num_files_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::set_current_num_files_linking(size_t num_files_linking_in){
    this->get_current()->num_files_linking = num_files_linking_in;
    return;
}
/** \brief Increment the num_groups_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::incr_current_num_groups_linking(){
    this->get_current()->num_groups_linking++;
    return;
}
/** \brief Decrement the num_groups_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::decr_current_num_groups_linking(){
    this->get_current()->num_groups_linking--;
    return;
}
/** \brief Increment the num_files_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::incr_current_num_files_linking(){
    this->get_current()->num_files_linking++;
    return;
}
/** \brief Decrement the num_files_linking of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::decr_current_num_files_linking(){
    this->get_current()->num_files_linking--;
    return;
}
/** \brief Get the linked_memory_space of the dataset that hdf5_datasets is currently pointing to. */
phez_space_t* hdf5_datasets::get_current_linked_memory_space(){
    return (this->get_current()->linked_memory_space);
}
/** \brief Set the linked_memory_space of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::set_current_linked_memory_space(phez_space_t* memory_space_in){
    this->get_current()->linked_memory_space = memory_space_in;
    return;
}
/** \brief Get the linked_file_space of the dataset that hdf5_datasets is currently pointing to. */
phez_space_t* hdf5_datasets::get_current_linked_file_space(){
    return(this->get_current()->linked_file_space);
}
/** \brief Set the linked_file_space of the dataset that hdf5_datasets is currently pointing to. */
void hdf5_datasets::set_current_linked_file_space(phez_space_t* file_space_in){
    this->get_current()->linked_file_space = file_space_in;
    return;
}
/** \brief Get the list of linked attributes of the dataset that hdf5_datasets is currently pointing to. */
phez_attribute_t*** hdf5_datasets::get_current_linked_attributes(){
    return (this->get_current()->linked_attributes);
}
/** \brief Get the dataset list. */
phez_dataset_t*** hdf5_datasets::get_dataset_list(){
    return(this->dataset_list);
}

phez_dataset_t* hdf5_datasets::lookup_by_name(char*){
    return(nullptr);
}
phez_dataset_t* hdf5_datasets::lookup_by_id(hid_t){
    return(nullptr);
}
/** \brief Creates a new hdf5_dataset struct and returns its address. */
phez_dataset_t* hdf5_datasets::initialize(){
    /** Fail immediately if it would exceed the maximum number
         of active datasets allowed */
    if(this->get_num() >= PHEZ_MAX_NUM_DATASETS_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot initialize another dataset struct; the maximum is ";
        cout << PHEZ_MAX_NUM_DATASETS_ALLOWED << "." << endl;
        PHEZ_FATAL_SUFFIX
        return nullptr;
    }else{

        /*Local variables*/
        int i;

        /** Find empty pointer in the dataset_list.*/
        for(i = 0; i < PHEZ_MAX_NUM_DATASETS_ALLOWED; i++){
            if(!(*(this->dataset_list))[i]){ /* Is this slot a nullptr? */
                phez_dataset_t* dstruct = new phez_dataset_t;
                (*(this->dataset_list))[i] = dstruct;
                this->set_current((*(this->dataset_list))[i]);
                break;
            }
        }

        /** Malloc chars. */
        this->get_current()->name = new char[PHEZ_MAX_NAME_LENGTH];
        this->get_current()->comment = new char[PHEZ_MAX_COMMENT_LENGTH];

        /** Set id to invalid.*/
        this->set_current_id(PHEZ_DATASET_ID_INVALID);

        /** Set group name and comment to null. */
        strcpy(this->get_current()->name, (char*)"");
        strcpy(this->get_current()->comment, (char*)"");

        /** Initialize group access and creation property lists with default settings. */
        this->set_current_access_properties( (dapl_t)call_H5Pcreate(H5P_DATASET_ACCESS) );
        this->set_current_creation_properties( (dcpl_t)call_H5Pcreate(H5P_DATASET_CREATE) );
        this->set_current_transfer_properties( (dxpl_t)call_H5Pcreate(H5P_DATASET_XFER) );

        /** Set data and dataset sizes. Note: data and space are malloced just
             before assigning, their sizes have to be set through the API first. */
        //this->set_current_size(0);

        /** Set type to invalid. */
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_TYPE_INVALID);

        /**< Set data to nullptr. */
        this->set_current_data(nullptr);

        /** Set inward link count to zero */
        this->set_current_num_groups_linking(0);
        this->set_current_num_files_linking(0);

        /** Set outward link count to zero.*/
        this->set_current_num_linked_attributes(0);

        /** Initialize link list pointers to nullptr. */
        this->get_current()->linked_attributes = nullptr;

        /** Set each space pointer to nullptr.*/
        this->set_current_linked_memory_space(nullptr);
        this->set_current_linked_file_space(nullptr);

        /** Set initial state to DEFINED. */
        this->set_current_state(PHEZ_DATASET_STATE_DEFINED);
        this->set_current_is_name_defined(false);
        this->set_current_is_type_defined(false);
        this->set_current_is_data_defined(false);

        /** Increment the number of groups. */
        this->incr_num();
        return (this->get_current());
    }
}

/** \brief Opens an existing dataset and copies info to struct. */
void hdf5_datasets::open(hid_t obj_id){

    this->check_current_state_can_open();

    htri_t status;
    hid_t datid;
    hid_t dattype;
    hid_t dattype_native;
    size_t bufsize;

    // Does the link to the dataset exist?
    status = call_H5Lexists(obj_id,
                            this->get_current_name(),
                            H5P_DEFAULT);
    if(status == 0){
        PHEZ_FATAL_PREFIX
        cout << "This dataset does not exist." << endl;
        PHEZ_FATAL_SUFFIX
    }

    // Does the dataset exist?
    status = call_H5Oexists_by_name(obj_id,
                                    this->get_current_name(),
                                    H5P_DEFAULT);
    if(status == 0){
        PHEZ_FATAL_PREFIX
        cout << "This dataset does not exist." << endl;
        PHEZ_FATAL_SUFFIX
    }

    datid = call_H5Dopen(obj_id,
                         this->get_current_name(),
                         this->get_current_access_properties());
    this->set_current_id(datid);

    dattype = call_H5Dget_type(datid);
    dattype_native = call_H5Tget_native_type(dattype,
                                             H5T_DIR_ASCEND);
    if(call_H5Tequal(dattype_native, PHEZ_DATASET_DATA_TYPE_BOOL)){
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_DATA_TYPE_BOOL);
    }else if(call_H5Tequal(dattype_native, PHEZ_DATASET_DATA_TYPE_INT)){
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_DATA_TYPE_INT);
    }else if(call_H5Tequal(dattype_native, PHEZ_DATASET_DATA_TYPE_FLOAT)){
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_DATA_TYPE_FLOAT);
    }else if(call_H5Tequal(dattype_native, PHEZ_DATASET_DATA_TYPE_DOUBLE)){
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_DATA_TYPE_DOUBLE);
    }else if(call_H5Tequal(dattype_native, PHEZ_DATASET_DATA_TYPE_STRING)){
        this->set_current_type((phez_dataset_type_t)PHEZ_DATASET_DATA_TYPE_STRING);
    }else{
    	PHEZ_FATAL_PREFIX
		cout << "Cannot open because the dataset's data type is not supported by this library.";
		PHEZ_FATAL_SUFFIX
    }

    /* First call gets the comment length, the second call retrieves the comment (?) */
    bufsize = call_H5Oget_comment(datid,
                                  this->get_current_comment(),
                                  PHEZ_MAX_COMMENT_LENGTH);
    call_H5Oget_comment(datid,
                        this->get_current_comment(),
                        bufsize);

    this->update_current_state_opened();

    return;
}

/** \brief Read the data of an existing HDF5 dataset. */
void hdf5_datasets::read(){

    /**> If a data buffer wasn't passed in, allocate one. */
    if(!this->get_current_is_data_defined()){
        if(this->get_current_linked_file_space()){
            if(this->get_current_linked_file_space()->dims_max){
                int ndims, dims_prod;
                ndims = this->get_current_linked_file_space()->size;
                dims_prod = 1;
                for(int i = 0; i < ndims; i++){
                    dims_prod *= this->get_current_linked_file_space()->dims_max[i];
                }

                if(this->get_current_type() == PHEZ_DATASET_DATA_TYPE_BOOL){
                    this->set_current_data( new bool[dims_prod] );
                }else if(this->get_current_type() == PHEZ_DATASET_DATA_TYPE_INT){
                    this->set_current_data( new int[dims_prod] );
                }else if(this->get_current_type() == PHEZ_DATASET_DATA_TYPE_FLOAT){
                    this->set_current_data( new float[dims_prod] );
                }else if(this->get_current_type() == PHEZ_DATASET_DATA_TYPE_DOUBLE){
                    this->set_current_data( new double[dims_prod] );
                }else if(this->get_current_type() == PHEZ_DATASET_DATA_TYPE_STRING){
                    this->set_current_data( new char*[dims_prod] );
                }

            }else{
				//fatal
            }
        }else{
	    	//fatal
        }
    }

    /**> Check that we are currently able to call the HDF5 read function. */
    this->check_current_state_can_read();

    /**> Apply memory and file spaces; use H5S_ALL if not. */
    hid_t memory_space_id;
    if(this->get_current_linked_memory_space()){
        if(this->get_current_linked_memory_space()->id != PHEZ_SPACE_ID_INVALID){
            memory_space_id = this->get_current_linked_memory_space()->id;
        }else{
            memory_space_id = H5S_ALL;
        }
    }else{
        memory_space_id = H5S_ALL;
    }

    hid_t file_space_id;
    if(this->get_current_linked_file_space()){
        if(this->get_current_linked_file_space()->id != PHEZ_SPACE_ID_INVALID){
            file_space_id = this->get_current_linked_file_space()->id;
        }else{
            file_space_id = H5S_ALL;
        }
    }else{
        file_space_id = H5S_ALL;
    }

    /**> Call H5Dread. */
    call_H5Dread(this->get_current_id(),
                 (hid_t)this->get_current_type(),
                 memory_space_id,
                 file_space_id,
                 this->get_current_transfer_properties(),
                 this->get_current_data<void>());

    /**> Update the current dataset's state to "read." */
    this->update_current_state_read();

    return;
}

/** \brief Create HDF5 dataset with struct info. Multiple copies of the same dataset can
 be written by make->write->close->make... */
void hdf5_datasets::make(hid_t obj_id){

    this->check_current_state_can_make();

    hid_t file_space_id;
    if(this->get_current_linked_file_space() &&
       this->get_current_linked_file_space()->id != PHEZ_SPACE_ID_INVALID){
        file_space_id = this->get_current_linked_file_space()->id;
    }else{
        file_space_id = H5S_ALL;
    }

    hid_t datid;
    datid = call_H5Dcreate(obj_id,
                           this->get_current_name(),
                           (hid_t)this->get_current_type(),
                           file_space_id,
                           H5P_DEFAULT, // no fancy linking for you!
                           this->get_current_creation_properties(),
                           this->get_current_access_properties());
    this->set_current_id(datid);

    this->update_current_state_made();

    return;
}

/** \brief Writes an existing dataset. */
void hdf5_datasets::write(){

    this->check_current_state_can_write();

    hid_t memory_space_id;
    if(this->get_current_linked_memory_space()){
        if(this->get_current_linked_memory_space()->id != PHEZ_SPACE_ID_INVALID){
            memory_space_id = this->get_current_linked_memory_space()->id;
        }else{
            memory_space_id = H5S_ALL;
        }
    }else{
        memory_space_id = H5S_ALL;
    }

    hid_t file_space_id;
    if(this->get_current_linked_file_space()){
        if(this->get_current_linked_file_space()->id != PHEZ_SPACE_ID_INVALID){
            file_space_id = this->get_current_linked_file_space()->id;
        }else{
            file_space_id = H5S_ALL;
        }
    }else{
        file_space_id = H5S_ALL;
    }

    call_H5Dwrite(this->get_current_id(),
                  (hid_t)this->get_current_type(),
                  memory_space_id,
                  file_space_id,
                  this->get_current_transfer_properties(),
                  this->get_current_data<void>());

    this->update_current_state_written();

    return;
}

/** \brief Closes an existing dataset. */
void hdf5_datasets::close(){

    this->check_current_state_can_close();

    hid_t h5id;

    h5id = (hid_t)this->get_current_id();
    call_H5Dclose(h5id);

    /** Set id to be invalid.*/
    this->set_current_id(PHEZ_DATASET_ID_INVALID);

    /** Return state to defined */
    this->update_current_state_closed();

    return;
}

/** \brief Destroys an hdf5_dataset struct. */
void hdf5_datasets::destroy(){

    if(!this->get_current()){
        PHEZ_FATAL_PREFIX
        cout << "Trying to destroy a nonexistent dataset." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        if(this->get_current_num_files_linking() != 0 &&
           this->get_current_num_groups_linking() != 0){
            PHEZ_FATAL_PREFIX
            cout << "Cannot destroy this dataset because " << this->get_current_num_files_linking();
            cout << " files and " << this->get_current_num_groups_linking() << " groups are still linking to it." << endl;
            PHEZ_FATAL_SUFFIX
        }else{
            /*Local variables*/
            int i;
            hid_t h5id;

            h5id = (hid_t)this->get_current_access_properties();
            call_H5Pclose(h5id);

            h5id = (hid_t)this->get_current_creation_properties();
            call_H5Pclose(h5id);

            h5id = (hid_t)this->get_current_transfer_properties();
            call_H5Pclose(h5id);

            this->set_current_id(0);
            delete[] this->get_current()->name;
            delete[] this->get_current()->comment;
            this->set_current_access_properties(0);
            this->set_current_creation_properties(0);
            this->set_current_transfer_properties(0);

            h5id = (hid_t)this->get_current_type();
            if(h5id != PHEZ_DATASET_TYPE_INVALID){
                //call_H5Tclose(h5id);
            }
            this->get_current()->type = (phez_dataset_type_t)0;

            if(this->get_current_data()){
                delete[] this->get_current_data(); // undefined behavior if this is still a (void*)
            }

            //this->set_current_size(0);

            this->set_current_num_groups_linking(0);
            this->set_current_num_files_linking(0);

            /** Set each object pointer to nullptr.*/
            if(this->get_current_linked_attributes()){
                for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                    if((*(this->get_current_linked_attributes()))[i]){
                        (*(this->get_current_linked_attributes()))[i] = nullptr;
                    }
                }

                delete[] (*(this->get_current_linked_attributes()));
            }

            delete this->get_current_linked_attributes();

            this->set_current_linked_memory_space(nullptr);
            this->set_current_linked_file_space(nullptr);
            delete this->get_current_linked_memory_space();
            delete this->get_current_linked_file_space();

            /** Free the phez_file_t object.*/
            delete this->current_dataset;

            /** Set the dataset_list slot to nullptr. */
            for(int i = 0; i < PHEZ_MAX_NUM_DATASETS_ALLOWED; i++){
                if((*(this->get_dataset_list()))[i]){
                    if((*(this->get_dataset_list()))[i] == this->get_current()){
                        (*(this->get_dataset_list()))[i] = nullptr;
                    }
                }
            }

            /** Set state to zero. */
            this->get_current()->state = (phez_dataset_state_t)0;
            this->set_current_is_name_defined(false);
            this->set_current_is_type_defined(false);
            this->set_current_is_data_defined(false);

            this->set_current((phez_dataset_t*)nullptr);

            this->decr_num();
        }
    }

    return;
}

/** \brief Link the current dataset to an attribute. */
void hdf5_datasets::link_attribute(phez_attribute_t* attribute_in){

    /** Allocate linked_attributes list if it hasn't been already. */
    if(!this->get_current_linked_attributes()){
        this->get_current()->linked_attributes = new phez_attribute_t**;
        *(this->get_current()->linked_attributes) = new
                        phez_attribute_t*[PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED];

        /** Set each object pointer to nullptr.*/
        for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            (*(this->get_current_linked_attributes()))[i] = nullptr;
        }
    }

    /** Fail immediately if it would exceed the maximum number
     of active attributes allowed */
    if(this->get_current_num_linked_attributes() >= PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link to another attribute; all the active attributes (";
        cout << PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED << ") are already linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i = 0; i < PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED; i++){
            if(!(*(this->get_current_linked_attributes()))[i]){
                (*(this->get_current_linked_attributes()))[i] = attribute_in;
                this->incr_current_num_linked_attributes();
                attribute_in->num_datasets_linking++;
                break;
            }
        }
    }
    return;
}

/** \brief Unlink an attribute from the current dataset. */
void hdf5_datasets::unlink_attribute(phez_attribute_t* attribute_in){
    /** Fail immediately if there are no linked attributes */
    if(this->get_current_num_linked_attributes() == 0){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink another attribute; none of the active attributes are linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        if(!this->get_current_linked_attributes()){
            PHEZ_FATAL_PREFIX
            cout << "Cannot unlink this attribute; the attribute link list has not been allocated." << endl;
            PHEZ_FATAL_SUFFIX
            return;
        }else{
            for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                if((*(this->get_current_linked_attributes()))[i]){
                    if((*(this->get_current_linked_attributes()))[i] == attribute_in){
                        (*(this->get_current_linked_attributes()))[i] = nullptr;
                        this->decr_current_num_linked_attributes();
                        attribute_in->num_datasets_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}

/** \brief Set the current dataset's file space to a space. */
void hdf5_datasets::link_file_space(phez_space_t* space_in){
    if(space_in == this->get_current_linked_file_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link this space; it is already linked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->set_current_linked_file_space(space_in);
        space_in->num_datasets_linking++;
    }

    return;
}

/** \brief Unlink the current dataset's file space. */
void hdf5_datasets::unlink_file_space(){
    if(!this->get_current_linked_file_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink this space; it is already unlinked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->get_current_linked_file_space()->num_datasets_linking--;
        this->set_current_linked_file_space((phez_space_t*)nullptr);
    }
    return;
}

/** \brief Set the current dataset's memory space to a space. */
void hdf5_datasets::link_memory_space(phez_space_t* space_in){
    if(space_in == this->get_current_linked_memory_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link this space; it is already linked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->set_current_linked_memory_space(space_in);
        space_in->num_datasets_linking++;
    }

    return;
}

/** \brief Unlink the current dataset's memory space. */
void hdf5_datasets::unlink_memory_space(){
    if(!this->get_current_linked_memory_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink this space; it is already unlinked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->get_current_linked_memory_space()->num_datasets_linking--;
        this->set_current_linked_memory_space((phez_space_t*)nullptr);
    }
    return;
}

/** \brief Trap open calls if some of the parameters it needs are undefined. */
void hdf5_datasets::check_current_state_can_open(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open dataset because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_DATASET_STATE_DEFINED):
            break;
        case(PHEZ_DATASET_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open dataset because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open dataset because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_READ):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open dataset because it is already read." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_WRITTEN):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open dataset because it is already written." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap make calls if some of the parameters it needs are undefined. */
void hdf5_datasets::check_current_state_can_make(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make dataset because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make dataset because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_linked_file_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make dataset because it does not link to a file space." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_DATASET_STATE_DEFINED):
            break;
        case(PHEZ_DATASET_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make dataset because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make dataset because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_READ):
            //PHEZ_FATAL_PREFIX
            //cout << "Cannot make dataset because it is already read." << endl;
            //PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_WRITTEN):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make dataset because it is already written." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap read calls if some of the parameters it needs are undefined. */
void hdf5_datasets::check_current_state_can_read(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read dataset because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read dataset because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_data_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read dataset because the data is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_DATASET_STATE_OPENED):
            break;
        case(PHEZ_DATASET_STATE_READ):
            break;
        case(PHEZ_DATASET_STATE_WRITTEN):
            break;
        case(PHEZ_DATASET_STATE_DEFINED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot read dataset because it is not open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_DATASET_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot read dataset because it has not been written yet." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap write calls if some of the parameters it needs are undefined. */
void hdf5_datasets::check_current_state_can_write(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write dataset because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write dataset because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_data_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write dataset because the data is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->get_current_state() == PHEZ_DATASET_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write dataset because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Trap close calls if nothing is open. */
void hdf5_datasets::check_current_state_can_close(){

    if(this->get_current_state() == PHEZ_DATASET_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot close dataset because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_datasets::update_current_state_opened(){

    if(this->get_current_state() == PHEZ_DATASET_STATE_DEFINED &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_DATASET_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current dataset state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_datasets::update_current_state_made(){

    if(this->get_current_state() == PHEZ_DATASET_STATE_DEFINED &&
       this->get_current_is_name_defined()                 &&
       this->get_current_is_type_defined()){

        this->set_current_state(PHEZ_DATASET_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current dataset state to made,";
        cout << " when the original state is not allowed to make. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_datasets::update_current_state_read(){

    if((this->get_current_state() == PHEZ_DATASET_STATE_OPENED   ||
        this->get_current_state() == PHEZ_DATASET_STATE_READ     ||
        this->get_current_state() == PHEZ_DATASET_STATE_WRITTEN) &&
       this->get_current_is_data_defined()                   &&
       this->get_current_is_type_defined()                   &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_DATASET_STATE_READ);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current dataset state to read,";
        cout << " when the original state is not allowed to read. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_datasets::update_current_state_written(){

    if((this->get_current_state() == PHEZ_DATASET_STATE_OPENED ||
        this->get_current_state() == PHEZ_DATASET_STATE_MADE   ||
        this->get_current_state() == PHEZ_DATASET_STATE_READ)  &&
       this->get_current_is_data_defined()                &&
       this->get_current_is_type_defined()                &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_DATASET_STATE_MADE);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current dataset state to written,";
        cout << " when the original state is not allowed to write. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_datasets::update_current_state_closed(){

    if(this->get_current_state() != PHEZ_DATASET_STATE_DEFINED){
        this->set_current_state(PHEZ_DATASET_STATE_DEFINED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current dataset state to closed,";
        cout << " when the original state is not allowed to close. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
