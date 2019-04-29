/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 29/04/2019
 *      Description: Global functions.
 ******************************************************************************/
#ifndef C950_GLOBAL_FUNCTIONS_H
#define C950_GLOBAL_FUNCTIONS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>

#include "h000_global_parameters.h"

#define GF_FILE_OPERATION_SUCCESS     0
#define GF_FILE_OPERATION_FAIL_CREATE 1
#define GF_FILE_OPERATION_FAIL_APPEND 2

#define GF_FILE_SEPARATE_SYMBOL ","

class Global_Functions : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    Global_Functions();


    /** Function 002: Extract file path from file full path. */
    static QString extractFile_path(QString file_full_path);
    /** Function 003: Extract file full name from file full path. */
    static QString extractFile_full_name(QString file_full_path);
    /** Function 004: Extract file name from file full path. */
    static QString extractFile_name(QString file_full_path);
    /** Function 005: Extract file type from file full path. */
    static QString extractFile_type(QString file_full_path);
    /** Function 006: Extract second part string in a QString separated by a space. */
    static QString extractSecondString(QString string);
    /** Function 007: Convert time in ms to the format hh:mm:ss. */
    static QString formatTime(qint64 time_ms);


    /** Function 008: Create new file. */
    static int createNew_file(QString file_path, QString target);
    /** Function 009: Append one line to file. */
    static int appendOne_line(QString file_path, QStringList content, QString separate_symbol = GF_FILE_SEPARATE_SYMBOL);
};

#endif // C950_GLOBAL_FUNCTIONS_H
