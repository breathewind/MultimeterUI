/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/02/2019
 * Last modify date: 30/04/2019
 *      Description: Main window controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: MainController
 *      Function ID: 000
 *      Create date: 14/02/2019
 * Last modify date: 12/04/2019
 *      Description: Construction function.
 ******************************************************************************/
MainController::MainController()
{
    initMainwindow();
    initProject_operaiton();
    initRun_operaiton();
    initFunction_operaiton();
    initSerial_operaiton();
    initTimer();
    initChart();

    synchronizeCurrent_path(QDir::homePath());
}

/******************************************************************************
 *             Name: MainController
 *      Function ID: 002
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Clear all project information.
 ******************************************************************************/
void MainController::clearProject_information()
{
    _project_name.clear();
    _project_file.clear();
    _project_path.clear();
    _project_file_full_path.clear();
    _project_output_path.clear();
}

/******************************************************************************
 *             Name: signal_synchronizeCurrent_Path
 *      Function ID: 003
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Synchronize project path.
 ******************************************************************************/
void MainController::synchronizeCurrent_path(QString current_path)
{
    _current_path = current_path;
    emit signal_synchronizeCurrent_Path(current_path);
}

/******************************************************************************
 *             Name: updateProject_information
 *      Function ID: 004
 *      Create date: 18/02/2019
 * Last modify date: 18/03/2019
 *      Description: Update project information according to project name and
 *                   project path.
 ******************************************************************************/
int MainController::updateProject_information(QString project_name, QString project_path, QString output_file)
{
    QString previous_project_name = _project_name;
    QString previous_project_path = _project_path;

    _project_name = project_name;
    _project_path = project_path + MULTIMETERUI_DIR_SYMBOL + _project_name;
    /** Create directory. */
    QDir dir(_project_path);
    if(dir.exists()){
        int ret = QMessageBox::warning(_main_window, tr("Directory already exists."),
                                       QString("%1 already exists, do you want to rewrite it?\n"
                                               "If you are not sure, please contact System Administrator").arg(_project_path),
                                       QMessageBox::Yes | QMessageBox::Cancel,
                                       QMessageBox::Yes);

        switch(ret){
        case QMessageBox::Yes:
            // Yes was clicked
            dir.removeRecursively();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            _project_name = previous_project_name;
            _project_path = previous_project_path;
            return MAINCONTROLLER_DIR_CREATE_FAIL;
        default:
            // should never be reached
            break;
        }
    }

    _project_file = _project_name + MULTIMETERUI_DAFAULT_PROJECT_SUFFIX;
    _project_file_full_path = _project_path + MULTIMETERUI_DIR_SYMBOL +
                              _project_name + MULTIMETERUI_DAFAULT_PROJECT_SUFFIX;
    _project_output_path = _project_path + MULTIMETERUI_DIR_SYMBOL + MULTIMETERUI_DEFAULT_OUTPUT_PAHT;
    synchronizeCurrent_path(project_path);

    _output_file_name = output_file;

    QDir().mkdir(_project_path);
    QDir().mkdir(_project_output_path);

    return MAINCONTROLLER_DIR_CREATE_SUCCEED;
}

/******************************************************************************
 *             Name: updateProject_information
 *      Function ID: 005
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Update project information according to project file full
 *                   path.
 ******************************************************************************/
void MainController::updateProject_information(QString project_file_full_path)
{
    clearProject_information();
    _project_name = Global_Functions::extractFile_name(project_file_full_path);
    _project_file = Global_Functions::extractFile_full_name(project_file_full_path);
    _project_path = Global_Functions::extractFile_path(project_file_full_path);
    _project_file_full_path = project_file_full_path;
    synchronizeCurrent_path(_project_path);
}

/******************************************************************************
 *             Name: initMain_Window
 *      Function ID: 200
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Main Window..
 ******************************************************************************/
void MainController::initMainwindow()
{
    _main_window = new MainWindow();
    connect(this, &MainController::signal_synchronizeCurrent_Path, _main_window, &MainWindow::slot_update_current_path);
    connect(this, &MainController::signal_warning_occurs, _main_window, &MainWindow::slot_display_warning_message_box);
}

/******************************************************************************
 *             Name: initProject_operaiton
 *      Function ID: 201
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Project operations.
 ******************************************************************************/
