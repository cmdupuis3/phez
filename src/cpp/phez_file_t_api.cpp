
#include "phez_file_t_api.hpp"

//using namespace std;
using std::cout;

/************************* HDF5 file functions ********************************/
/**< \brief HDF5 files constructor */
hdf5_files::hdf5_files(){

    /** Initialize number of active files to zero.*/
    this->set_num(0);
    this->set_current((phez_file_t*)nullptr);

    /** Malloc space for file_list and set pointers to nullptr. */
    this->file_list = new phez_file_t**;
    *(this->file_list) = new phez_file_t*[PHEZ_MAX_NUM_FILES_ALLOWED];
    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        (*(this->file_list))[i] = nullptr;
    }

    PHEZ_NOTE_PREFIX
    cout << "hdf5_files was created" << endl;
}
/**< \brief HDF5 files destructor */
hdf5_files::~hdf5_files(){
    // demalloc stuff
    if(this->get_file_list()){
        for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
            if((*(this->get_file_list()))[i]){
                this->set_current((*(this->get_file_list()))[i]);

                if(this->get_current_state() == PHEZ_FILE_STATE_OPENED){
                    this->close();
                }

                this->destroy();
                (*(this->file_list))[i] = nullptr;
            }
        }

        delete[] *(this->file_list);
    }

    // free current_ pointers
    delete this->current_file;

    this->set_num(0);

    PHEZ_NOTE_PREFIX
    cout << "hdf5_files was destroyed" << endl;
}

/** \brief Get the address of the file that hdf5_files is currently pointing to. */
phez_file_t* hdf5_files::get_current(){
    return(this->current_file);
}
/** \brief Set the address of the file that hdf5_files will point to. */
void hdf5_files::set_current(phez_file_t* current_file_in){
    this->current_file = current_file_in;
    return;
}
/** \brief Get the num_files of hdf5_files currently in use. */
size_t hdf5_files::get_num(){
    return(this->num_files);
}
/** \brief Set the num_files of hdf5_files currently in use.*/
void hdf5_files::set_num(size_t num_files_in){
    this->num_files = num_files_in;
    return;
}
/** \brief Increment the num_files of hdf5_files currently in use. */
void hdf5_files::incr_num(){
    this->num_files++;
    return;
}
/** \brief Decrement the num_files of hdf5_files currently in use. */
void hdf5_files::decr_num(){
    this->num_files--;
    return;
}
/** \brief Get the HDF5 ID of the file that hdf5_files is currently pointing to. */
hid_t hdf5_files::get_current_id(){
    return(this->get_current()->id);
}
/** \brief Set the HDF5 ID of the file that hdf5_files is currently pointing to. */
void hdf5_files::set_current_id(hid_t id_in){
    this->get_current()->id = id_in;
    return;
}
/** \brief Get the name of the file that hdf5_files is currently pointing to.
 *
 *   \throw <fatal> {Cannot retrieve current file name because it is not defined.}
 */
