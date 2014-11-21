/**
 * @file itead_iot.cpp
 *
 * Provide the implementation of ITEAD IoT API
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2014/11/10
 * @copyright 
 * Copyright (C) 2013-2014 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include <itead_iot.h>

int ITEADIoT::refcount = 0;
int ITEADIoT::imported = 0;
PyObject *ITEADIoT::pymod_name = NULL;
PyObject *ITEADIoT::pymod = NULL;

ITEADIoT::ITEADIoT(void)
{
    refcount++;
    if (imported == 0)
    {
        Py_Initialize();
        PySys_SetArgv(0,(char **)"");
        pymod_name = PyString_FromString("iteadiot");
        pymod = PyImport_Import(pymod_name);
        Py_XDECREF(pymod_name);
        imported = 1;
        //printf("Module initialize\n");
    }

    memset((void *)buffer, '\0', sizeof(buffer));
}

ITEADIoT::~ITEADIoT(void)
{
    refcount--;
    if(refcount == 0)
    {
        Py_XDECREF(pymod);
        Py_Finalize();
        imported = 0;
        //printf("Module finalize\n");
    }
}

const char *ITEADIoT::init(const char *device_id, const char *check_code)
{
    PyObject *pyfun;
    PyObject *pyargs;
    PyObject *pyret;

    const char *ret;
        
    if (ITEADIoT::pymod != NULL) 
    {
        pyfun = PyObject_GetAttrString(pymod, "init");
        if (pyfun && PyCallable_Check(pyfun))
        {
            pyargs = Py_BuildValue("(ss)", device_id, check_code);
            pyret = PyObject_CallObject(pyfun, pyargs);
            Py_XDECREF(pyargs);

            ret = PyString_AsString(pyret);
            ret = strstr(ret, "apikey");
            if (ret != NULL)
            {
                ret += 9;/* {"error":0,"apikey":"0783eab8-0641-421f-83fd-31c19f844b69"} */
                strncpy(this->buffer, ret, APIKEY_LEN);
            }
            Py_XDECREF(pyret);
            
        }  
        Py_XDECREF(pyfun);
    }
    
    return (const char *)this->buffer;
}

const char *ITEADIoT::query(const char *params[])
{
    PyObject *pyfun;
    PyObject *pyargs;
    PyObject *pyret;
    PyObject *pyitem;
    PyObject *pylist;
    
    const char *ret;

    int params_cnt = 0;
    int i=0;

    if (pymod != NULL) 
    {
        pyfun = PyObject_GetAttrString(pymod, "query");
        if (pyfun && PyCallable_Check(pyfun))
        {
            for (i=0; params[i] != NULL; i++)
            {
                //printf("params[%d]=%s\n", i, params[i]);
            }
            params_cnt = i;
            pylist = PyList_New(params_cnt);
            for (i=0; i<params_cnt; i++) 
            {
                pyitem = PyString_FromString(params[i]);
                PyList_SetItem(pylist, i, pyitem);
            }
            
            pyargs = Py_BuildValue("(O)", pylist);
            pyret = PyObject_CallObject(pyfun, pyargs);
            Py_XDECREF(pyargs);
            Py_XDECREF(pylist);
            
            ret = PyString_AsString(pyret);
            //printf("ret = %s\n", ret);
            
            strcpy(this->buffer, ret);
            Py_XDECREF(pyret);
            
        }  
        Py_XDECREF(pyfun);
    }
    
    return (const char *)(this->buffer);
}

const char *ITEADIoT::update(const char *params[], const char *values[])
{
    PyObject *pyfun;
    PyObject *pyargs;
    PyObject *pyret;
    PyObject *pyitem;
    PyObject *pydict;
    
    const char *ret;

    int params_cnt = 0;
    int i=0;

    if (pymod != NULL) 
    {
        pyfun = PyObject_GetAttrString(pymod, "update");
        if (pyfun && PyCallable_Check(pyfun))
        {
            for (i=0; params[i] != NULL; i++)
            {
                //printf("params[%d]=%s\n", i, params[i]);
            }
            params_cnt = i;
            pydict = PyDict_New();
            for (i=0; i<params_cnt; i++) 
            {
                pyitem = PyString_FromString(values[i]);
                PyDict_SetItemString(pydict, params[i], pyitem);
            }
            
            pyargs = Py_BuildValue("(O)", pydict);
            pyret = PyObject_CallObject(pyfun, pyargs);
            Py_XDECREF(pyargs);
            Py_XDECREF(pydict);
            
            ret = PyString_AsString(pyret);
            //printf("ret = %s\n", ret);
            
            strcpy(this->buffer, ret);
            Py_XDECREF(pyret);
            
        }  
        Py_XDECREF(pyfun);
    }
    
    return (const char *)(this->buffer);
}

