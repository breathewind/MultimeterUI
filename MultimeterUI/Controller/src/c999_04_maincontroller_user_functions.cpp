/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 01/04/2019
 * Last modify date: 29/04/2019
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
 * Last modify date: 29/04/2019
 *      Description: Start meausuremnt.
 ******************************************************************************/
void MainController::startMeasurement()
{
/** Set measurement information */
    QString chart_title;
    QString y_unit;

    /** Set meausurement command */

    chart_title = _command_panel->getMeasurement_Target_Text();
    switch(_command_panel->getMeasurementTarget()){
    case COMMAND_PANEL_TARGET_CURRENT:
        _meausrement_command = MEASUREMENTUI_CURRENT_COMMAND;
        y_unit = COMMAND_PANEL_UNIT_CURRENT;
        break;
    case COMMAND_PANEL_TARGET_VOLTAGE:
        _meausrement_command = MEASUREMENTUI_VOLTAGE_COMMAND;
        y_unit = COMMAND_PANEL_UNIT_VOLTAGE;
        break;
    case COMMAND_PANEL_TARGET_RESISTANCE:
        _meausrement_command = MEASUREMENTUI_RESISTANCE_COMMAND;
        y_unit = COMMAND_PANEL_UNIT_RESISTANCE;
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
        _main_window->setEnable_execution_buttons(false);
        break;
    case COMMAND_PANEL_TYPE_PERIODIC_SAMPLING:
        _continue_sampling_flag = true;
        _sampling_period = _command_panel->getSamplingPeriod();
        _main_window->setEnable_execution_buttons(false);

        _chart_controller->reset(chart_title, 0, y_unit);

        if(_command_panel->getSaveFlag()){
            Global_Functions::createNew_file(_command_panel->getSavePath(), _command_panel->getMeasurement_Target_Text());
        }

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

/******************************************************************************
 *             Name: setEnable_command_and_settings
 *      Function ID: 304
 *      Create date: 03/04/2019
 * Last modify date: 03/04/2019
 *      Description: Enable/disable command panel and settings dialog.
 ******************************************************************************/
void MainController::setEnable_command_and_settings(bool flag)
{
    _command_panel->setEnabled(flag);
    _settings_dialog->setEnabled(flag);
}

/******************************************************************************
 *             Name: createOutput_file
 *      Function ID: 305
 *      Create date: 12/04/2019
 * Last modify date: 12/04/2019
 *      Description: Create a new output file if the file of filepath not
 *                   exists.
 ******************************************************************************/
void MainController::createOutput_file(QString filepath)
{
    QFile output_file(filepath);
    if(!output_file.exists()){
        if(output_file.open(QFile::WriteOnly | QFile::Text)){
#ifdef MAINCONTROLLER_DEBUG
            qDebug() << "+ MainController: " << __FUNCTION__ << " - new file created: " << filepath;
#endif
            output_file.close();
        }
    }
}

/******************************************************************************
 *             Name: appendOutput_file
 *      Function ID: 306
 *      Create date: 12/04/2019
 * Last modify date: 12/04/2019
 *      Description: Append one line of data to an already existed output file.
 ******************************************************************************/
void MainController::appendOutput_file(QString filepath, QString data_line)
{
    QFile output_file(filepath);
    if(output_file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){
        QTextStream out_stream(&output_file);
        out_stream << data_line;

#ifdef MAINCONTROLLER_DEBUG
        qDebug() << "+ MainController: " << __FUNCTION__ << " - file opened: " << filepath;
#endif
        out_stream.flush();
        output_file.close();
    }
}