char* hdf5_files::get_current_name(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current file name because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->name);
}
/** \brief Set the name of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_name(char* name_in){
    strcpy(this->get_current()->name, name_in);
    this->set_current_is_name_defined(true);
    return;
}
/** \brief Get the access properties of the file that hdf5_files is currently pointing to. */
fapl_t hdf5_files::get_current_access_properties(){
    return(this->get_current()->fapl);
}
/** \brief Set the access properties of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_access_properties(fapl_t fapl_in){
    this->get_current()->fapl = fapl_in;
    return;
}
/** \brief Reset the access properties of the file that hdf5_files is currently pointing to to the value on the HDF5 side. */
void hdf5_files::reset_current_access_properties(){
    call_H5Pclose((hid_t)this->get_current_access_properties()); // don't leak memory
    //this->get_current()->fapl = (fapl_t)call_H5Pcreate(H5P_FILE_ACCESS);
    this->set_current_access_properties( (fapl_t)call_H5Fget_access_plist(this->get_current_id()) );
    return;
}
/** \brief Set the access properties of the file that hdf5_files is currently pointing to to H5P_DEFAULT. */
void hdf5_files::default_current_access_properties(){
    call_H5Pclose((hid_t)this->get_current_access_properties()); // don't leak memory
    this->set_current_access_properties( (fapl_t)call_H5Pcreate(H5P_FILE_ACCESS) );
    return;
}
/** \brief Set the access properties such that the file is only manipulated in memory (see H5Pset_fapl_core) */
void hdf5_files::access_current_from_memory(size_t memory_increment, bool file_writes_to_disk){
    call_H5Pset_fapl_core((hid_t)this->get_current_access_properties(),
                          memory_increment,
                          file_writes_to_disk);
    return;
}
/** \brief Set the access properties such that the file is only manipulated in disk (see H5Pset_fapl_direct) */
/*void hdf5_files::access_current_from_disk(size_t alignment, size_t block_size, size_t cbuf_size){
    call_H5Pclose(this->get_current_access_properties()); // don't leak memory
    this->get_current()->fapl = (fapl_t)call_H5Pcreate(H5P_FILE_ACCESS);
    call_H5Pset_fapl_direct((hid_t)this->get_current_access_properties(),
                            alignment,
                            block_size,
                            cbuf_size);
    return;
}*/
/** \brief Get the creation properties of the file that hdf5_files is currently pointing to. */
fcpl_t hdf5_files::get_current_creation_properties(){
    return(this->get_current()->fcpl);
}
/** \brief Set the creation properties of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_creation_properties(fcpl_t fcpl_in){
    this->get_current()->fcpl = fcpl_in;
    return;
}
/** \brief Reset the creation properties of the file that hdf5_files is currently pointing to to the value on the HDF5 side. */
void hdf5_files::reset_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    //this->get_current()->fcpl = (fcpl_t)call_H5Pcreate(H5P_FILE_CREATE);
    this->set_current_creation_properties( (fcpl_t)call_H5Fget_create_plist(this->get_current_id()) );
    return;
}
/** \brief Set the creation properties of the file that hdf5_files is currently pointing to H5P_DEFAULT. */
void hdf5_files::default_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( (fcpl_t)call_H5Pcreate(H5P_FILE_CREATE) );
    return;
}
/** \brief Get the action of the file that hdf5_files is currently pointing to.
 *
 *   \throw <fatal> {Cannot retrieve current file action because it is not defined.}
 */
phez_file_action_t hdf5_files::get_current_action(){

    if(!this->get_current_is_action_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current file action because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->action);
}
/** \brief Set the action of the file that hdf5_files is currently pointing to.
 *
 *   \throw <fatal> {Attempted to set current file action to something other than
 *                   PHEZ_FILE_ACTION_INVALID, PHEZ_FILE_ACTION_RDONLY, PHEZ_FILE_ACTION_WRONLY,
 *                   PHEZ_FILE_ACTION_OVERWR, or PHEZ_FILE_ACTION_APPEND.}
 */
