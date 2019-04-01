/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 18/02/2019
 * Last modify date: 01/04/2019
 *      Description: Main window controller.
 *                   - Functions related to file menu actions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: handleStart
 *      Function ID: 236
 *      Create date: 18/02/2019
 * Last modify date: 01/04/2019
 *      Description: Function for handle operations related to Start.
 ******************************************************************************/
void MainController::handleStart()
{
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: handleStart";
#endif
    /** Update all labels */
    _main_window->updateCommand_panel_labels(_command_panel->getMeasurement_Target_Text(),
                                             _command_panel->getMeasurementType(),
                                             _command_panel->getSamplingPeriod(),
                                             _command_panel->getSaveFlag(),
                                             _command_panel->getSavePath());
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
