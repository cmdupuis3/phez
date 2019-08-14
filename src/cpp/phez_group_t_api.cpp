
#include "phez_group_t_api.hpp"
#include "phez_macros.hpp"

//using namespace std;

/************************* HDF5 group functions *******************************/
/** \brief HDF5 groups class constructor */
hdf5_groups::hdf5_groups(){

    /** Initialize number of active groups to zero.*/
    this->set_num(0);
    this->set_current((phez_group_t*)nullptr);

    /** Malloc space for dataset_list and set pointers to nullptr. */
    this->group_list = new phez_group_t**;
    *(this->group_list) = new phez_group_t*[PHEZ_MAX_NUM_GROUPS_ALLOWED];
    for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
        (*(this->group_list))[i] = nullptr;
    }

    PHEZ_NOTE_PREFIX
    cout << "hdf5_groups was created" << endl;
}
/** \brief HDF5 groups class destructor */
hdf5_groups::~hdf5_groups(){
    // demalloc stuff
    if(this->get_group_list()){
        for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            if((*(this->get_group_list()))[i]){
                this->set_current((*(this->get_group_list()))[i]);

                if(this->get_current_state() == PHEZ_GROUP_STATE_OPENED ||
                   this->get_current_state() == PHEZ_GROUP_STATE_MADE){
                    this->close();
                }

                this->destroy();
                (*(this->group_list))[i] = nullptr;
            }
        }

        delete[] *(this->group_list);
    }

    // free current_ pointer
    delete this->current_group;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_groups was destroyed" << endl;
}

/** \brief Get the address of the group that hdf5_groups is currently pointing to. */
phez_group_t* hdf5_groups::get_current(){
    return(this->current_group);
}
/** \brief Set the address of the group that hdf5_groups will point to. */
void hdf5_groups::set_current(phez_group_t* current_group_in){
    this->current_group = current_group_in;
    return;
}
/** \brief Get the num_groups of hdf5_groups currently in use. */
size_t hdf5_groups::get_num(){
    return(this->num_groups);
}
/** \brief Set the num_groups of hdf5_groups currently in use.*/
void hdf5_groups::set_num(size_t num_groups_in){
    this->num_groups = num_groups_in;
    return;
}
/** \brief Increment the num_groups of hdf5_groups currently in use. */
void hdf5_groups::incr_num(){
    this->num_groups++;
    return;
}
/** \brief Decrement the num_groups of hdf5_groups currently in use. */
void hdf5_groups::decr_num(){
    this->num_groups--;
    return;
}
/** \brief Get the HDF5 ID of the group that hdf5_groups is currently pointing to. */
hid_t hdf5_groups::get_current_id(){
    return(this->get_current()->id);
}
/** \brief Set the HDF5 ID of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::set_current_id(hid_t id_in){
    this->get_current()->id = id_in;
    return;
}
/** \brief Get the name of the group that hdf5_groups is currently pointing to.
 *
 *   \throw <fatal> {Cannot retrieve current group name because it is not defined.}
 */
