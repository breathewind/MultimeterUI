/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 30/01/2019
 * Last modify date: 19/02/2019
 *      Description: Main window of MeasurementUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#ifndef C200_MAINWINDOW_H
#define C200_MAINWINDOW_H

#define MAINWINDOW_PROJECT_ACTIVATE   true
#define MAINWINDOW_PROJECT_DEACTIVATE false

#define MAINWINDOW_PROJECT_RUNNING 0
#define MAINWINDOW_PROJECT_PASUE   1
#define MAINWINDOW_PROJECT_STOP    2

#include <QMainWindow>
#include <QMessageBox>
#include <QActionGroup>
#include <QFileDialog>
#include <QIcon>
#include <QCloseEvent>

#include "h000_global_parameters.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit MainWindow(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~MainWindow();


    /** Function 300: Change display status depending on if there is any project activated. */
    void changeDisplay_status(bool display_flag);
    /** Function 301: Reset display status for all the menu actions. */
    void resetAll_menu_actions();

public slots:
    /** Function 750: Slot for updating current path. */
    void slot_update_current_path(QString current_path);
    /** Function 751: Slot for quit application confirmed. */
    void slot_confirm_quit_application();

private:
    /** Function 002: Run time action group initialization. */
    void initializeRun_time_group();
    /** Function 003: File action group initialization. */
    void initializeFile_group();
    /** Function 004: Setting action group initialization. */
    void initializeSetting_group();
    /** Function 005: Full file action group initialization. */
    void initializeCreate_file_group();

    /** Function 010: Set display status for the Run operation menu actions depending project running information. */
    void setRun_menu_action_enable(bool flag);

    /** Function 090: Overwrite close event. */
    void closeEvent (QCloseEvent *event);

    /** Function 200: Function for New Project menu action triggered. */
    void handleNew_Project_triggered();
    /** Function 201: Function for Open Project menu action triggered. */
    QString handleOpen_Project_triggered();
    /** Function 202: Function for Save Project menu action triggered. */
    void handleSave_Project_triggered();
    /** Function 203: Function for Save Project As menu action triggered. */
    QString handleSave_Project_As_triggered();
    /** Function 204: Function for Close Project menu action triggered. */
    void handleClose_Project_triggered();

    /** Function 205: Function for Start menu action triggered. */
    void handleStart_triggered();
    /** Function 206: Function for Stop menu action triggered. */
    void handleStop_triggered();

    Ui::MainWindow *ui;

    QActionGroup *_run_time_group;
    QActionGroup *_file_group;
    QActionGroup *_create_file_group;
    QActionGroup *_setting_group;

    bool _project_activated;
    char _project_running;

    QString _current_path;

private slots:
    /** Function 700: Slot for New Project menu action triggered. */
    void on_actionNew_Project_triggered();
    /** Function 701: Slot for Open Project menu action triggered. */
    void on_actionOpen_Project_triggered();
    /** Function 702: Slot for Save Project menu action triggered. */
    void on_actionSave_project_triggered();
    /** Function 703: Slot for Save Project As menu action triggered. */
    void on_actionSave_project_as_triggered();
    /** Function 704: Slot for Close Project menu action triggered. */
    void on_actionClose_project_triggered();

    /** Function 705: Slot for Start menu action triggered. */
    void on_actionStart_triggered();
    /** Function 706: Slot for Stop menu action triggered. */
    void on_actionStop_triggered();

    /** Function 710: Slot for Information menu action triggered. */
    void on_actionInformation_triggered();
    /** Function 711: Slot for Quit menu action triggered. */
    void on_actionQuit_triggered();

signals:
    /** Signal 001: Signal emitted when New Project menu action triggered. */
    void signal_new_project_menu_action_triggered();
    /** Signal 002: Signal emitted when Open Project menu action triggered. */
    void signal_open_project_menu_action_triggered(QString project_file_full_path);
    /** Signal 003: Signal emitted when Save Project menu action triggered. */
    void signal_save_project_menu_action_triggered();
    /** Signal 004: Signal emitted when Save Project As menu action triggered. */
    void signal_save_project_as_menu_action_triggered(QString project_file_full_path);
    /** Signal 005: Signal emitted when Close Project menu action triggered. */
    void signal_close_project_menu_action_triggered();

    /** Signal 006: Signal emitted when Start menu action triggered. */
    void signal_start_menu_action_triggered();
    /** Signal 007: Signal emitted when Stop menu action triggered. */
    void signal_stop_menu_action_triggered();

    /** Signal 012: Signal emitted when Quit menu action triggered. */
    void signal_quit_menu_action_triggered();
};

#endif // C200_MAINWINDOW_H
