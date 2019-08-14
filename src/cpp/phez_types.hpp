#ifndef SET_PHEZ_TYPES_H_
#define SET_PHEZ_TYPES_H_

// From debug.h...
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <hdf5.h>
#include "phez_macros.hpp"

/************************* HDF5 subclass notes ********************************/
//
//  All HDF5 subclass routines act on the current_... variable, set this pointer
//  to the correct address before calling a routine!
//
//  e.g.,
//      context.hdf5.file.set_current(file_ptr);
//      context.hdf5.file.destroy();
//
/******************************************************************************/

//typedef hid_t aapl_t;
typedef hid_t acpl_t;
typedef hid_t dapl_t;
typedef hid_t dcpl_t;
typedef hid_t dxpl_t;
typedef hid_t gapl_t;
typedef hid_t gcpl_t;
typedef hid_t fapl_t;
typedef hid_t fcpl_t;


/** \enum cmpp_hdf5_otype_t
 * \brief Enumerates valid PHEZ object types.
 */
enum phez_hdf5_otype_t {
    PHEZ_OBJECT_START               = 10,//!< PHEZ_OBJECT_START

    PHEZ_SPACE                      = 11,//!< PHEZ_SPACE
    PHEZ_ATTRIBUTE                  = 12,//!< PHEZ_ATTRIBUTE
    PHEZ_DATASET                    = 13,//!< PHEZ_DATASET
    PHEZ_GROUP                      = 14,//!< PHEZ_GROUP
    PHEZ_FILE                       = 15,//!< PHEZ_FILE

    PHEZ_OBJECT_END                 = 16 //!< PHEZ_OBJECT_END
};

/** \enum phez_space_type_t
 * \brief Enumerates valid PHEZ space types.
 */
enum phez_space_type_t {
    PHEZ_SPACE_TYPE_INVALID         = -100,

    PHEZ_SPACE_TYPE_NULL            = 100,
    PHEZ_SPACE_TYPE_SIMPLE          = 101,
    PHEZ_SPACE_TYPE_SCALAR          = 102
};
/** \enum phez_space_ptype_t
 * \brief Enumerates valid PHEZ space parent object types.
 */
enum phez_space_ptype_t {
    PHEZ_SPACE_PTYPE_INVALID        = -101,

    PHEZ_SPACE_PTYPE_ATTRIBUTE      = 103,
    PHEZ_SPACE_PTYPE_DATASET        = 104
};
#define PHEZ_SPACE_ID_INVALID        -102
#define PHEZ_SPACE_SIZE_INVALID      -103

typedef hid_t phez_attribute_type_t;
#define PHEZ_ATTRIBUTE_TYPE_INVALID  -200
#define PHEZ_ATTRIBUTE_ID_INVALID    -201

typedef hid_t phez_dataset_type_t;
#define PHEZ_DATASET_TYPE_INVALID    -300
#define PHEZ_DATASET_ID_INVALID      -301
#define PHEZ_DATASET_SIZE_INVALID    -302

#define PHEZ_GROUP_ID_INVALID        -401

/** \enum phez_file_action_t
 * \brief Enumerates valid PHEZ file actions.
 */
enum phez_file_action_t {
    PHEZ_FILE_ACTION_INVALID        = -500,

    PHEZ_FILE_ACTION_RDONLY         = 500,
    PHEZ_FILE_ACTION_WRONLY         = 501,
    PHEZ_FILE_ACTION_OVERWR         = 502,
    PHEZ_FILE_ACTION_APPEND         = 503
};
#define PHEZ_FILE_ID_INVALID         -501


/** \enum phez_space_state_t
 * \brief Enumerates valid PHEZ space states.
 */
enum phez_space_state_t {
    PHEZ_SPACE_STATE_START          = 1000,

    PHEZ_SPACE_STATE_DEFINED        = 1001,
    PHEZ_SPACE_STATE_OPENED         = 1002,
    PHEZ_SPACE_STATE_MADE           = 1003,

    // closed state is the same as "defined" state

    PHEZ_SPACE_STATE_END            = 1004
};

/** \enum phez_attribute_state_t
 * \brief Enumerates valid PHEZ attribute states.
 */
enum phez_attribute_state_t {
    PHEZ_ATTRIBUTE_STATE_START      = 2000,

    PHEZ_ATTRIBUTE_STATE_DEFINED    = 2001,
    PHEZ_ATTRIBUTE_STATE_OPENED     = 2002,
    PHEZ_ATTRIBUTE_STATE_MADE       = 2003,
    PHEZ_ATTRIBUTE_STATE_READ       = 2004,
    PHEZ_ATTRIBUTE_STATE_WRITTEN    = 2005,

    // closed state is the same as "defined" state

