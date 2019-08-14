
#include "phez_cnames.hpp"

/********************** PHEZ context functions ***************************/

phez_context_t* cwrap_phez_context_start(){
    return(new phez_context_t);
}
void cwrap_phez_context_stop(phez_context_t* context){
    delete context;
    return;
}

phez_test_context_t* cwrap_phez_test_context_start(){
    return(new phez_test_context_t);

}
void cwrap_phez_test_context_stop(phez_test_context_t* context){
    delete context;
    return;
}

/******************** PHEZ convenience functions *************************/

void cwrap_phez_populate(phez_context_t* context, phez_hash_t* hash_in){
    context->hdf5->populate(hash_in);
    return;
}
void cwrap_phez_flush(phez_context_t* context, phez_hash_t* hash_in){
    context->hdf5->flush(hash_in);
    return;
}
void cwrap_phez_close(phez_context_t* context, phez_hash_t* hash_in){
    context->hdf5->close(hash_in);
    return;
}
void cwrap_phez_forget(phez_context_t* context, phez_hash_t* hash_in){
    context->hdf5->forget(hash_in);
    return;
}
void cwrap_phez_remove(phez_context_t* context, phez_hash_t* hash_in){
    context->hdf5->remove(hash_in);
    return;
}
void cwrap_phez_populate_all(phez_context_t* context){
    context->hdf5->populate_all();
    return;
}
void cwrap_phez_flush_all(phez_context_t* context){
    context->hdf5->flush_all();
    return;
}
void cwrap_phez_close_all(phez_context_t* context){
    context->hdf5->close_all();
    return;
}
void cwrap_phez_forget_all(phez_context_t* context){
    context->hdf5->forget_all();
    return;
}
void cwrap_phez_remove_all(phez_context_t* context){
    context->hdf5->remove_all();
    return;
}
phez_hash_t* cwrap_phez_appear(phez_context_t* context, phez_hash_t* hash_in){
    return(context->hdf5->appear(hash_in));
}
phez_hash_t* cwrap_phez_extract(phez_context_t*       context,
                                phez_hash_t*        hash_in,
                                phez_hdf5_otype_t   type_in,
                                char*               name_in){

    phez_hash_t* hash_out = context->hdf5->extract(hash_in, type_in, name_in);
    phez_space_t* sptr;

    /* Autolink spaces (datasets and attributes only) */
    switch(type_in){
        case(PHEZ_DATASET):
            context->hdf5->stash_current_pointers();
            context->hdf5->dataset->set_current(context->hdf5->dehash(hash_out).ptr.d);
            sptr = context->hdf5->space->initialize();
            context->hdf5->space->open(context->hdf5->dataset->get_current_id());
            context->hdf5->dataset->link_file_space(sptr);
            context->hdf5->pop_current_pointers();
            break;
        case(PHEZ_ATTRIBUTE):
            context->hdf5->stash_current_pointers();
            context->hdf5->attribute->set_current(context->hdf5->dehash(hash_out).ptr.a);
            sptr = context->hdf5->space->initialize();
            context->hdf5->space->open(context->hdf5->attribute->get_current_id());
            context->hdf5->attribute->link_space(sptr);
            context->hdf5->pop_current_pointers();
            break;
        default:
            break;
    }

    return(hash_out);
}

/******************** PHEZ convenience functions *************************/



/************************ PHEZ file functions ****************************/

