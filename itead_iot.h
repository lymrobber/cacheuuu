/**
 * @file itead_iot.h
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
#ifndef __ITEAD_IOT_H__
#define __ITEAD_IOT_H__
#ifdef __cplusplus

#include <Python.h>
#include <string.h>

class ITEADIoT
{
public:
    ITEADIoT();
   ~ITEADIoT();
    const char *init(const char *device_id, const char *check_code);
    const char *query(const char *params[]);
    const char *update(const char *params[], const char *values[]);

public:
    enum 
    {
        IOT_BUFFER_SIZE = 1024,
        APIKEY_LEN = 36,
    };
    
private:    
    static int refcount;
    static int imported;
    static PyObject *pymod_name;
    static PyObject *pymod;
    
private:
    char buffer[IOT_BUFFER_SIZE];
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __ITEAD_IOT_H__ */
