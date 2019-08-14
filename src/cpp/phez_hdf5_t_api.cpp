#include <cmath>
#include <iostream>

#include "phez_hdf5_t_api.hpp"
#include "phez_macros.hpp"

/************************ HDF5 class functions ********************************/
/** \brief HDF5 class constructor */
hdf5_class::hdf5_class(){
    this->indx_min = 0;
    this->indx_max = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                        + PHEZ_MAX_NUM_GROUPS_ALLOWED
                        + PHEZ_MAX_NUM_DATASETS_ALLOWED
                        + PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED
                        + PHEZ_MAX_NUM_SPACES_ALLOWED;
    this->indx_range = this->indx_max - this->indx_min;
    this->hash_base = 62;
    this->hash_digits = (size_t)(log(this->indx_range) / log(this->hash_base)) + 1;

    char* hash_chars;
    hash_chars = new char[this->hash_base];
    this->hash_list = new phez_hash_pair_t[this->hash_base];

    // init hash_char array
    //hash_chars = (char*)"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    hash_chars[0] = '0';
    hash_chars[1] = '1';
    hash_chars[2] = '2';
    hash_chars[3] = '3';
    hash_chars[4] = '4';
    hash_chars[5] = '5';
    hash_chars[6] = '6';
    hash_chars[7] = '7';
    hash_chars[8] = '8';
    hash_chars[9] = '9';
    hash_chars[10] = 'a';
    hash_chars[11] = 'b';
    hash_chars[12] = 'c';
    hash_chars[13] = 'd';
    hash_chars[14] = 'e';
    hash_chars[15] = 'f';
    hash_chars[16] = 'g';
    hash_chars[17] = 'h';
    hash_chars[18] = 'i';
    hash_chars[19] = 'j';
    hash_chars[20] = 'k';
    hash_chars[21] = 'l';
    hash_chars[22] = 'm';
    hash_chars[23] = 'n';
    hash_chars[24] = 'o';
    hash_chars[25] = 'p';
    hash_chars[26] = 'q';
    hash_chars[27] = 'r';
    hash_chars[28] = 's';
    hash_chars[29] = 't';
    hash_chars[30] = 'u';
    hash_chars[31] = 'v';
    hash_chars[32] = 'w';
    hash_chars[33] = 'x';
    hash_chars[34] = 'y';
    hash_chars[35] = 'z';
    hash_chars[36] = 'A';
    hash_chars[37] = 'B';
    hash_chars[38] = 'C';
    hash_chars[39] = 'D';
    hash_chars[40] = 'E';
    hash_chars[41] = 'F';
    hash_chars[42] = 'G';
    hash_chars[43] = 'H';
    hash_chars[44] = 'I';
    hash_chars[45] = 'J';
    hash_chars[46] = 'K';
    hash_chars[47] = 'L';
    hash_chars[48] = 'M';
    hash_chars[49] = 'N';
    hash_chars[50] = 'O';
    hash_chars[51] = 'P';
    hash_chars[52] = 'Q';
    hash_chars[53] = 'R';
    hash_chars[54] = 'S';
    hash_chars[55] = 'T';
    hash_chars[56] = 'U';
    hash_chars[57] = 'V';
    hash_chars[58] = 'W';
    hash_chars[59] = 'X';
    hash_chars[60] = 'Y';
    hash_chars[61] = 'Z';

    // sort the characters by value to ensure they are ordinal;
    // this guarantees that we can use binary search for dehashing
    char tmp;
    for (int i = 1; i < this->hash_base; ++i){
        for (int j = i; j > 0 && hash_chars[j] < hash_chars[j-1]; --j){
                tmp = hash_chars[j-1];
                hash_chars[j-1] = hash_chars[j];
                hash_chars[j] = tmp;
        }
    }

    for(int i = 0; i < this->hash_base; i++){
        this->hash_list[i].number = i;
        this->hash_list[i].digit = hash_chars[i];
    }

    this->space = new hdf5_spaces;
    this->attribute = new hdf5_attributes;
    this->dataset = new hdf5_datasets;
    this->group = new hdf5_groups;
    this->file = new hdf5_files;

    this->stash_fptr = nullptr;
    this->stash_gptr = nullptr;
    this->stash_dptr = nullptr;
    this->stash_aptr = nullptr;
    this->stash_sptr = nullptr;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_class was created" << endl;
}
/** \brief HDF5 class destructor */
hdf5_class::~hdf5_class(){

    /** Unlink everything from everything else here. */
    phez_attribute_t* lnk_attribute;
    phez_dataset_t* lnk_dataset;
    phez_group_t* lnk_group;
    phez_attribute_t* current_attribute;
    phez_dataset_t* current_dataset;
    phez_group_t* current_group;
    phez_file_t* current_file;

    /** Unlink everything the files are linking to.*/
    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        current_file = (*(this->file->get_file_list()))[i];
        if(current_file){
            this->file->set_current(current_file);

            if(this->file->get_current_linked_attributes()){
                for(int j=0; j < PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED; j++){
                    lnk_attribute = (*(this->file->get_current_linked_attributes()))[j];
                    if(lnk_attribute){
                        this->file->unlink_attribute(lnk_attribute);
                    }
                }
            }
            this->file->get_current()->linked_attributes = nullptr;

            if(this->file->get_current_linked_datasets()){
                for(int j=0; j < PHEZ_MAX_NUM_DATASETS_ALLOWED; j++){
                    lnk_dataset = (*(this->file->get_current_linked_datasets()))[j];
                    if(lnk_dataset){
                        this->file->unlink_dataset(lnk_dataset);
                    }
                }
            }
            this->file->get_current()->linked_datasets = nullptr;

            if(this->file->get_current_linked_groups()){
                for(int j=0; j < PHEZ_MAX_NUM_GROUPS_ALLOWED; j++){
                    lnk_group = (*(this->file->get_current_linked_groups()))[j];
                    if(lnk_group){
                        this->file->unlink_group(lnk_group);
                    }
                }
            }
            this->file->get_current()->linked_attributes = nullptr;
        }
    }

    /** Unlink everything the groups are linking to.*/
    for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
        current_group = (*(this->group->get_group_list()))[i];
        if(current_group){
            this->group->set_current(current_group);

            if(this->group->get_current_linked_attributes()){
                for(int j=0; j < PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED; j++){
                    lnk_attribute = (*(this->group->get_current_linked_attributes()))[j];
                    if(lnk_attribute){
                        this->group->unlink_attribute(lnk_attribute);
                    }
                }
            }
            this->group->get_current()->linked_attributes = nullptr;

            if(this->group->get_current_linked_datasets()){
                for(int j=0; j < PHEZ_MAX_NUM_DATASETS_ALLOWED; j++){
                    lnk_dataset = (*(this->group->get_current_linked_datasets()))[j];
                    if(lnk_dataset){
                        this->group->unlink_dataset(lnk_dataset);
                    }
                }
            }
            this->group->get_current()->linked_datasets = nullptr;

            if(this->group->get_current_linked_groups()){
                for(int j=0; j < PHEZ_MAX_NUM_GROUPS_ALLOWED; j++){
                    lnk_group = (*(this->group->get_current_linked_groups()))[j];
                    if(lnk_group){
                        this->group->unlink_group(lnk_group);
                    }
                }
            }
            this->group->get_current()->linked_attributes = nullptr;
        }
    }

    /** Unlink everything the datasets are linking to.*/
    for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
        current_dataset = (*(this->dataset->get_dataset_list()))[i];
        if(current_dataset){
            this->dataset->set_current(current_dataset);

            if(this->dataset->get_current_linked_file_space()){
                this->dataset->unlink_file_space();
            }

            if(this->dataset->get_current_linked_memory_space()){
                this->dataset->unlink_memory_space();
            }

            if(this->dataset->get_current_linked_attributes()){
                for(int j=0; j < PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED; j++){
                    lnk_attribute = (*(this->dataset->get_current_linked_attributes()))[j];
                    if(lnk_attribute){
                        this->dataset->unlink_attribute(lnk_attribute);
                    }
                }
            }
            this->dataset->get_current()->linked_attributes = nullptr;
        }
    }

    /** Unlink everything the attributes are linking to.*/
    for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
        current_attribute = (*(this->attribute->get_attribute_list()))[i];
        if(current_attribute){
            this->attribute->set_current(current_attribute);

            if(this->attribute->get_current_linked_space()){
                this->attribute->unlink_space();
            }
        }
    }

    delete this->file;
    delete this->group;
    delete this->dataset;
    delete this->attribute;
    delete this->space;

    PHEZ_NOTE_PREFIX
    cout << "hdf5_class was destroyed" << endl;
}