phez_hash_t* cwrap_phez_file_initialize(phez_context_t* context){
    phez_object_t fobj;
    fobj.type = PHEZ_FILE;
    fobj.ptr.f = context->hdf5->file->initialize();
    return(context->hdf5->hash(fobj));
}
void cwrap_phez_current_file_open(phez_context_t* context){
    switch(context->hdf5->file->get_current_action()){
        case(PHEZ_FILE_ACTION_RDONLY):
            context->hdf5->file->open();
            break;
        case(PHEZ_FILE_ACTION_APPEND):
            context->hdf5->file->open();
            break;
        case(PHEZ_FILE_ACTION_WRONLY):
            context->hdf5->file->make();
            break;
        case(PHEZ_FILE_ACTION_OVERWR):
            context->hdf5->file->make();
            break;
        default:
            PHEZ_FATAL_PREFIX
            cout << "Invalid file action." << endl;
            PHEZ_FATAL_SUFFIX
    }
    return;
}
/*
void cwrap_phez_current_file_make(phez_context_t* context){
    context->hdf5->file->make();
    return;
}
*/
phez_hash_t* cwrap_phez_current_file_link_group(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_GROUP){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with group objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->link_group(obj.ptr.g);
    return(context->hdf5->append_to_hash(cwrap_phez_file_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_file_link_dataset(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_DATASET){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with dataset objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->link_dataset(obj.ptr.d);
    return(context->hdf5->append_to_hash(cwrap_phez_file_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_file_link_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->link_attribute(obj.ptr.a);
    return(context->hdf5->append_to_hash(cwrap_phez_file_get_current(context), hash_in));
}
void cwrap_phez_current_file_unlink_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->unlink_attribute(obj.ptr.a);
    return;
}
void cwrap_phez_current_file_unlink_dataset(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with dataset objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->unlink_dataset(obj.ptr.d);
    return;
}
void cwrap_phez_current_file_unlink_group(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_GROUP){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with group objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->unlink_group(obj.ptr.g);
    return;
}
void cwrap_phez_current_file_close(phez_context_t* context){
    context->hdf5->file->close();
    return;
}
void cwrap_phez_current_file_destroy(phez_context_t* context){
    context->hdf5->file->destroy();
    return;
}
phez_hash_t* cwrap_phez_file_get_current(phez_context_t* context){
    phez_object_t fobj;
    fobj.type = PHEZ_FILE;
    fobj.ptr.f = context->hdf5->file->get_current();
    return(context->hdf5->hash(fobj));
}
void cwrap_phez_file_set_current(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_FILE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with file objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->file->set_current(obj.ptr.f);
    return;
}
size_t cwrap_phez_file_get_num(phez_context_t* context){
    return(context->hdf5->file->get_num());
}
char* cwrap_phez_current_file_get_name(phez_context_t* context){
    return(context->hdf5->file->get_current_name());
}
void cwrap_phez_current_file_set_name(phez_context_t* context, char* name_in){
    context->hdf5->file->set_current_name(name_in);
    return;
}
phez_file_action_t cwrap_phez_current_file_get_action(phez_context_t* context){
    return(context->hdf5->file->get_current_action());
}
void cwrap_phez_current_file_set_action(phez_context_t* context, phez_file_action_t action_in){
    context->hdf5->file->set_current_action(action_in);
    return;
}
void cwrap_phez_current_file_reset_access_properties(phez_context_t* context){
    context->hdf5->file->reset_current_access_properties();
    return;
}
void cwrap_phez_current_file_default_access_properties(phez_context_t* context){
    context->hdf5->file->default_current_access_properties();
    return;
}
void cwrap_phez_current_file_access_from_memory(phez_context_t* context,
                                          size_t memory_increment_in,
                                          bool file_writes_to_disk_in){
    context->hdf5->file->access_current_from_memory(memory_increment_in,
                                                    file_writes_to_disk_in);
    return;
}
void cwrap_phez_current_file_reset_creation_properties(phez_context_t* context){
    context->hdf5->file->reset_current_creation_properties();
    return;
}
void cwrap_phez_current_file_default_creation_properties(phez_context_t* context){
    context->hdf5->file->default_current_creation_properties();
    return;
}
size_t cwrap_phez_current_file_get_num_linked_attributes(phez_context_t* context){
    return(context->hdf5->file->get_current_num_linked_attributes());
}
size_t cwrap_phez_current_file_get_num_linked_datasets(phez_context_t* context){
    return(context->hdf5->file->get_current_num_linked_datasets());
}
size_t cwrap_phez_current_file_get_num_linked_groups(phez_context_t* context){
    return(context->hdf5->file->get_current_num_linked_groups());
}

/************************ PHEZ file functions ****************************/



/*********************** PHEZ group functions ****************************/

phez_hash_t* cwrap_phez_group_initialize(phez_context_t* context){
    phez_object_t gobj;
    gobj.type = PHEZ_GROUP;
    gobj.ptr.g = context->hdf5->group->initialize();
    return(context->hdf5->hash(gobj));
}
phez_hash_t* cwrap_phez_current_group_open(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    phez_object_t current_obj;
    hid_t id;
    phez_hash_t* hash_out = nullptr;

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            current_obj.type = PHEZ_FILE;
            current_obj.ptr.f = context->hdf5->file->get_current();
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->group->open(id);
            context->hdf5->file->link_group(context->hdf5->group->get_current());
            context->hdf5->file->set_current(current_obj.ptr.f);
            break;

        case(PHEZ_GROUP):
            current_obj.type = PHEZ_GROUP;
            current_obj.ptr.g = context->hdf5->group->get_current();
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->group->link_group(current_obj.ptr.g);
            context->hdf5->group->set_current(current_obj.ptr.g);
            context->hdf5->group->open(id);
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Parent object can only be a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            return(hash_out);
    }

    hash_out = context->hdf5->append_to_hash(context->hdf5->hash(current_obj), hash_in);
    return(hash_out);
}

/*
void cwrap_phez_current_group_make(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    phez_group_t* gptr;
    hid_t id;

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->group->make(id);

        case(PHEZ_GROUP):
            gptr = context->hdf5->group->get_current();
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->group->set_current(gptr);
            context->hdf5->group->make(id);

        //default:
            // error
    }
    return;
}
*/

phez_hash_t* cwrap_phez_current_group_link_group(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_GROUP){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with group objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->link_group(obj.ptr.g);
    return(context->hdf5->append_to_hash(cwrap_phez_group_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_group_link_dataset(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_DATASET){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with dataset objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->link_dataset(obj.ptr.d);
    return(context->hdf5->append_to_hash(cwrap_phez_group_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_group_link_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->link_attribute(obj.ptr.a);
    return(context->hdf5->append_to_hash(cwrap_phez_group_get_current(context), hash_in));
}
void cwrap_phez_current_group_unlink_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->unlink_attribute(obj.ptr.a);
    return;
}
void cwrap_phez_current_group_unlink_dataset(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with dataset objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->unlink_dataset(obj.ptr.d);
    return;
}
void cwrap_phez_current_group_unlink_group(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_GROUP){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with group objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->unlink_group(obj.ptr.g);
    return;
}
void cwrap_phez_current_group_close(phez_context_t* context){
    context->hdf5->group->close();
    return;
}
void cwrap_phez_current_group_destroy(phez_context_t* context){
    context->hdf5->group->destroy();
    return;
}
phez_hash_t* cwrap_phez_group_get_current(phez_context_t* context){
    phez_object_t gobj;
    gobj.type = PHEZ_GROUP;
    gobj.ptr.g = context->hdf5->group->get_current();
    return(context->hdf5->hash(gobj));
}
void cwrap_phez_group_set_current(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_GROUP){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with group objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->group->set_current(obj.ptr.g);
    return;
}
size_t cwrap_phez_group_get_num(phez_context_t* context){
    return(context->hdf5->group->get_num());
}
char* cwrap_phez_current_group_get_name(phez_context_t* context){
    return(context->hdf5->group->get_current_name());
}
void cwrap_phez_current_group_set_name(phez_context_t* context, char* name_in){
    context->hdf5->group->set_current_name(name_in);
    return;
}
char* cwrap_phez_current_group_get_comment(phez_context_t* context){
    return(context->hdf5->group->get_current_comment());
}
void cwrap_phez_current_group_set_comment(phez_context_t* context, char* name_in){
    context->hdf5->group->set_current_comment(name_in);
    return;
}
void cwrap_phez_current_group_default_access_properties(phez_context_t* context){
    context->hdf5->group->default_current_access_properties();
    return;
}
void cwrap_phez_current_group_reset_creation_properties(phez_context_t* context){
    context->hdf5->group->reset_current_creation_properties();
    return;
}
void cwrap_phez_current_group_default_creation_properties(phez_context_t* context){
    context->hdf5->group->default_current_creation_properties();
    return;
}
size_t cwrap_phez_current_group_get_num_groups_linking(phez_context_t* context){
    return(context->hdf5->group->get_current_num_groups_linking());
}
size_t cwrap_phez_current_group_get_num_files_linking(phez_context_t* context){
    return(context->hdf5->group->get_current_num_files_linking());
}
size_t cwrap_phez_current_group_get_num_linked_attributes(phez_context_t* context){
    return(context->hdf5->group->get_current_num_linked_attributes());
}
size_t cwrap_phez_current_group_get_num_linked_datasets(phez_context_t* context){
    return(context->hdf5->group->get_current_num_linked_datasets());
}
size_t cwrap_phez_current_group_get_num_linked_groups(phez_context_t* context){
    return(context->hdf5->group->get_current_num_linked_groups());
}

/*********************** PHEZ group functions ****************************/



/********************** PHEZ dataset functions ***************************/


phez_hash_t* cwrap_phez_dataset_initialize(phez_context_t* context){
    phez_object_t dobj;
    dobj.type = PHEZ_DATASET;
    dobj.ptr.d = context->hdf5->dataset->initialize();
    return(context->hdf5->hash(dobj));
}
phez_hash_t* cwrap_phez_current_dataset_open(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    phez_object_t current_obj;
    hid_t id;
    phez_space_t* sptr;
    phez_hash_t* hash_out = nullptr;

    context->hdf5->stash_current_pointers();

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            current_obj.type = PHEZ_FILE;
            current_obj.ptr.f = context->hdf5->file->get_current();
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->dataset->open(id);
            context->hdf5->file->link_dataset(context->hdf5->dataset->get_current());
            break;

        case(PHEZ_GROUP):
            current_obj.type = PHEZ_GROUP;
            current_obj.ptr.g = context->hdf5->group->get_current();
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->dataset->open(id);
            context->hdf5->group->link_dataset(context->hdf5->dataset->get_current());
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Parent object can only be a file or group." << endl;
            PHEZ_FATAL_SUFFIX
            return(hash_out);
    }

    sptr = context->hdf5->space->initialize();
    context->hdf5->space->open(context->hdf5->dataset->get_current_id());
    context->hdf5->dataset->link_file_space(sptr);

    context->hdf5->pop_current_pointers();

    hash_out = context->hdf5->append_to_hash(context->hdf5->hash(current_obj), hash_in);
    return(hash_out);
}

/*
void cwrap_phez_current_dataset_make(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    hid_t id;

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->dataset->make(id);

        case(PHEZ_GROUP):
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->dataset->make(id);

        //default:
            // error
    }
    return;
}
*/

void cwrap_phez_current_dataset_read(phez_context_t* context){
    context->hdf5->dataset->read();
    return;
}
phez_hash_t* cwrap_phez_current_dataset_link_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->dataset->link_attribute(obj.ptr.a);
    return(context->hdf5->append_to_hash(cwrap_phez_dataset_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_dataset_link_file_space(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_SPACE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with space objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->dataset->link_file_space(obj.ptr.s);
    return(context->hdf5->append_to_hash(cwrap_phez_dataset_get_current(context), hash_in));
}
phez_hash_t* cwrap_phez_current_dataset_link_memory_space(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_SPACE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with space objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->dataset->link_memory_space(obj.ptr.s);
    return(context->hdf5->append_to_hash(cwrap_phez_dataset_get_current(context), hash_in));
}
void cwrap_phez_current_dataset_unlink_memory_space(phez_context_t* context){
    context->hdf5->dataset->unlink_memory_space();
    return;
}
void cwrap_phez_current_dataset_unlink_file_space(phez_context_t* context){
    context->hdf5->dataset->unlink_file_space();
    return;
}
void cwrap_phez_current_dataset_unlink_attribute(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->dataset->link_attribute(obj.ptr.a);
    return;
}
void cwrap_phez_current_dataset_write(phez_context_t* context){
    context->hdf5->dataset->write();
    return;
}
void cwrap_phez_current_dataset_close(phez_context_t* context){
    context->hdf5->dataset->close();
    return;
}
void cwrap_phez_current_dataset_destroy(phez_context_t* context){
    context->hdf5->dataset->destroy();
    return;
}
phez_hash_t* cwrap_phez_dataset_get_current(phez_context_t* context){
    phez_object_t dobj;
    dobj.type = PHEZ_DATASET;
    dobj.ptr.d = context->hdf5->dataset->get_current();
    return(context->hdf5->hash(dobj));
}
void cwrap_phez_dataset_set_current(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_DATASET){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with dataset objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->dataset->set_current(obj.ptr.d);
    return;
}
size_t cwrap_phez_dataset_get_num(phez_context_t* context){
    return(context->hdf5->dataset->get_num());
}
char* cwrap_phez_current_dataset_get_name(phez_context_t* context){
    return(context->hdf5->dataset->get_current_name());
}
void cwrap_phez_current_dataset_set_name(phez_context_t* context, char* name_in){
    context->hdf5->dataset->set_current_name(name_in);
    return;
}
char* cwrap_phez_current_dataset_get_comment(phez_context_t* context){
    return(context->hdf5->dataset->get_current_comment());
}
void cwrap_phez_current_dataset_set_comment(phez_context_t* context, char* comment_in){
    context->hdf5->dataset->set_current_comment(comment_in);
    return;
}
phez_dataset_type_t cwrap_phez_current_dataset_get_type(phez_context_t* context){
    return(context->hdf5->dataset->get_current_type());
}
bool* cwrap_phez_current_dataset_get_data_bool(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->dataset->get_current_type() != PHEZ_DATASET_DATA_TYPE_BOOL){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return dataset data as bool type, ";
        cout << "but the dataset type is not a bool type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->dataset->get_current_data<bool>());
}
void cwrap_phez_current_dataset_set_data_bool(phez_context_t* context, bool* data_in){
    context->hdf5->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_BOOL);
    context->hdf5->dataset->set_current_data<bool>(data_in);
    return;
}
int* cwrap_phez_current_dataset_get_data_int(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->dataset->get_current_type() != PHEZ_DATASET_DATA_TYPE_INT){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return dataset data as int type, ";
        cout << "but the dataset type is not an int type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->dataset->get_current_data<int>());
}
void cwrap_phez_current_dataset_set_data_int(phez_context_t* context, int* data_in){
    context->hdf5->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_INT);
    context->hdf5->dataset->set_current_data<int>(data_in);
    return;
}
float* cwrap_phez_current_dataset_get_data_float(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->dataset->get_current_type() != PHEZ_DATASET_DATA_TYPE_FLOAT){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return dataset data as float type, ";
        cout << "but the dataset type is not a float type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->dataset->get_current_data<float>());
}
void cwrap_phez_current_dataset_set_data_float(phez_context_t* context, float* data_in){
    context->hdf5->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_FLOAT);
    context->hdf5->dataset->set_current_data<float>(data_in);
    return;
}
double* cwrap_phez_current_dataset_get_data_double(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->dataset->get_current_type() != PHEZ_DATASET_DATA_TYPE_DOUBLE){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return dataset data as double type, ";
        cout << "but the dataset type is not a double type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->dataset->get_current_data<double>());
}
void cwrap_phez_current_dataset_set_data_double(phez_context_t* context, double* data_in){
    context->hdf5->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_DOUBLE);
    context->hdf5->dataset->set_current_data<double>(data_in);
    return;
}
char** cwrap_phez_current_dataset_get_data_string(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->dataset->get_current_type() != PHEZ_DATASET_DATA_TYPE_STRING){
        PHEZ_FATAL_PREFIX
        cout << "Trying to set dataset data as string type, ";
        cout << "but the dataset type is not a string type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->dataset->get_current_data<char*>());
}
void cwrap_phez_current_dataset_set_data_string(phez_context_t* context, char** data_in){
    context->hdf5->dataset->set_current_type(PHEZ_DATASET_DATA_TYPE_STRING);
    context->hdf5->dataset->set_current_data<char*>(data_in);
    return;
}
void cwrap_phez_current_dataset_reset_access_properties(phez_context_t* context){
    context->hdf5->dataset->reset_current_access_properties();
    return;
}
void cwrap_phez_current_dataset_default_access_properties(phez_context_t* context){
    context->hdf5->dataset->default_current_access_properties();
    return;
}
void cwrap_phez_current_dataset_reset_creation_properties(phez_context_t* context){
    context->hdf5->dataset->reset_current_creation_properties();
    return;
}
void cwrap_phez_current_dataset_default_creation_properties(phez_context_t* context){
    context->hdf5->dataset->default_current_creation_properties();
    return;
}
void cwrap_phez_current_dataset_default_transfer_properties(phez_context_t* context){
    context->hdf5->dataset->default_current_transfer_properties();
    return;
}
size_t cwrap_phez_current_dataset_get_num_groups_linking(phez_context_t* context){
    return(context->hdf5->dataset->get_current_num_groups_linking());
}
size_t cwrap_phez_current_dataset_get_num_files_linking(phez_context_t* context){
    return(context->hdf5->dataset->get_current_num_files_linking());
}
size_t cwrap_phez_current_dataset_get_num_linked_attributes(phez_context_t* context){
    return(context->hdf5->dataset->get_current_num_linked_attributes());
}

/********************** PHEZ dataset functions ***************************/



/********************* PHEZ attribute functions **************************/

phez_hash_t* cwrap_phez_attribute_initialize(phez_context_t* context){
    phez_object_t aobj;
    aobj.type = PHEZ_ATTRIBUTE;
    aobj.ptr.a = context->hdf5->attribute->initialize();
    return(context->hdf5->hash(aobj));
}
phez_hash_t* cwrap_phez_current_attribute_open(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    phez_object_t current_obj;
    hid_t id;
    phez_space_t* sptr;
    phez_hash_t* hash_out = nullptr;

    context->hdf5->stash_current_pointers();

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            current_obj.type = PHEZ_FILE;
            current_obj.ptr.f = context->hdf5->file->get_current();
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->attribute->open(id);
            context->hdf5->file->link_attribute(context->hdf5->attribute->get_current());
            break;

        case(PHEZ_GROUP):
            current_obj.type = PHEZ_GROUP;
            current_obj.ptr.g = context->hdf5->group->get_current();
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->attribute->open(id);
            context->hdf5->group->link_attribute(context->hdf5->attribute->get_current());
            break;

        case(PHEZ_DATASET):
            current_obj.type = PHEZ_DATASET;
            current_obj.ptr.d = context->hdf5->dataset->get_current();
            context->hdf5->dataset->set_current(obj.ptr.d);
            id = context->hdf5->dataset->get_current_id();
            context->hdf5->attribute->open(id);
            context->hdf5->dataset->link_attribute(context->hdf5->attribute->get_current());
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Parent object can only be a file, group, or dataset." << endl;
            PHEZ_FATAL_SUFFIX
            return(hash_out);
    }

    sptr = context->hdf5->space->initialize();
    context->hdf5->space->open(context->hdf5->attribute->get_current_id());
    context->hdf5->attribute->link_space(sptr);

    context->hdf5->pop_current_pointers();

    hash_out = context->hdf5->append_to_hash(context->hdf5->hash(current_obj), hash_in);
    return(hash_out);
}

/*
void cwrap_phez_current_attribute_make(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    hid_t id;

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_FILE):
            context->hdf5->file->set_current(obj.ptr.f);
            id = context->hdf5->file->get_current_id();
            context->hdf5->attribute->make(id);

        case(PHEZ_GROUP):
            context->hdf5->group->set_current(obj.ptr.g);
            id = context->hdf5->group->get_current_id();
            context->hdf5->attribute->make(id);

        case(PHEZ_DATASET):
            context->hdf5->dataset->set_current(obj.ptr.d);
            id = context->hdf5->dataset->get_current_id();
            context->hdf5->attribute->make(id);

        //default:
            // error
    }
    return;
}
*/

void cwrap_phez_current_attribute_read(phez_context_t* context){
    context->hdf5->attribute->read();
    return;
}
phez_hash_t* cwrap_phez_current_attribute_link_space(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_SPACE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with space objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->attribute->link_space(obj.ptr.s);
    return(context->hdf5->append_to_hash(cwrap_phez_attribute_get_current(context), hash_in));
}
void cwrap_phez_current_attribute_unlink_space(phez_context_t* context){
    context->hdf5->attribute->unlink_space();
    return;
}
void cwrap_phez_current_attribute_write(phez_context_t* context){
    context->hdf5->attribute->write();
    return;
}
void cwrap_phez_current_attribute_close(phez_context_t* context){
    context->hdf5->attribute->close();
    return;
}
void cwrap_phez_current_attribute_destroy(phez_context_t* context){
    context->hdf5->attribute->destroy();
    return;
}
phez_hash_t* cwrap_phez_attribute_get_current(phez_context_t* context){
    phez_object_t aobj;
    aobj.type = PHEZ_ATTRIBUTE;
    aobj.ptr.a = context->hdf5->attribute->get_current();
    return(context->hdf5->hash(aobj));
}
void cwrap_phez_attribute_set_current(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_ATTRIBUTE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with attribute objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->attribute->set_current(obj.ptr.a);
    return;
}
size_t cwrap_phez_attribute_get_num(phez_context_t* context){
    return(context->hdf5->attribute->get_num());
}
char* cwrap_phez_current_attribute_get_name(phez_context_t* context){
    return(context->hdf5->attribute->get_current_name());
}
void cwrap_phez_current_attribute_set_name(phez_context_t* context, char* name_in){
    context->hdf5->attribute->set_current_name(name_in);
    return;
}
phez_attribute_type_t cwrap_phez_current_attribute_get_type(phez_context_t* context){
    return(context->hdf5->attribute->get_current_type());
}
bool* cwrap_phez_current_attribute_get_data_bool(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->attribute->get_current_type() != PHEZ_ATTRIBUTE_DATA_TYPE_BOOL){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return attribute data as bool type, ";
        cout << "but the attribute type is not a bool type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->attribute->get_current_data<bool>());
}
void cwrap_phez_current_attribute_set_data_bool(phez_context_t* context, bool* data_in){
    context->hdf5->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_BOOL);
    context->hdf5->attribute->set_current_data<bool>(data_in);
    return;
}
int* cwrap_phez_current_attribute_get_data_int(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->attribute->get_current_type() != PHEZ_ATTRIBUTE_DATA_TYPE_INT){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return attribute data as int type, ";
        cout << "but the attribute type is not an int type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->attribute->get_current_data<int>());
}
void cwrap_phez_current_attribute_set_data_int(phez_context_t* context, int* data_in){
    context->hdf5->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_INT);
    context->hdf5->attribute->set_current_data<int>(data_in);
    return;
}
float* cwrap_phez_current_attribute_get_data_float(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->attribute->get_current_type() != PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return attribute data as float type, ";
        cout << "but the attribute type is not a float type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->attribute->get_current_data<float>());
}
void cwrap_phez_current_attribute_set_data_float(phez_context_t* context, float* data_in){
    context->hdf5->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT);
    context->hdf5->attribute->set_current_data<float>(data_in);
    return;
}
double* cwrap_phez_current_attribute_get_data_double(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->attribute->get_current_type() != PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE){
        PHEZ_FATAL_PREFIX
        cout << "Trying to return attribute data as double type, ";
        cout << "but the attribute type is not a double type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->attribute->get_current_data<double>());
}
void cwrap_phez_current_attribute_set_data_double(phez_context_t* context, double* data_in){
    context->hdf5->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE);
    context->hdf5->attribute->set_current_data<double>(data_in);
    return;
}
char** cwrap_phez_current_attribute_get_data_string(phez_context_t* context){
    // Can expand if statement
    if(context->hdf5->attribute->get_current_type() != PHEZ_ATTRIBUTE_DATA_TYPE_STRING){
        PHEZ_FATAL_PREFIX
        cout << "Trying to set attribute data as string type, ";
        cout << "but the attribute type is not a string type." << endl;
        PHEZ_FATAL_SUFFIX
    }
    return(context->hdf5->attribute->get_current_data<char*>());
}
void cwrap_phez_current_attribute_set_data_string(phez_context_t* context, char** data_in){
    context->hdf5->attribute->set_current_type(PHEZ_ATTRIBUTE_DATA_TYPE_STRING);
    context->hdf5->attribute->set_current_data<char*>(data_in);
    return;
}
void cwrap_phez_current_attribute_reset_creation_properties(phez_context_t* context){
    context->hdf5->attribute->reset_current_creation_properties();
    return;
}
void cwrap_phez_current_attribute_default_creation_properties(phez_context_t* context){
    context->hdf5->attribute->default_current_creation_properties();
    return;
}
size_t cwrap_phez_current_attribute_get_num_datasets_linking(phez_context_t* context){
    return(context->hdf5->attribute->get_current_num_datasets_linking());
}
size_t cwrap_phez_current_attribute_get_num_groups_linking(phez_context_t* context){
    return(context->hdf5->attribute->get_current_num_groups_linking());
}
size_t cwrap_phez_current_attribute_get_num_files_linking(phez_context_t* context){
    return(context->hdf5->attribute->get_current_num_files_linking());
}