    PHEZ_ATTRIBUTE_STATE_END        = 2017
};

/** \enum phez_dataset_state_t
 * \brief Enumerates valid PHEZ dataset states.
 */
enum phez_dataset_state_t {
    PHEZ_DATASET_STATE_START        = 3000,

    PHEZ_DATASET_STATE_DEFINED      = 3001,
    PHEZ_DATASET_STATE_OPENED       = 3002,
    PHEZ_DATASET_STATE_MADE         = 3003,
    PHEZ_DATASET_STATE_READ         = 3004,
    PHEZ_DATASET_STATE_WRITTEN      = 3005,

    // closed state is the same as "defined" state

    PHEZ_DATASET_STATE_END          = 3017
};

/** \enum phez_group_state_t
 * \brief Enumerates valid PHEZ group states.
 */
enum phez_group_state_t {
    PHEZ_GROUP_STATE_START          = 4000,

    PHEZ_GROUP_STATE_DEFINED        = 4001,
    PHEZ_GROUP_STATE_OPENED         = 4002,
    PHEZ_GROUP_STATE_MADE           = 4003,

    // closed state is the same as "defined" state

    PHEZ_GROUP_STATE_END            = 4005
};

/** \enum phez_file_state_t
 * \brief Enumerates valid PHEZ file states.
 */
enum phez_file_state_t {
    PHEZ_FILE_STATE_START           = 5000,

    PHEZ_FILE_STATE_DEFINED         = 5001,
    PHEZ_FILE_STATE_OPENED          = 5002,
    PHEZ_FILE_STATE_MADE            = 5003,

    // closed state is the same as "defined" state

    PHEZ_FILE_STATE_END             = 5004
};

typedef struct phez_space_type phez_space_t;
typedef struct phez_attribute_type phez_attribute_t;
typedef struct phez_dataset_type phez_dataset_t;
typedef struct phez_group_type phez_group_t;
typedef struct phez_file_type phez_file_t;


/** \struct phez_space_type phez_types.hpp
 *  \brief The struct where basic information about an HDF5 space is stored.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_space_type {
    hid_t id;            /**< HDF5 space ID. */
    phez_space_ptype_t ptype; /**< Type of object that can link to this space
                                 (only attributes and datasets). */
    int size;            /**< Length of the dataspace (i.e., the number of dimensions). */
    phez_space_type_t type;/**< HDF5 dataspace type. WARNING! Always assign
                              with the HDF5 macros, the actual values are not persistent! */
    size_t *dims_now;    /**< Current dimension sizes; malloc before assigning,
                              and do that before malloccing any data. */
    size_t *dims_max;    /**< Maximum dimension sizes; malloc before assigning,
                              and do that before malloccing any data. */

    phez_space_state_t state;         /**< PHEZ_SPACE state; flags prevent function calls
                                         before all the necessary info is defined */
    bool state_size;     /**< Has the space size been defined? */
    bool state_dims_now; /**< Have the space's current dimension sizes been defined? */
    bool state_dims_max; /**< Have the space's maximum dimension sizes been defined? */
    bool state_ptype;    /**< Has the space's parent type been defined? */

    // inward links:
    size_t num_datasets_linking;    /**< Number of datasets currently pointing
                                         at this space.*/
    size_t num_attributes_linking;  /**< Number of attributes currently pointing
                                         at this space.*/
};

/** \struct phez_attribute_type phez_types.hpp
 *  \brief The struct where basic information about an HDF5 attribute is stored.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_attribute_type {
    hid_t id;           /**< HDF5 attribute ID. */
    char *name;         /**< HDF5 attribute name. */
//    aapl_t aapl;        /**< HDF5 attribute access property list. Each file
//                             may only have one, hence why it is defined
//                             separately from the pls array. */
    acpl_t acpl;        /**< HDF5 attribute creation property list. Each file
                             may only have one, hence why it is defined
                             separately from the pls array. */
    phez_attribute_type_t type;/**< HDF5 predefined data type. WARNING! Always assign
                             with the HDF5 macros, the actual values are not
                             persistent! */
    void *data;         /**< Data for attribute. */

    phez_attribute_state_t state;       /**< PHEZ_ATTRIBUTE state; flags prevent function calls
                                       before all the necessary info is defined */
    bool state_name;    /**< Has the attribute name been defined? */
    bool state_type;    /**< Has the attribute type been defined? */
    bool state_data;    /**< Has the attribute data been defined? */

    // inward links:
    size_t num_files_linking;     /**< Number of files currently pointing
                                       at this attribute.*/
    size_t num_groups_linking;    /**< Number of groups currently pointing
                                       at this attribute.*/
    size_t num_datasets_linking;  /**< Number of datasets currently pointing
                                       at this attribute.*/

    // outward links:
    phez_space_t *linked_space;  /**< Pointer to space of the attribute. */
};

