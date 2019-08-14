
#ifndef SET_PHEZ_HDF5_T_API_H_
#define SET_PHEZ_HDF5_T_API_H_

#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>

#include "phez_macros.hpp"

#include "phez_types.hpp"
#include "phez_space_t_api.hpp"
#include "phez_attribute_t_api.hpp"
#include "phez_dataset_t_api.hpp"
#include "phez_group_t_api.hpp"
#include "phez_file_t_api.hpp"

using std::cout;

typedef char phez_hash_t;
typedef struct phez_object_type phez_object_t;
typedef struct phez_hash_pair_type phez_hash_pair_t;
typedef struct phez_hdf5_callback_type phez_hdf5_callback_t;

/** \struct phez_object_type phez_hdf5_t_api.hpp
 *  \brief A struct with information about an arbitrary object's pointer,
 *         including the pointer, its type, and the hash length.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_object_type {
    //size_t            length;
    phez_hdf5_otype_t type;
    union ptr_t {
        phez_file_t*        f;
        phez_group_t*       g;
        phez_dataset_t*     d;
        phez_attribute_t*   a;
        phez_space_t*       s;
    } ptr;
};

/** \struct phez_object_type phez_hdf5_t_api.hpp
 *  \brief A struct with information about an arbitrary object's pointer,
 *         including the pointer, its type, and the hash length.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_hdf5_subclass_t {
    phez_hdf5_otype_t type;
    union ptr_t {
        hdf5_files*        f;
        hdf5_groups*       g;
        hdf5_datasets*     d;
        hdf5_attributes*   a;
        hdf5_spaces*       s;
    } ptr;
};

struct phez_hash_pair_type {
    int number;
    char digit;
};

/** \class hdf5_class phez_hdf5_t_api.hpp
 *  \brief The PHEZ I/O class. Contains recursive API functions and hashing functions.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
class hdf5_class {

    public:
        // constructor
        hdf5_class();
        // destructor
        ~hdf5_class();

        hdf5_files* file;
        hdf5_groups* group;
        hdf5_datasets* dataset;
        hdf5_attributes* attribute;
        hdf5_spaces* space;

        // cascading API functions for convenience
        void populate(phez_hash_t*); /* read in data for all discovered objects in input object */
        void flush(phez_hash_t*);    /* flush to input object; all flushed objects (including input) will be closed */
        void close(phez_hash_t*);    /* close input object and everything in it,
                                                but maintain structs and links */
        void forget(phez_hash_t*);   /* unlink all objects linked from input object; close and destroy
                                                any that are no longer linked */
        void remove(phez_hash_t*);   /* forget everything in input object, then destroy its struct */

        void populate_all();    /* populate everything in every open file */
        void flush_all();       /* flush everything in every open file */
        void close_all();       /* close everything in every open file */
        void forget_all();      /* forget everything in every open file */
        void remove_all();      /* remove everything in every open file */

        // other API functions
        //void            reduce_redundant();           /* delete extra object copies and relink */
        phez_hash_t*    extract(phez_hash_t*,         /* Open an object and append its ID to a hash, nested objects */
                                phez_hdf5_otype_t,    /* entail sequential "extract" calls; can use cascading calls */
                                char*);
        phez_hash_t*    appear(phez_hash_t*);         /* turn object into a file and load into memory (Nate's method) */

        phez_hash_t*    hash(phez_object_t);          /* Create a hash for an object (by itself) */
        phez_object_t   dehash(phez_hash_t*);         /* Parse the hash for the object ID and type */
        phez_hash_t*    append_to_hash(phez_hash_t*,  /* Append the ID of the object to the hash; */
                                               phez_hash_t*); /* also check for recursive linking here */
        phez_hash_t*    peel_from_hash(phez_hash_t*); /* Return the ID of the oldest ancestor of the
                                                                         hashed object and remove it from the hash */
        phez_hash_t*    get_hash_parent(phez_hash_t*);  /* Return the ID of the hashed object and remove it from the hash */

        /* Only need for fortran bindings */
        size_t get_hash_digits();

        void stash_current_pointers();
        void pop_current_pointers();
        void clear_current_pointers();

    private:
        int indx_min;       /**< Minimum index of all objects (default is 0) */
        int indx_max;       /**< Maximum index of all objects */
        int indx_range;     /**< Range of indices for all objects */
        int hash_base;      /**< Number base for hashes (default is 62, the number of alphanumeric characters) */
        size_t hash_digits; /**< Number of digits in hash_base required to represent all possible objects */
        phez_hash_pair_t* hash_list;

        char                    int_to_hash_digit(int);               /* Convert int to base-62 digit (as alphanumeric) */
        int                     hash_digit_to_int(char);              /* Convert base-62 digit (as alphanumeric) to int */

        /**************************************/
        /*                                    */
        /*  internal callbacks and iterators  */
        /*                                    */
        /**************************************/

        template<typename FUNC> void iterate_attributes(phez_object_t, FUNC);
        template<typename FUNC> void iterate_datasets(phez_object_t, FUNC);
        template<typename FUNC> void iterate_groups(phez_object_t, FUNC);
        template<typename FFUNC,
                 typename GFUNC,
                 typename DFUNC,
                 typename AFUNC,
                 typename SFUNC> void iterate(phez_hash_t*, FFUNC, GFUNC, DFUNC, AFUNC, SFUNC);

        void open_spaces(phez_object_t); // paired with close_spaces for populate routines
        void make_spaces(phez_object_t); // paired with close_spaces for flush routines
        void close_spaces(phez_object_t);

        void populate_attributes(phez_object_t);
        void populate_datasets(phez_object_t);
        void populate_groups(phez_object_t);

        // iterators
        void flush_attributes(phez_object_t);
        void flush_datasets(phez_object_t);
        void flush_groups(phez_object_t);
        // code meat
        void flush_space(hid_t, phez_object_t);
        void flush_attribute(hid_t, phez_object_t);
        void flush_dataset(hid_t, phez_object_t);
        void flush_group(hid_t, phez_object_t);
        void flush_file(phez_object_t);

        void close_attributes(phez_object_t);
        void close_datasets(phez_object_t);
        void close_groups(phez_object_t);

        void forget_spaces(phez_hash_t*);
        void forget_attributes(phez_hash_t*);
        void forget_datasets(phez_hash_t*);
        void forget_groups(phez_hash_t*);

        phez_file_t* stash_fptr;
        phez_group_t* stash_gptr;
        phez_dataset_t* stash_dptr;
        phez_attribute_t* stash_aptr;
        phez_space_t* stash_sptr;
};

struct phez_hdf5_callback_type {
    hdf5_class* thisptr;
    phez_object_t obj;
};

#endif

