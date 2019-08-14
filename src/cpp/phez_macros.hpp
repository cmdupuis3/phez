#ifndef SET_PHEZ_MACROS_H_
#define SET_PHEZ_MACROS_H_

#include <iostream>
#include <hdf5.h>
#include "phez_errmacros.hpp"

#define PHEZ_MAX_NUM_FILES_ALLOWED 100
#define PHEZ_MAX_NUM_GROUPS_ALLOWED 512
#define PHEZ_MAX_NUM_DATASETS_ALLOWED 64
#define PHEZ_MAX_NUM_ATTRIBUTES_ALLOWED 128
#define PHEZ_MAX_NUM_SPACES_ALLOWED 512
#define PHEZ_MAX_NAME_LENGTH 256
#define PHEZ_MAX_COMMENT_LENGTH 256
#define PHEZ_MAX_HASH_LENGTH 128 /* Malloc hashes with one less; last char is for \0 */

#define PHEZ_DATASET_DATA_TYPE_BOOL     H5T_NATIVE_UCHAR
#define PHEZ_DATASET_DATA_TYPE_INT      H5T_NATIVE_INT
#define PHEZ_DATASET_DATA_TYPE_FLOAT    H5T_NATIVE_FLOAT
#define PHEZ_DATASET_DATA_TYPE_DOUBLE   H5T_NATIVE_DOUBLE
#define PHEZ_DATASET_DATA_TYPE_STRING   H5T_NATIVE_CHAR

#define PHEZ_ATTRIBUTE_DATA_TYPE_BOOL   H5T_NATIVE_UCHAR
#define PHEZ_ATTRIBUTE_DATA_TYPE_INT    H5T_NATIVE_INT
#define PHEZ_ATTRIBUTE_DATA_TYPE_FLOAT  H5T_NATIVE_FLOAT
#define PHEZ_ATTRIBUTE_DATA_TYPE_DOUBLE H5T_NATIVE_DOUBLE
#define PHEZ_ATTRIBUTE_DATA_TYPE_STRING H5T_C_S1

using std::cout;
using std::endl;

/* Wrappers for raw HDF5 functions; basically these are just buffers to trap for
   internal HDF5 errors. */

