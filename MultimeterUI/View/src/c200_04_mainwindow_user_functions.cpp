/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/03/2019
 * Last modify date: 01/04/2019
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
 * Last modify date: 01/04/2019
 *      Description: Initialize all labels when a project is created or opened.
 ******************************************************************************/
void MainWindow::initializeLabel(QString target, int type, double period, bool checked, QString save_path)
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
 *      Create date: 01/03/2019
 * Last modify date: 01/04/2019
 *      Description: Update all labels as command window settings.
 ******************************************************************************/
void MainWindow::updateCommand_panel_labels(QString target, int type, double period, bool checked, QString save_path)
{
    ui->label_value_target->setText(target);

    switch(type){
    case COMMAND_PANEL_TYPE_SINGLE_DATA:
        ui->label_value_type->setText(COMMAND_PANEL_TYPE_SINGLE_DATA_TEXT);
        ui->label_text_sampling_period->setVisible(false);
        ui->label_value_sampling_period->clear();
        break;
    case COMMAND_PANEL_TYPE_PERIODIC_SAMPLING:
        ui->label_value_type->setText(COMMAND_PANEL_TYPE_PERIODIC_SAMPLING_TEXT);
        ui->label_text_sampling_period->setVisible(true);
        ui->label_value_sampling_period->setText(QString().number(period));
        break;
    default:;
    }

    if(checked){
        ui->label_text_save_path->setVisible(true);
        ui->label_value_save_path->setText(save_path);
    } else {
        ui->label_text_save_path->setVisible(false);
        ui->label_value_save_path->clear();
    }
}
