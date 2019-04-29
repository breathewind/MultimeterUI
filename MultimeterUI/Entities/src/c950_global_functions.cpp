/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 29/04/2019
 *      Description: Global functions.
 ******************************************************************************/
#include "Entities/inc/c950_global_functions.h"

/******************************************************************************
 *             Name: Global_Functions
 *      Function ID: 000
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Construction function.
 ******************************************************************************/
Global_Functions::Global_Functions()
{

}

/******************************************************************************
 *             Name: extractFile_path
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file path from file full path.
 ******************************************************************************/
QString Global_Functions::extractFile_path(QString file_full_path)
{
    return file_full_path.left(file_full_path.lastIndexOf(MULTIMETERUI_DIR_SYMBOL));
}

/***********************************************************************
 *             Name: extractFile_full_name
 *      Function ID: 003
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file full name from file full path.
 ***********************************************************************/
QString Global_Functions::extractFile_full_name(QString file_full_path)
{
    return file_full_path.right(file_full_path.size() - file_full_path.lastIndexOf(MULTIMETERUI_DIR_SYMBOL) - 1);
}

/***********************************************************************
 *             Name: extractFile_name
 *      Function ID: 004
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file name from file full path.
 ***********************************************************************/
QString Global_Functions::extractFile_name(QString file_full_path)
{
    QString file_full_name = extractFile_full_name(file_full_path);
    return file_full_name.left(file_full_name.lastIndexOf("."));
}

/***********************************************************************
 *             Name: extractFile_type
 *      Function ID: 005
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Extract file name from file full type.
 ***********************************************************************/
QString Global_Functions::extractFile_type(QString file_full_path)
{
    if(file_full_path.lastIndexOf(".")>=0){
        return file_full_path.right(file_full_path.size() - file_full_path.lastIndexOf(".") - 1);
    }else{
        return QString();
    }
}

/***********************************************************************
 *             Name: extractSecondString
 *      Function ID: 006
 *      Create date: 20/03/2019
 * Last modify date: 20/03/2019
 *      Description: Extract second part string in a QString separated
 *                   by a space.
 ***********************************************************************/
QString Global_Functions::extractSecondString(QString string)
{
    return string.right(string.size() - string.indexOf(" ") - 1);
}

/***********************************************************************
 *             Name: formatTime
 *      Function ID: 007
 *      Create date: 02/04/2019
 * Last modify date: 02/04/2019
 *      Description: Convert time in ms to the format hh:mm:ss.
 ***********************************************************************/
QString Global_Functions::formatTime(qint64 time_ms)
{
    int sec;
    int min;
    int hour;

    qint64 temp_time = time_ms/1000;

    sec = temp_time % 60;
    temp_time /= 60;

    min = temp_time % 60;
    temp_time /= 60;

    hour = static_cast<int>(temp_time);

    return QString("%1:%2:%3").arg(hour,2,10,QLatin1Char('0'))
                              .arg(min ,2,10,QLatin1Char('0'))
            .arg(sec ,2,10,QLatin1Char('0'));
}


/***********************************************************************
 *             Name: createNew_file
 *      Function ID: 008
 *      Create date: 29/04/2019
 * Last modify date: 29/04/2019
 *      Description: Create new file.
 ***********************************************************************/
int Global_Functions::createNew_file(QString file_path, QString target)
{
    QFile output_file(file_path);
    if(output_file.exists()){
        output_file.remove();
    }
    if(output_file.open(QFile::WriteOnly|QFile::Text)){
        QTextStream out_stream(&output_file);
        out_stream << "Time(s)," << target << MULTIMETERUI_DAFAULT_NEW_LINE;
        out_stream.flush();
        output_file.close();
    } else {
        return GF_FILE_OPERATION_FAIL_CREATE;
    }
    return GF_FILE_OPERATION_SUCCESS;
}

/***********************************************************************
 *             Name: createNew_file
 *      Function ID: 009
 *      Create date: 29/04/2019
 * Last modify date: 29/04/2019
 *      Description: Append one line to file.
 ***********************************************************************/
int Global_Functions::appendOne_line(QString file_path, QStringList content, QString separate_symbol)
{
    QFile output_file(file_path);

    if(output_file.open(QFile::WriteOnly|QFile::Text|QFile::Append)){
        QTextStream out_stream(&output_file);
        if(content.length()>0){
            out_stream << content.at(0);
            for (int i=1; i<content.length();i++) {
                out_stream << separate_symbol << content.at(i);
            }
        }
        out_stream << MULTIMETERUI_DAFAULT_NEW_LINE;
        out_stream.flush();
        output_file.close();
    } else {
        return GF_FILE_OPERATION_FAIL_APPEND;
    }
    return GF_FILE_OPERATION_SUCCESS;
}
