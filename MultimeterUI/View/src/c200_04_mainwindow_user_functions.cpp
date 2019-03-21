/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 21/03/2019
 * Last modify date: 21/03/2019
 *      Description: Main window of MeasurementUI application.
 *                   - User Functions.
 ******************************************************************************/
#include "View/inc/c200_mainwindow.h"
#include "ui_c200_mainwindow.h"

/******************************************************************************
 *             Name: clearAllPanels
 *      Function ID: 300
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
 *      Function ID: 300
 *      Create date: 21/03/2019
 * Last modify date: 21/03/2019
 *      Description: Set all labels as default value.
 ******************************************************************************/
void MainWindow::setLabels_by_default()
{
    ui->label_text_time->setVisible(true);
//    ui->label_value_time->setText();
    ui->label_text_value->setVisible(true);
//    ui->label_value_value->clear();

    ui->label_text_target->setVisible(true);
//    ui->label_value_target->clear();

    ui->label_text_type->setVisible(true);
//    ui->label_value_type->clear();

    ui->label_text_save_path->setVisible(true);
//    ui->label_value_save_path->clear();
}