char* hdf5_groups::get_current_name(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current group name because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->name);
}
/** \brief Set the name of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_name(char* name_in){
    strcpy(this->get_current()->name, name_in);
    this->set_current_is_name_defined(true);
    return;
}
/** \brief Get the comment of the group that hdf5_groups is currently pointing to. */
char* hdf5_groups::get_current_comment(){
    return(this->get_current()->comment);
}
/** \brief Set the comment of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_comment(char* comment_in){
    strcpy(this->get_current()->comment, comment_in);
    return;
}
/** \brief Get the access properties of the group that hdf5_groups is currently pointing to. */
gapl_t hdf5_groups::get_current_access_properties(){
    return(this->get_current()->gapl);
}
/** \brief Set the access properties of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_access_properties(gapl_t gapl_in){
    this->get_current()->gapl = gapl_in;
    return;
}
/** \brief Set the access properties of the group that hdf5_groups is currently pointing to to H5P_DEFAULT. */
void hdf5_groups::default_current_access_properties(){
    call_H5Pclose(this->get_current_access_properties()); // don't leak memory
    this->set_current_access_properties( (gapl_t)call_H5Pcreate(H5P_GROUP_ACCESS) );
    return;
}
/** \brief Get the creation properties of the group that hdf5_groups is currently pointing to. */
gcpl_t hdf5_groups::get_current_creation_properties(){
    return(this->get_current()->gcpl);
}
/** \brief Set the creation properties of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_creation_properties(gcpl_t gcpl_in){
    this->get_current()->gcpl = gcpl_in;
    return;
}
/** \brief Reset the creation properties of the group that hdf5_groups is currently pointing to to the value on the HDF5 side. */
void hdf5_groups::reset_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( (gcpl_t)call_H5Gget_create_plist(this->get_current_id()) );
    return;
}
/** \brief Set the creation properties of the group that hdf5_groups is currently pointing to to H5P_DEFAULT. */
void hdf5_groups::default_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( (gcpl_t)call_H5Pcreate(H5P_GROUP_ACCESS) );
    return;
}
/** \brief Get the state of the group that hdf5_groups is currently pointing to. */
phez_group_state_t hdf5_groups::get_current_state(){
    return(this->get_current()->state);
}
/** \brief Set the comment of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_state(phez_group_state_t state_in){

    switch(state_in){
        case(PHEZ_GROUP_STATE_DEFINED):
            break;
        case(PHEZ_GROUP_STATE_OPENED):
            break;
        case(PHEZ_GROUP_STATE_MADE):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot set current group state; state is invalid." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->state = state_in;
    return;
}
/** \brief Get whether the name of the group that hdf5_groups is currently pointing to is defined. */
bool hdf5_groups::get_current_is_name_defined(){
    return(this->get_current()->state_name);
}
/** \brief Set whether the name of the group that hdf5_groups is currently pointing to is defined. */
void hdf5_groups::set_current_is_name_defined(bool state_name_in){
    this->get_current()->state_name = state_name_in;
    return;
}
/** \brief Get the num_linked_attributes of the group that hdf5_groups is currently pointing to. */
size_t hdf5_groups::get_current_num_linked_attributes(){
    return(this->get_current()->num_linked_attributes);
}
/** \brief Set the num_linked_attributes of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_num_linked_attributes(size_t num_linked_attributes_in){
    this->get_current()->num_linked_attributes = num_linked_attributes_in;
    return;
}
/** \brief Increment the num_linked_attributes of hdf5_group currently in use. */
void hdf5_groups::incr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes++;
    return;
}
/** \brief Decrement the num_linked_attributes of hdf5_group currently in use. */
void hdf5_groups::decr_current_num_linked_attributes(){
    this->get_current()->num_linked_attributes--;
    return;
}
/** \brief Get the num_linked_datasets of the group that hdf5_groups is currently pointing to. */
size_t hdf5_groups::get_current_num_linked_datasets(){
    return(this->get_current()->num_linked_datasets);
}
/** \brief Set the num_linked_datasets of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_num_linked_datasets(size_t num_linked_datasets_in){
    this->get_current()->num_linked_datasets = num_linked_datasets_in;
    return;
}
/** \brief Increment the num_linked_datasets of hdf5_group currently in use. */
void hdf5_groups::incr_current_num_linked_datasets(){
    this->get_current()->num_linked_datasets++;
    return;
}
/** \brief Decrement the num_linked_datasets of hdf5_group currently in use. */
void hdf5_groups::decr_current_num_linked_datasets(){
    this->get_current()->num_linked_datasets--;
    return;
}
/** \brief Get the num_linked_groups of the group that hdf5_groups is currently pointing to. */
size_t hdf5_groups::get_current_num_linked_groups(){
    return(this->get_current()->num_linked_groups);
}
/** \brief Set the num_linked_groups of the group that hdf5_groups is currently pointing to.*/
void hdf5_groups::set_current_num_linked_groups(size_t num_linked_groups_in){
    this->get_current()->num_linked_groups = num_linked_groups_in;
    return;
}
/** \brief Increment the num_linked_groups of hdf5_group currently in use. */
void hdf5_groups::incr_current_num_linked_groups(){
    this->get_current()->num_linked_groups++;
    return;
}
/** \brief Decrement the num_linked_groups of hdf5_group currently in use. */
void hdf5_groups::decr_current_num_linked_groups(){
    this->get_current()->num_linked_groups--;
    return;
}
/** \brief Set the num_groups_linking of the group that hdf5_groups is currently pointing to. */
size_t hdf5_groups::get_current_num_groups_linking(){
    return(this->get_current()->num_groups_linking);
}
/** \brief Get the num_groups_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::set_current_num_groups_linking(size_t num_groups_linking_in){
    this->get_current()->num_groups_linking = num_groups_linking_in;
    return;
}
/** \brief Set the num_files_linking of the group that hdf5_groups is currently pointing to. */
size_t hdf5_groups::get_current_num_files_linking(){
    return(this->get_current()->num_files_linking);
}
/** \brief Get the num_files_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::set_current_num_files_linking(size_t num_files_linking_in){
    this->get_current()->num_files_linking = num_files_linking_in;
    return;
}
/** \brief Increment the num_groups_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::incr_current_num_groups_linking(){
    this->get_current()->num_groups_linking++;
    return;
}
/** \brief Decrement the num_groups_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::decr_current_num_groups_linking(){
    this->get_current()->num_groups_linking--;
    return;
}
/** \brief Increment the num_files_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::incr_current_num_files_linking(){
    this->get_current()->num_files_linking++;
    return;
}
/** \brief Decrement the num_files_linking of the group that hdf5_groups is currently pointing to. */
void hdf5_groups::decr_current_num_files_linking(){
    this->get_current()->num_files_linking--;
    return;
}
/** \brief Get the list of linked attributes of the group that hdf5_groups is currently pointing to. */
phez_attribute_t*** hdf5_groups::get_current_linked_attributes(){
    return(this->get_current()->linked_attributes);
}
/** \brief Get the list of linked datasets of the group that hdf5_groups is currently pointing to. */
phez_dataset_t*** hdf5_groups::get_current_linked_datasets(){
    return(this->get_current()->linked_datasets);
}
/** \brief Get the list of linked groups of the group that hdf5_groups is currently pointing to. */
phez_group_t*** hdf5_groups::get_current_linked_groups(){
    return(this->get_current()->linked_groups);
}
/** \brief Get the group list. */
phez_group_t*** hdf5_groups::get_group_list(){
    return(this->group_list);
}

