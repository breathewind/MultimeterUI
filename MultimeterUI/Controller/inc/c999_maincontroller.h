/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/02/2019
 * Last modify date: 12/04/2019
 *      Description: Main window controller.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C999_MAINCONTROLLER_H
#define C999_MAINCONTROLLER_H

#define MAINCONTTROLLER_SETTINGS_DISPLAY_TEXT       "settings_display"
#define MAINCONTTROLLER_COMMAND_PANEL_DISPLAY_TEXT  "command_panel_display"
#define MAINCONTTROLLER_OUTPUT_PANEL_DISPLAY_TEXT   "output_panel_display"

#define MAINCONTTROLLER_SERIAL_DMM_BAUDRATE_TEXT    "dmm_baudrate"
#define MAINCONTTROLLER_SERIAL_DMM_DATABITS_TEXT    "dmm_databits"
#define MAINCONTTROLLER_SERIAL_DMM_STOPBITS_TEXT    "dmm_stopbits"
#define MAINCONTTROLLER_SERIAL_DMM_PARITY_TEXT      "dmm_parity"
#define MAINCONTTROLLER_SERIAL_DMM_FLOWCONTROL_TEXT "dmm_flowcontrol"


#define MAINCONTTROLLER_MEASUREMENT_TARGET_TEXT "measurement_target"
#define MAINCONTTROLLER_MEASUREMENT_TYPE_TEXT   "measurement_type"
#define MAINCONTTROLLER_SAMPLING_PERIOD_TEXT    "sampling_period"
#define MAINCONTTROLLER_SAVE_FLAG_TEXT          "save_filg"
#define MAINCONTTROLLER_SAVE_PATH_TEXT          "save_path"

#define MAINCONTROLLER_DIR_CREATE_SUCCEED 0
#define MAINCONTROLLER_DIR_CREATE_FAIL    1

#define MAINCONTROLLER_COMMAND_STOP  0
#define MAINCONTROLLER_COMMAND_RUN   1
#define MAINCONTROLLER_COMMAND_PAUSE 2

#include <QObject>
#include <QElapsedTimer>

#include "h000_global_parameters.h"
#include "Entities/inc/c950_global_functions.h"

#include "Controller/inc/c100_serial_controller.h"
#include "Controller/inc/c110_chart_controller.h"

#include "View/inc/c200_mainwindow.h"
#include "View/inc/c201_new_project_dialog.h"
#include "View/inc/c202_settings_dialog.h"
#include "View/inc/c203_command_panel.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    /** Function 000: Construction function. */
    MainController();

    /** Function 300: Show main window. */
    void showMainwindow();

private:
    /** Function 002: Clear all project information. */
    void clearProject_information();
    /** Function 003: Synchronize project path. */
    void synchronizeCurrent_path(QString current_path);
    /** Function 004: Update project information according to project name and project path. */
    int updateProject_information(QString project_name, QString project_path, QString output_file);
    /** Function 005: Update project information according to project file full path. */
    void updateProject_information(QString project_file_full_path);

    /** Function 200: Initilize functions related to Main Window. */
    void initMainwindow();
    /** Function 201: Initilize functions related to Project operations. */
    void initProject_operaiton();
    /** Function 202: Initilize functions related to Run operations. */
    void initRun_operaiton();
    /** Function 203: Initilize functions related to Function operations. */
    void initFunction_operaiton();
    /** Function 204: Initilize functions related to Serial operations. */
    void initSerial_operaiton();
    /** Function 205: Initilize functions related to timers. */
    void initTimer();
    /** Function 206: Initilize functions related to charts. */
    void initChart();


    /** Function 211: Initilize functions related to New Project operations. */
    void initNew_Project();
    /** Function 212: Initilize functions related to Open Project operations. */
    void initOpen_Project();
    /** Function 213: Initilize functions related to Save Project operations. */
    void initSave_Project();
    /** Function 214: Initilize functions related to Save Project As operations. */
    void initSave_Project_As();
    /** Function 215: Initilize functions related to Close Project operations. */
    void initClose_Project();

    /** Function 216: Initilize functions related to Start operations. */
    void initStart();
    /** Function 217: Initilize functions related to Stop operations. */
    void initStop();

    /** Function 218: Initilize functions related to Settings operations. */
    void initSettings();
    /** Function 219: Initilize functions related to Command Panel operations. */
    void initCommand_Panel();

    /** Function 222: Initilize functions related to Quit operations. */
    void initQuit();

    /** Function 231: Function for handle operations related to New Project. */
    bool handleNew_Project();
    /** Function 232: Function for handle operations related to Open Project. */
    bool handleOpen_Project();
    /** Function 233: Function for handle operations related to Save Project. */
    void handleSave_Project();
    /** Function 234: Function for handle operations related to Save Project as. */
    void handleSave_Project_As();
    /** Function 235: Function for handle operations related to Close Project. */
    void handleClose_Project();

    /** Function 236: Function for handle operations related to Start. */
    void handleStart();
    /** Function 237: Function for handle operations related to Stop. */
    void handleStop();

    /** Function 238: Function for handle operations related to Settings. */
    void handleSettings();
    /** Function 239: Function for handle operations related to Command Panel. */
    void handleCommand_Panel();

    /** Function 301: Update all settings opertions. */
    void UpdateSettings();
    /** Function 302: Start meausuremnt. */
    void startMeasurement();
    /** Function 303: Send one measurement request to DMM. */
    void sendMeasurement_request();
    /** Function 304: Enable/disable command panel and settings dialog. */
    void setEnable_command_and_settings(bool flag);

    /** Function 305: Create a new output file if the file of filepath not exists.. */
    void createOutput_file(QString filepath);
    /** Function 306: Append one line of data to an already existed output file. */
    void appendOutput_file(QString filepath, QString data_line);

    /** Function 600: Print data read from project file. */
    void printData_read_from_project_file(QString domain, QString content);