void hdf5_files::set_current_action(phez_file_action_t action_in){

    switch(action_in){
        case(PHEZ_FILE_ACTION_INVALID):
            break;
        case(PHEZ_FILE_ACTION_RDONLY):
            break;
        case(PHEZ_FILE_ACTION_WRONLY):
            break;
        case(PHEZ_FILE_ACTION_OVERWR):
            break;
        case(PHEZ_FILE_ACTION_APPEND):
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Attempted to set current file action to something other than ";
            cout << "PHEZ_FILE_ACTION_INVALID, PHEZ_FILE_ACTION_RDONLY, PHEZ_FILE_ACTION_WRONLY,";
            cout << " PHEZ_FILE_ACTION_OVERWR, or PHEZ_FILE_ACTION_APPEND." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->action = action_in;
    if(action_in != PHEZ_FILE_ACTION_INVALID){
        this->set_current_is_action_defined(true);
    }

    return;
}
/** \brief Get the num_linked_attributes of the file that hdf5_files is currently pointing to. */
size_t hdf5_files::get_current_num_linked_attributes(){
    return(this->get_current()->num_linked_attributes);
}
/** \brief Set the num_linked_attributes of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_num_linked_attributes(size_t num_linked_attributes_in){
    this->get_current()->num_linked_attributes = num_linked_attributes_in;
    return;
}
/** \brief Increment the num_linked_attributes of hdf5_files currently in use. */
void hdf5_files::incr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes++;
    return;
}
/** \brief Decrement the num_linked_attributes of hdf5_files currently in use. */
void hdf5_files::decr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes--;
    return;
}
/** \brief Get the num_linked_datasets of the file that hdf5_files is currently pointing to. */
size_t hdf5_files::get_current_num_linked_datasets(){
    return(this->get_current()->num_linked_datasets);
}
/** \brief Set the num_linked_datasets of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_num_linked_datasets(size_t num_linked_datasets_in){
    this->get_current()->num_linked_datasets = num_linked_datasets_in;
    return;
}
/** \brief Increment the num_linked_datasets of hdf5_files currently in use. */
void hdf5_files::incr_current_num_linked_datasets(){
    this->get_current()->num_linked_datasets++;
    return;
}
/** \brief Decrement the num_linked_datasets of hdf5_files currently in use. */
void hdf5_files::decr_current_num_linked_datasets(){
    this->get_current()->num_linked_datasets--;
    return;
}
/** \brief Get the num_linked_groups of the file that hdf5_files is currently pointing to. */
size_t hdf5_files::get_current_num_linked_groups(){
    return(this->get_current()->num_linked_groups);
}
/** \brief Set the num_linked_groups of the file that hdf5_files is currently pointing to.*/
void hdf5_files::set_current_num_linked_groups(size_t num_linked_groups_in){
    this->get_current()->num_linked_groups = num_linked_groups_in;
    return;
}
/** \brief Increment the num_linked_groups of hdf5_files currently in use. */
void hdf5_files::incr_current_num_linked_groups(){
    this->get_current()->num_linked_groups++;
    return;
}
/** \brief Decrement the num_linked_groups of hdf5_files currently in use. */
void hdf5_files::decr_current_num_linked_groups(){
    this->get_current()->num_linked_groups--;
    return;
}
/** \brief Get the current state of the file that hdf5_files is currently pointing to. */
phez_file_state_t hdf5_files::get_current_state(){
    return(this->get_current()->state);
}
/** \brief Set the current state of the file that hdf5_files is currently pointing to. */
void hdf5_files::set_current_state(phez_file_state_t state_in){

    switch(state_in){
        case(PHEZ_FILE_STATE_DEFINED):
            break;
        case(PHEZ_FILE_STATE_OPENED):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot set current file state; state is invalid." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->state = state_in;
    return;
}
/** \brief Get whether the name of the file that hdf5_files is currently pointing to is defined. */
bool hdf5_files::get_current_is_name_defined(){
    return(this->get_current()->state_name);
}
/** \brief Set whether the name of the file that hdf5_files is currently pointing to is defined. */
void hdf5_files::set_current_is_name_defined(bool state_name_in){
    this->get_current()->state_name = state_name_in;
    return;
}
/** \brief Get whether the action of the file that hdf5_files is currently pointing to is defined. */
bool hdf5_files::get_current_is_action_defined(){
    return(this->get_current()->state_action);
}
/** \brief Set whether the action of the file that hdf5_files is currently pointing to is defined. */
void hdf5_files::set_current_is_action_defined(bool state_action_in){
    this->get_current()->state_action = state_action_in;
    return;
}
/** \brief Get the list of linked attributes of the file that hdf5_files is currently pointing to. */
phez_attribute_t*** hdf5_files::get_current_linked_attributes(){
    return(this->get_current()->linked_attributes);
}
/** \brief Get the list of linked datasets of the file that hdf5_files is currently pointing to. */
phez_dataset_t*** hdf5_files::get_current_linked_datasets(){
    return(this->get_current()->linked_datasets);
}
/** \brief Get the list of linked groups of the file that hdf5_files is currently pointing to. */
phez_group_t*** hdf5_files::get_current_linked_groups(){
    return(this->get_current()->linked_groups);
}
/** \brief Get the file list. */
phez_file_t*** hdf5_files::get_file_list(){
    return(this->file_list);
}

phez_file_t* hdf5_files::lookup_by_name(char*){
    return(nullptr);
}
phez_file_t* hdf5_files::lookup_by_id(hid_t){
    return(nullptr);
}
/** \brief Creates a new hdf5_file struct and returns its address. Note that this function
            automatically sets current_file to the new file.
 *
 *   \throw <fatal> {Cannot initialize another file struct; the maximum is [PHEZ_MAX_NUM_FILES_ALLOWED].}
 */
phez_file_t* hdf5_files::initialize(){
    /** Fail immediately if it would exceed the maximum number
         of active files allowed */
    if(this->get_num() >= PHEZ_MAX_NUM_FILES_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot initialize another file struct; the maximum is " << PHEZ_MAX_NUM_FILES_ALLOWED << "." << endl;
        PHEZ_FATAL_SUFFIX
        return nullptr;
    }else{
        /*Local variables*/
        int i;

        /** Find empty pointer in the file_list and allocate the struct. */
        for(i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
            if(!(*(this->file_list))[i]){ /* Is this slot a nullptr? */
                phez_file_t* fstruct = new phez_file_t;
                (*(this->file_list))[i] = fstruct;
                this->set_current((*(this->file_list))[i]);
                break;
            }
        }

        /** Malloc chars. */
        this->get_current()->name      = new char[PHEZ_MAX_NAME_LENGTH];

        /** Set id to zero.*/
        this->set_current_id(PHEZ_FILE_ID_INVALID);

        /** Set file name to nullptr. */
        strcpy(this->get_current()->name, (char*)"");

        /** Initialize file access and creation property lists with default settings. */
        this->set_current_access_properties( (fapl_t)call_H5Pcreate(H5P_FILE_ACCESS) );
        this->set_current_creation_properties( (fcpl_t)call_H5Pcreate(H5P_FILE_CREATE) );

        /** Set action to invalid */
        this->set_current_action(PHEZ_FILE_ACTION_INVALID);

        /** Set num_linked_ quantities to zero.*/
        this->set_current_num_linked_attributes(0);
        this->set_current_num_linked_datasets(0);
        this->set_current_num_linked_groups(0);

        /** Initialize link list pointers to nullptr. */
        this->get_current()->linked_groups = nullptr;
        this->get_current()->linked_datasets = nullptr;
        this->get_current()->linked_attributes = nullptr;

        /** Set initial states to DEFINED_NONE. */
        this->set_current_state(PHEZ_FILE_STATE_DEFINED);
        this->set_current_is_name_defined(false);
        this->set_current_is_action_defined(false);

        /** Increment the number of files */
        this->incr_num();
        return(this->get_current());
    }
}

/** \brief Open an HDF5 file.
 *
 *   \throw <fatal> {Trying to open file with an invalid action.}
 *   \throw <fatal> {Attempted to open current file with an action that is not allowed to open. (This should never happen!)}
 */
void hdf5_files::open(){

    this->check_current_state_can_open();

    // also need to check if file exists first
    /*
    if(call_H5Fis_hdf5(this->get_current_name()) == 0){
        PHEZ_FATAL_PREFIX
        cout << "The file name does not refer to an HDF5 file." << endl;
        PHEZ_FATAL_SUFFIX
    }
*/
    /*Local variables*/
    hid_t h5id;                   /**< HDF5 id of the file that is created.*/

    /*Set the correct flags and open the file.*/
    switch(this->get_current_action()){
        case(PHEZ_FILE_ACTION_RDONLY):
            h5id = call_H5Fopen(this->get_current_name(),
                                H5F_ACC_RDONLY,
                                (hid_t)this->get_current_access_properties());
            break;
        case(PHEZ_FILE_ACTION_APPEND):
            h5id = call_H5Fopen(this->get_current_name(),
                                H5F_ACC_RDWR,
                                (hid_t)this->get_current_access_properties());
            break;
        case(PHEZ_FILE_ACTION_WRONLY):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_ACTION_OVERWR):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_ACTION_INVALID):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Attempted to open current file with an action that is not";
            cout << " allowed to open. (This should never happen!)" << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->set_current_id(h5id);
    this->update_current_state_opened();

    return;
}