/********************* PHEZ attribute functions **************************/



/*********************** PHEZ space functions ****************************/

phez_hash_t* cwrap_phez_space_initialize(phez_context_t* context){
    phez_object_t sobj;
    sobj.type = PHEZ_SPACE;
    sobj.ptr.s = context->hdf5->space->initialize();
    return(context->hdf5->hash(sobj));
}
phez_hash_t* cwrap_phez_current_space_open(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    phez_object_t current_obj;
    hid_t id;
    phez_hash_t* hash_out = nullptr;

    obj = context->hdf5->dehash(hash_in);

    switch(obj.type){
        case(PHEZ_DATASET):
            current_obj.type = PHEZ_DATASET;
            current_obj.ptr.d = context->hdf5->dataset->get_current();
            context->hdf5->dataset->set_current(obj.ptr.d);
            id = context->hdf5->dataset->get_current_id();
            context->hdf5->space->open(id);
            context->hdf5->dataset->link_file_space(context->hdf5->space->get_current());
            context->hdf5->dataset->set_current(current_obj.ptr.d);
            break;

        case(PHEZ_ATTRIBUTE):
            current_obj.type = PHEZ_ATTRIBUTE;
            current_obj.ptr.a = context->hdf5->attribute->get_current();
            context->hdf5->attribute->set_current(obj.ptr.a);
            id = context->hdf5->attribute->get_current_id();
            context->hdf5->space->open(id);
            context->hdf5->attribute->link_space(context->hdf5->space->get_current());
            context->hdf5->attribute->set_current(current_obj.ptr.a);
            break;

        default:
            PHEZ_FATAL_PREFIX
            cout << "Parent object can only be a dataset or attribute." << endl;
            PHEZ_FATAL_SUFFIX
            return(hash_out);
    }

    hash_out = context->hdf5->append_to_hash(context->hdf5->hash(current_obj), hash_in);
    return(hash_out);
}

