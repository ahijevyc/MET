

////////////////////////////////////////////////////////////////////////


#ifndef  __MET_PYTHON_TUPLE_H__
#define  __MET_PYTHON_TUPLE_H__


////////////////////////////////////////////////////////////////////////


extern "C" {

#include "Python.h"

}


////////////////////////////////////////////////////////////////////////


static const int max_tuple_data_dims = 10;


////////////////////////////////////////////////////////////////////////


extern void get_tuple_int_values(PyObject * tuple, int & dim, int * values);


////////////////////////////////////////////////////////////////////////


#endif   /*  __MET_PYTHON_TUPLE_H__  */


////////////////////////////////////////////////////////////////////////



