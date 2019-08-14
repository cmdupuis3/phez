#ifndef SET_PHEZ_ERRMACROS_H_
#define SET_PHEZ_ERRMACROS_H_

#define PHEZ_FATAL_PREFIX \
            cout << "PHEZ error in " << __func__ << " (" <<__FILE__ << ", line " << __LINE__ << "); ";

#define PHEZ_WARNING_PREFIX \
            cout << "PHEZ warning in " << __func__ << " (" <<__FILE__ << ", line " << __LINE__ << "); ";

#define PHEZ_NOTE_PREFIX \
            cout << "PHEZ note in " << __func__ << " (" <<__FILE__ << ", line " << __LINE__ << "); ";

#define PHEZ_FATAL_SUFFIX \
            exit(-1);

#define PHEZ_WARNING_SUFFIX

/*
#define PHEZ_FATAL_SUFFIX \
            cout << " ";
*/
#endif