phez_group_t* hdf5_groups::lookup_by_name(char*){
    return(nullptr);
}
phez_group_t* hdf5_groups::lookup_by_id(hid_t){
    return(nullptr);
}
/** \brief Creates a new hdf5_group struct and returns its address. */
phez_group_t* hdf5_groups::initialize(){
    /** Fail immediately if it would exceed the maximum number
         of active groups allowed */
    if(this->get_num() >= PHEZ_MAX_NUM_GROUPS_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot initialize another group struct; the maximum is ";
        cout << PHEZ_MAX_NUM_GROUPS_ALLOWED << endl;
        PHEZ_FATAL_SUFFIX
        return nullptr;
    }else{
        /*Local variables*/
        int i;

        /** Find empty pointer in the group_list.*/
        for(i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            if(!(*(this->group_list))[i]){ /* Is this slot a nullptr? */
                phez_group_t* gstruct = new phez_group_t;
                (*(this->group_list))[i] = gstruct;
                this->set_current((*(this->group_list))[i]);
                break;
            }
        }

        /** Malloc chars. */
        this->get_current()->name      = new char[PHEZ_MAX_NAME_LENGTH];
        this->get_current()->comment   = new char[PHEZ_MAX_COMMENT_LENGTH];

        /** Set id to be invalid.*/
        this->set_current_id(PHEZ_GROUP_ID_INVALID);

        /** Set group name and comment to null. */
        strcpy(this->get_current()->name, (char*)"");
        strcpy(this->get_current()->comment, (char*)"");

        /** Initialize group access and creation property lists with default settings. */
        this->set_current_access_properties( (gapl_t)call_H5Pcreate(H5P_GROUP_ACCESS) );
        this->set_current_creation_properties( (gcpl_t)call_H5Pcreate(H5P_GROUP_CREATE) );

        /** Set inward link count to zero */
        this->set_current_num_groups_linking(0);
        this->set_current_num_files_linking(0);

        /** Set outward link count to zero.*/
        this->set_current_num_linked_attributes(0);
        this->set_current_num_linked_datasets(0);
        this->set_current_num_linked_groups(0);

        /** Initialize link list pointers to nullptr. */
        this->get_current()->linked_groups = nullptr;
        this->get_current()->linked_datasets = nullptr;
        this->get_current()->linked_attributes = nullptr;

        /** Set initial state to DEFINED. */
        this->set_current_state(PHEZ_GROUP_STATE_DEFINED);
        this->set_current_is_name_defined(false);

        /** Increment the number of groups. */
        this->incr_num();
        return(this->get_current());
    }
}

