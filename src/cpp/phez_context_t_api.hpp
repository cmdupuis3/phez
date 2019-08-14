
#ifndef SET_PHEZ_CONTEXT_T_API_H_
#define SET_PHEZ_CONTEXT_T_API_H_

#include <cstdlib>
#include "phez_hdf5_t_api.hpp"
#include "phez_macros.hpp"
#include "phez_tests.hpp"


/** \mainpage PHEZ I/O
 *
 *  \class phez_context_t phez_context_t_api.h
 *  \brief The context is the base class for PHEZ I/O.
 *  \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 *
 *  \detail The context is the base class for PHEZ I/O. HDF5 is currently implemented,
 *          but other I/O packages formatted as a class can also be strapped into the
 *          I/O context.
 */
class phez_context_t {

    public:
        // constructor
        phez_context_t();
        // destructor
        ~phez_context_t();

        hdf5_class* hdf5;

    private:
};

/** \class phez_test_context_t phez_context_t_api.h
 *  \brief The context is a version of the base clase for PHEZ I/O that includes unit tests
 *  \author Christopher Dupuis<Christopher.Dupuis@noaa.gov>
 */
class phez_test_context_t {

    public:
        // constructor
        phez_test_context_t();
        // destructor
        ~phez_test_context_t();

        hdf5_test_class* hdf5_test;

    private:
};

#endif