/*
void cwrap_phez_current_space_make(phez_context_t* context){
    context->hdf5->space->make();
    return;
}
*/

void cwrap_phez_current_space_close(phez_context_t* context){
    context->hdf5->space->close();
    return;
}
void cwrap_phez_current_space_destroy(phez_context_t* context){
    context->hdf5->space->destroy();
    return;
}
phez_hash_t* cwrap_phez_space_get_current(phez_context_t* context){
    phez_object_t sobj;
    sobj.type = PHEZ_SPACE;
    sobj.ptr.s = context->hdf5->space->get_current();
    return(context->hdf5->hash(sobj));
}
void cwrap_phez_space_set_current(phez_context_t* context, phez_hash_t* hash_in){
    phez_object_t obj;
    obj = context->hdf5->dehash(hash_in);
    if(obj.type != PHEZ_SPACE){
        PHEZ_FATAL_PREFIX
        cout << "This function can only be called with space objects." << endl;
        PHEZ_FATAL_SUFFIX
    }
    context->hdf5->space->set_current(obj.ptr.s);
    return;
}
size_t cwrap_phez_space_get_num(phez_context_t* context){
    return(context->hdf5->space->get_num());
}

phez_space_ptype_t cwrap_phez_current_space_get_ptype(phez_context_t* context){
    return(context->hdf5->space->get_current_ptype());
}
void cwrap_phez_current_space_set_ptype(phez_context_t* context, phez_space_ptype_t ptype_in){
    context->hdf5->space->set_current_ptype(ptype_in);
    return;
}

