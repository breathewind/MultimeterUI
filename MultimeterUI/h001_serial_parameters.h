/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Global parameters related to serial port.
 ******************************************************************************/
#ifndef H001_SERIAL_PARAMETERS_H
#define H001_SERIAL_PARAMETERS_H

#define DMM_BAUDRATE       "9600 baud"
#define DMM_PARITY         "No Parity"
#define DMM_DATABITS       "8 bits"
#define DMM_STOPBITS       "2 bit"
#define DMM_FLOWCONTROL    "No Flow Control"

#define SERIAL_INDEX_BAUDRATE    0
#define SERIAL_INDEX_DATABITS    1
#define SERIAL_INDEX_STOPBITS    2
#define SERIAL_INDEX_PARITY      3
#define SERIAL_INDEX_FLOWCONTROL 4
#define SERIAL_INDEX_PORT        5

#define MEASUREMENTUI_CURRENT_COMMAND ":MEAS:CURR:DC?"

#include "Entities/inc/c900_serial_definitions.h"

static Serial_definitions __serial_definitions;

#endif // H001_SERIAL_PARAMETERS_H