/** \struct phez_dataset_type phez_types.hpp
 *  \brief The struct where basic information about an HDF5 dataset is stored.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_dataset_type {
    hid_t id;           /**< HDF5 dataset ID. */
    char *name;         /**< HDF5 dataset name. */
    char *comment;      /**< HDF5 dataset comment. */
    dapl_t dapl;        /**< HDF5 dataset access property list. */
    dcpl_t dcpl;        /**< HDF5 dataset creation property list. */
    dxpl_t dxpl;        /**< HDF5 dataset transfer property list. */

    //size_t size;        /**< Number of data elements. */
    phez_dataset_type_t type;/**< HDF5 predefined data type. WARNING! Always assign
                                  with the HDF5 macros, the actual values are not
                                  persistent!*/
    void *data;         /**< Data for dataset. */

    phez_dataset_state_t state;       /**< PHEZ_DATASET state; flags prevent function calls
                                       before all the necessary info is defined */
    bool state_name;    /**< Has the dataset name been defined? */
    bool state_type;    /**< Has the dataset type been defined? */
    bool state_data;    /**< Has the dataset data been defined? */

    // inward links:
    size_t num_files_linking;     /**< Number of files currently pointing
                                       at this dataset.*/
    size_t num_groups_linking;    /**< Number of groups currently pointing
                                       at this dataset.*/

    // outward links:
    size_t num_linked_attributes; /**< Number of attributes in the dataset. */
    phez_attribute_t ***linked_attributes;  /**< Pointer to array of pointers to
                                                         attributes in the dataset. */
    phez_space_t *linked_memory_space;  /**< Pointer to memory space of the dataset. */
    phez_space_t *linked_file_space;    /**< Pointer to file space of the dataset. */
};

/** \struct phez_group_type phez_types.hpp
 *  \brief The struct where basic information about an HDF5 group is stored.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
struct phez_group_type {
    hid_t id;            /**< HDF5 group ID. */
    char *name;          /**< HDF5 group name. */
    char *comment;       /**< HDF5 group comment. */
    gapl_t gapl;         /**< HDF5 group access property list. */
    gcpl_t gcpl;         /**< HDF5 group creation property list. */

    phez_group_state_t state;       /**< PHEZ_GROUP state; flags prevent function calls
                                       before all the necessary info is defined */
    bool state_name;    /**< Has the group name been defined? */

    // inward links:
    size_t num_files_linking;     /**< Number of files currently pointing
                                       at this group.*/
    size_t num_groups_linking;    /**< Number of groups currently pointing
                                       at this group.*/

    // outward links:
    size_t num_linked_attributes; /**< Number of attributes in the group. */
    size_t num_linked_datasets;   /**< Number of datasets in the group. */
    size_t num_linked_groups;     /**< Number of subgroups in the group. */
    phez_attribute_t ***linked_attributes;  /**< Pointer to array of pointers to
                                                         attributes in the group.*/
    phez_dataset_t ***linked_datasets;      /**< Pointer to array of pointers to
                                                         all datasets in the group.*/
    phez_group_t ***linked_groups;          /**< Pointer to array of pointers to
                                                         all subgroups in the group.*/
};

/** \struct phez_file_type phez_types.hpp
 *  \brief The struct where basic information about an HDF5 file is stored.
 * \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 *
 * \detail The struct where basic information about an HDF5 file is stored.
 *         This is a hybrid data type; it refers to the root group in HDF5
 *         regions, but refers to the file itself in PHEZ I/O regions.
 */
struct phez_file_type {
    hid_t id;           /**< HDF5 file ID. */
    char *name;         /**< HDF5 file name. */
    fapl_t fapl;        /**< HDF5 file access property list. */
    fcpl_t fcpl;        /**< HDF5 file creation property list. */
    phez_file_action_t action;         /**< Read/write settings. */

    phez_file_state_t state;       /**< PHEZ_FILE state; flags prevent function calls before all the
                                       necessary info is defined */
    bool state_name;    /**< Has the file name been defined? */
    bool state_action;  /**< Has the file action been defined? */

    // outward links:
    size_t num_linked_attributes; /**< Number of global attributes in the file. */
    size_t num_linked_datasets;   /**< Number of datasets in the file. */
    size_t num_linked_groups;     /**< Number of groups in the file. */
    phez_attribute_t ***linked_attributes;  /**< Pointer to array of pointers to
                                                         global attributes in the file.*/
    phez_dataset_t ***linked_datasets;      /**< Pointer to array of pointers to
                                                         global datasets in the file.*/
    phez_group_t ***linked_groups;          /**< Pointer to array of pointers to
                                                         all groups in the file.*/
};

#endif