/** \brief Opens an existing group and copies info to struct */
void hdf5_groups::open(hid_t obj_id){

    this->check_current_state_can_open();

    htri_t status;
    hid_t grpid;
    size_t bufsize;

    // Does the link to the group exist?
    status = call_H5Lexists(obj_id,
                            this->get_current_name(),
                            H5P_DEFAULT);
    if(status == 0){
        PHEZ_FATAL_PREFIX
        cout << "This group does not exist." << endl;
        PHEZ_FATAL_SUFFIX
    }

    // Does the group exist?
    status = call_H5Oexists_by_name(obj_id,
                                    this->get_current_name(),
                                    H5P_DEFAULT);
    if(status == 0){
        PHEZ_FATAL_PREFIX
        cout << "This group does not exist." << endl;
        PHEZ_FATAL_SUFFIX
    }

    grpid = call_H5Gopen(obj_id,
                         this->get_current_name(),
                         this->get_current_access_properties());
    this->set_current_id(grpid);

    /* First call gets the comment length, the second call retrieves the comment (?) */
    bufsize = call_H5Oget_comment(grpid,
                                  this->get_current_comment(),
                                  PHEZ_MAX_COMMENT_LENGTH);

    this->get_current()->comment = new char[bufsize];

    call_H5Oget_comment(grpid,
                        this->get_current_comment(),
                        bufsize);

    this->update_current_state_opened();

    return;
}

/** \brief Create HDF5 group with struct info. */
void hdf5_groups::make(hid_t obj_id){

    this->check_current_state_can_make();

    hid_t grpid;

    grpid = call_H5Gcreate(obj_id,
                           this->get_current_name(),
                           H5P_DEFAULT, // no fancy linking for you!
                           this->get_current_creation_properties(),
                           this->get_current_access_properties());

    this->set_current_id(grpid);

    this->update_current_state_made();

    return;
}
/** \brief Writes an existing group. */
/*
void hdf5_groups::write(){

    this->check_current_state_can_write();

    hid_t h5id;
    h5id = this->get_current_id();
    call_H5Gflush(h5id); // only in HDF5 1.10.0 and higher!

    // no need to update state, can flush as many times as you want

    return;
}
*/
/** \brief Closes an existing group */
void hdf5_groups::close(){

    this->check_current_state_can_close();

    hid_t h5id;
    h5id = this->get_current_id();
    call_H5Gclose(h5id);

    /** Set id to be invalid.*/
    this->set_current_id(PHEZ_GROUP_ID_INVALID);

    this->update_current_state_closed();

    return;
}
/** \brief Destroys an hdf5_group struct.
 *
 *   \throw <fatal> {Trying to destroy a nonexistent group.}
 *   \throw <fatal> {Cannot destroy this group because [num_files_linking] files and
 *                   [num_groups_linking] groups are still linking to it.}
 * */