#define call_H5close() \
            [&]() -> herr_t { \
                herr_t retval = H5close(); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5close call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5open() \
            [&]() -> herr_t { \
                herr_t retval = H5open(); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5open call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Aclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Acreate(x1, x2, x3, x4, x5, x6) \
            [&]() -> hid_t { \
                hid_t retval = H5Acreate(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Acreate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aexists(x1, x2) \
            [&]() -> htri_t { \
                htri_t retval = H5Aexists(x1, x2); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aexists call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aget_create_plist(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Aget_create_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aget call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aget_space(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Aget_space(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aget_space call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aget_type(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Aget_type(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aget_type call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aiterate(x1, x2, x3, x4, x5, x6) \
            [&]() -> herr_t { \
                herr_t retval = H5Aiterate(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aiterate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aopen(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Aopen(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aopen call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Aread(x1, x2, x3) \
            [&]() -> herr_t { \
                herr_t retval = H5Aread(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Aread call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Awrite(x1, x2, x3) \
            [&]() -> herr_t { \
                herr_t retval = H5Awrite(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Awrite call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Dclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dcreate(x1, x2, x3, x4, x5, x6, x7) \
            [&]() -> hid_t { \
                hid_t retval = H5Dcreate(x1, x2, x3, x4, x5, x6, x7); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dcreate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dget_access_plist(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Dget_access_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dget_access_plist call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dget_create_plist(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Dget_create_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dget_create_plist call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dget_space(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Dget_space(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dget_space call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dget_type(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Dget_type(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dget_type call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dopen(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Dopen2(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dopen call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dread(x1, x2, x3, x4, x5, x6) \
            [&]() -> herr_t { \
                herr_t retval = H5Dread(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dread call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Dwrite(x1, x2, x3, x4, x5, x6) \
            [&]() -> herr_t { \
                herr_t retval = H5Dwrite(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Dwrite call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Fclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fcreate(x1, x2, x3, x4) \
            [&]() -> hid_t { \
                hid_t retval = H5Fcreate(x1, x2, x3, x4); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fcreate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fflush(x1, x2) \
            [&]() -> herr_t { \
                herr_t retval = H5Fflush(x1, x2); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fflush call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fis_hdf5(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Fis_hdf5(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fis_hdf5 call; does the file actually exist?." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fopen(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Fopen(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fopen call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fget_access_plist(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Fget_access_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fget_access_plist call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fget_create_plist(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Fget_create_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fget_create_plist call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Fget_file_image(x1, x2, x3) \
            [&]() -> ssize_t { \
                ssize_t retval = H5Fget_file_image(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Fget_file_image call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Gclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Gclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Gclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Gcreate(x1, x2, x3, x4, x5) \
            [&]() -> hid_t { \
                hid_t retval = H5Gcreate(x1, x2, x3, x4, x5); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Gcreate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Gflush(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Gflush(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Gflush call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

//#define call_H5Gget_access_plist

#define call_H5Gget_create_plist(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Gget_create_plist(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Gget_create_plist call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Gopen(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Gopen2(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Gopen call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Iget_type(x1) \
            [&]() -> H5I_type_t { \
                H5I_type_t retval = H5Iget_type(x1); \
                if(retval == H5I_BADID){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Iget_type call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Lexists(x1, x2, x3) \
            [&]() -> htri_t { \
                htri_t retval = H5Lexists(x1, x2, x3); \
                if(retval == H5I_BADID){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Lexists call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Ocopy(x1, x2, x3, x4, x5, x6) \
            [&]() -> herr_t { \
                herr_t retval = H5Ocopy(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Ocopy call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Oexists_by_name(x1, x2, x3) \
            [&]() -> htri_t { \
                htri_t retval = H5Oexists_by_name(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Oexists_by_name call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Oget_comment(x1, x2, x3) \
            [&]() -> ssize_t { \
                ssize_t retval = H5Oget_comment(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Oget_comment call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Ovisit(x1, x2, x3, x4, x5) \
            [&]() -> herr_t { \
                herr_t retval = H5Ovisit(x1, x2, x3, x4, x5); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Ovisit call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Pset_fapl_core(x1, x2, x3) \
            [&]() -> herr_t { \
                herr_t retval = H5Pset_fapl_core(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Pset_fapl_core call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Pset_fapl_direct(x1, x2, x3) \
            [&]() -> herr_t { \
                herr_t retval = H5Pset_fapl_direct(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Pset_fapl_direct call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Pclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Pclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Pclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Pcreate(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Pcreate(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Pcreate call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Pequal(x1, x2) \
            [&]() -> hid_t { \
                htri_t retval = H5Pequal(x1, x2); \
                if(retval == -1){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Pequal call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Sclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Screate_simple(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Screate_simple(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Screate_simple call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sget_simple_extent_dims(x1, x2, x3) \
            [&]() -> hid_t { \
                hid_t retval = H5Sget_simple_extent_dims(x1, x2, x3); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sget_simple_extent_dims call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sget_simple_extent_ndims(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Sget_simple_extent_ndims(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sget_simple_extent_ndims call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sget_simple_extent_type(x1) \
            [&]() -> hid_t { \
                hid_t retval = H5Sget_simple_extent_type(x1); \
                if(retval == H5S_NO_CLASS){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sget_simple_extent_type call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sselect_all(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Sselect_all(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sselect_all call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sselect_elements(x1, x2, x3, x4) \
            [&]() -> herr_t { \
                herr_t retval = H5Sselect_elements(x1, x2, x3, x4); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sselect_elements call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sselect_hyperslab(x1, x2, x3, x4, x5, x6) \
            [&]() -> herr_t { \
                herr_t retval = H5Sselect_hyperslab(x1, x2, x3, x4, x5, x6); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sselect_hyperslab call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Sselect_none(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Sselect_none(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Sselect_none call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Tclose(x1) \
            [&]() -> herr_t { \
                herr_t retval = H5Tclose(x1); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Tclose call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Tequal(x1, x2) \
            [&]() -> htri_t { \
            	htri_t retval = H5Tequal(x1, x2); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Tequal call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#define call_H5Tget_native_type(x1, x2) \
            [&]() -> hid_t { \
                hid_t retval = H5Tget_native_type(x1, x2); \
                if(retval < 0){ \
                    PHEZ_FATAL_PREFIX \
                    cout << "Internal error in H5Tget_native_type call." << endl; \
                    PHEZ_FATAL_SUFFIX \
                } \
                return(retval); \
            }()

#endif
