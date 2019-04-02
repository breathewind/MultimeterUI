/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 01/04/2019
 * Last modify date: 02/04/2019
 *      Description: Main window controller.
 *                   - User Functions.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: UpdateSettings
 *      Function ID: 301
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Update all settings opertions.
 ******************************************************************************/
void MainController::UpdateSettings()
{
    QStringList data_list;

    data_list.append(_dmm_baudrate);
    data_list.append(_dmm_databits);
    data_list.append(_dmm_stopbits);
    data_list.append(_dmm_parity);
    data_list.append(_dmm_flowcontrol);

    _settings_dialog->updateDMM_combobox(data_list);
}

/******************************************************************************
 *             Name: UpdateSettings
 *      Function ID: 302
 *      Create date: 01/04/2019
 * Last modify date: 02/04/2019
 *      Description: Start meausuremnt.
 ******************************************************************************/
void MainController::startMeasurement()
{
/** Set measurement information */
    /** Set meausurement command */
    switch(_command_panel->getMeasurementTarget()){
    case COMMAND_PANEL_TARGET_CURRENT:
        _meausrement_command = MEASUREMENTUI_CURRENT_COMMAND;
        break;
    case COMMAND_PANEL_TARGET_VOLTAGE:
        _meausrement_command = MEASUREMENTUI_VOLTAGE_COMMAND;
        break;
    case COMMAND_PANEL_TARGET_RESISTANCE:
        _meausrement_command = MEASUREMENTUI_RESISTANCE_COMMAND;
        break;
    default:
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << " - Invalid measurement target.";
#endif
        return;
    }

    switch (_command_panel->getMeasurementType()) {
    case COMMAND_PANEL_TYPE_SINGLE_DATA:
        _continue_sampling_flag = false;
        break;
    case COMMAND_PANEL_TYPE_PERIODIC_SAMPLING:
        _continue_sampling_flag = true;
        break;
    default:
#ifdef MAINCONTROLLER_DEBUG
    qDebug() << "+ MainController: " << __FUNCTION__ << " - Invalid measurement type.";
#endif
        return;
    }


    /** Set execution command as RUN */
    _exe_command = MAINCONTROLLER_COMMAND_RUN;

    sendMeasurement_request();
}

/******************************************************************************
 *             Name: sendMeasurement_request
 *      Function ID: 303
 *      Create date: 01/04/2019
 * Last modify date: 01/04/2019
 *      Description: Send one measurement request to DMM.
 ******************************************************************************/
void MainController::sendMeasurement_request()
{
    _DMM_controller->writeDMM_command(":SYST:REM", false);
    _DMM_controller->writeDMM_command(_meausrement_command);
}