size_t cwrap_phez_current_space_get_size(phez_context_t* context){
    return(context->hdf5->space->get_current_size());
}
void cwrap_phez_current_space_set_size(phez_context_t* context, size_t size_in){
    context->hdf5->space->set_current_size(size_in);
    return;
}
size_t* cwrap_phez_current_space_get_dims_now(phez_context_t* context){
    return(context->hdf5->space->get_current_dims_now());
}
void cwrap_phez_current_space_set_dims_now(phez_context_t* context, size_t* dims_now_in){
    context->hdf5->space->set_current_dims_now(dims_now_in);
    return;
}
size_t* cwrap_phez_current_space_get_dims_max(phez_context_t* context){
    return(context->hdf5->space->get_current_dims_max());
}
void cwrap_phez_current_space_set_dims_max(phez_context_t* context, size_t* dims_max_in){
    context->hdf5->space->set_current_dims_max(dims_max_in);
    return;
}
phez_space_type_t cwrap_phez_current_space_get_type(phez_context_t* context){
    return(context->hdf5->space->get_current_type());
}
void cwrap_phez_current_space_set_type(phez_context_t* context, phez_space_type_t type_in){
    context->hdf5->space->set_current_type(type_in);
    return;
}

/*
void cwrap_phez_current_space_select_all(phez_context_t* context){
    context->hdf5->space->select_all();
    return;
}
void cwrap_phez_current_space_select_none(phez_context_t* context){
    context->hdf5->space->select_none();
    return;
}
void cwrap_phez_current_space_select_inverse(phez_context_t* context){
    context->hdf5->space->select_inverse();
    return;
}
void cwrap_phez_current_space_add_elements_to_selection(phez_context_t* context,
                                                  size_t nelements_in,
                                                  size_t* coords_in){

    context->hdf5->space->add_elements_to_selection(nelements_in,
                                                 coords_in);
    return;
}
void cwrap_phez_current_space_subtract_elements_from_selection(phez_context_t* context,
                                                         size_t nelements_in,
                                                         size_t* coords_in){

    context->hdf5->space->subtract_elements_from_selection(nelements_in,
                                                        coords_in);
    return;
}
void cwrap_phez_current_space_and_elements_with_selection(phez_context_t* context,
                                                    size_t nelements_in,
                                                    size_t* coords_in){

    context->hdf5->space->and_elements_with_selection(nelements_in,
                                                   coords_in);
    return;
}
void cwrap_phez_current_space_xor_elements_with_selection(phez_context_t* context,
                                                    size_t nelements_in,
                                                    size_t* coords_in){

    context->hdf5->space->xor_elements_with_selection(nelements_in,
                                                   coords_in);
    return;
}
void cwrap_phez_current_space_add_hyperslabs_to_selection(phez_context_t* context,
                                                    size_t* start_in,
                                                    size_t* stride_in,
                                                    size_t* count_in,
                                                    size_t* block_in){

    context->hdf5->space->add_hyperslabs_to_selection(start_in,
                                                   stride_in,
                                                   count_in,
                                                   block_in);

    return;
}
void cwrap_phez_current_space_subtract_hyperslabs_from_selection(phez_context_t* context,
                                                           size_t* start_in,
                                                           size_t* stride_in,
                                                           size_t* count_in,
                                                           size_t* block_in){

    context->hdf5->space->subtract_hyperslabs_from_selection(start_in,
                                                          stride_in,
                                                          count_in,
                                                          block_in);

    return;
}
void cwrap_phez_current_space_and_hyperslabs_with_selection(phez_context_t* context,
                                                      size_t* start_in,
                                                      size_t* stride_in,
                                                      size_t* count_in,
                                                      size_t* block_in){

    context->hdf5->space->and_hyperslabs_with_selection(start_in,
                                                     stride_in,
                                                     count_in,
                                                     block_in);

    return;
}
void cwrap_phez_current_space_xor_hyperslabs_with_selection(phez_context_t* context,
                                                      size_t* start_in,
                                                      size_t* stride_in,
                                                      size_t* count_in,
                                                      size_t* block_in){

    context->hdf5->space->xor_hyperslabs_with_selection(start_in,
                                                     stride_in,
                                                     count_in,
                                                     block_in);

    return;
}
*/