void hdf5_groups::destroy(){

    if(!this->get_current()){
        PHEZ_FATAL_PREFIX
        cout << "Trying to destroy a nonexistent group." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        if( this->get_current_num_files_linking() != 0 && \
            this->get_current_num_groups_linking() != 0){
            PHEZ_FATAL_PREFIX
            cout << "Cannot destroy this group because " << this->get_current_num_files_linking();
            cout << " files and " << this->get_current_num_groups_linking() << " groups are still linking to it." << endl;
            PHEZ_FATAL_SUFFIX
        }else{

            /*Local variables*/
            int i;
            hid_t h5id;

            h5id = (hid_t)this->get_current_access_properties();
            //call_H5Pclose(h5id);

            h5id = (hid_t)this->get_current_creation_properties();
            //call_H5Pclose(h5id);

            this->set_current_id(0);
            delete[] this->get_current()->name;
            delete[] this->get_current()->comment;
            this->set_current_access_properties(0);
            this->set_current_creation_properties(0);

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
            this->get_current()->state = (phez_group_state_t)0;
            this->set_current_is_name_defined(false);

            /*Free the phez_file_t object.*/
            delete this->current_group;

            /** Set the group_list slot to nullptr. */
            for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
                if((*(this->get_group_list()))[i]){
                    if((*(this->get_group_list()))[i] == this->get_current()){
                        (*(this->get_group_list()))[i] = nullptr;
                    }
                }
            }

            this->set_current((phez_group_t*)nullptr);

            this->decr_num();
        }
    }

    return;
}

void hdf5_groups::link_group(phez_group_t* group_in){

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
        cout << PHEZ_MAX_NUM_GROUPS_ALLOWED << ") are already linked" << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            if(!(*(this->get_current_linked_groups()))[i]){
                (*(this->get_current_linked_groups()))[i] = group_in;
                this->incr_current_num_linked_groups();
                group_in->num_groups_linking++;
                break;
            }
        }
        return;
    }
}
void hdf5_groups::link_dataset(phez_dataset_t* dataset_in){

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
        cout << PHEZ_MAX_NUM_DATASETS_ALLOWED << ") are already linked" << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
            if(!(*(this->get_current_linked_datasets()))[i]){
                (*(this->get_current_linked_datasets()))[i] = dataset_in;
                this->incr_current_num_linked_datasets();
                dataset_in->num_groups_linking++;
                break;
            }
        }
        return;
    }
}
void hdf5_groups::link_attribute(phez_attribute_t* attribute_in){

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
        cout << PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED << ") are already linked" << endl;
        PHEZ_FATAL_SUFFIX
        return;
    }else{
        for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            if(!(*(this->get_current_linked_attributes()))[i]){
                (*(this->get_current_linked_attributes()))[i] = attribute_in;
                this->incr_current_num_linked_attributes();
                attribute_in->num_groups_linking++;
                break;
            }
        }
        return;
    }
}
void hdf5_groups::unlink_attribute(phez_attribute_t* attribute_in){
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
                        attribute_in->num_groups_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
void hdf5_groups::unlink_dataset(phez_dataset_t* dataset_in){
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
                        dataset_in->num_groups_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
void hdf5_groups::unlink_group(phez_group_t* group_in){
    /** Fail immediately if there are no linked groups */
    if(this->get_current_num_linked_groups() == 0){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink another group; none of the active groups are linked" << endl;
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
                        group_in->num_groups_linking--;
                        break;
                    }
                }
            }
        }
    }
    return;
}
void hdf5_groups::check_current_state_can_open(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open group because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->get_current_state() == PHEZ_GROUP_STATE_OPENED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open group because it is already open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_GROUP_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make group because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_GROUP_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make group because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
void hdf5_groups::check_current_state_can_make(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make group because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_GROUP_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make group because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_GROUP_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make group because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
void hdf5_groups::check_current_state_can_write(){

    if(this->get_current_state() == PHEZ_GROUP_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write group because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_groups::check_current_state_can_close(){

    if(this->get_current_state() == PHEZ_GROUP_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot close group because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Update the state of the current file's state to an equivalent opened state.*/
void hdf5_groups::update_current_state_opened(){

    if(this->get_current_state() == PHEZ_GROUP_STATE_DEFINED &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_GROUP_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current group state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Update the state of the current file's state to an equivalent made state.*/
void hdf5_groups::update_current_state_made(){

    if(this->get_current_state() == PHEZ_GROUP_STATE_DEFINED &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_GROUP_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current group state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Update the state of the current file's state to an equivalent closed/defined state.*/
void hdf5_groups::update_current_state_closed(){

    if((this->get_current_state() == PHEZ_GROUP_STATE_OPENED ||
       this->get_current_state() == PHEZ_GROUP_STATE_MADE)   &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_GROUP_STATE_DEFINED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current group state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
