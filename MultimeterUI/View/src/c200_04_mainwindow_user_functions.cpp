/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/03/2019
 * Last modify date: 12/04/2019
 *      Description: Main window of MeasurementUI application.
 *                   - User Functions.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: clearAllPanels
 *      Function ID: 302
 *      Create date: 21/03/2019
 * Last modify date: 21/03/2019
 *      Description: Clear content of all labels.
 ******************************************************************************/
void MainWindow::clearAll_labels()
{
    ui->label_text_time->setVisible(false);
    ui->label_value_time->clear();
    ui->label_text_value->setVisible(false);
    ui->label_value_value->clear();

    ui->label_text_target->setVisible(false);
    ui->label_value_target->clear();

    ui->label_text_type->setVisible(false);
    ui->label_value_type->clear();
    ui->label_text_sampling_period->setVisible(false);
    ui->label_value_sampling_period->clear();

    ui->label_text_save_path->setVisible(false);
    ui->label_value_save_path->clear();
}

/******************************************************************************
 *             Name: setLabels_by_default
 *      Function ID: 303
 *      Create date: 21/03/2019
 * Last modify date: 02/04/2019
 *      Description: Initialize all labels when a project is created or opened.
 ******************************************************************************/
void MainWindow::initializeLabel(int target, int type, double period, bool checked, QString save_path)
{
    ui->label_text_time->setVisible(true);
    ui->label_value_time->setText("0");
    ui->label_text_value->setVisible(true);
    ui->label_value_value->setText("0");

    ui->label_text_target->setVisible(true);

    ui->label_text_type->setVisible(true);

    updateCommand_panel_labels(target, type, period, checked, save_path);
}

/******************************************************************************
 *             Name: updateCommand_panel_labels
 *      Function ID: 304
 *      Create date: 01/04/2019
 * Last modify date: 02/04/2019
 *      Description: Update all labels as command window settings.
 ******************************************************************************/
void MainWindow::updateCommand_panel_labels(int target, int type, double period, bool checked, QString save_path)
{
    switch(target){
    case COMMAND_PANEL_TARGET_CURRENT:
        ui->label_value_target->setText(COMMAND_PANEL_TARGET_CURRENT_TEXT);
        _measurement_unit = COMMAND_PANEL_UNIT_CURRENT;
        break;
    case COMMAND_PANEL_TARGET_VOLTAGE:
        ui->label_value_target->setText(COMMAND_PANEL_TARGET_VOLTAGE_TEXT);
        _measurement_unit = COMMAND_PANEL_UNIT_VOLTAGE;
        break;
    case COMMAND_PANEL_TARGET_RESISTANCE:
        ui->label_value_target->setText(COMMAND_PANEL_TARGET_RESISTANCE_TEXT);
        _measurement_unit = COMMAND_PANEL_UNIT_RESISTANCE;
        break;
    default:
        break;
    }

    switch(type){
    case COMMAND_PANEL_TYPE_SINGLE_DATA:
        ui->label_value_type->setText(COMMAND_PANEL_TYPE_SINGLE_DATA_TEXT);
        ui->label_text_sampling_period->setVisible(false);
        ui->label_value_sampling_period->clear();
        break;
    case COMMAND_PANEL_TYPE_PERIODIC_SAMPLING:
        ui->label_value_type->setText(COMMAND_PANEL_TYPE_PERIODIC_SAMPLING_TEXT);
        ui->label_text_sampling_period->setVisible(true);
        ui->label_value_sampling_period->setText(QString().number(period)+ " s");
        break;
    default:
        break;
    }

    if(checked){
        ui->label_text_save_path->setVisible(true);
        ui->label_value_save_path->setText(save_path);
    } else {
        ui->label_text_save_path->setVisible(false);
        ui->label_value_save_path->clear();
    }
}

/******************************************************************************
 *             Name: updateMeasurement_value
 *      Function ID: 305
 *      Create date: 02/04/2019
 * Last modify date: 03/04/2019
 *      Description: Update measurement value.
 ******************************************************************************/
void MainWindow::updateMeasurement_value(double value)
{
    ui->label_value_value->setText(QString("%1 %2").arg(value).arg(_measurement_unit));
}

/******************************************************************************
 *             Name: updateMeasurement_time
 *      Function ID: 306
 *      Create date: 02/04/2019
 * Last modify date: 12/04/2019
 *      Description: Update measurement time.
 ******************************************************************************/
void MainWindow::updateMeasurement_time(qint64 time)
{
    ui->label_value_time->setText(Global_Functions::formatTime(time));
}

/******************************************************************************
 *             Name: setSTOP
 *      Function ID: 307
 *      Create date: 03/04/2019
 * Last modify date: 03/04/2019
 *      Description: Set the buttons related to exection as the operation
 *                   "STOP".
 ******************************************************************************/
void MainWindow::setSTOP()
{
    handleStop_triggered();
}

/******************************************************************************
 *             Name: setEnable_execution_buttons
 *      Function ID: 308
 *      Create date: 03/04/2019
 * Last modify date: 03/04/2019
 *      Description: Set the buttons related to exection as the operation
 *                   "STOP".
 ******************************************************************************/
void MainWindow::setEnable_execution_buttons(bool flag)
{
    _run_time_group->setEnabled(flag);
}

/******************************************************************************
 *             Name: addChart_view
 *      Function ID: 309
 *      Create date: 08/04/2019
 * Last modify date: 12/04/2019
 *      Description: Add a chart view to mainwindow.
 ******************************************************************************/
void MainWindow::addChart_view(QChartView *chart)
{
    ui->verticalLayout_chart->addWidget(chart);
}
