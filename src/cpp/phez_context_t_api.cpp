
#include "phez_context_t_api.hpp"

using namespace std;

/******************** PHEZ IO context class functions *************************/
/** \brief PHEZ IO context class constructor */
phez_context_t::phez_context_t(){

    call_H5open();

    hdf5 = new hdf5_class;

    PHEZ_NOTE_PREFIX
    cout << "phez_context was created" << endl;
}
/** \brief PHEZ IO context class destructor */
phez_context_t::~phez_context_t(){

    delete hdf5;

    call_H5close();

    PHEZ_NOTE_PREFIX
    cout << "phez_context was destroyed" << endl;
}


/******************** PHEZ IO context_tests class functions******************/
/** \brief PHEZ IO context_tests class constructor */
phez_test_context_t::phez_test_context_t(){

    call_H5open();

    hdf5_test = new hdf5_test_class;

    PHEZ_NOTE_PREFIX
    cout << "phez_test_context was created" << endl;
}
/** \brief PHEZ IO context_tests class destructor */
phez_test_context_t::~phez_test_context_t(){

    delete hdf5_test;

    call_H5close();

    PHEZ_NOTE_PREFIX
    cout << "phez_test_context was destroyed" << endl;
}