size_t cwrap_phez_current_space_get_num_datasets_linking(phez_context_t* context){
    return(context->hdf5->space->get_current_num_datasets_linking());
}
size_t cwrap_phez_current_space_get_num_attributes_linking(phez_context_t* context){
    return(context->hdf5->space->get_current_num_attributes_linking());
}

/*********************** PHEZ space functions ****************************/


/*********************** PHEZ unit tests ****************************/


bool cwrap_phez_tests_but_is_it_art(phez_test_context_t* context){
    return(context->hdf5_test->but_is_it_art());
}
bool cwrap_phez_tests_can_init_and_destroy_a_file(phez_test_context_t* context){
    return(context->hdf5_test->can_init_and_destroy_a_file());
}
bool cwrap_phez_tests_can_init_and_destroy_a_group(phez_test_context_t* context){
    return(context->hdf5_test->can_init_and_destroy_a_group());
}
bool cwrap_phez_tests_can_init_and_destroy_a_dataset(phez_test_context_t* context){
    return(context->hdf5_test->can_init_and_destroy_a_dataset());
}
bool cwrap_phez_tests_can_init_and_destroy_an_attribute(phez_test_context_t* context){
    return(context->hdf5_test->can_init_and_destroy_an_attribute());
}
bool cwrap_phez_tests_can_init_and_destroy_a_space(phez_test_context_t* context){
    return(context->hdf5_test->can_init_and_destroy_a_space());
}
bool cwrap_phez_tests_can_file_link_and_unlink_to_group(phez_test_context_t* context){
    return(context->hdf5_test->can_file_link_and_unlink_to_group());
}
bool cwrap_phez_tests_can_file_link_and_unlink_to_dataset(phez_test_context_t* context){
    return(context->hdf5_test->can_file_link_and_unlink_to_dataset());
}
bool cwrap_phez_tests_can_file_link_and_unlink_to_attribute(phez_test_context_t* context){
    return(context->hdf5_test->can_file_link_and_unlink_to_attribute());
}
bool cwrap_phez_tests_can_group_link_and_unlink_to_group(phez_test_context_t* context){
    return(context->hdf5_test->can_group_link_and_unlink_to_group());
}
bool cwrap_phez_tests_can_group_link_and_unlink_to_dataset(phez_test_context_t* context){
    return(context->hdf5_test->can_group_link_and_unlink_to_dataset());
}
bool cwrap_phez_tests_can_group_link_and_unlink_to_attribute(phez_test_context_t* context){
    return(context->hdf5_test->can_group_link_and_unlink_to_attribute());
}
bool cwrap_phez_tests_can_dataset_link_and_unlink_to_attribute(phez_test_context_t* context){
    return(context->hdf5_test->can_dataset_link_and_unlink_to_attribute());
}
bool cwrap_phez_tests_can_make_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_make_any_object());
}
bool cwrap_phez_tests_can_open_and_close_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_open_and_close_any_object());
}
bool cwrap_phez_tests_can_write_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_write_any_object());
}
bool cwrap_phez_tests_can_read_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_read_any_object());
}
bool cwrap_phez_tests_can_recursively_populate_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_recursively_populate_any_object());
}
bool cwrap_phez_tests_can_recursively_flush_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_recursively_flush_any_object());
}
bool cwrap_phez_tests_can_recursively_close_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_recursively_close_any_object());
}
bool cwrap_phez_tests_can_recursively_forget_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_recursively_forget_any_object());
}
bool cwrap_phez_tests_can_recursively_remove_any_object(phez_test_context_t* context){
    return(context->hdf5_test->can_recursively_remove_any_object());
}
bool cwrap_phez_tests_can_hash_then_dehash(phez_test_context_t* context){
    return(context->hdf5_test->can_hash_then_dehash());
}
bool cwrap_phez_tests_can_append_to_hash_then_peel_from_hash(phez_test_context_t* context){
    return(context->hdf5_test->can_append_to_hash_then_peel_from_hash());
}
bool cwrap_phez_tests_can_extract_object_with_hash(phez_test_context_t* context){
    return(context->hdf5_test->can_extract_object_with_hash());
}
bool cwrap_phez_tests_can_appear_any_object_with_hash(phez_test_context_t* context){
    return(context->hdf5_test->can_appear_any_object_with_hash());
}