/** \brief Make a new HDF5 file.
 *
 *   \throw <fatal> {Trying to make file with an invalid action.}
 *   \throw <fatal> {Attempted to make current file with an action that is not allowed to open. (This should never happen!)}
 */
void hdf5_files::make(){

    this->check_current_state_can_make();
/*
    if(call_H5Fis_hdf5(this->get_current_name()) == 0){
        PHEZ_FATAL_PREFIX
        cout << "The file name does not refer to an HDF5 file." << endl;
        PHEZ_FATAL_SUFFIX
    }
*/
    /*Local variables*/
    hid_t h5id;                   /**< HDF5 id of the file that is created.*/

    /*Set the correct flags and open the file.*/
    switch(this->get_current_action()){
        case(PHEZ_FILE_ACTION_WRONLY):
            h5id = call_H5Fcreate(this->get_current_name(),
                                  H5F_ACC_EXCL,
                                  (hid_t)this->get_current_creation_properties(),
                                  (hid_t)this->get_current_access_properties());
            break;
        case(PHEZ_FILE_ACTION_OVERWR):
            h5id = call_H5Fcreate(this->get_current_name(),
                                  H5F_ACC_TRUNC,
                                  (hid_t)this->get_current_creation_properties(),
                                  (hid_t)this->get_current_access_properties());
            break;
        case(PHEZ_FILE_ACTION_RDONLY):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_ACTION_APPEND):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_ACTION_INVALID):
            PHEZ_FATAL_PREFIX
            cout << "Trying to open file with an invalid action." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Attempted to open current file with an action that is not";
            cout << " allowed to open. (This should never happen!)" << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->set_current_id(h5id);
    this->update_current_state_opened();

    return;
}