void hdf5_class::open_spaces(phez_object_t parent){
    /* Local variables */

    phez_space_t* sptr = nullptr;

    switch(parent.type){
        case(PHEZ_DATASET):

            sptr = this->dataset->get_current_linked_file_space();
            if(sptr){
                this->space->set_current(sptr);
                this->space->open(this->dataset->get_current_id());
            }

            break;

        case(PHEZ_ATTRIBUTE):

            sptr = this->attribute->get_current_linked_space();
            if(sptr){
                this->space->set_current(sptr);
                this->space->open(this->attribute->get_current_id());
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to open spaces for an object other than a dataset or attribute." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    return;
}

void hdf5_class::make_spaces(phez_object_t parent){
    /* Local variables */

    phez_space_t* sptr = nullptr;

    switch(parent.type){
        case(PHEZ_DATASET):

            sptr = this->dataset->get_current_linked_memory_space();
            if(sptr){
                this->space->set_current(sptr);
                this->space->make();
            }

            sptr = this->dataset->get_current_linked_file_space();
            if(sptr){
                this->space->set_current(sptr);
                this->space->make();
            }

            break;

        case(PHEZ_ATTRIBUTE):

            sptr = this->attribute->get_current_linked_space();
            if(sptr){
                this->space->set_current(sptr);
                this->space->make();
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to make spaces for an object other than a dataset or attribute." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    return;
}

void hdf5_class::close_spaces(phez_object_t parent){
    /* Local variables */

    phez_space_t* sptr = nullptr;

    switch(parent.type){
        case(PHEZ_DATASET):

            this->dataset->set_current(parent.ptr.d);

            sptr = this->dataset->get_current_linked_memory_space();
            if(sptr){
                this->space->set_current(sptr);
                if(this->space->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
                    this->space->close();
                }
            }

            sptr = this->dataset->get_current_linked_file_space();
            if(sptr){
                this->space->set_current(sptr);
                if(this->space->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
                    this->space->close();
                }
            }
            break;

        case(PHEZ_ATTRIBUTE):

            this->attribute->set_current(parent.ptr.a);

            sptr = this->attribute->get_current_linked_space();
            if(sptr){
                this->space->set_current(sptr);
                if(this->space->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
                    this->space->close();
                }
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to close spaces for an object other than a dataset or attribute." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    return;
}

template<typename FUNC> void hdf5_class::iterate_attributes(phez_object_t parent, FUNC func){


    /* Local variables */
    hid_t parent_id;                        /**< Parent object's id */
    phez_object_t child;
    child.type = PHEZ_ATTRIBUTE;
    phez_attribute_t*** links = nullptr;
    size_t link_ct;

    switch(parent.type){
        case(PHEZ_FILE):
            links = this->file->get_current_linked_attributes();
            link_ct = this->file->get_current_num_linked_attributes();
            parent_id = this->file->get_current_id();
            break;

        case(PHEZ_GROUP):
            links = this->group->get_current_linked_attributes();
            link_ct = this->group->get_current_num_linked_attributes();
            parent_id = this->group->get_current_id();
            break;

        case(PHEZ_DATASET):
            links = this->dataset->get_current_linked_attributes();
            link_ct = this->dataset->get_current_num_linked_attributes();
            parent_id = this->dataset->get_current_id();
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to iterate attributes for an object other than a file, group, or dataset." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    if(links){
        size_t ct = 0;        /**< current attribute count (used for short-circuiting) */
        for(int i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
            child.ptr.a = (*links)[i];
            if(child.ptr.a){
                this->attribute->set_current(child.ptr.a);
                ct++;

                func(parent_id, child);

                if(ct >= link_ct) break;
            }
        }
    }

    return;
}

template<typename FUNC> void hdf5_class::iterate_datasets(phez_object_t parent, FUNC func){

    /* Local variables */
    hid_t parent_id;                        /**< Parent object's id */
    phez_object_t child;
    child.type = PHEZ_DATASET;
    phez_dataset_t*** links = nullptr;
    size_t link_ct;

    switch(parent.type){
        case(PHEZ_FILE):
            links = this->file->get_current_linked_datasets();
            link_ct = this->file->get_current_num_linked_datasets();
            parent_id = this->file->get_current_id();
            break;

        case(PHEZ_GROUP):
            links = this->group->get_current_linked_datasets();
            link_ct = this->group->get_current_num_linked_datasets();
            parent_id = this->group->get_current_id();
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to flush datasets for an object other than a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    /* Loop through links to create the correct file structure. We only need to
       loop through the first layer, the iterators will cascade
       downward to lower levels. */

    if(links){
        size_t ct = 0;        /**< current dataset count (used for short-circuiting) */
        for(int i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
            child.ptr.d = (*links)[i];
            if(child.ptr.d){
                this->dataset->set_current(child.ptr.d);
                ct++;

                func(parent_id, child);

                if(ct >= link_ct) break;
            }
        }
    }

    return;
}

template<typename FUNC> void hdf5_class::iterate_groups(phez_object_t parent, FUNC func){

    /* Local variables */
    hid_t parent_id;                        /**< Parent object's id */
    phez_object_t child;
    child.type = PHEZ_GROUP;
    phez_group_t*** links = nullptr;
    size_t link_ct;

    switch(parent.type){
        case(PHEZ_FILE):
            links = this->file->get_current_linked_groups();
            link_ct = this->file->get_current_num_linked_groups();
            parent_id = this->file->get_current_id();
            break;

        case(PHEZ_GROUP):
            links = this->group->get_current_linked_groups();
            link_ct = this->group->get_current_num_linked_groups();
            parent_id = this->group->get_current_id();
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to populate groups for an object other than a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    /* Loop through links to create the correct file structure. We only need to
       loop through the first layer, the iterators will cascade
       downward to lower levels. */

    if(links){
        size_t ct = 0;        /**< current group count (used for short-circuiting) */
        for(int i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
            child.ptr.g = (*links)[i];
            if(child.ptr.g){
                this->group->set_current(child.ptr.g);
                ct++;

                func(parent_id, child);

                if(ct >= link_ct) break;
            }
        }
    }

    return;
}

/** \brief Iterate over the current object, then everything inside. This can be used to easily build new recursive functions. */
template<typename FFUNC,
         typename GFUNC,
         typename DFUNC,
         typename AFUNC,
         typename SFUNC> void hdf5_class::iterate(phez_hash_t* hash_in, FFUNC ffunc,
                                                                        GFUNC gfunc,
                                                                        DFUNC dfunc,
                                                                        AFUNC afunc,
                                                                        SFUNC sfunc){

    this->stash_current_pointers();

    hid_t parent_id; /* Parent group ID (especially needed if parent and child are both groups) */
    phez_object_t object;
    object = this->dehash(hash_in);

    if(object.type == PHEZ_FILE){

        this->file->set_current(object.ptr.f);

        ffunc(object);

    }else{

        phez_object_t parent;
        parent = this->dehash(this->get_hash_parent(hash_in));

        switch(parent.type){
            case(PHEZ_GROUP):
                this->group->set_current(parent.ptr.g);
                parent_id = this->group->get_current_id();
                break;

            case(PHEZ_DATASET):
                this->dataset->set_current(parent.ptr.d);
                parent_id = this->dataset->get_current_id();
                break;

            case(PHEZ_ATTRIBUTE):
                this->attribute->set_current(parent.ptr.a);
                parent_id = this->attribute->get_current_id();
                break;

            case(PHEZ_SPACE):
                PHEZ_FATAL_PREFIX
                cout << "Spaces cannot be parent objects." << endl;
                PHEZ_FATAL_SUFFIX
                break;

            default:
                PHEZ_FATAL_PREFIX
                cout << "Tried to iterate an object with an invalid parent object type." << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }

        switch(object.type){
            case(PHEZ_GROUP):
                this->group->set_current(object.ptr.g);
                gfunc(parent_id, object);
                break;

            case(PHEZ_DATASET):
                this->dataset->set_current(object.ptr.d);
                dfunc(parent_id, object);
                break;

            case(PHEZ_ATTRIBUTE):
                this->attribute->set_current(object.ptr.a);
                afunc(parent_id, object);
                break;

            case(PHEZ_SPACE):
                this->space->set_current(object.ptr.s);
                sfunc(parent_id, object);
                break;

            default:
                PHEZ_FATAL_PREFIX
                cout << "Tried to iterate an object with an invalid object type." << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }

    }

    this->pop_current_pointers();

    return;
}

void hdf5_class::populate_attributes(phez_object_t parent){

    this->iterate_attributes(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->open_spaces(child);
        this->attribute->open(parent_id);
        this->attribute->read();
        this->close_spaces(child);
        this->attribute->close();
    });

    return;
}

void hdf5_class::populate_datasets(phez_object_t parent){

    this->iterate_datasets(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->open_spaces(child);
        this->dataset->open(parent_id);

        this->populate_attributes(child);

        this->dataset->read();
        this->close_spaces(child);
        this->dataset->close();
    });

    return;
}

void hdf5_class::populate_groups(phez_object_t parent){

    this->iterate_groups(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->group->open(parent_id);

        this->populate_attributes(child);
        this->populate_datasets(child);
        this->populate_groups(child); // recursion!

        this->group->set_current(child.ptr.g);
        this->group->close();
    });

    return;
}

/** \brief Iterate through a discovered file, reading in all the object data. */
void hdf5_class::populate(phez_hash_t* hash_in){
    this->stash_current_pointers();

    hid_t parent_id; /* Parent group ID (especially needed if parent and child are both groups) */
    phez_object_t object;
    object = this->dehash(hash_in);

    if(object.type == PHEZ_FILE){

        this->file->set_current(object.ptr.f);

        // We CANNOT use the the call_ macro here, because it will crash the whole program
        // if the file doesn't exist. We need it to do something somewhat different...
        int fstat;
        fstat = H5Fis_hdf5(this->file->get_current_name());

        if(fstat > 0){ // exists
            this->file->set_current_action(PHEZ_FILE_ACTION_APPEND);
            this->file->open();
        }else if(fstat < 0){ // doesn't exist
            PHEZ_FATAL_PREFIX
            cout << "Cannot populate because file does not exist." << endl;
            PHEZ_FATAL_SUFFIX
        }else{ // non-HDF5
            PHEZ_FATAL_PREFIX
            cout << "Cannot populate because file is not an HDF5 file." << endl;
            PHEZ_FATAL_SUFFIX
        }

        this->populate_attributes(object);
        this->populate_datasets(object);
        this->populate_groups(object);

        this->file->close();

    }else{

        phez_object_t parent_object;
        parent_object = this->dehash(this->get_hash_parent(hash_in));

        switch(parent_object.type){
            case(PHEZ_GROUP):
                this->group->set_current(parent_object.ptr.g);
                parent_id = this->group->get_current_id();
                break;

            case(PHEZ_DATASET):
                this->dataset->set_current(parent_object.ptr.d);
                parent_id = this->dataset->get_current_id();
                break;

            case(PHEZ_ATTRIBUTE):
                this->attribute->set_current(parent_object.ptr.a);
                parent_id = this->attribute->get_current_id();
                break;

            case(PHEZ_SPACE):
                PHEZ_FATAL_PREFIX
                cout << "Tried to populate a space." << endl;
                PHEZ_FATAL_SUFFIX
                break;

            default:
                PHEZ_FATAL_PREFIX
                cout << "Tried to populate an object with an invalid parent object type." << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }

        switch(object.type){
            case(PHEZ_GROUP):
                this->group->set_current(object.ptr.g);
                this->group->open(parent_id);

                this->populate_attributes(object);
                this->populate_datasets(object);
                this->populate_groups(object);

                this->group->close();

                break;

            case(PHEZ_DATASET):
                this->dataset->set_current(object.ptr.d);
                this->dataset->open(parent_id);

                this->flush_attributes(object);

                this->make_spaces(object);
                this->dataset->write();
                this->close_spaces(object);
                this->dataset->close();

                break;

            case(PHEZ_ATTRIBUTE):
                this->attribute->set_current(object.ptr.a);
                this->attribute->open(parent_id);

                this->make_spaces(object);
                this->attribute->write();
                this->close_spaces(object);
                this->attribute->close();

                break;

            default:
                PHEZ_FATAL_PREFIX
                cout << "Tried to populate a non-file object with an invalid object type." << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }
    }

    this->pop_current_pointers();

    return;
}

/** \brief Iterate through all files, reading in all the object data. */
void hdf5_class::populate_all(){
    phez_object_t file;
    file.type = PHEZ_FILE;

    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        file.ptr.f = (*(this->file->get_file_list()))[i];
        if(file.ptr.f){
            this->file->set_current(file.ptr.f);
            this->populate(this->hash(file));
        }
    }
    return;
}

void hdf5_class::flush_attributes(phez_object_t parent){

    this->iterate_attributes(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->flush_attribute(parent_id, child);
    });

    return;
}
void hdf5_class::flush_datasets(phez_object_t parent){

    this->iterate_datasets(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->flush_dataset(parent_id, child);
    });

    return;
}
void hdf5_class::flush_groups(phez_object_t parent){

    this->iterate_groups(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->flush_group(parent_id, child);
    });

    return;
}

void hdf5_class::flush_space(hid_t parent_id, phez_object_t child){
    PHEZ_FATAL_PREFIX
    cout << "Tried to flush a space." << endl;
    PHEZ_FATAL_SUFFIX
    return;
}

void hdf5_class::flush_attribute(hid_t parent_id, phez_object_t child){

    this->make_spaces(child);

    if(call_H5Aexists(parent_id,
                      this->attribute->get_current_name())){
        this->attribute->open(parent_id);
    }else{
        this->attribute->make(parent_id);
    }

    this->attribute->write();
    this->close_spaces(child);
    this->attribute->close();

    return;
}

void hdf5_class::flush_dataset(hid_t parent_id, phez_object_t child){

    this->make_spaces(child);

    if(call_H5Lexists(parent_id,
                      this->dataset->get_current_name(),
                      H5P_DEFAULT)){
        if(call_H5Oexists_by_name(parent_id,
                                  this->dataset->get_current_name(),
                                  H5P_DEFAULT)){
            // We should check that the name we found is actually a dataset,
            // but that's a corner case; check the type with H5Oget_info_by_name
            // if this is ever a problem.
            this->dataset->open(parent_id);
        }
    }else{
        this->dataset->make(parent_id);
    }

    this->flush_attributes(child);

    this->dataset->write();
    this->close_spaces(child);
    this->dataset->close();

    return;
}

void hdf5_class::flush_group(hid_t parent_id, phez_object_t child){

    if(call_H5Lexists(parent_id,
                      this->group->get_current_name(),
                      H5P_DEFAULT)){
        if(call_H5Oexists_by_name(parent_id,
                                  this->group->get_current_name(),
                                  H5P_DEFAULT)){
            // We should check that the name we found is actually a group,
            // but that's a corner case; check the type with H5Oget_info_by_name
            // if this is ever a problem.
            this->group->open(parent_id);
        }
    }else{
        this->group->make(parent_id);
    }

    this->flush_attributes(child);
    this->flush_datasets(child);
    this->flush_groups(child); // recursion!

    this->group->set_current(child.ptr.g);
    this->group->close();

    return;
}

void hdf5_class::flush_file(phez_object_t object){
    // We CANNOT use the the call_ macro here, because it will crash the whole program
    // if the file doesn't exist. We need it to do something somewhat different...
    int fstat;
    fstat = H5Fis_hdf5(this->file->get_current_name());

    if(fstat > 0){ // exists
        this->file->set_current_action(PHEZ_FILE_ACTION_APPEND);
        this->file->open();
    }else if(fstat < 0){ // doesn't exist
        this->file->set_current_action(PHEZ_FILE_ACTION_OVERWR);
        this->file->make();
    }else{ // non-HDF5
        PHEZ_FATAL_PREFIX
        cout << "File is not an HDF5 file." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->flush_attributes(object);
    this->flush_datasets(object);
    this->flush_groups(object); // recursion!

    this->file->close();
    return;
}

/** \brief Flush the current object, then everything inside the current object. */
void hdf5_class::flush(phez_hash_t* hash_in){

    this->iterate(hash_in,
        [&](phez_object_t object)                 -> void { this->flush_file     (object); },
        [&](hid_t parent_id, phez_object_t child) -> void { this->flush_group    (parent_id, child); },
        [&](hid_t parent_id, phez_object_t child) -> void { this->flush_dataset  (parent_id, child); },
        [&](hid_t parent_id, phez_object_t child) -> void { this->flush_attribute(parent_id, child); },
        [&](hid_t parent_id, phez_object_t child) -> void { this->flush_space    (parent_id, child); }
    );

    return;
}
/** \brief Flush everything inside all files. File must be initialized and opened first. */
void hdf5_class::flush_all(){
    phez_object_t file;
    file.type = PHEZ_FILE;

    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        file.ptr.f = (*(this->file->get_file_list()))[i];
        if(file.ptr.f){
            this->file->set_current(file.ptr.f);
            this->flush(this->hash(file));
        }
    }
    return;
}
/** \brief Close all the open attributes inside an object. */
void hdf5_class::close_attributes(phez_object_t parent){

    // Don't actually need the parent_id, it's only initialized to avoid having to make variadic templates.
    this->iterate_attributes(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->close_spaces(child);
        if(this->attribute->get_current_state() != PHEZ_ATTRIBUTE_STATE_DEFINED){
            this->attribute->close();
        }
    });

    return;
}
/** \brief Close all the open datasets inside an object. */
void hdf5_class::close_datasets(phez_object_t parent){

    // Don't actually need the parent_id, it's only initialized to avoid having to make variadic templates.
    this->iterate_attributes(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->close_spaces(child);
        this->close_attributes(child);
        if(this->dataset->get_current_state() != PHEZ_DATASET_STATE_DEFINED){
            this->dataset->close();
        }
    });

    return;
}
/** \brief Close all the open groups inside an object, then delete their structs
            if nothing links to them anymore. */
