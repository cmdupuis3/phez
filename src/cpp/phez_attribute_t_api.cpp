
#include "phez_attribute_t_api.hpp"

//using namespace std;

/************************* HDF5 attribute functions ***************************/
/** \brief HDF5 attributes class constructor */
hdf5_attributes::hdf5_attributes(){

    /** Initialize number of active attributes to zero.*/
    this->set_num(0);
    this->set_current((phez_attribute_t*)nullptr);

    /** Malloc space for attribute_list and set pointers to nullptr. */
    this->attribute_list = new phez_attribute_t**;
    *(this->attribute_list) = new phez_attribute_t*[PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED];
    for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        (*(this->attribute_list))[i] = nullptr;
    }

    PHEZ_NOTE_PREFIX
    cout << "hdf5_attributes was created" << endl;
}
/** \brief HDF5 attributes class destructor */
hdf5_attributes::~hdf5_attributes(){
    // demalloc stuff

    if(this->get_attribute_list()){
        for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            if((*(this->get_attribute_list()))[i]){
                this->set_current((*(this->get_attribute_list()))[i]);
                switch(this->get_current_state()){
                    case (PHEZ_ATTRIBUTE_STATE_OPENED):
                        this->close();
                        break;
                    case (PHEZ_ATTRIBUTE_STATE_MADE):
                        this->close();
                        break;
                    case (PHEZ_ATTRIBUTE_STATE_READ):
                        this->close();
                        break;
                    case (PHEZ_ATTRIBUTE_STATE_WRITTEN):
                        this->close();
                        break;
                    default:
                        break;
                }
                this->destroy();
                (*(this->attribute_list))[i] = nullptr;
            }
        }

        delete[] *(this->attribute_list);
    }

    //this->set_num(0);

    // free current_ pointer
    delete this->current_attribute;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_attributes was destroyed" << endl;
}