/** \brief Close an HDF5 file.*/
void hdf5_files::close(){

    this->check_current_state_can_close();

    hid_t h5id;

    h5id = this->get_current_id();
    call_H5Fclose(h5id);

    /** Set id to be invalid.*/
    this->set_current_id(PHEZ_FILE_ID_INVALID);

    this->update_current_state_closed();

    return;
}

/** \brief Destroys an hdf5_file struct.
 *
 *   \throw <fatal> {Trying to destroy a nonexistent file.}
 */
void hdf5_files::destroy(){

    if(!this->get_current()){
        PHEZ_FATAL_PREFIX
        cout << "Trying to destroy a nonexistent file." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        /* Close if open */

        /*Local variables*/
        int i;
        hid_t h5id;

        h5id = (hid_t)this->get_current_access_properties();
        call_H5Pclose(h5id);

        h5id = (hid_t)this->get_current_creation_properties();
        call_H5Pclose(h5id);

        this->set_current_id(0);
        this->set_current_access_properties(0);
        this->set_current_creation_properties(0);
        delete[] this->get_current()->name;
        this->get_current()->action = (phez_file_action_t)0;

        /** Set each object pointer to nullptr.*/
        if(this->get_current_linked_attributes()){
            for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                if((*(this->get_current_linked_attributes()))[i]){
                    (*(this->get_current_linked_attributes()))[i] = nullptr;
                }
            }

            delete[] (*(this->get_current_linked_attributes()));
        }

        if(this->get_current_linked_datasets()){
            for(i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
                if((*(this->get_current_linked_datasets()))[i]){
                    (*(this->get_current_linked_datasets()))[i] = nullptr;
                }
            }

            delete[] (*(this->get_current_linked_datasets()));
        }

        if(this->get_current_linked_groups()){
            for(i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
                if((*(this->get_current_linked_groups()))[i]){
                    (*(this->get_current_linked_groups()))[i] = nullptr;
                }
            }

            delete[] (*(this->get_current_linked_groups()));
        }

        delete this->get_current_linked_attributes();
        delete this->get_current_linked_datasets();
        delete this->get_current_linked_groups();

        /** Set state to zero. */
        this->get_current()->state = (phez_file_state_t)0;
        this->set_current_is_name_defined(false);
        this->set_current_is_action_defined(false);

        /*Free the phez_file_t object.*/
        delete this->current_file;

        /** Set the file_list slot to nullptr. */
        for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
            if((*(this->get_file_list()))[i]){
                if((*(this->get_file_list()))[i] == this->get_current()){
                    (*(this->get_file_list()))[i] = nullptr;
                }
            }
        }

        this->set_current((phez_file_t*)nullptr);

        this->decr_num();
    }

    return;
}
/** \brief Link the current file to a group.
 *
 *   \throw <fatal> {Cannot link to another group; all the active groups
 *                   ([PHEZ_MAX_NUM_GROUPS_ALLOWED]) are already linked.}
 */