void MainController::initProject_operaiton()
{
    initNew_Project();
    initOpen_Project();
    initSave_Project();
    initSave_Project_As();
    initClose_Project();
}

/******************************************************************************
 *             Name: initRun_operaiton
 *      Function ID: 202
 *      Create date: 18/02/2019
 * Last modify date: 19/02/2019
 *      Description: Initilize functions related to Run operations.
 ******************************************************************************/
void MainController::initRun_operaiton()
{
    initStart();
    initStop();
}

/******************************************************************************
 *             Name: initFunction_operaiton
 *      Function ID: 203
 *      Create date: 19/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Function operations.
 ******************************************************************************/
void MainController::initFunction_operaiton()
{
    initSettings();
    initCommand_Panel();
    initQuit();;
}

/******************************************************************************
 *             Name: initSerial_operaiton
 *      Function ID: 204
 *      Create date: 01/04/2019
 * Last modify date: 01/04/2019
 *      Description: Initilize functions related to Serial operations.
 ******************************************************************************/
void MainController::initSerial_operaiton()
{
    /** DMM serial settings */
    _DMM_controller = new Serial_Controller();
    connect(_DMM_controller, &Serial_Controller::data_received, this, &MainController::slot_retrieveDMM_data);
}

/******************************************************************************
 *             Name: initTimer
 *      Function ID: 205
 *      Create date: 02/04/2019
 * Last modify date: 29/04/2019
 *      Description: Initilize functions related to timers
 ******************************************************************************/
void MainController::initTimer()
{
    _run_timer = new QTimer();
    connect(_run_timer, &QTimer::timeout, this, &MainController::slot_updateRun_timer);
    _sampling_timer = new QTimer();
    connect(_sampling_timer, &QTimer::timeout, this, &MainController::slot_updateSampling_timer);
}

/******************************************************************************
 *             Name: initChart
 *      Function ID: 206
 *      Create date: 08/04/2019
 * Last modify date: 12/04/2019
 *      Description: Initilize functions related to charts.
 ******************************************************************************/
void MainController::initChart()
{
    _chart_controller = new Chart_Controller(tr(""), CHART_CONTROLLER_DEFAULT_TIME_RANGE, tr("A"));
    _main_window->addChart_view(_chart_controller->getChart_view());

}

/******************************************************************************
 *             Name: initNew_Project
 *      Function ID: 211
 *      Create date: 16/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to New Project operations.
 ******************************************************************************/