/** \brief Get the address of the attribute that hdf5_attributes is currently pointing to. */
phez_attribute_t* hdf5_attributes::get_current(){
    return(this->current_attribute);
}
/** \brief Set the address of the attribute that hdf5_attributes will point to. */
void hdf5_attributes::set_current(phez_attribute_t* current_attribute_in){
    this->current_attribute = current_attribute_in;
    return;
}
/** \brief Get the num_attributes of hdf5_attributes currently in use. */
size_t hdf5_attributes::get_num(){
    return(this->num_attributes);
}
/** \brief Set the num_attributes of hdf5_attributes currently in use.*/
void hdf5_attributes::set_num(size_t num_attributes_in){
    this->num_attributes = num_attributes_in;
    return;
}
/** \brief Increment the num_attributes of hdf5_attributes currently in use. */
void hdf5_attributes::incr_num(){
    this->num_attributes++;
    return;
}
/** \brief Decrement the num_attributes of hdf5_attributes currently in use.*/
void hdf5_attributes::decr_num(){
    this->num_attributes--;
    return;
}
/** \brief Get the ID of the attribute that hdf5_attributes is currently pointing to. */
hid_t hdf5_attributes::get_current_id(){
    return(this->get_current()->id);
}
/** \brief Set the ID of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_id(hid_t id_in){
    this->get_current()->id = id_in;
    return;
}
/** \brief Get the name of the attribute that hdf5_attributes is currently pointing to. */
char* hdf5_attributes::get_current_name(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot retrieve current attribute name because it is not defined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return(this->get_current()->name);
}
/** \brief Set the name of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_name(char* name_in){
    strcpy(this->get_current()->name, name_in);
    this->set_current_is_name_defined(true);
    return;
}
/** \brief Get the access properties of the attribute that hdf5_attributes is currently pointing to. */
//aapl_t hdf5_attributes::get_current_access_properties(){
//    return(this->get_current()->aapl);
//}
/** \brief Set the access properties of the attribute that hdf5_attributes is currently pointing to. */
//void hdf5_attributes::set_current_access_properties(aapl_t aapl_in){
//    this->get_current()->aapl = aapl_in;
//    return;
//}
/** \brief Get the creation properties of the attribute that hdf5_attributes is currently pointing to. */
acpl_t hdf5_attributes::get_current_creation_properties(){
    return(this->get_current()->acpl);
}
/** \brief Set the creation properties of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_creation_properties(acpl_t acpl_in){
    this->get_current()->acpl = acpl_in;
    return;
}
/** \brief Reset the creation properties of the attribute that hdf5_attributes is currently pointing to to the value on the HDF5 side. */
void hdf5_attributes::reset_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( call_H5Aget_create_plist(this->get_current_id()) );
    return;
}
/** \brief Set the creation properties of the attribute that hdf5_attributes is currently pointing to H5P_DEFAULT. */
void hdf5_attributes::default_current_creation_properties(){
    call_H5Pclose(this->get_current_creation_properties()); // don't leak memory
    this->set_current_creation_properties( (acpl_t)call_H5Pcreate(H5P_ATTRIBUTE_CREATE) );
    return;
}
/** \brief Get the type of the attribute that hdf5_attributes is currently pointing to. */
phez_attribute_type_t hdf5_attributes::get_current_type(){

    if(!this->get_current_is_type_defined()){
        if(this->get_current()->type != PHEZ_ATTRIBUTE_TYPE_INVALID){
            PHEZ_FATAL_PREFIX
            cout << "Cannot retrieve current attribute type because it is not defined." << endl;
            PHEZ_FATAL_SUFFIX
        }
    }

    return(this->get_current()->type);
}
/** \brief Set the type of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_type(phez_attribute_type_t type_in){
    if(this->get_current()->type != PHEZ_ATTRIBUTE_TYPE_INVALID){
        //call_H5Tclose((hid_t)this->get_current_type());
    }

    this->get_current()->type = type_in;

    if(type_in == PHEZ_ATTRIBUTE_TYPE_INVALID){
        this->set_current_is_type_defined(false);
    }else{
        this->set_current_is_type_defined(true);
    }

    return;
}
/** \brief Get the data of the dataset that hdf5_datasets is currently pointing to. */
nullptr_t* hdf5_attributes::get_current_data(){
    return(nullptr); // Can't do it the normal way, C++ is stupid sometimes.
}
/** \brief Set the data pointer of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_data(nullptr_t* data_in){
    this->get_current()->data = data_in;
    this->set_current_is_name_defined(false);
    return;
}
/** \brief Get the comment of the group that hdf5_attributes is currently pointing to. */
phez_attribute_state_t hdf5_attributes::get_current_state(){
    return(this->get_current()->state);
}
/** \brief Set the comment of the group that hdf5_attributes is currently pointing to.*/
void hdf5_attributes::set_current_state(phez_attribute_state_t state_in){

    switch(state_in){
        case(PHEZ_ATTRIBUTE_STATE_DEFINED):
            break;
        case(PHEZ_ATTRIBUTE_STATE_OPENED):
            break;
        case(PHEZ_ATTRIBUTE_STATE_MADE):
            break;
        case(PHEZ_ATTRIBUTE_STATE_READ):
            break;
        case(PHEZ_ATTRIBUTE_STATE_WRITTEN):
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Cannot set current attribute state; state is invalid." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->get_current()->state = state_in;
    return;
}
/** \brief Get whether the name of the attribute that hdf5_attributes is currently pointing to is defined. */
bool hdf5_attributes::get_current_is_name_defined(){
    return(this->get_current()->state_name);
}
/** \brief Set whether the name of the attribute that hdf5_attributes is currently pointing to is defined. */
void hdf5_attributes::set_current_is_name_defined(bool state_name_in){
    this->get_current()->state_name = state_name_in;
    return;
}
/** \brief Get whether the type of the attribute that hdf5_attributes is currently pointing to is defined. */
bool hdf5_attributes::get_current_is_type_defined(){
    return(this->get_current()->state_type);
}
/** \brief Set whether the type of the attribute that hdf5_attributes is currently pointing to is defined. */
void hdf5_attributes::set_current_is_type_defined(bool state_type_in){
    this->get_current()->state_type = state_type_in;
    return;
}
/** \brief Get whether the data of the attribute that hdf5_attributes is currently pointing to is defined. */
bool hdf5_attributes::get_current_is_data_defined(){
    return(this->get_current()->state_data);
}
/** \brief Set whether the data of the attribute that hdf5_attributes is currently pointing to is defined. */
void hdf5_attributes::set_current_is_data_defined(bool state_data_in){
    this->get_current()->state_data = state_data_in;
    return;
}
/** \brief Set the num_datasets_linking of the attribute that hdf5_attributes is currently pointing to. */
size_t hdf5_attributes::get_current_num_datasets_linking(){
    return(this->get_current()->num_datasets_linking);
}
/** \brief Get the num_datasets_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_num_datasets_linking(size_t num_datasets_linking_in){
    this->get_current()->num_datasets_linking = num_datasets_linking_in;
    return;
}
/** \brief Set the num_groups_linking of the attribute that hdf5_attributes is currently pointing to. */
size_t hdf5_attributes::get_current_num_groups_linking(){
    return(this->get_current()->num_groups_linking);
}
/** \brief Get the num_groups_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_num_groups_linking(size_t num_groups_linking_in){
    this->get_current()->num_groups_linking = num_groups_linking_in;
    return;
}
/** \brief Set the num_files_linking of the attribute that hdf5_attributes is currently pointing to. */
size_t hdf5_attributes::get_current_num_files_linking(){
    return(this->get_current()->num_files_linking);
}
/** \brief Get the num_files_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::set_current_num_files_linking(size_t num_files_linking_in){
    this->get_current()->num_files_linking = num_files_linking_in;
    return;
}
/** \brief Increment the num_datasets_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::incr_current_num_datasets_linking(){
    this->get_current()->num_datasets_linking++;
    return;
}
/** \brief Decrement the num_datasets_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::decr_current_num_datasets_linking(){
    this->get_current()->num_datasets_linking--;
    return;
}
/** \brief Increment the num_groups_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::incr_current_num_groups_linking(){
    this->get_current()->num_groups_linking++;
    return;
}
/** \brief Decrement the num_groups_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::decr_current_num_groups_linking(){
    this->get_current()->num_groups_linking--;
    return;
}
/** \brief Increment the num_files_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::incr_current_num_files_linking(){
    this->get_current()->num_files_linking++;
    return;
}
/** \brief Decrement the num_files_linking of the attribute that hdf5_attributes is currently pointing to. */
void hdf5_attributes::decr_current_num_files_linking(){
    this->get_current()->num_files_linking--;
    return;
}

phez_space_t* hdf5_attributes::get_current_linked_space(){
    return(this->get_current()->linked_space);
}
void hdf5_attributes::set_current_linked_space(phez_space_t* space_in){
    this->get_current()->linked_space = space_in;
    return;
}
/** \brief Get the attribute list. */
phez_attribute_t*** hdf5_attributes::get_attribute_list(){
    return(this->attribute_list);
}

phez_attribute_t* hdf5_attributes::lookup_by_name(char*){
    return(nullptr);
}
phez_attribute_t* hdf5_attributes::lookup_by_id(hid_t){
    return(nullptr);
}
/** \brief Creates a new hdf5_attribute struct and returns its address. */
phez_attribute_t* hdf5_attributes::initialize(){
    /** Fail immediately if it would exceed the maximum number
        of active attributes allowed */
    if(this->get_num() >= PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot initialize another attribute struct; the maximum is ";
        cout << PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED << "." << endl;
        PHEZ_FATAL_SUFFIX
        return nullptr;
    }else{
        /*Local variables*/
        int i;

        /** Find empty pointer in the attribute_list.*/
        for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            if(!(*(this->attribute_list))[i]){
                phez_attribute_t* astruct = new phez_attribute_t;
                (*(this->attribute_list))[i] = astruct;
                this->set_current((*(this->attribute_list))[i]);
                break;
            }
        }

        /** Allocate chars. */
        this->get_current()->name = new char[PHEZ_MAX_NAME_LENGTH];

        /** Set id to invalid.*/
        this->set_current_id(PHEZ_ATTRIBUTE_ID_INVALID);

        /** Set attribute name and comment to null. */
        strcpy(this->get_current()->name, (char*)"");

        /** Initialize attribute access and creation property lists with default settings. */
        this->set_current_creation_properties( (acpl_t)call_H5Pcreate(H5P_ATTRIBUTE_CREATE) );

        /** Set type to invalid. */
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_TYPE_INVALID);

        /** Set data to nullptr. */
        this->set_current_data(nullptr);

        /** Set inward link count to zero */
        this->set_current_num_datasets_linking(0);
        this->set_current_num_groups_linking(0);
        this->set_current_num_files_linking(0);

        /** Set each object pointer to nullptr.*/
        this->set_current_linked_space(nullptr);

        /** Set initial state to DEFINED_NONE. */
        this->set_current_state(PHEZ_ATTRIBUTE_STATE_DEFINED);
        this->set_current_is_name_defined(false);
        this->set_current_is_type_defined(false);
        this->set_current_is_data_defined(false);

        /** Increment the number of attributes. */
        this->incr_num();
        return(this->get_current());
    }
}

