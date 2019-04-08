/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 22/02/2019
 * Last modify date: 08/04/2019
 *      Description: Main window controller.
 *                   - Functional slots.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: slot_update_data_from_settings
 *      Function ID: 750
 *      Create date: 22/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for updating data from settings dialog to main
 *                   controller.
 ******************************************************************************/
void MainController::slot_update_data_from_settings()
{
    QStringList data_set = _settings_dialog->retrieveDMM_data();

    _dmm_baudrate = data_set.at(SERIAL_INDEX_BAUDRATE);
    _dmm_databits = data_set.at(SERIAL_INDEX_DATABITS);
    _dmm_stopbits = data_set.at(SERIAL_INDEX_STOPBITS);
    _dmm_parity = data_set.at(SERIAL_INDEX_PARITY);
    _dmm_flowcontrol = data_set.at(SERIAL_INDEX_FLOWCONTROL);
    _dmm_port = data_set.at(SERIAL_INDEX_PORT);

#ifdef MAINCONTROLLER_DEBUG
    debug_printSerial_information();
#endif
}

/******************************************************************************
 *             Name: slot_retrieveDMM_data
 *      Function ID: 751
 *      Create date: 01/04/2019
 * Last modify date: 08/04/2019
 *      Description: Slot for retrieving data from DMM when capture timer
 *                   timeout is reached.
 ******************************************************************************/
void MainController::slot_retrieveDMM_data(QString received_data)
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ ;
#endif
//    if(_exe_command == MAINCONTROLLER_COMMAND_RUN){
    _data_read_buffer = received_data;
    _main_window->updateMeasurement_value(received_data.toDouble());

#ifdef MAINCONTROLLER_DEBUG
    qint64 elapsed_time = _elapsed_timer.elapsed() - _previous_elapsed_time;
    qDebug() << "+ MainController: " << __FUNCTION__ << " The measurement operation took: " << elapsed_time << " milliseconds";
    qDebug() << "+ MainController: " << __FUNCTION__ << "- received_data: " << received_data;
#endif
//    } else {
//        _DMM_controller->closeSerial();
//        _main_window->setEnable_execution_buttons(true);
//        setEnable_command_and_settings(true);
//    }
}

/******************************************************************************
 *             Name: slot_updateRun_timer
 *      Function ID: 752
 *      Create date: 02/04/2019
 * Last modify date: 03/04/2019
 *      Description: Slot for updating run timer when run timer timeout.
 ******************************************************************************/
void MainController::slot_updateRun_timer()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ ;
#endif
    _run_timer->stop();
    if(_exe_command == MAINCONTROLLER_COMMAND_RUN){
        if(_continue_sampling_flag){
            _run_timer->start(MULTIMETERUI_DEFAULT_RUN_TIMER_TIMEOUT);
        } else {
            // Used for updating _exe_commnad when the measurement type is "single data"
            _DMM_controller->closeSerial();
            _exe_command = MAINCONTROLLER_COMMAND_STOP;
            _main_window->setSTOP();
            _main_window->setEnable_execution_buttons(true);
            setEnable_command_and_settings(true);
        }
        _main_window->updateMeasurement_time(_elapsed_timer.elapsed());
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << " Current time: " << _elapsed_timer.elapsed() << " milliseconds";
#endif
    }
}

/******************************************************************************
 *             Name: slot_updateSampling_timer
 *      Function ID: 753
 *      Create date: 08/04/2019
 * Last modify date: 08/04/2019
 *      Description: Slot for updating sampling timer when sampling timer
 *                   timeout.
 ******************************************************************************/
void MainController::slot_updateSampling_timer()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ ;
#endif
    _sampling_timer->stop();
    _main_window->setEnable_execution_buttons(true);
    if(_exe_command == MAINCONTROLLER_COMMAND_RUN){
        _sampling_timer->start(static_cast<int>(_sampling_period*1000));
        sendMeasurement_request();
    } else {
        _DMM_controller->closeSerial();
        _main_window->setSTOP();
        setEnable_command_and_settings(true);
    }
}