/*********************** PHEZ unit tests ****************************/

/*********************** PHEZ internal functions ****************************/

phez_hash_t* cwrap_phez_current_dataset_get_linked_file_space(phez_context_t* context){
    phez_object_t sobj;
    sobj.type = PHEZ_SPACE;
    sobj.ptr.s = context->hdf5->dataset->get_current_linked_file_space();
    return(context->hdf5->hash(sobj));
}
phez_hash_t* cwrap_phez_current_dataset_get_linked_memory_space(phez_context_t* context){
    phez_object_t sobj;
    sobj.type = PHEZ_SPACE;
    sobj.ptr.s = context->hdf5->dataset->get_current_linked_memory_space();
    return(context->hdf5->hash(sobj));
}
phez_hash_t* cwrap_phez_current_attribute_get_linked_space(phez_context_t* context){
    phez_object_t sobj;
    sobj.type = PHEZ_SPACE;
    sobj.ptr.s = context->hdf5->attribute->get_current_linked_space();
    return(context->hdf5->hash(sobj));
}
size_t cwrap_phez_internal_get_hash_digits(phez_context_t* context){
    return(context->hdf5->get_hash_digits());
}


void cwrap_phez_internal_file_set_current_to_null(phez_context_t* context){
    context->hdf5->file->set_current((phez_file_type*)nullptr);
	return;
}
void cwrap_phez_internal_group_set_current_to_null(phez_context_t* context){
    context->hdf5->group->set_current((phez_group_type*)nullptr);
	return;
}
void cwrap_phez_internal_dataset_set_current_to_null(phez_context_t* context){
    context->hdf5->dataset->set_current((phez_dataset_type*)nullptr);
	return;
}
void cwrap_phez_internal_attribute_set_current_to_null(phez_context_t* context){
    context->hdf5->attribute->set_current((phez_attribute_type*)nullptr);
	return;
}
void cwrap_phez_internal_space_set_current_to_null(phez_context_t* context){
    context->hdf5->space->set_current((phez_space_type*)nullptr);
	return;
}

/*********************** PHEZ internal functions ****************************/

