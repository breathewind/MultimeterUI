/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 18/03/2019
 *      Description: Command Panel dialog of MultimeterUI application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c203_command_panel.h"
#include "ui_c203_command_panel.h"

/******************************************************************************
 *             Name: Command_Panel
 *      Function ID: 000
 *      Create date: 14/03/2019
 * Last modify date: 18/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Command_Panel::Command_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Command_Panel)
{
    ui->setupUi(this);

    setWindowTitle("Command Panel");
    setFixedSize(480,240);
}

/******************************************************************************
 *             Name: ~Command_Panel
 *      Function ID: 001
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Destruction function.
 ******************************************************************************/
Command_Panel::~Command_Panel()
{
    delete ui;
}

/******************************************************************************
 *             Name: showDialog
 *      Function ID: 300
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Show window and record its postion.
 ******************************************************************************/
void Command_Panel::showDialog()
{
    show();
    /** Let system remember dialog current position. */
    move(pos().x(), pos().y());
}

/******************************************************************************
 *             Name: setDefault
 *      Function ID: 301
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Set all options in command window as default value.
 ******************************************************************************/
void Command_Panel::setDefault(QString output_file)
{
    /** Initialize measurement target */
    ui->radioButton_current->setChecked(true);
    ui->radioButton_voltage->setChecked(false);
    ui->radioButton_resistance->setChecked(false);


    /** Initialize measurement type */
    ui->radioButton_single_data->setChecked(true);
    ui->radioButton_periodic_sampling->setChecked(false);
    ui->doubleSpinBox_sampling_period->setMinimum(COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setValue(COMMAND_PANEL_DEFAULT_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setEnabled(false);

    /** Initialize save file */
    ui->checkBox_save_file->setChecked(true);
    ui->lineEdit_file_path->setEnabled(true);
    ui->lineEdit_file_path->setText(output_file);
}

/******************************************************************************
 *             Name: updateInformation
 *      Function ID: 302
 *      Create date: 18/03/2019
 * Last modify date: 18/03/2019
 *      Description: Update all options in command window.
 ******************************************************************************/
void Command_Panel::updateInformation(int target, int type, double sampling_period, int save_file_checked, QString output_file)
{
    /** Update measurement target information */
    switch(target){
    case COMMAND_PANEL_TARGET_CURRENT:
        ui->radioButton_current->setChecked(true);
        ui->radioButton_voltage->setChecked(false);
        ui->radioButton_resistance->setChecked(false);
        break;
    case COMMAND_PANEL_TARGET_VOLTAGE:
        ui->radioButton_current->setChecked(false);
        ui->radioButton_voltage->setChecked(true);
        ui->radioButton_resistance->setChecked(false);
        break;
    case COMMAND_PANEL_TARGET_RESISTANCE:
        ui->radioButton_current->setChecked(false);
        ui->radioButton_voltage->setChecked(false);
        ui->radioButton_resistance->setChecked(true);
        break;
    default:
        break;
    }

    /** Update measurement type information */
    ui->doubleSpinBox_sampling_period->setMinimum(COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setValue(sampling_period);

    if(type == COMMAND_PANEL_TYPE_SINGLE_DATA){
        ui->radioButton_single_data->setChecked(true);
        ui->radioButton_periodic_sampling->setChecked(false);
        ui->doubleSpinBox_sampling_period->setEnabled(false);
    } else {
        ui->radioButton_single_data->setChecked(false);
        ui->radioButton_periodic_sampling->setChecked(true);
        ui->doubleSpinBox_sampling_period->setEnabled(true);
    }

    /** Update save file information */
    if(save_file_checked){
        ui->checkBox_save_file->setChecked(true);
        ui->lineEdit_file_path->setEnabled(true);
    } else {
        ui->checkBox_save_file->setChecked(false);
        ui->lineEdit_file_path->setEnabled(false);
    }
    ui->lineEdit_file_path->setText(output_file);
}
