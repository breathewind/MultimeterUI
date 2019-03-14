/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Function for handle operations related to New Project.
 ******************************************************************************/
bool MainController::handleNew_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleNew_Project";
#endif

    QStringList available_ports = Serial_definitions::getSerial_port_name();
    if(available_ports.size() > 0){
        _dmm_port = available_ports.at(0);
    } else {
        _dmm_port = QString();
    }
    _dmm_baudrate    = DMM_BAUDRATE;
    _dmm_databits    = DMM_DATABITS;
    _dmm_stopbits    = DMM_STOPBITS;
    _dmm_parity      = DMM_PARITY;
    _dmm_flowcontrol = DMM_FLOWCONTROL;

    /** Create directory. */
    QDir dir(_project_path);
    if(dir.exists()){
        dir.removeRecursively();
    }
    QDir().mkdir(_project_path);
    QDir().mkdir(_project_output_path);
    /** Create project file. */
    QFile file(_project_file_full_path);
    if (!file.open(QFile::WriteOnly | QFile::Text )) {
        emit signal_warning_occurs(QString("Fail to create file: %1").arg(_project_file_full_path));
        return false;
    }
    QTextStream out_stream(&file);

    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT      << " 0" << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " 1" << MULTIMETERUI_DAFAULT_NEW_LINE;
//    out_stream << MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT  << " 0" << MULTIMETERUI_DAFAULT_NEW_LINE;

    file.flush();
    file.close();
    /** Show command panel when a new project is created. */
    _main_window->setCommand_panel_action_checked(true);
    _command_panel->showDialog();
    /** Reset all dialogs */
    _settings_dialog->resetAll_frames();

    return true;
}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Open Project.
 ******************************************************************************/
bool MainController::handleOpen_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleOpen_Project";
#endif

    return true;
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Save Project.
 ******************************************************************************/
void MainController::handleSave_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project";
#endif
}

/******************************************************************************
 *             Name: handleSave_Project_As
 *      Function ID: 234
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Save Project As.
 ******************************************************************************/
void MainController::handleSave_Project_As()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project_As";
#endif
}

/******************************************************************************
 *             Name: handle_CloseProject
 *      Function ID: 235
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handle_CloseProject";
#endif
}