void hdf5_files::link_group(phez_group_t* group_in){

    /** Allocate linked_groups list if it hasn't been already. */
    if(!this->get_current_linked_groups()){
        this->get_current()->linked_groups = new phez_group_t**;
        *(this->get_current()->linked_groups) = new
                        phez_group_t*[PHEZ_MAX_NUM_GROUPS_ALLOWED];

        /** Set each object pointer to nullptr.*/
        for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            (*(this->get_current_linked_groups()))[i] = nullptr;
        }
    }

    /** Fail immediately if it would exceed the maximum number
         of active groups allowed */
    if(this->get_current_num_linked_groups() >= PHEZ_MAX_NUM_GROUPS_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link to another group; all the active groups (";
        cout << PHEZ_MAX_NUM_GROUPS_ALLOWED << ") are already linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            if(!(*(this->get_current_linked_groups()))[i]){
                (*(this->get_current_linked_groups()))[i] = group_in;
                this->incr_current_num_linked_groups();
                group_in->num_files_linking++;
                break;
            }
        }
    }
    return;
}
/** \brief Link the current file to a dataset.
 *
 *   \throw <fatal> {Cannot link to another dataset; all the active datasets
 *                   ([PHEZ_MAX_NUM_DATASETS_ALLOWED]) are already linked.}
 */
void hdf5_files::link_dataset(phez_dataset_t* dataset_in){

    /** Allocate linked_datasets list if it hasn't been already. */
    if(!this->get_current_linked_datasets()){
        this->get_current()->linked_datasets = new phez_dataset_t**;
        *(this->get_current()->linked_datasets) = new
                        phez_dataset_t*[PHEZ_MAX_NUM_DATASETS_ALLOWED];

        /** Set each object pointer to nullptr.*/
        for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
            (*(this->get_current_linked_datasets()))[i] = nullptr;
        }
    }

    /** Fail immediately if it would exceed the maximum number
         of active datasets allowed */
    if(this->get_current_num_linked_datasets() >= PHEZ_MAX_NUM_DATASETS_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link to another dataset; all the active datasets (";
        cout << PHEZ_MAX_NUM_DATASETS_ALLOWED << ") are already linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
            if(!(*(this->get_current_linked_datasets()))[i]){
                (*(this->get_current_linked_datasets()))[i] = dataset_in;
                this->incr_current_num_linked_datasets();
                dataset_in->num_files_linking++;
                break;
            }
        }
    }
    return;
}
/** \brief Link the current file to an attribute.
 *
 *   \throw <fatal> {Cannot link to another attribute; all the active attributes
 *                   ([PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED]) are already linked.}
 */
void hdf5_files::link_attribute(phez_attribute_t* attribute_in){

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
        for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            if(!(*(this->get_current_linked_attributes()))[i]){
                (*(this->get_current_linked_attributes()))[i] = attribute_in;
                this->incr_current_num_linked_attributes();
                attribute_in->num_files_linking++;
                break;
            }
        }
    }
    return;
}
/** \brief Unlink the current file from an attribute.
 *
 *   \throw <fatal> {Cannot unlink another attribute; none of the active attributes are linked.}
 */
