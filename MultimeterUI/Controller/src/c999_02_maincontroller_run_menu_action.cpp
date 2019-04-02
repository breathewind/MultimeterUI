/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 02/04/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleStart
 *      Function ID: 236
 *      Create date: 18/02/2019
 * Last modify date: 02/04/2019
 *      Description: Function for handle operations related to Start.
 ******************************************************************************/
void MainController::handleStart()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleStart";
#endif
    /** Update all labels */
    _main_window->updateCommand_panel_labels(_command_panel->getMeasurementTarget(),
                                             _command_panel->getMeasurementType(),
                                             _command_panel->getSamplingPeriod(),
                                             _command_panel->getSaveFlag(),
                                             _command_panel->getSavePath());
    /** Serial port configuration */
    _DMM_controller->setPortName(_dmm_port);
    _DMM_controller->setBaudRate(__serial_definitions.getBaudrate(_dmm_baudrate));
    _DMM_controller->setParity(static_cast<QSerialPort::Parity>(__serial_definitions.getParity(_dmm_parity)));
    _DMM_controller->setDataBits(static_cast<QSerialPort::DataBits>(__serial_definitions.getDataBits(_dmm_databits)));
    _DMM_controller->setStopBits(static_cast<QSerialPort::StopBits>(__serial_definitions.getStopBits(_dmm_stopbits)));
    _DMM_controller->setFlowControl(static_cast<QSerialPort::FlowControl>(__serial_definitions.getFlowcontrol(_dmm_flowcontrol)));

    _DMM_controller->startSerial();

    /** Start elapse timer */
    _previous_elapsed_time = 0;
    _elapsed_timer.start();

    /** Start measurement */
    startMeasurement();
}

/******************************************************************************
 *             Name: handleStop
 *      Function ID: 237
 *      Create date: 18/02/2019
 * Last modify date: 18/02/2019
 *      Description: Function for handle operations related to Stop.
 ******************************************************************************/
void MainController::handleStop()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleStop";
#endif
}
