/**
 * @example iotgo.ino
 * 
 * @par Show how to use API of class IoTgo
 *
 * We assume an virtual device (type of DIY) named iotgo has 
 * one parameter(or many as you wish) "state" which's value can be one
 * of "on" and "off". 
 *
 * The sequence of using iogto:
 *      -# create it. 
 *      -# connect to internet for later communication. 
 *      -# initialize the device(atctually, connect to sever). 
 *      -# now, it can be update or query the parameter. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2014/11/14
 * @copyright 
 * Copyright (C) 2013-2014 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
 
/* Include all device classes supported by IoTgo Library */
#include <IoTgo_device.h>

/* An unique identifier of user registed on IoTgo platform */
#define IOTGO_APIKEY        "9bed6c2c-fbc6-4400-9ef8-087f9f0d996e"

/* 
 * An identifier of device which has been created and belongs to
 * a user registed to IoTgo platform. The first two letters indicates
 * the categories: 
 *  00 : Customized device which can has as many as you want
 *       parameters and the corresponding values.
 *  01 : Switch which has at least one parameter: 
 *       "switch" with value "on" or "off". 
 *  02 : Light which has at least one parameter:
 *       "light" with value "on" or "off". 
 *  03 : THSensor which has at least two parameters: 
 *       "temperature" with value "xx.xx" in Celsius, 
 *       "humidity" with value "xx.xx" in persentage. 
 */
#define IOTGO_DEVICEID      "0000000001" /* Customized device category*/

/*
 * If you have a finished product, a check code or apikey-like code or 
 * factory apikey will be found around it. We are naming the code 
 * "IOTGO_CHECK_CODE". Here is empty. 
 */
#define IOTGO_CHECK_CODE    ""

/* 
 * The SSID (more generally, WiFi's name) for accessing to internet.
 * Maybe you need to replace "ITEAD" with yours. 
 */
#define WIFI_SSID           "ITEAD"

/* 
 * The SSID's password
 * Is it the same to yours? if not, change it.
 */
#define WIFI_PASS           "12345678"

/*
 * IP address or domain name of IoTgo platform servers. 
 * Maybe you need to change it.
 */
#define IOT_SERVER          "172.16.7.6"


IoTgo iotgo;

void printBody(const char *buffer)
{
    if (buffer != NULL)
    {
        buffer = strstr(buffer, "{");
        if (buffer == NULL)
        {
            Serial.println("no \"{\" found!");
            return;
        }
        Serial.print("[");
        Serial.print(buffer);
        Serial.println("]");
    }
}

void setup()
{
    const char *apikey;

    iotgo.setServer(IOT_SERVER);
    if (!iotgo.connectWiFi(WIFI_SSID, WIFI_PASS))
    {
        Serial.println("connectWiFI error and halt...");
        while(1);
    }

    Serial.println("Connecting device to server...");
    apikey = iotgo.init(IOTGO_DEVICEID, IOTGO_APIKEY);
    //apikey = iotgo.init(IOTGO_DEVICEID, IOTGO_CHECK_CODE, DEVICE_PRODUCT);
    Serial.print("apikey = ");
    Serial.println(apikey);    
    
    Serial.println("setup done.");
}


void loop()
{
    static int32_t counter = 0;
    Serial.print("\ncounter = ");
    Serial.println(++counter);
    
    const char *iotgo_state[] = 
    {
        "state",
        NULL
    };
    const char *iotgo_on[] = 
    {
        "on",
        NULL
    };
    const char *iotgo_off[] = 
    {
        "off",
        NULL
    };
    
    const char *ret;

    Serial.println("update to on");
    ret = iotgo.update(iotgo_state, iotgo_on);
    Serial.print("iotgo.update =  ");
    printBody(ret);

    ret = iotgo.query(iotgo_state);
    Serial.print("iotgo.query =   ");
    printBody(ret);

    Serial.println("update to off");
    ret = iotgo.update(iotgo_state, iotgo_off);
    Serial.print("iotgo.update =  ");
    printBody(ret);

    ret = iotgo.query(NULL);
    Serial.print("iotgo.query =   ");
    printBody(ret);

    delay(1000);
}