void hdf5_class::close_groups(phez_object_t parent){

    // Don't actually need the parent_id, it's only initialized to avoid having to make variadic templates.
    this->iterate_attributes(parent, [&](hid_t parent_id, phez_object_t child) -> void {
        this->close_attributes(child);
        this->close_datasets(child);
        this->close_groups(child); // recursion!

        if(this->group->get_current_state() != PHEZ_GROUP_STATE_DEFINED){
            this->group->close();
        }
    });

    return;
}
/** \brief Close everything in the current file and then the file itself. */
void hdf5_class::close(phez_hash_t* hash_in){

    this->stash_current_pointers();

    phez_object_t object;
    object = this->dehash(hash_in);

    switch(object.type){
        case(PHEZ_FILE):
            this->file->set_current(object.ptr.f);

            this->close_attributes(object);
            this->close_datasets(object);
            this->close_groups(object);
            if(this->file->get_current_state() != PHEZ_FILE_STATE_DEFINED){
                this->file->close();
            }

            break;

        case(PHEZ_GROUP):
            this->group->set_current(object.ptr.g);

            this->close_attributes(object);
            this->close_datasets(object);
            this->close_groups(object);
            if(this->group->get_current_state() != PHEZ_GROUP_STATE_DEFINED){
                this->group->close();
            }

            break;

        case(PHEZ_DATASET):
            this->dataset->set_current(object.ptr.d);

            this->close_spaces(object);
            this->close_attributes(object);
            if(this->dataset->get_current_state() != PHEZ_DATASET_STATE_DEFINED){
                this->dataset->close();
            }

            break;

        case(PHEZ_ATTRIBUTE):
            this->attribute->set_current(object.ptr.a);

            this->close_spaces(object);
            if(this->attribute->get_current_state() != PHEZ_ATTRIBUTE_STATE_DEFINED){
                this->attribute->close();
            }

            break;

        case(PHEZ_SPACE): // don't need any callbacks
            this->space->set_current(object.ptr.s);

            if(this->space->get_current_state() != PHEZ_SPACE_STATE_DEFINED){
                this->space->close();
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to close an object other than a file, group, dataset, attribute, or space." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->pop_current_pointers();

    return;
}
/** \brief Close everything in all files and then the file itself. */
void hdf5_class::close_all(){
    phez_object_t file;
    file.type = PHEZ_FILE;

    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        file.ptr.f = (*(this->file->get_file_list()))[i];
        if(file.ptr.f){
            this->file->set_current(file.ptr.f);
            this->close(this->hash(file));
        }
    }
    return;
}
/** \brief Close all the open spaces inside an object, then delete their structs
            if nothing links to them anymore. */
void hdf5_class::forget_spaces(phez_hash_t* hash_in){
    /* Local variables */
    phez_space_t* sptr = nullptr;      /**< Current space pointer linked from file */

    phez_object_t object;
    object = this->dehash(hash_in);

    switch(object.type){
        case(PHEZ_DATASET):

            this->dataset->set_current(object.ptr.d);

            sptr = this->dataset->get_current_linked_memory_space();
            if(sptr){
                this->space->set_current(sptr);
                this->dataset->unlink_memory_space();

                if(this->space->get_current_num_attributes_linking() == 0 &&
                   this->space->get_current_num_datasets_linking()   == 0){

                    this->space->close();
                    this->space->destroy();
                }
            }

            sptr = this->dataset->get_current_linked_file_space();
            if(sptr){
                this->space->set_current(sptr);
                this->dataset->unlink_file_space();

                if(this->space->get_current_num_attributes_linking() == 0 &&
                   this->space->get_current_num_datasets_linking()   == 0){

                    this->space->close();
                    this->space->destroy();
                }
            }

            break;

        case(PHEZ_ATTRIBUTE):

            this->attribute->set_current(object.ptr.a);

            sptr = this->attribute->get_current_linked_space();
            if(sptr){
                this->space->set_current(sptr);
                this->attribute->unlink_space();

                if(this->space->get_current_num_attributes_linking() == 0 &&
                   this->space->get_current_num_datasets_linking()   == 0){

                    this->space->close();
                    this->space->destroy();
                }
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to forget space for an object other than a dataset or attribute." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }
    return;
}
/** \brief Close all the open attributes inside an object, then delete their structs
            if nothing links to them anymore. */
void hdf5_class::forget_attributes(phez_hash_t* hash_in){
    /* Local variables */
    int i;
    size_t act; /**< Current attribute count (used for short-circuiting) */

    act = 0;

    phez_object_t parent;
    parent = this->dehash(hash_in);

    phez_object_t child;
    child.type = PHEZ_ATTRIBUTE;

    switch(parent.type){
        case(PHEZ_FILE):

            this->file->set_current(parent.ptr.f);

            for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                child.ptr.a = (*(this->file->get_current_linked_attributes()))[i];
                if(child.ptr.a){
                    this->attribute->set_current(child.ptr.a);
                    act++;

                    this->forget_spaces(this->hash(child));

                    this->file->unlink_attribute(child.ptr.a);

                    if(this->attribute->get_current_num_datasets_linking() == 0 &&
                       this->attribute->get_current_num_groups_linking()   == 0 &&
                       this->attribute->get_current_num_files_linking()    == 0){

                        this->attribute->close();
                        this->attribute->destroy();
                    }
                    if( act >= this->file->get_current_num_linked_attributes()) break;
                }
            }

            break;

        case(PHEZ_GROUP):

            this->group->set_current(parent.ptr.g);

            for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                child.ptr.a = (*(this->group->get_current_linked_attributes()))[i];
                if(child.ptr.a){
                    this->attribute->set_current(child.ptr.a);
                    act++;

                    this->forget_spaces(this->hash(child));

                    this->group->unlink_attribute(child.ptr.a);

                    if(this->attribute->get_current_num_datasets_linking() == 0 &&
                       this->attribute->get_current_num_groups_linking()   == 0 &&
                       this->attribute->get_current_num_files_linking()    == 0){

                        this->attribute->close();
                        this->attribute->destroy();
                    }
                    if( act >= this->group->get_current_num_linked_attributes()) break;
                }
            }

            break;

        case(PHEZ_DATASET):

            this->dataset->set_current(parent.ptr.d);

            for(i=0;i<PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;i++){
                child.ptr.a = (*(this->dataset->get_current_linked_attributes()))[i];
                if(child.ptr.a){
                    this->attribute->set_current(child.ptr.a);
                    act++;

                    this->forget_spaces(this->hash(child));

                    this->dataset->unlink_attribute(child.ptr.a);

                    if(this->attribute->get_current_num_datasets_linking() == 0 &&
                       this->attribute->get_current_num_groups_linking()   == 0 &&
                       this->attribute->get_current_num_files_linking()    == 0){

                        this->attribute->close();
                        this->attribute->destroy();
                    }
                    if( act >= this->dataset->get_current_num_linked_attributes()) break;
                }
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to forget attributes for an object other than a file, group, or dataset." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }
    return;
}
/** \brief Close all the open datasets inside an object, then delete their structs
            if nothing links to them anymore. */
void hdf5_class::forget_datasets(phez_hash_t* hash_in){
    /* Local variables */
    int i;
    size_t dct;  /**< current dataset count (used for short-circuiting) */

    dct = 0;

    phez_object_t parent;
    parent = this->dehash(hash_in);

    phez_object_t child;
    child.type = PHEZ_DATASET;

    switch(parent.type){
        case(PHEZ_FILE):

            this->file->set_current(parent.ptr.f);

            for(i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
                child.ptr.d = (*(this->file->get_current_linked_datasets()))[i];
                if(child.ptr.d){
                    this->dataset->set_current(child.ptr.d);
                    dct++;

                    this->forget_spaces(this->hash(child));
                    this->forget_attributes(this->hash(child));

                    this->file->unlink_dataset(child.ptr.d);

                    if(this->dataset->get_current_num_groups_linking() == 0 &&
                       this->dataset->get_current_num_files_linking()  == 0){

                        this->dataset->close();
                        this->dataset->destroy();
                    }
                    if( dct >= this->file->get_current_num_linked_datasets()) break;
                }
            }

            break;

        case(PHEZ_GROUP):

            this->group->set_current(parent.ptr.g);

            for(i=0;i<PHEZ_MAX_NUM_DATASETS_ALLOWED;i++){
                child.ptr.d = (*(this->group->get_current_linked_datasets()))[i];
                if(child.ptr.d){
                    this->dataset->set_current(child.ptr.d);
                    dct++;

                    this->forget_spaces(this->hash(child));
                    this->forget_attributes(this->hash(child));

                    this->group->unlink_dataset(child.ptr.d);

                    if(this->dataset->get_current_num_groups_linking() == 0 &&
                       this->dataset->get_current_num_files_linking()  == 0){

                        this->dataset->close();
                        this->dataset->destroy();
                    }
                    if( dct >= this->group->get_current_num_linked_datasets()) break;
                }
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to forget datasets for an object other than a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }
    return;
}
/** \brief Close all the open groups inside an object, then delete their structs
            if nothing links to them anymore. */
void hdf5_class::forget_groups(phez_hash_t* hash_in){
    /* Local variables */
    int i;
    size_t gct; /**< current group count (used for short-circuiting) */

    gct = 0;

    phez_object_t parent;
    parent = this->dehash(hash_in);

    phez_object_t child;
    child.type = PHEZ_GROUP;

    switch(parent.type){
        case(PHEZ_FILE):

            this->file->set_current(parent.ptr.f);

            for(i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
                child.ptr.g = (*(this->file->get_current_linked_groups()))[i];
                if(child.ptr.g){
                    this->group->set_current(child.ptr.g);
                    gct++;

                    this->forget_attributes(this->hash(child));
                    this->forget_datasets(this->hash(child));
                    this->forget_groups(this->hash(child)); // recursion!

                    this->file->unlink_group(child.ptr.g);

                    if(this->group->get_current_num_groups_linking() == 0 &&
                       this->group->get_current_num_files_linking()  == 0){

                        this->group->close();
                        this->group->destroy();
                    }
                    if( gct >= this->file->get_current_num_linked_groups()) break;
                }
            }

            break;

        case(PHEZ_GROUP):

            // recursion makes things complicated...
            for(i=0;i<PHEZ_MAX_NUM_GROUPS_ALLOWED;i++){
                this->group->set_current(parent.ptr.g); // needs to be inside loop
                child.ptr.g = (*(this->group->get_current_linked_groups()))[i];
                if(child.ptr.g){
                    this->group->set_current(child.ptr.g);
                    gct++;

                    this->forget_attributes(this->hash(child));
                    this->forget_datasets(this->hash(child));
                    this->forget_groups(this->hash(child)); // recursion!

                    this->group->set_current(parent.ptr.g);
                    this->group->unlink_group(child.ptr.g);

                    this->group->set_current(child.ptr.g);
                    if(this->group->get_current_num_groups_linking() == 0 &&
                       this->group->get_current_num_files_linking()  == 0){

                        this->group->close();
                        this->group->destroy();
                    }
                    if( gct >= this->group->get_current_num_linked_groups()) break;
                }
            }

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to forget groups for an object other than a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }
    return;
}
/** \brief Unlink all objects linked from the current object and pop any that are
            no longer linked; this does not close the object, so memory can be cleared
            to write more info to it. */
void hdf5_class::forget(phez_hash_t* hash_in){
    phez_object_t object;
    object = this->dehash(hash_in);

    switch(object.type){
        case(PHEZ_FILE):
            this->file->set_current(object.ptr.f);

            this->forget_attributes(hash_in);
            this->forget_datasets(hash_in);
            this->forget_groups(hash_in);

            break;

        case(PHEZ_GROUP):
            this->group->set_current(object.ptr.g);

            this->forget_attributes(hash_in);
            this->forget_datasets(hash_in);
            this->forget_groups(hash_in);

            break;

        case(PHEZ_DATASET):
            this->dataset->set_current(object.ptr.d);

            this->forget_spaces(hash_in);
            this->forget_attributes(hash_in);

            break;

        case(PHEZ_ATTRIBUTE):
            this->attribute->set_current(object.ptr.a);

            this->forget_spaces(hash_in);

            break;

        case(PHEZ_SPACE):
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to forget an object other than a file, group, dataset, attribute, or space." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->clear_current_pointers();

    return;
}
/** \brief Unlink all objects linked from all files and pop any that are
            no longer linked; this does not close the file, so memory can be cleared
            to write more info to it. */
void hdf5_class::forget_all(){
    phez_object_t file;
    file.type = PHEZ_FILE;

    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        file.ptr.f = (*(this->file->get_file_list()))[i];
        if(file.ptr.f){
            this->file->set_current(file.ptr.f);
            this->forget(this->hash(file));
        }
    }

    this->clear_current_pointers();

    return;
}
/** \brief Forget everything in the current file and delete all the structs */
void hdf5_class::remove(phez_hash_t* hash_in){

    phez_object_t object;
    object = this->dehash(hash_in);

    switch(object.type){
        case(PHEZ_FILE):
            this->file->set_current(object.ptr.f);

            this->forget(hash_in);
            this->file->close();
            this->file->destroy();

            break;

        case(PHEZ_GROUP):
            this->group->set_current(object.ptr.g);

            this->forget(hash_in);
            this->group->close();
            this->group->destroy();

            break;

        case(PHEZ_DATASET):
            this->dataset->set_current(object.ptr.d);

            this->forget(hash_in);
            this->dataset->close();
            this->dataset->destroy();

            break;

        case(PHEZ_ATTRIBUTE):
            this->attribute->set_current(object.ptr.a);

            this->forget(hash_in);
            this->attribute->close();
            this->attribute->destroy();

            break;

        case(PHEZ_SPACE):
            this->space->set_current(object.ptr.s);

            //this->forget(hash_in);
            this->space->close();
            this->space->destroy();

            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Tried to remove an object other than a file, group, dataset, attribute, or space." << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    this->clear_current_pointers();

    return;
}
/** \brief Forget everything in all files and delete all the structs */
void hdf5_class::remove_all(){
    phez_object_t file;
    file.type = PHEZ_FILE;

    for(int i=0;i<PHEZ_MAX_NUM_FILES_ALLOWED;i++){
        file.ptr.f = (*(this->file->get_file_list()))[i];
        if(file.ptr.f){
            this->file->set_current(file.ptr.f);
            this->remove(this->hash(file));
        }
    }

    this->clear_current_pointers();

    return;
}
/*
void hdf5_class::reduce_redundant(){

    return;
}
*/
/** \brief Open an object and append its ID to a hash, nested objects entail sequential "extract" calls */
phez_hash_t* hdf5_class::extract(phez_hash_t*  hash_in,
                                         phez_hdf5_otype_t     child_type,
                                         char*                 child_name){

    this->stash_current_pointers();

    phez_object_t parent;
    parent = this->dehash(hash_in);

    hid_t                 parent_id = -1;
    phez_hash_t*  hash_out = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];
    hash_out[0] = '\0';
    phez_object_t child;

    switch(parent.type){
        case(PHEZ_FILE):
            this->file->set_current(parent.ptr.f);
            parent_id = this->file->get_current_id();
            hash_out = this->append_to_hash(hash_out, hash_in); // otherwise file hash won't be there

            break;

        case(PHEZ_GROUP):
            this->group->set_current(parent.ptr.g);
            parent_id = this->group->get_current_id();

            break;

        case(PHEZ_DATASET):
            this->dataset->set_current(parent.ptr.d);
            parent_id = this->dataset->get_current_id();

            break;

        case(PHEZ_ATTRIBUTE):
            this->attribute->set_current(parent.ptr.a);
            parent_id = this->attribute->get_current_id();

            break;

        case(PHEZ_SPACE):
            // spaces cannot be parents
            return(nullptr);

        default:
            break;
    }

    switch(child_type){
        case(PHEZ_FILE):
            // files cannot be children
            return(nullptr);

        case(PHEZ_GROUP):
            child.type = PHEZ_GROUP;
            this->group->initialize();
            this->group->set_current_name(child_name);
            this->group->open(parent_id);
            child.ptr.g = this->group->get_current();

            hash_out = this->append_to_hash(hash_in, this->hash(child));

            break;

        case(PHEZ_DATASET):
            child.type = PHEZ_DATASET;
            this->dataset->initialize();
            this->dataset->set_current_name(child_name);
            //this->dataset->set_current_data<float>(nullptr);
            this->dataset->open(parent_id);
            child.ptr.d = this->dataset->get_current();

            hash_out = this->append_to_hash(hash_in, this->hash(child));

            break;

        case(PHEZ_ATTRIBUTE):
            child.type = PHEZ_ATTRIBUTE;
            this->attribute->initialize();
            this->attribute->set_current_name(child_name);
            //this->attribute->set_current_data<float>(nullptr);
            this->attribute->open(parent_id);
            child.ptr.a = this->attribute->get_current();

            hash_out = this->append_to_hash(hash_in, this->hash(child));

            break;

        case(PHEZ_SPACE):
            child.type = PHEZ_SPACE;
            this->space->initialize();
            this->space->open(parent_id);
            child.ptr.s = this->space->get_current();

            hash_out = this->append_to_hash(hash_in, this->hash(child));

            break;

        default:
            break;
    }

    this->pop_current_pointers();

    switch(child_type){
        case(PHEZ_FILE):
            // files cannot be children
            return(nullptr);

        case(PHEZ_GROUP):
            this->group->set_current(child.ptr.g);
            break;

        case(PHEZ_DATASET):
            this->dataset->set_current(child.ptr.d);
            break;

        case(PHEZ_ATTRIBUTE):
            this->attribute->set_current(child.ptr.a);
            break;

        case(PHEZ_SPACE):
            this->space->set_current(child.ptr.s);
            break;

        default:
            break;
    }

    return(hash_out);
}
/** \brief Turns the current group into a temporary file in memory. */
phez_hash_t* hdf5_class::appear(phez_hash_t* hash_in){
    size_t mem_incr               = 1000000;
    bool file_writes_to_disk      = false;   /**< File never is written to disk */

    char* buf_name                = new char[PHEZ_MAX_NAME_LENGTH];
    for(int n = 0; n < PHEZ_MAX_NAME_LENGTH; n++) buf_name[n] = '\0';
    void* buf_ptr                 = nullptr;
    size_t buf_len                = -1;

    phez_hash_t* phash    = nullptr;
    phez_hash_t* chash    = nullptr;
    phez_hash_t* nhash    = nullptr;
    phez_object_t parent;
    phez_object_t child;
    phez_object_t fnew;
    hid_t parent_id               = -1;
    hid_t fcurrent_id             = -1;

    /** Save the current_ pointers so they can be restored later */
    this->stash_current_pointers();

    /** Check that the hash is an object that can appear */
    child = this->dehash(hash_in);
    switch(child.type){
        case(PHEZ_FILE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot call 'appear' on a file." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_GROUP):
            break;
        case(PHEZ_DATASET):
            break;
        case(PHEZ_ATTRIBUTE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot call 'appear' on an attribute." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        case(PHEZ_SPACE):
            PHEZ_FATAL_PREFIX
            cout << "Cannot call 'appear' on a space." << endl;
            PHEZ_FATAL_SUFFIX
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "This is not a valid HDF5 object type. How did you even get here?" << endl;
            PHEZ_FATAL_SUFFIX
            break;
    }

    /** Peel off the first layer of the hash (must be a file!) */
    phash = this->peel_from_hash(hash_in);
    parent = this->dehash(phash);
    if(parent.type == PHEZ_FILE){
        this->file->set_current(parent.ptr.f);
        fcurrent_id = this->file->get_current_id();
    }else{
        //fail miserably
        PHEZ_FATAL_PREFIX
        cout << "The object could not be found because the hash does not start with a file." << endl;
        PHEZ_FATAL_SUFFIX
        return(nullptr);
    }

    /** Prepare buffer file and build the the new file object to hash. */
    fnew.type = PHEZ_FILE;
    fnew.ptr.f = this->file->initialize();
    nhash = this->hash(fnew);

    this->file->access_current_from_memory((unsigned long int)mem_incr,
                                          file_writes_to_disk);
    this->file->set_current_action(PHEZ_FILE_ACTION_OVERWR);

    int hash_len = (int)(strlen(hash_in) / this->hash_digits);
    for(int i = 0; i < hash_len; i++){
        /* Get the HDF5 ID of the parent object */
        switch(parent.type){
            case(PHEZ_FILE):
                parent_id = fcurrent_id;
                break;
            case(PHEZ_GROUP):
                this->group->set_current(parent.ptr.g);
                parent_id = this->group->get_current_id();
                break;
            case(PHEZ_DATASET):
                /*
                this->dataset->set_current(parent.ptr.d);
                parent_id = this->dataset->get_current_id();
                */
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy a dataset's linked objects to a file by themselves because";
                cout << " appearing an attribute is currently unimplemented." << endl;
                PHEZ_FATAL_SUFFIX
                break;
            case(PHEZ_ATTRIBUTE):
                // attributes can only be parents of spaces, which can't be
                // in files by themselves, so attributes in this specific case
                // only have illegitimate children
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy an attribute's linked objects to a file by themselves because";
                cout << " it would create orphaned spaces." << endl;
                PHEZ_FATAL_SUFFIX

                return(nullptr);
            case(PHEZ_SPACE):
                // spaces cannot be parents
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy a space's linked objects to a file, because spaces cannot";
                cout << " have linked objects." << endl;
                PHEZ_FATAL_SUFFIX
                return(nullptr);

            default:
                PHEZ_FATAL_PREFIX
                cout << "This is not a valid HDF5 object type. How did you even get here?" << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }

        chash = this->peel_from_hash(hash_in);
        child = this->dehash(chash);

        switch(child.type){
            case(PHEZ_FILE):
                // files cannot be children
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy a file from one file to another file. How did you even get here?" << endl;
                PHEZ_FATAL_SUFFIX
                return(nullptr);
            case(PHEZ_GROUP):
                if(strlen(hash_in) == 0){ // no more layers to peel means that chash is the object in question
                    // We arrived at our destination! Now copy current group to new file...
                    this->group->set_current(child.ptr.g);
                    strcat(buf_name, this->group->get_current_name());
                    strcat(buf_name, ".h5");

                    this->file->set_current_name(buf_name);
                    this->file->make();
                    call_H5Ocopy(parent_id,
                                 this->group->get_current_name(),
                                 this->file->get_current_id(),
                                 this->group->get_current_name(),
                                 H5P_DEFAULT,
                                 H5P_DEFAULT);

                    nhash = this->extract(nhash, PHEZ_GROUP, (char*)this->group->get_current_name());

                }
                break;

            case(PHEZ_DATASET):
                if(strlen(hash_in) == 0){
                    // We arrived at our destination! Now copy current dataset to new file...
                    this->dataset->set_current(child.ptr.d);
                    strcat(buf_name, this->dataset->get_current_name());
                    strcat(buf_name, ".h5");

                    this->file->set_current_name(buf_name);
                    this->file->make();
                    call_H5Ocopy(parent_id,
                                 this->dataset->get_current_name(),
                                 this->file->get_current_id(),
                                 this->dataset->get_current_name(),
                                 H5P_DEFAULT,
                                 H5P_DEFAULT);

                    nhash = this->extract(nhash, PHEZ_DATASET, (char*)this->dataset->get_current_name());
                }
                break;

            case(PHEZ_ATTRIBUTE):
                /*
                if(strlen(hash_in) == 0){
                    // We arrived at our destination! Now copy current attribute to new file...
                    this->attribute->set_current(child.ptr.a);
                    strcat(buf_name, this->attribute->get_current_name());
                    strcat(buf_name, ".h5");

                    this->file->set_current_name(buf_name);
                    this->file->make();
                    call_H5Ocopy(parent_id,
                                 this->attribute->get_current_name(),
                                 this->file->get_current_id(),
                                 this->attribute->get_current_name(),
                                 H5P_DEFAULT,
                                 H5P_DEFAULT);

                    nhash = this->extract(nhash, PHEZ_ATTRIBUTE, (char*)this->attribute->get_current_name());
                }
                */
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy an attribute by itself to another file." << endl;
                PHEZ_FATAL_SUFFIX
                break;

            case(PHEZ_SPACE):
                PHEZ_FATAL_PREFIX
                cout << "Cannot copy a space by itself to another file. How did you even get here?" << endl;
                PHEZ_FATAL_SUFFIX
                break;

            default:
                PHEZ_FATAL_PREFIX
                cout << "This is not a valid HDF5 object type. How did you even get here?" << endl;
                PHEZ_FATAL_SUFFIX
                break;
        }
        /* We're one step closer to our destination */
        parent = child;
    }

    call_H5Fflush(this->file->get_current_id(),
                  H5F_SCOPE_GLOBAL);

    /* First call gets length of buffer, second call fills buffer */
    buf_len = call_H5Fget_file_image(this->file->get_current_id(),
                                      NULL,
                                      (unsigned long int)buf_len);

    /* malloc the buffer */
    buf_ptr = malloc((unsigned long int)buf_len);

    call_H5Fget_file_image(this->file->get_current_id(),
                           buf_ptr,
                           (unsigned long int)buf_len);

    /** Reset the current_ pointers. */
    this->pop_current_pointers();

    /** Set current_file to new file */
    this->file->set_current(fnew.ptr.f);

    return(nhash);
}
/** \brief Convert base-62 digit (as alphanumeric) to int using a binary search.
 *
 *   \param [in] char_in    A single alphanumeric character. Used to represent base-62 numbers.
 *
 *   \return                An integer from 0 to 61.
 */
int hdf5_class::hash_digit_to_int(char char_in){
    int left = 0;
    int right = this->hash_base;
    int retint;

    while (left <= right) {
        retint = (left + right) / 2;
        if(this->hash_list[retint].digit == char_in){
            return(retint);
        }else if(this->hash_list[retint].digit > char_in){
            right = retint - 1;
        }else{
            left = retint + 1;
        }
    }

    PHEZ_FATAL_PREFIX
    cout << "char that was passed in is not a valid hash digit." << endl;
    PHEZ_FATAL_SUFFIX
    return(-1);
}

/** \brief Create a hash for an object (by itself)
 *
 *   \param [in] object_in  An object struct with the pointer and type set.
 *
 *   \return                A single-object hash.
 */
phez_hash_t* hdf5_class::hash(phez_object_t object_in){
    int min;    /**< The minimum the index can be for a particular object type. */
    size_t i;   /**< Iterator. */
    int n;      /**< Individual digit to hash */
    int indx = -1;   /**< The branch index out of all possible objects. */
    char c;     /**< Temporary char. */
    char* hash_out = new char[this->hash_digits];   /**< Output hash. */

    /** Check the object type */
    switch(object_in.type){
        case(PHEZ_FILE):
            /** Calculate the minimum possible index for an object of this type */
            min = this->indx_min;

            /** Find which index the object pointer refers to in the object list */
            for(i = 0; i < PHEZ_MAX_NUM_FILES_ALLOWED; i++){
                if((*(this->file->get_file_list()))[i]){ /* Avoid null pointers */
                    if(object_in.ptr.f == (*(this->file->get_file_list()))[i]){
                        indx = min + i;
                        break;
                    }
                }
            }

            break;

        case(PHEZ_GROUP):
            min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED;

            for(i = 0; i < PHEZ_MAX_NUM_GROUPS_ALLOWED; i++){
                if((*(this->group->get_group_list()))[i]){ /* Avoid null pointers */
                    if(object_in.ptr.g == (*(this->group->get_group_list()))[i]){
                        indx = min + i;
                        break;
                    }
                }
            }

            break;

        case(PHEZ_DATASET):
            min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                                 + PHEZ_MAX_NUM_GROUPS_ALLOWED;

            for(i = 0; i < PHEZ_MAX_NUM_DATASETS_ALLOWED; i++){
                if((*(this->dataset->get_dataset_list()))[i]){ /* Avoid null pointers */
                    if(object_in.ptr.d == (*(this->dataset->get_dataset_list()))[i]){
                        indx = min + i;
                        break;
                    }
                }
            }

            break;

        case(PHEZ_ATTRIBUTE):
            min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                                 + PHEZ_MAX_NUM_GROUPS_ALLOWED
                                 + PHEZ_MAX_NUM_DATASETS_ALLOWED;

            for(i = 0; i < PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED; i++){
                if((*(this->attribute->get_attribute_list()))[i]){ /* Avoid null pointers */
                    if(object_in.ptr.a == (*(this->attribute->get_attribute_list()))[i]){
                        indx = min + i;
                        break;
                    }
                }
            }

            break;

        case(PHEZ_SPACE):
            min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                                 + PHEZ_MAX_NUM_GROUPS_ALLOWED
                                 + PHEZ_MAX_NUM_DATASETS_ALLOWED
                                 + PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;

            for(i = 0; i < PHEZ_MAX_NUM_SPACES_ALLOWED; i++){
                if((*(this->space->get_space_list()))[i]){ /* Avoid null pointers */
                    if(object_in.ptr.s == (*(this->space->get_space_list()))[i]){
                        indx = min + i;
                        break;
                    }
                }
            }

            break;

        default:
            break;
    }

    if(indx < 0){

        /** If the index wasn't found, are we trying to hash nullptr?
         *  It should give an empty string. */
        switch(object_in.type){
            case(PHEZ_FILE):
                if(!object_in.ptr.f){
                    hash_out[0] = '\0';
                }else{
                    // Megafail
                    PHEZ_FATAL_PREFIX
                    cout << "The object pointer could not be found." << endl;
                    PHEZ_FATAL_SUFFIX
                }
                break;
            case(PHEZ_GROUP):
                if(!object_in.ptr.g){
                    hash_out[0] = '\0';
                }else{
                    // Megafail
                    PHEZ_FATAL_PREFIX
                    cout << "The object pointer could not be found." << endl;
                    PHEZ_FATAL_SUFFIX
                }
                break;
            case(PHEZ_DATASET):
                if(!object_in.ptr.d){
                    hash_out[0] = '\0';
                }else{
                    // Megafail
                    PHEZ_FATAL_PREFIX
                    cout << "The object pointer could not be found." << endl;
                    PHEZ_FATAL_SUFFIX
                }
                break;
            case(PHEZ_ATTRIBUTE):
                if(!object_in.ptr.a){
                    hash_out[0] = '\0';
                }else{
                    // Megafail
                    PHEZ_FATAL_PREFIX
                    cout << "The object pointer could not be found." << endl;
                    PHEZ_FATAL_SUFFIX
                }
                break;
            case(PHEZ_SPACE):
                if(!object_in.ptr.s){
                    hash_out[0] = '\0';
                }else{
                    // Megafail
                    PHEZ_FATAL_PREFIX
                    cout << "The object pointer could not be found." << endl;
                    PHEZ_FATAL_SUFFIX
                }
                break;
            default:
                break;
        }

        return(nullptr); // This is just here so compilers/analyzers don't complain.
    }else{
        /** Hash the index */
        n = (int)(indx / (int)pow(this->hash_base, this->hash_digits-1));
        c = this->hash_list[n].digit;
        hash_out[0] = c;
        for(i = 1; i < this->hash_digits; i++){
            n = indx % (int)pow(this->hash_base, this->hash_digits-i);
            c = this->hash_list[n].digit;
            hash_out[i] = c;
        }
        hash_out[this->hash_digits] = '\0';
    }

    return( (phez_hash_t*)hash_out );
}
/** \brief Parse the hash for the object ID and type.
 *
 *   \param [in] hash_in    A single-object hash.
 *
 *   \return                An object struct with the pointer and type set.
 */
phez_object_t hdf5_class::dehash(phez_hash_t* hash_in){
    int indx;   /**< The branch index out of all possible objects. */
    int min;    /**< The minimum the index can be for a particular object type. */
    size_t i;   /**< Iterator. */
    char c;     /**< Temporary char. */

    phez_object_t* object = new phez_object_t; /**< Output object struct. */

    this->stash_current_pointers();

    /** Calculate the branch index by converting the hash to a base-10 number */
    indx = 0;
    for(i = 0; i < this->hash_digits; i++){
        c = hash_in[i];
        indx += this->hash_digit_to_int(c) * pow(this->hash_base, this->hash_digits-(i+1));
    }

    /** Find the type of object the index refers to. */
    if(indx < PHEZ_MAX_NUM_FILES_ALLOWED){

        /** Find the minimum index an object of the same type could be */
        min = this->indx_min;

        /** Subtract the minimum from the index, and set the current
         *   object to the object in that slot */
        this->file->set_current((*(this->file->get_file_list()))[indx - min]);

        /** Set the object struct parameters. */
        object->ptr.f = this->file->get_current();
        object->type = PHEZ_FILE;

    }else if(indx < PHEZ_MAX_NUM_FILES_ALLOWED +
                    PHEZ_MAX_NUM_GROUPS_ALLOWED){

        min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED;
        this->group->set_current((*(this->group->get_group_list()))[indx - min]);
        object->ptr.g = this->group->get_current();
        object->type = PHEZ_GROUP;

    }else if(indx < PHEZ_MAX_NUM_FILES_ALLOWED +
                    PHEZ_MAX_NUM_GROUPS_ALLOWED +
                    PHEZ_MAX_NUM_DATASETS_ALLOWED){

        min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                             + PHEZ_MAX_NUM_GROUPS_ALLOWED;
        this->dataset->set_current((*(this->dataset->get_dataset_list()))[indx - min]);
        object->ptr.d = this->dataset->get_current();
        object->type = PHEZ_DATASET;

    }else if(indx < PHEZ_MAX_NUM_FILES_ALLOWED +
                    PHEZ_MAX_NUM_GROUPS_ALLOWED +
                    PHEZ_MAX_NUM_DATASETS_ALLOWED +
                    PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED){

        min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                             + PHEZ_MAX_NUM_GROUPS_ALLOWED
                             + PHEZ_MAX_NUM_DATASETS_ALLOWED;
        this->attribute->set_current((*(this->attribute->get_attribute_list()))[indx - min]);
        object->ptr.a = this->attribute->get_current();
        object->type = PHEZ_ATTRIBUTE;

    }else if(indx < PHEZ_MAX_NUM_FILES_ALLOWED +
                    PHEZ_MAX_NUM_GROUPS_ALLOWED +
                    PHEZ_MAX_NUM_DATASETS_ALLOWED +
                    PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED +
                    PHEZ_MAX_NUM_SPACES_ALLOWED){

        min = this->indx_min + PHEZ_MAX_NUM_FILES_ALLOWED
                             + PHEZ_MAX_NUM_GROUPS_ALLOWED
                             + PHEZ_MAX_NUM_DATASETS_ALLOWED
                             + PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED;
        this->space->set_current((*(this->space->get_space_list()))[indx - min]);
        object->ptr.s = this->space->get_current();
        object->type = PHEZ_SPACE;

    }else{
        // Asplode
        PHEZ_FATAL_PREFIX
        cout << "Index does not correspond to a PHEZ object." << endl;
        PHEZ_FATAL_SUFFIX
    }

    this->pop_current_pointers();

    //delete[] hash_in;
    return(*object);
}
/** \brief Append the ID of the object to the hash; also check for recursive linking here
 *
 *   \param [in,out] orig_hash_in   An object hash.
 *   \param [in]     new_hash_in    A single-object hash, to be pushed to orig_hash_in.
 *
 *   \return                        The original object hash, with the new hash appended to the front of it.
 */
phez_hash_t* hdf5_class::append_to_hash(phez_hash_t* orig_hash_in,
                                        phez_hash_t* new_hash_in){
    bool is_circular = false;
    phez_hash_t* hash_out = new phez_hash_t[PHEZ_MAX_HASH_LENGTH];

    /** If the hash would end up longer than the maximum, fail. */
    if( strlen(new_hash_in) + strlen(orig_hash_in) > PHEZ_MAX_HASH_LENGTH-1){
        PHEZ_FATAL_PREFIX
        cout << "Cannot append to existing hash because it would be too long." << endl;
        PHEZ_FATAL_SUFFIX
    }else{
        /** If the new link structure would result in recursion, fail. */
        for(size_t i = 0; i < strlen(orig_hash_in) / this->hash_digits; i++){
            /* (Actually easier with C-style string operations) */
            for(size_t j = 0; j < this->hash_digits; j++){
                if(new_hash_in[j] != orig_hash_in[j + i*this->hash_digits]){
                    break;
                }
                /* This 'if' must be the last statement in loop */
                if(j == this->hash_digits - 1){
                    is_circular = true;
                }
            }
        }

        if(is_circular){
            // Baleen Fail
            PHEZ_FATAL_PREFIX
            cout << "Cannot append to existing hash because it would result in a circular dependency." << endl;
            PHEZ_FATAL_SUFFIX
            return(nullptr);
        }

        /** Cat the new hash to the front of the original hash. */
        strcpy(hash_out, new_hash_in);
        strcat(hash_out, orig_hash_in);
    }

    /** Delete hash_temp. */
    return( (phez_hash_t*)hash_out );
}
/** \brief Return the ID of the oldest ancestor of the hashed object and remove it from the hash,
 *          similar to popping something off a queue.
 *
 *   \param [in] hash_in An object hash. This will be shortened by popping the first object
 *                       off the back of the hash.
 *   \return             An object hash for the popped object.
 */
phez_hash_t* hdf5_class::peel_from_hash(phez_hash_t* hash_in){
    phez_hash_t* hash_out = new phez_hash_t[PHEZ_MAX_HASH_LENGTH]; /**< The peeled part of hash_in. */
    phez_hash_t* hash_temp = new phez_hash_t[PHEZ_MAX_HASH_LENGTH]; /**< Temporary hash; stores the remainder of hash_in. */
    size_t i; /**< Iterator */

    /** If the length of the string is too short to be a full hash, fail immediately. */
    if(strlen(hash_in) >= this->hash_digits){
        /** Set hash_out to be the last */
        for(i = strlen(hash_in) - this->hash_digits; i < strlen(hash_in); i++){
            hash_out[i - (strlen(hash_in) - this->hash_digits)] = hash_in[i];
        }
        hash_out[this->hash_digits] = '\0';
        /** Store the rest of the hash in hash_temp */
        if(strlen(hash_in) != this->hash_digits){
            for(i = 0; i < strlen(hash_in) - this->hash_digits; i++){
                hash_temp[i] = hash_in[i];
            }
            hash_temp[strlen(hash_in) - this->hash_digits] = '\0';
        }else{
            hash_temp[0] = '\0';
        }
        /* probably a way to do this without manually copying everything */
        /** Update hash_in by copying hash_temp to hash_in. */
        strcpy(hash_in, hash_temp);
    }else{
        // Failboat
        PHEZ_FATAL_PREFIX
        cout << "Cannot peel from existing hash because it is empty." << endl;
        PHEZ_FATAL_SUFFIX
        return(nullptr);
    }

    /** Delete hash_temp. */
    delete[] hash_temp;
    return(hash_out);
}
/** \brief Return the hash of the hashed object's parent.
 *
 *   \param [in] hash_in An object hash.
 *   \return             An object hash for the object's parent.
 */
phez_hash_t* hdf5_class::get_hash_parent(phez_hash_t* hash_in){
    phez_hash_t* hash_out = new phez_hash_t[this->hash_digits+1]; /**< The popped part of hash_in. */
    size_t i; /**< Iterator */

    size_t hash_in_len = strlen(hash_in);

    /** If the length of the string is too short to have a parent, fail immediately. */
    if(hash_in_len >= 2*this->hash_digits){
        /** Set hash_out to be the last */
        for(i = this->hash_digits; i < 2*this->hash_digits; i++){
            hash_out[i] = hash_in[i];
        }
        hash_out[this->hash_digits] = '\0';
    }else{
        // Failboat
        PHEZ_FATAL_PREFIX
        cout << "Cannot get hash's parent from existing hash because it has no parent." << endl;
        PHEZ_FATAL_SUFFIX
        return(nullptr);
    }

    return(hash_out);
}

/** \brief Stash all the current_ pointers so they can be restored later. */
void hdf5_class::stash_current_pointers(){

    this->stash_fptr = this->file->get_current();
    this->stash_gptr = this->group->get_current();
    this->stash_dptr = this->dataset->get_current();
    this->stash_aptr = this->attribute->get_current();
    this->stash_sptr = this->space->get_current();

    return;
}

/** \brief Pop all the current_ pointers to the values that were stashed earlier. */
void hdf5_class::pop_current_pointers(){

    this->file->set_current(this->stash_fptr);
    this->group->set_current(this->stash_gptr);
    this->dataset->set_current(this->stash_dptr);
    this->attribute->set_current(this->stash_aptr);
    this->space->set_current(this->stash_sptr);

    return;
}

/** \brief Sets all the current_ pointers to nullptr. */
void hdf5_class::clear_current_pointers(){

    this->stash_fptr = nullptr;
    this->stash_gptr = nullptr;
    this->stash_dptr = nullptr;
    this->stash_aptr = nullptr;
    this->stash_sptr = nullptr;

    return;

}

/** \brief Gets the number of hash digits, i.e., how many characters long each object's hash will be */
size_t hdf5_class::get_hash_digits(){
    return(this->hash_digits);
}


