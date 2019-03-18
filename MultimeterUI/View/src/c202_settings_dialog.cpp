/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 18/03/2019
 *      Description: Settings dialog of Multimeter application.
 *
 *  Function Number: 0XX - Normal logic functions
 *                   3XX - User level functions
 *                   6XX - View control functions
 *                   7XX - Slot functions
 *                   8XX - Get/set funcions
 *                   9XX - Debug functions
 ******************************************************************************/
#include "View/inc/c202_settings_dialog.h"
#include "ui_c202_settings_dialog.h"

/******************************************************************************
 *             Name: Settings_Dialog
 *      Function ID: 000
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Settings_Dialog::Settings_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_Dialog)
{
    ui->setupUi(this);

    setWindowTitle("Settings");
    initDMM_group();
}

/******************************************************************************
 *             Name: ~Settings_Dialog
 *      Function ID: 001
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Destruction function.
 ******************************************************************************/
Settings_Dialog::~Settings_Dialog()
{
    delete ui;
}

/******************************************************************************
 *             Name: initDMM_group
 *      Function ID: 002
 *      Create date: 20/02/2019
 * Last modify date: 14/03/2019
 *      Description: Initialize DMM group.
 ******************************************************************************/
void Settings_Dialog::initDMM_group()
{
    ui->comboBox_DMM_baudrate->addItems(__serial_definitions.getBaudrate_list());
    ui->comboBox_DMM_databits->addItems(__serial_definitions.getDataBits_list());
    ui->comboBox_DMM_stopbits->addItems(__serial_definitions.getStopBits_list());
    ui->comboBox_DMM_parity->addItems(__serial_definitions.getParity_list());
    ui->comboBox_DMM_flowcontrol->addItems(__serial_definitions.getFlowcontrol_list());
    ui->comboBox_DMM_port->addItems(Serial_definitions::getSerial_port_name());
}

/******************************************************************************
 *             Name: updateSerial_port_combobox
 *      Function ID: 003
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Update port combobbox.
 ******************************************************************************/
void Settings_Dialog::updateSerial_port_combobox(QStringList data)
{
    ui->comboBox_DMM_port->clear();

    ui->comboBox_DMM_port->addItems(data);
}

/******************************************************************************
 *             Name: setCombobox_default
 *      Function ID: 004
 *      Create date: 15/03/2019
 * Last modify date: 15/03/2019
 *      Description: Set all combobox by default settings.
 ******************************************************************************/
void Settings_Dialog::setCombobox_default()
{
    rescanSerial_port();

    ui->comboBox_DMM_baudrate->setCurrentText(DMM_BAUDRATE);
    ui->comboBox_DMM_databits->setCurrentText(DMM_DATABITS);
    ui->comboBox_DMM_stopbits->setCurrentText(DMM_STOPBITS);
    ui->comboBox_DMM_parity->setCurrentText(DMM_PARITY);
    ui->comboBox_DMM_flowcontrol->setCurrentText(DMM_FLOWCONTROL);
}

/******************************************************************************
 *             Name: showDialog
 *      Function ID: 300
 *      Create date: 20/02/2019
 * Last modify date: 20/02/2019
 *      Description: Show window and record its postion.
 ******************************************************************************/
void Settings_Dialog::showDialog()
{
    show();
    /** Let system remember dialog current position. */
    move(pos().x(), pos().y());
}

/******************************************************************************
 *             Name: updateDMM_combobox
 *      Function ID: 301
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
 *      Description: Update all DMM combo boxes.
 ******************************************************************************/
void Settings_Dialog::updateDMM_combobox(QStringList data)
{
    ui->comboBox_DMM_baudrate->setCurrentText(data.at(SERIAL_INDEX_BAUDRATE));
    ui->comboBox_DMM_databits->setCurrentText(data.at(SERIAL_INDEX_DATABITS));
    ui->comboBox_DMM_stopbits->setCurrentText(data.at(SERIAL_INDEX_STOPBITS));
    ui->comboBox_DMM_parity->setCurrentText(data.at(SERIAL_INDEX_PARITY));
    ui->comboBox_DMM_flowcontrol->setCurrentText(data.at(SERIAL_INDEX_FLOWCONTROL));
}

/******************************************************************************
 *             Name: rescanSerial_port
 *      Function ID: 302
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Rescan serial ports.
 ******************************************************************************/
void Settings_Dialog::rescanSerial_port()
{
    updateSerial_port_combobox(Serial_definitions::getSerial_port_name());
}

/******************************************************************************
 *             Name: resetAll_frames
 *      Function ID: 303
 *      Create date: 15/03/2019
 * Last modify date: 15/03/2019
 *      Description: Set all frames as default values.
 ******************************************************************************/
void Settings_Dialog::resetAll_frames()
{
    setCombobox_default();
}

/******************************************************************************
 *             Name: retrieveDMM_data
 *      Function ID: 304
 *      Create date: 21/02/2019
 * Last modify date: 22/02/2019
 *      Description: Retrieving data from all DMM combobbox.
 ******************************************************************************/
QStringList Settings_Dialog::retrieveDMM_data()
{
    QStringList data;

    data.append(ui->comboBox_DMM_baudrate->currentText());
    data.append(ui->comboBox_DMM_databits->currentText());
    data.append(ui->comboBox_DMM_stopbits->currentText());
    data.append(ui->comboBox_DMM_parity->currentText());
    data.append(ui->comboBox_DMM_flowcontrol->currentText());
    data.append(ui->comboBox_DMM_port->currentText());

    return data;
}

/******************************************************************************
 *             Name: on_pushButton_Apply_clicked
 *      Function ID: 700
 *      Create date: 20/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for Apply pushbutton clicked.
 ******************************************************************************/
void Settings_Dialog::on_pushButton_Apply_clicked()
{
    emit signal_accept_button_clicked();
}

/******************************************************************************
 *             Name: on_pushButton_Rescan_clicked
 *      Function ID: 710
 *      Create date: 21/02/2019
 * Last modify date: 21/02/2019
 *      Description: Slot for Rescan push button clicked.
 ******************************************************************************/
void Settings_Dialog::on_pushButton_Rescan_clicked()
{
    rescanSerial_port();
}