void MainController::initNew_Project()
{
    _new_project_dialog = new New_Project_Dialog(_main_window);
    /** Connect signals and slots related to click New Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_new_project_menu_action_triggered, _new_project_dialog, &New_Project_Dialog::slot_trigger_new_project_dialog);
    connect(_new_project_dialog, &New_Project_Dialog::signal_new_project_comfirmed, this, &MainController::slot_create_new_project);
    connect(this, &MainController::signal_synchronizeCurrent_Path, _new_project_dialog, &New_Project_Dialog::slot_update_current_path);
}

/******************************************************************************
 *             Name: initOpen_Project
 *      Function ID: 212
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Open Project operations.
 ******************************************************************************/
void MainController::initOpen_Project()
{
    /** Connect signals and slots related to click Open menu action button in main window. */
    connect(_main_window, &MainWindow::signal_open_project_menu_action_triggered, this, &MainController::slot_open_project);
}

/******************************************************************************
 *             Name: initSave_Project
 *      Function ID: 213
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Save Project operations.
 ******************************************************************************/
void MainController::initSave_Project()
{
    /** Connect signals and slots related to click Save Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_save_project_menu_action_triggered, this, &MainController::slot_save_project);
}

/******************************************************************************
 *             Name: initSave_Project_As
 *      Function ID: 214
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Save Project As operations.
 ******************************************************************************/
void MainController::initSave_Project_As()
{
    /** Connect signals and slots related to click Close Project menu action button in main window. */
    connect(_main_window, &MainWindow::signal_save_project_as_menu_action_triggered, this, &MainController::slot_save_project_as);
}

/******************************************************************************
 *             Name: initClose_Project
 *      Function ID: 215
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Initilize functions related to Close project operations.
 ******************************************************************************/
void MainController::initClose_Project()
{
    connect(_main_window, &MainWindow::signal_close_project_menu_action_triggered, this, &MainController::slot_close_project);
}

/******************************************************************************
 *             Name: initStart
 *      Function ID: 216
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Start operations.
 ******************************************************************************/
void MainController::initStart()
{
    /** Connect signals and slots related to click Start menu action button in main window. */
    connect(_main_window, &MainWindow::signal_start_menu_action_triggered, this, &MainController::slot_Start);
}

/******************************************************************************
 *             Name: initStop
 *      Function ID: 217
 *      Create date: 18/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Stop operations.
 ******************************************************************************/
void MainController::initStop()
{
    /** Connect signals and slots related to click Stop menu action button in main window. */
    connect(_main_window, &MainWindow::signal_stop_menu_action_triggered, this, &MainController::slot_Stop);
}

/******************************************************************************
 *             Name: initSettings
 *      Function ID: 218
 *      Create date: 19/02/2019
 * Last modify date: 30/04/2019
 *      Description: Initilize functions related to Settings operations.
 ******************************************************************************/
void MainController::initSettings()
{
    _settings_dialog = new Settings_Dialog(_main_window);
    /** Connect signals and slots related to click Settings menu action button in main window. */
    connect(_main_window, &MainWindow::signal_settings_menu_action_triggered, this, &MainController::slot_settings);
    /** Connect signals and slots related to close Settings dialog. */
    connect(_settings_dialog, &Settings_Dialog::accepted, _main_window, &MainWindow::slot_close_settings_dialog);
    connect(_settings_dialog, &Settings_Dialog::rejected, _main_window, &MainWindow::slot_close_settings_dialog);
    /** Connect signals and slots related to click Apply button in Settings Dialog. */
    connect(_settings_dialog, &Settings_Dialog::signal_accept_button_clicked, this, &MainController::slot_update_data_from_settings);
    connect(_settings_dialog, &Settings_Dialog::accepted, this, &MainController::slot_update_data_from_settings);
    /** Connect signals and slots related to click Test Connection button in Settings Dialog. */
    connect(_settings_dialog, &Settings_Dialog::signal_test_connection_button_clicked, this, &MainController::slot_startIDN_test);
}

/******************************************************************************
 *             Name: initCommand_Panel
 *      Function ID: 219
 *      Create date: 19/02/2019
 * Last modify date: 20/02/2019
 *      Description: Initilize functions related to Command Panel operations.
 ******************************************************************************/
void MainController::initCommand_Panel()
{
    _command_panel = new Command_Panel(_main_window);
    /** Connect signals and slots related to click Command panel menu action button in main window. */
    connect(_main_window, &MainWindow::signal_command_panel_menu_action_triggered, this, &MainController::slot_command_panel);
    /** Connect signals and slots related to close Command panel. */
    connect(_command_panel, &Command_Panel::rejected, _main_window, &MainWindow::slot_close_command_panel);
}

/******************************************************************************
 *             Name: initQuit
 *      Function ID: 222
 *      Create date: 19/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initilize functions related to Quit operations.
 ******************************************************************************/
void MainController::initQuit()
{
    /** Connect signals and slots related to click Quit menu action button in main window. */
    connect(_main_window, &MainWindow::signal_quit_menu_action_triggered, this, &MainController::slot_Quit);
    connect(this, &MainController::signal_confirm_quit_application, _main_window, &MainWindow::slot_confirm_quit_application);
}

/******************************************************************************
 *             Name: showMain_Window
 *      Function ID: 300
 *      Create date: 16/02/2019
 * Last modify date: 16/02/2019
 *      Description: Show main window.
 ******************************************************************************/
void MainController::showMainwindow()
{
    _main_window->show();
}

/******************************************************************************
 *             Name: printData_read_from_project_file
 *      Function ID: 600
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Print data read from project file.
 ******************************************************************************/
void MainController::printData_read_from_project_file(QString domain, QString content)
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << domain << " " << content;
#endif
}

/******************************************************************************
 *             Name: slot_create_new_project
 *      Function ID: 700
 *      Create date: 16/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for new project created.
 ******************************************************************************/
void MainController::slot_create_new_project(QString project_name, QString project_path)
{
    if(!updateProject_information(project_name, project_path, MULTIMETERUI_DEFAULT_OUTPUT_FILE_NAME)){
        if(handleNew_Project()){
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
            _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);
        }
    }

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: New Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_open_project
 *      Function ID: 701
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Slot for open a project.
 ******************************************************************************/
void MainController::slot_open_project(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        updateProject_information(project_file_full_path);

        if(handleOpen_Project()){
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
            _main_window->changeDisplay_status(MAINWINDOW_PROJECT_ACTIVATE);
        }
    }

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Open Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_save_project
 *      Function ID: 702
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for saving current project.
 ******************************************************************************/
void MainController::slot_save_project()
{
    handleSave_Project();

#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Save Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_save_project_as
 *      Function ID: 703
 *      Create date: 18/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for saving project as another project.
 ******************************************************************************/
void MainController::slot_save_project_as(QString project_file_full_path)
{
    if(project_file_full_path.length() > 0){
        if(!updateProject_information(Global_Functions::extractFile_name(project_file_full_path),
                                      Global_Functions::extractFile_path(project_file_full_path),
                                      MULTIMETERUI_DEFAULT_OUTPUT_FILE_NAME)){
            handleSave_Project_As();
            _main_window->setWindowTitle(QString("%1 - %2").arg(APP_NAME).arg(_project_name));
        }
    }
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: Save Project as";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_close_project
 *      Function ID: 704
 *      Create date: 18/02/2019
 * Last modify date: 15/03/2019
 *      Description: Slot for current project closed.
 ******************************************************************************/
void MainController::slot_close_project()
{
    clearProject_information();

    handleClose_Project();

    _main_window->resetAll_menu_actions();
    _command_panel->hide();
    _settings_dialog->hide();
    _main_window->setWindowTitle(QString(APP_NAME));

#ifdef MAINCONTROLLER_DEBUG
    clearProject_information();
    qDebug() << "+ MainController: Close Project";
    printProject_information();
#endif
}

/******************************************************************************
 *             Name: slot_Start
 *      Function ID: 705
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for starting new measrement.
 ******************************************************************************/
void MainController::slot_Start()
{
    handleStart();
}

/******************************************************************************
 *             Name: slot_Stop
 *      Function ID: 706
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Slot for stoping current measurement.
 ******************************************************************************/
void MainController::slot_Stop()
{
    handleStop();
}

/******************************************************************************
 *             Name: slot_settings
 *      Function ID: 707
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for displaying Settings panel.
 ******************************************************************************/
void MainController::slot_settings()
{
    handleSettings();
}

/******************************************************************************
 *             Name: slot_command_panel
 *      Function ID: 708
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for displaying Command panel.
 ******************************************************************************/
void MainController::slot_command_panel()
{
    handleCommand_Panel();
}

/******************************************************************************
 *             Name: slot_Stop
 *      Function ID: 711
 *      Create date: 19/02/2019
 * Last modify date: 19/02/2019
 *      Description: Slot for quiting application.
 ******************************************************************************/
void MainController::slot_Quit()
{
    emit signal_confirm_quit_application();
}

#ifdef MAINCONTROLLER_DEBUG
/******************************************************************************
 *             Name: printProject_Information -Debug function
 *      Function ID: 900
 *      Create date: 18/02/2019
 * Last modify date: 19/03/2019
 *      Description: Print project information.
 ******************************************************************************/
void MainController::printProject_information()
{
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project name: " << _project_name;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project file: " << _project_file;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project path: " << _project_path;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Project file full path: " <<  _project_file_full_path;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Current path: " << _current_path;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "Output file: " << _project_output_path + MULTIMETERUI_DIR_SYMBOL + _output_file_name;
    qDebug() << DEBUG_SPLIT_LINE;
}

/******************************************************************************
 *             Name: debug_printSerial_inforation -Debug function
 *      Function ID: 903
 *      Create date: 24/02/2019
 * Last modify date: 24/02/2019
 *      Description: Print serial information.
 ******************************************************************************/
void MainController::debug_printSerial_information()
{
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << "DMM Current Port"            << _dmm_port;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT << _dmm_baudrate;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT << _dmm_databits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT << _dmm_stopbits;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT   <<  _dmm_parity;;
    qDebug() << MAINCONTORLLER_DEBUG_PREFIX << MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT << _dmm_flowcontrol;
}
#endif