/** \brief Opens an existing attribute and copies info to struct */
void hdf5_attributes::open(hid_t obj_id){

    this->check_current_state_can_open();

    htri_t status;
    hid_t attrid;
    hid_t attrtype;

    status = call_H5Aexists(obj_id,
                            this->get_current_name());

    if(status == 0){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open attribute; attribute does not exist." << endl;
        PHEZ_FATAL_SUFFIX
    }

    attrid = call_H5Aopen(obj_id,
                          this->get_current_name(),
                          //this->get_current_access_properties()
                          H5P_DEFAULT);
    this->set_current_id(attrid);

    attrtype = call_H5Aget_type(attrid);
    if(call_H5Tequal(attrtype, PHEZ_ATTRIBUTE_DATA_TYPE_BOOL)){
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_DATA_TYPE_BOOL);
    }else if(call_H5Tequal(attrtype, PHEZ_ATTRIBUTE_DATA_TYPE_INT)){
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_DATA_TYPE_INT);
    }else if(call_H5Tequal(attrtype, PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT)){
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    }else if(call_H5Tequal(attrtype, PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE)){
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE);
    }else if(call_H5Tequal(attrtype, PHEZ_ATTRIBUTE_DATA_TYPE_STRING)){
        this->set_current_type((phez_attribute_type_t)PHEZ_ATTRIBUTE_DATA_TYPE_STRING);
    }else{
    	PHEZ_FATAL_PREFIX
		cout << "Cannot open because the attribute's data type is not supported by this library.";
		PHEZ_FATAL_SUFFIX
    }

    //call_H5Tclose(attrid); // crashes for some reason but leaks memory without it

    this->update_current_state_opened();

    return;
}

