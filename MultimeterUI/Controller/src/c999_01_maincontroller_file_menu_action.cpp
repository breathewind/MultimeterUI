/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleNew_Project
 *      Function ID: 231
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
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

    out_stream << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_dmm_baudrate)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_dmm_databits)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_dmm_stopbits)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      << " " << __serial_definitions.getParity(_dmm_parity)        << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_dmm_flowcontrol) << MULTIMETERUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_MEASUREMENT_TARGET_TEXT <<  " " << COMMAND_PANEL_TARGET_CURRENT          << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MEASUREMENT_TYPE_TEXT   <<  " " << COMMAND_PANEL_TYPE_SINGLE_DATA        << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAMPLING_PERIOD_TEXT    <<  " " << COMMAND_PANEL_DEFAULT_SAMPLING_PERIOD << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_FLAG_TEXT          <<  " " << COMMAND_PANEL_SAVE_FILE_CHECKED       << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_PATH_TEXT     <<  " " << _project_output_path + MULTIMETERUI_DIR_SYMBOL + _output_file_name << MULTIMETERUI_DAFAULT_NEW_LINE;

    file.flush();
    file.close();
    /** Show command panel when a new project is created. */
    _main_window->setCommand_panel_action_checked(true);
    _command_panel->setDefault(_project_output_path + MULTIMETERUI_DIR_SYMBOL + _output_file_name);
    _command_panel->showDialog();
    /** Hide settings dialog when a new project is created. */
    _main_window->setSettings_action_checked(false);
    _settings_dialog->hide();
    /** Reset all dialogs */
    _settings_dialog->resetAll_frames();

    return true;
}

/******************************************************************************
 *             Name: handleOpen_Project
 *      Function ID: 232
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Function for handle operations related to Open Project.
 ******************************************************************************/
bool MainController::handleOpen_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleOpen_Project";
#endif
    QFile file(_project_file_full_path);
    if (!file.open(QFile::ReadOnly | QFile::Text )) {
        emit signal_warning_occurs(QString("Fail to create file: %1").arg(_project_file_full_path));
        return false;
    }
    QTextStream in_stream(&file);
    while(!in_stream.atEnd()) {
        QString line = in_stream.readLine();
        QStringList fields = line.split(" ");
/************************* GENERAL SETTINGS *************************/
        if(fields.at(0) == MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT) {
            /************************* SETTINGS_DISPLAY *************************/
            printData_read_from_project_file(MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT, fields.at(1));
            if(fields.at(1).toInt()){
                _main_window->setSettings_action_checked(true);
                _settings_dialog->showDialog();
            } else {
                _main_window->setSettings_action_checked(false);
                _settings_dialog->hide();
            }
        } else if (fields.at(0) == MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT) {
            /************************* COMMAND_PANEL_DISPLAY *************************/
            printData_read_from_project_file(MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT, fields.at(1));
            if(fields.at(1).toInt()){
                _main_window->setCommand_panel_action_checked(true);
                _command_panel->showDialog();
            } else {
                _main_window->setCommand_panel_action_checked(false);
                _command_panel->hide();
            }
        } else
/************************* DMM *************************/
            if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT) {
            /************************* DMM_BAUDRATE *************************/
            _dmm_baudrate = __serial_definitions.getBaudrate_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT, _dmm_baudrate);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT) {
            /************************* DMM_DATABITS *************************/
            _dmm_databits = __serial_definitions.getDataBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT, _dmm_databits);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT) {
            /************************* DMM_STOPBITS *************************/
            _dmm_stopbits = __serial_definitions.getStopBits_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT, _dmm_stopbits);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT) {
            /************************* DMM_PARITY *************************/
            _dmm_parity = __serial_definitions.getParity_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT, _dmm_parity);
        } else if (fields.at(0) == MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT) {
            /************************* DMM_FLOWCONTROL *************************/
            _dmm_flowcontrol = __serial_definitions.getFlowcontrol_string(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT, _dmm_flowcontrol);
        } else
