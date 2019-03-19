/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 19/03/2019
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
 *             Name: setLogic_target
 *      Function ID: 002
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set display logic for discharge measurement target.
 ******************************************************************************/
void Command_Panel::setLogic_target(int target)
{
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
}

/******************************************************************************
 *             Name: setLogic_target
 *      Function ID: 003
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set display logic for discharge measurement type.
 ******************************************************************************/
void Command_Panel::setLogic_type(int type)
{
    if(type == COMMAND_PANEL_TYPE_SINGLE_DATA){
        ui->radioButton_single_data->setChecked(true);
        ui->radioButton_periodic_sampling->setChecked(false);
        ui->doubleSpinBox_sampling_period->setEnabled(false);
    } else {
        ui->radioButton_single_data->setChecked(false);
        ui->radioButton_periodic_sampling->setChecked(true);
        ui->doubleSpinBox_sampling_period->setEnabled(true);
    }
}

/******************************************************************************
 *             Name: setLogic_target
 *      Function ID: 004
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set display logic for save file..
 ******************************************************************************/
void Command_Panel::setLogic_save_file(int save_flag)
{
    if(save_flag == COMMAND_PANEL_SAVE_FILE_CHECKED){
        ui->groupBox_save_file->setEnabled(true);
    } else {
        ui->groupBox_save_file->setEnabled(false);
    }
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
 * Last modify date: 19/03/2019
 *      Description: Set all options in command window as default value.
 ******************************************************************************/
void Command_Panel::setDefault(QString output_file)
{
    /** Initialize measurement target */
    setLogic_target(COMMAND_PANEL_TARGET_CURRENT);


    /** Initialize measurement type */
    ui->doubleSpinBox_sampling_period->setMinimum(COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setValue(COMMAND_PANEL_DEFAULT_SAMPLING_PERIOD);

    setLogic_type(COMMAND_PANEL_TYPE_SINGLE_DATA);

    /** Initialize save file */
    ui->lineEdit_file_path->setText(output_file);

    ui->checkBox_save_file->setChecked(true);
    setLogic_save_file(COMMAND_PANEL_SAVE_FILE_CHECKED);
}

/******************************************************************************
 *             Name: updateInformation
 *      Function ID: 302
 *      Create date: 18/03/2019
 * Last modify date: 19/03/2019
 *      Description: Update all options in command window.
 ******************************************************************************/
void Command_Panel::updateInformation(int target,
                                      int type, double sampling_period,
                                      int save_flag, QString save_path)
{
    /** Update measurement target information */
    setLogic_target(target);

    /** Update measurement type information */
    ui->doubleSpinBox_sampling_period->setMinimum(COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setValue(sampling_period);

    setLogic_type(type);

    /** Update save file information */
    ui->lineEdit_file_path->setText(save_path);

    ui->checkBox_save_file->setChecked(static_cast<bool>(save_flag));
    setLogic_save_file(save_flag);
}

/******************************************************************************
 *             Name: getMeasurementSettings
 *      Function ID: 800
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Get measurement settings.
 ******************************************************************************/
QStringList Command_Panel::getMeasurementSettings()
{
    QStringList data_list;
    /** Retrieve data about measurement target. */
    if(ui->radioButton_current->isChecked()){
        data_list.append(QString::number(COMMAND_PANEL_TARGET_CURRENT));
    } else if (ui->radioButton_voltage->isChecked()) {
        data_list.append(QString::number(COMMAND_PANEL_TARGET_VOLTAGE));
    } else {
        data_list.append(QString::number(COMMAND_PANEL_TARGET_RESISTANCE));
    }
    /** Retrieve data about measurement type. */
    if(ui->radioButton_single_data->isChecked()){
        data_list.append(QString::number(COMMAND_PANEL_TYPE_SINGLE_DATA));
    } else {
        data_list.append(QString::number(COMMAND_PANEL_TYPE_PERIODIC_SAMPLING));
    }
    /** Retrieve data about sampling period. */
    data_list.append(ui->doubleSpinBox_sampling_period->text());
    /** Retrieve data about if measurement will be saved to file. */
    if(ui->checkBox_save_file->isChecked()){
        data_list.append(QString::number(COMMAND_PANEL_SAVE_FILE_CHECKED));
    } else {
        data_list.append(QString::number(COMMAND_PANEL_SAVE_FILE_UNCHECKED));
    }
    /** Retrieve data about save file path. */
    data_list.append(ui->lineEdit_file_path->text());

    return data_list;
}

/******************************************************************************
 *             Name: setMeasurementTarget
 *      Function ID: 801
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set measurement target.
 ******************************************************************************/
void Command_Panel::setMeasurementTarget(int target)
{
    setLogic_target(target);
}

/******************************************************************************
 *             Name: setMeasurementType
 *      Function ID: 802
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set measurement type.
 ******************************************************************************/
void Command_Panel::setMeasurementType(int type)
{
    setLogic_type(type);
}

/******************************************************************************
 *             Name: setSamplingPeriod
 *      Function ID: 803
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set sampling period.
 ******************************************************************************/
void Command_Panel::setSamplingPeriod(double period)
{
    ui->doubleSpinBox_sampling_period->setMinimum(COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD);
    ui->doubleSpinBox_sampling_period->setValue(period);
}

/******************************************************************************
 *             Name: setSaveFlag
 *      Function ID: 804
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set save flag.
 ******************************************************************************/
void Command_Panel::setSaveFlag(int flag)
{
    ui->checkBox_save_file->setChecked(static_cast<bool>(flag));
    setLogic_save_file(flag);
}

/******************************************************************************
 *             Name: setSavePath
 *      Function ID: 805
 *      Create date: 19/03/2019
 * Last modify date: 19/03/2019
 *      Description: Set save path.
 ******************************************************************************/
void Command_Panel::setSavePath(QString save_path)
{
    ui->lineEdit_file_path->setText(save_path);
}