void hdf5_files::unlink_attribute(phez_attribute_t* attribute_in){
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
                        attribute_in->num_files_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
/** \brief Unlink the current file from a dataset.
 *
 *   \throw <fatal> {Cannot unlink another dataset; none of the active datasets are linked.}
 */
void hdf5_files::unlink_dataset(phez_dataset_t* dataset_in){
    /** Fail immediately if there are no linked datasets */
    if(this->get_current_num_linked_datasets() == 0){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink another dataset; none of the active datasets are linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        if(!this->get_current_linked_datasets()){
            PHEZ_FATAL_PREFIX
            cout << "Cannot unlink this dataset; the dataset link list has not been allocated." << endl;
            PHEZ_FATAL_SUFFIX
            return;
        }else{
            for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
                if((*(this->get_current_linked_datasets()))[i]){
                    if((*(this->get_current_linked_datasets()))[i] == dataset_in){
                        (*(this->get_current_linked_datasets()))[i] = nullptr;
                        this->decr_current_num_linked_datasets();
                        dataset_in->num_files_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
/** \brief Unlink the current file from a group.
 *
 *   \throw <fatal> {Cannot unlink another group; none of the active groups are linked.}
 */
void hdf5_files::unlink_group(phez_group_t* group_in){
    /** Fail immediately if there are no linked groups */
    if(this->get_current_num_linked_groups() == 0){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink another group; none of the active groups are linked." << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        if(!this->get_current_linked_groups()){
            PHEZ_FATAL_PREFIX
            cout << "Cannot unlink this group; the group link list has not been allocated." << endl;
            PHEZ_FATAL_SUFFIX
            return;
        }else{
            for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
                if((*(this->get_current_linked_groups()))[i]){
                    if((*(this->get_current_linked_groups()))[i] == group_in){
                        (*(this->get_current_linked_groups()))[i] = nullptr;
                        this->decr_current_num_linked_groups();
                        group_in->num_files_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
/** \brief Check the state of the current file and pass if it can be opened (fail otherwise).
 *
 *   \throw <fatal> {Cannot open file because the name is undefined.}
 *   \throw <fatal> {Cannot open file because the action is undefined.}
 *   \throw <fatal> {Cannot open file because it is already open.}
 *   \throw <fatal> {Cannot open file because it is already made.}
 */
void hdf5_files::check_current_state_can_open(){

    if(!this->get_current_is_action_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open file because the action is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open file because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_FILE_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make file because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make file because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Check the state of the current file and pass if it can be made (fail otherwise).
 *
 *   \throw <fatal> {Cannot make file because the name is undefined.}
 *   \throw <fatal> {Cannot make file because the action is undefined.}
 *   \throw <fatal> {Cannot make file because it is already open.}
 *   \throw <fatal> {Cannot make file because it is already made.}
 */
void hdf5_files::check_current_state_can_make(){

    if(!this->get_current_is_action_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open file because the action is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open file because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_FILE_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make file because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_FILE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make file because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Check the state of the current file and pass if it can be closed (fail otherwise).
 *
 *   \throw <fatal> {Cannot close file because it is not currently open.}
 */
void hdf5_files::check_current_state_can_close(){

    if(this->get_current_state() == PHEZ_FILE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot close file because it is not currently open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Update the state of the current file's state to an equivalent opened state.
 *
 *   \throw <fatal> {Attempted to update current file state to opened, when the original
 *                   state is not allowed to open. (This should never happen!)}
 */
void hdf5_files::update_current_state_opened(){

    if(this->get_current_state() == PHEZ_FILE_STATE_DEFINED &&
       this->get_current_is_name_defined()                 &&
       this->get_current_is_action_defined()){

        this->set_current_state(PHEZ_FILE_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current file state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Update the state of the current file's state to an equivalent closed/defined state.
 *
 *   \throw <fatal> {Attempted to update current file state to closed, when the original state
 *                   is not allowed to close. (This should never happen!)}
 */
void hdf5_files::update_current_state_closed(){

    if(this->get_current_state() == PHEZ_FILE_STATE_OPENED  &&
       this->get_current_is_name_defined()                 &&
       this->get_current_is_action_defined()){

        this->set_current_state(PHEZ_FILE_STATE_DEFINED);
    }else{
            PHEZ_FATAL_PREFIX
            cout << "Attempted to update current file state to closed,";
            cout << " when the original state is not allowed to close. (This should never happen!)" << endl;
            PHEZ_FATAL_SUFFIX
    }

    return;
}