/************************* MEASUREMENT SETTINGS *************************/
            if (fields.at(0) == MAINCONTTROLLER_MEASUREMENT_TARGET_TEXT) {
            /************************* MEASUREMENT_TARGET *************************/
            _command_panel->setMeasurementTarget(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_MEASUREMENT_TARGET_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_MEASUREMENT_TYPE_TEXT) {
            /************************* MEASUREMENT_TYPE *************************/
            _command_panel->setMeasurementType(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_MEASUREMENT_TYPE_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SAMPLING_PERIOD_TEXT) {
            /************************* SAMPLING_PERIOD *************************/
            _command_panel->setSamplingPeriod(fields.at(1).toDouble());
            printData_read_from_project_file(MAINCONTTROLLER_SAMPLING_PERIOD_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SAVE_FLAG_TEXT) {
            /************************* SAVE_FLAG *************************/
            _command_panel->setSaveFlag(fields.at(1).toInt());
            printData_read_from_project_file(MAINCONTTROLLER_SAVE_FLAG_TEXT, fields.at(1));
        } else if (fields.at(0) == MAINCONTTROLLER_SAVE_PATH_TEXT) {
            /************************* SAVE_PATH *************************/
            _command_panel->setSavePath(fields.at(1));
            _output_file_name = Global_Functions::extractFile_full_name(fields.at(1));
            _project_output_path = Global_Functions::extractFile_path(fields.at(1));
            printData_read_from_project_file(MAINCONTTROLLER_SAVE_PATH_TEXT, fields.at(1));
            printData_read_from_project_file("_output_file_name", _output_file_name);
            printData_read_from_project_file("_project_output_path", _project_output_path);
        } else {
            file.close();
            emit signal_warning_occurs(QString("Unknow parameter: %1").arg(fields.at(0)));
            return false;
        }
    }
    file.close();

    UpdateSettings();
    QStringList available_ports = Serial_definitions::getSerial_port_name();
    _dmm_port = available_ports.size() > 0? available_ports.at(0):QString();

    return true;
}

/******************************************************************************
 *             Name: handleSave_Project
 *      Function ID: 233
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Function for handle operations related to Save Project.
 ******************************************************************************/
void MainController::handleSave_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project";
#endif
    /** Save project file. */
    QFile file(_project_file_full_path);
    if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
        emit signal_warning_occurs(QString("Fail to open file: %1").arg(_project_file_full_path));
        return;
    }

    QStringList measurement_settings = _command_panel->getMeasurementSettings();

    QTextStream out_stream(&file);
    out_stream << MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT << " " << _main_window->getSettings_action_checked() << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT << " " << _main_window->getCommand_panel_action_checked() << MULTIMETERUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    << " " << __serial_definitions.getBaudrate(_dmm_baudrate)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    << " " << __serial_definitions.getDataBits(_dmm_databits)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    << " " << __serial_definitions.getStopBits(_dmm_stopbits)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      << " " << __serial_definitions.getParity(_dmm_parity)        << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << " " << __serial_definitions.getFlowcontrol(_dmm_flowcontrol) << MULTIMETERUI_DAFAULT_NEW_LINE;

    out_stream << MAINCONTTROLLER_MEASUREMENT_TARGET_TEXT <<  " " << measurement_settings.at(COMMAND_PANEL_TARGET_INDEX)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_MEASUREMENT_TYPE_TEXT   <<  " " << measurement_settings.at(COMMAND_PANEL_TYPE_INDEX)      << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAMPLING_PERIOD_TEXT    <<  " " << measurement_settings.at(COMMAND_PANEL_PERIOD_INDEX)    << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_FLAG_TEXT          <<  " " << measurement_settings.at(COMMAND_PANEL_SAVE_FLAG_INDEX) << MULTIMETERUI_DAFAULT_NEW_LINE;
    out_stream << MAINCONTTROLLER_SAVE_PATH_TEXT     <<  " " << measurement_settings.at(COMMAND_PANEL_SAVE_PATH_INDEX) << MULTIMETERUI_DAFAULT_NEW_LINE;

    file.flush();
    file.close();
}

/******************************************************************************
 *             Name: handleSave_Project_As
 *      Function ID: 234
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Function for handle operations related to Save Project As.
 ******************************************************************************/
void MainController::handleSave_Project_As()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleSave_Project_As";
#endif
    handleSave_Project();
}

/******************************************************************************
 *             Name: handle_CloseProject
 *      Function ID: 235
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Function for handle operations related to Close Project.
 ******************************************************************************/
void MainController::handleClose_Project()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handle_CloseProject";
#endif
}
