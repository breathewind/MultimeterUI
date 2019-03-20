/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 16/02/2019
 * Last modify date: 20/03/2019
 *      Description: Global parameters.
 ******************************************************************************/
#ifndef H000_GLOBAL_PARAMETERS_H
#define H000_GLOBAL_PARAMETERS_H

#define APP_NAME "MultimeterUI"
#define VERSION_ID "0.0.1"

#define MULTIMETERUI_DIR_SYMBOL "/"
#define MULTIMETERUI_DAFAULT_PROJECT_NAME   "Multimeter"
#define MULTIMETERUI_DAFAULT_PROJECT_SUFFIX ".proj"
#define MULTIMETERUI_DAFAULT_PROJECT_FILE_TYPE tr("Project File (*.proj)")
//#define MULTIMETERUI_DAFAULT_PROJECT_FILE_TYPE tr("Project File (*.proj);;All Files (*.*)")
#define MULTIMETERUI_DAFAULT_NEW_LINE "\n"

#define MULTIMETERUI_DEFAULT_OUTPUT_PAHT "output"
#define MULTIMETERUI_DEFAULT_OUTPUT_FILE_NAME "result.txt"
#define MULTIMETERUI_DEFAULT_OUTPUT_FILE_SUFFIX "txt"

#define MULTIMETERUI_DEBUG

#ifdef MULTIMETERUI_DEBUG

#include <QDebug>
#define DEBUG_SPLIT_LINE "------------------------------------------------------"

#define MAINCONTROLLER_DEBUG
#define MAINCONTORLLER_DEBUG_PREFIX "= "

#define MAINWINDOW_DEBUG

#define NEWPROJECT_DEBUG
#endif


#endif // H000_GLOBAL_PARAMETERS_H