/** \brief Read the data of an existing HDF5 attribute */
void hdf5_attributes::read(){

    /**> If a data buffer wasn't passed in, allocate one. */
    if(!this->get_current_is_data_defined()){
        if(this->get_current_linked_space()){
            if(this->get_current_linked_space()->dims_max){
                int ndims, dims_prod;
                ndims = this->get_current_linked_space()->size;
                dims_prod = 1;
                for(int i = 0; i < ndims; i++){
                    dims_prod *= this->get_current_linked_space()->dims_max[i];
                }

                if(this->get_current_type() == PHEZ_ATTRIBUTE_DATA_TYPE_BOOL){
                    this->set_current_data( new bool[dims_prod] );
                }else if(this->get_current_type() == PHEZ_ATTRIBUTE_DATA_TYPE_INT){
                    this->set_current_data( new int[dims_prod] );
                }else if(this->get_current_type() == PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT){
                    this->set_current_data( new float[dims_prod] );
                }else if(this->get_current_type() == PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE){
                    this->set_current_data( new double[dims_prod] );
                }else if(this->get_current_type() == PHEZ_ATTRIBUTE_DATA_TYPE_STRING){
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

    /**> Call H5Aread. */
    call_H5Aread(this->get_current_id(),
                 (hid_t)this->get_current_type(),
                 this->get_current_data<void>());

    /**> Update the current attribute's state to "read." */
    this->update_current_state_read();

    return;
}

/** \brief Create HDF5 attribute with struct info. Multiple copies of the same attribute can
            be written by make->write->close->make... */
void hdf5_attributes::make(hid_t obj_id){

    this->check_current_state_can_make();

    hid_t space_id;
    if(this->get_current_linked_space() &&
       this->get_current_linked_space()->id != PHEZ_SPACE_ID_INVALID){
        space_id = this->get_current_linked_space()->id;
    }else{
        space_id = H5S_ALL;
    }

    hid_t attrid;

    attrid = call_H5Acreate(obj_id,
                            this->get_current_name(),
                            (hid_t)this->get_current_type(),
                            space_id,
                            this->get_current_creation_properties(),
                            //this->get_current_access_properties()
                            H5P_DEFAULT);
    this->set_current_id(attrid);

    this->update_current_state_made();

    return;
}

/** \brief Writes an attribute to file */
void hdf5_attributes::write(){

    this->check_current_state_can_write();

    call_H5Awrite(this->get_current_id(),
                  (hid_t)this->get_current_type(),
                  this->get_current_data<void>());

    this->update_current_state_written();

    return;
}

/** \brief Closes an existing attribute */
void hdf5_attributes::close(){

    this->check_current_state_can_close();

    hid_t h5id;

    h5id = this->get_current_id();
    call_H5Aclose(h5id);

    /** Set id to be invalid.*/
    this->set_current_id(PHEZ_ATTRIBUTE_ID_INVALID);

    /** Return state to defined */
    this->update_current_state_closed();

    return;
}

/** \brief Destroys an hdf5_attribute struct */
void hdf5_attributes::destroy(){

    if(!this->get_current()){
        PHEZ_FATAL_PREFIX
        cout << "Trying to destroy a nonexistent attribute." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        if( this->get_current_num_files_linking() != 0 || \
            this->get_current_num_groups_linking() != 0 || \
            this->get_current_num_datasets_linking() != 0){
            PHEZ_FATAL_PREFIX
            cout << "Cannot destroy this attribute because " << this->get_current_num_files_linking();
            cout << " files, " << this->get_current_num_groups_linking();
            cout << " groups, and " << this->get_current_num_datasets_linking();
            cout << " datasets are still linking to it." << endl;
            PHEZ_FATAL_SUFFIX
        }else{

            hid_t h5id;

            h5id = (hid_t)this->get_current_creation_properties();
            call_H5Pclose(h5id);

            this->set_current_id(0);
            delete[] this->get_current()->name;
            //this->set_current_access_properties(0);
            this->set_current_creation_properties(0);

            this->set_current_data(0);

            this->get_current()->type = (phez_attribute_type_t)0;

            this->set_current_num_datasets_linking(0);
            this->set_current_num_groups_linking(0);
            this->set_current_num_files_linking(0);

            if(this->get_current_linked_space()){
                this->unlink_space();
            }

            /** Set state to zero. */
            this->get_current()->state = (phez_attribute_state_t)0;

            /** Free the phez_attribute_t object.*/
            delete this->current_attribute;

            /** Set the attribute_list slot to nullptr. */
            for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                if((*(this->get_attribute_list()))[i]){
                    if((*(this->get_attribute_list()))[i] == this->get_current()){
                        (*(this->get_attribute_list()))[i] = nullptr;
                    }
                }
            }

            /** Set initial state to DEFINED_NONE. */
            this->set_current_state(PHEZ_ATTRIBUTE_STATE_DEFINED);
            this->set_current_is_name_defined(false);
            this->set_current_is_type_defined(false);
            this->set_current_is_data_defined(false);

            this->set_current((phez_attribute_t*)nullptr);

            this->decr_num();
        }
    }

    return;
}
void hdf5_attributes::link_space(phez_space_t* space_in){
    if(space_in == this->get_current_linked_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot link this space; it is already linked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->set_current_linked_space(space_in);
        space_in->num_attributes_linking++;
    }
    return;
}
void hdf5_attributes::unlink_space(){
    if(!this->get_current_linked_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot unlink this space; it is already unlinked." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        this->get_current_linked_space()->num_attributes_linking--;
        this->set_current_linked_space((phez_space_t*)nullptr);
    }
    return;
}

/** \brief Trap open calls if some of the parameters it needs are undefined. */
void hdf5_attributes::check_current_state_can_open(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot open attribute because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_ATTRIBUTE_STATE_DEFINED):
            break;
        case(PHEZ_ATTRIBUTE_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open attribute because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open attribute because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_READ):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open attribute because it is already read." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_WRITTEN):
            PHEZ_FATAL_PREFIX
            cout << "Cannot open attribute because it is already written." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap make calls if some of the parameters it needs are undefined. */
void hdf5_attributes::check_current_state_can_make(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make attribute because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make attribute because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_linked_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot make attribute because it does not link to a space." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_ATTRIBUTE_STATE_DEFINED):
            break;
        case(PHEZ_ATTRIBUTE_STATE_OPENED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make attribute because it is already open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make attribute because it is already made." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_READ):
            //PHEZ_FATAL_PREFIX
            //cout << "Cannot make attribute because it is already read." << endl;
            //PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_WRITTEN):
            PHEZ_FATAL_PREFIX
            cout << "Cannot make attribute because it is already written." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap read calls if some of the parameters it needs are undefined. */
void hdf5_attributes::check_current_state_can_read(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read attribute because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read attribute because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_data_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot read attribute because the data is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }

    switch(this->get_current_state()){
        case(PHEZ_ATTRIBUTE_STATE_OPENED):
            break;
        case(PHEZ_ATTRIBUTE_STATE_READ):
            break;
        case(PHEZ_ATTRIBUTE_STATE_WRITTEN):
            break;
        case(PHEZ_ATTRIBUTE_STATE_DEFINED):
            PHEZ_FATAL_PREFIX
            cout << "Cannot read attribute because it is not open." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_ATTRIBUTE_STATE_MADE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot read attribute because it has not been written yet." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            break;
    }

    return;
}
/** \brief Trap write calls if some of the parameters it needs are undefined. */
void hdf5_attributes::check_current_state_can_write(){

    if(!this->get_current_is_name_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write attribute because the name is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_type_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write attribute because the type is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_is_data_defined()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write attribute because the data is undefined." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(!this->get_current_linked_space()){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write attribute because it does not link to a space." << endl;
        PHEZ_FATAL_SUFFIX
    }
    if(this->get_current_state() == PHEZ_ATTRIBUTE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot write attribute because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
/** \brief Trap close calls if nothing is open. */
void hdf5_attributes::check_current_state_can_close(){

    if(this->get_current_state() == PHEZ_ATTRIBUTE_STATE_DEFINED){
        PHEZ_FATAL_PREFIX
        cout << "Cannot close attribute because it is not open." << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_attributes::update_current_state_opened(){

    if(this->get_current_state() == PHEZ_ATTRIBUTE_STATE_DEFINED &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_ATTRIBUTE_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current attribute state to opened,";
        cout << " when the original state is not allowed to open. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_attributes::update_current_state_made(){

    if(this->get_current_state() == PHEZ_ATTRIBUTE_STATE_DEFINED &&
       this->get_current_is_name_defined()                 &&
       this->get_current_is_type_defined()){

        this->set_current_state(PHEZ_ATTRIBUTE_STATE_OPENED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current attribute state to made,";
        cout << " when the original state is not allowed to make. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_attributes::update_current_state_read(){

    if((this->get_current_state() == PHEZ_ATTRIBUTE_STATE_OPENED   ||
        this->get_current_state() == PHEZ_ATTRIBUTE_STATE_READ     ||
        this->get_current_state() == PHEZ_ATTRIBUTE_STATE_WRITTEN) &&
       this->get_current_is_data_defined()                   &&
       this->get_current_is_type_defined()                   &&
       this->get_current_is_name_defined()){

        this->set_current_state(PHEZ_ATTRIBUTE_STATE_READ);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current attribute state to read,";
        cout << " when the original state is not allowed to read. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_attributes::update_current_state_written(){

    if((this->get_current_state() == PHEZ_ATTRIBUTE_STATE_OPENED ||
        this->get_current_state() == PHEZ_ATTRIBUTE_STATE_MADE   ||
        this->get_current_state() == PHEZ_ATTRIBUTE_STATE_READ)  &&
       this->get_current_is_data_defined()                &&
       this->get_current_is_type_defined()                &&
       this->get_current_is_name_defined()                &&
       this->get_current_linked_space()){

        this->set_current_state(PHEZ_ATTRIBUTE_STATE_MADE);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current attribute state to written,";
        cout << " when the original state is not allowed to write. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
void hdf5_attributes::update_current_state_closed(){

    if(this->get_current_state() != PHEZ_ATTRIBUTE_STATE_DEFINED){
        this->set_current_state(PHEZ_ATTRIBUTE_STATE_DEFINED);
    }else{
        PHEZ_FATAL_PREFIX
        cout << "Attempted to update current attribute state to closed,";
        cout << " when the original state is not allowed to close. (This should never happen!)" << endl;
        PHEZ_FATAL_SUFFIX
    }

    return;
}