#ifdef MAINCONTROLLER_DEBUG
    /** Function 900: Print project information. -Debug function*/
    void printProject_information();
    /** Function 903: Print serial information. -Debug function */
    void debug_printSerial_information();
#endif

    MainWindow* _main_window;

    /** Parameters for file operations. */
    New_Project_Dialog* _new_project_dialog;

    QString _project_name;
    QString _project_file;
    QString _project_path;
    QString _project_file_full_path;
    QString _current_path;

    QString _project_output_path;
    QString _output_file_name;

    /** Parameters for execution. */
    int _exe_command;

    QTimer *_run_timer;
    QElapsedTimer _elapsed_timer;
    qint64 _previous_elapsed_time;
    QTimer *_sampling_timer;

    /** Parameters for serial communication. */
    Serial_Controller *_DMM_controller;
    QString _data_read_buffer;

    QString _meausrement_command;
    bool _continue_sampling_flag;
    double _sampling_period;

    Settings_Dialog* _settings_dialog;

    QString _dmm_port;
    QString _dmm_baudrate;
    QString _dmm_databits;
    QString _dmm_stopbits;
    QString _dmm_parity;
    QString _dmm_flowcontrol;

    /** Parameters for controlling measurement. */
    Command_Panel* _command_panel;

    /** Parameters for controlling charts. */
    Chart_Controller* _chart_controller;

private slots:
    /** Function 700: Slot for new project created. */
    void slot_create_new_project(QString project_name, QString project_path);
    /** Function 701: Slot for open a project. */
    void slot_open_project(QString project_file_full_path);
    /** Function 702: Slot for saving current project. */
    void slot_save_project();
    /** Function 703: Slot for saving project as another project. */
    void slot_save_project_as(QString project_file_full_path);
    /** Function 704: Slot for current project closed. */
    void slot_close_project();

    /** Function 705: Slot for starting new measrement. */
    void slot_Start();
    /** Function 706: Slot for stoping current measurement. */
    void slot_Stop();

    /** Function 707: Slot for displaying Settings panel. */
    void slot_settings();
    /** Function 708: Slot for displaying Command panel. */
    void slot_command_panel();

    /** Function 711: Slot for quiting application. */
    void slot_Quit();

    /** Function 750: Slot for updating data from settings dialog to main controller. */
    void slot_update_data_from_settings();
    /** Function 751: Slot for retrieving data from DMM when one data to read is ready. */
    void slot_retrieveDMM_data(QString received_data);
    /** Function 752: Slot for updating run timer when run timer timeout. */
    void slot_updateRun_timer();
    /** Function 753: Slot for updating sampling timer when sampling timer timeout. */
    void slot_updateSampling_timer();

signals:
    /** Signal 001: Signal for synchronizing project path. */
    void signal_synchronizeCurrent_Path(QString project_path);
    /** Signal 002: Signal for comfirming quit appliaciton. */
    void signal_confirm_quit_application();
    /** Signal 003: Signal emitted when a warning event occurs. */
    void signal_warning_occurs(QString text);
};

#endif // C999_MAINCONTROLLER_H
