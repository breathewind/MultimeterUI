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
#ifndef C202_SETTINGS_DIALOG_H
#define C202_SETTINGS_DIALOG_H

#define SETTINGS_DIALOG_CONTROLLER_DATA_DMM  0

#include <QDialog>

#include "h001_serial_parameters.h"

namespace Ui {
class Settings_Dialog;
}

class Settings_Dialog : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Settings_Dialog(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Settings_Dialog();
    /** Function 002: Initialize DMM group. */
    void initDMM_group();
    /** Function 003: Update port combobbox. */
    void updateSerial_port_combobox(QStringList data);
    /** Function 004: Set all combobox by default settings. */
    void setCombobox_default();

    /** Function 300: Show window and record its postion. */
    void showDialog();
    /** Function 301: Update all frames. */
    void updateDMM_combobox(QStringList data);
    /** Function 302: Rescan serial ports. */
    void rescanSerial_port();
    /** Function 303: Set all frames as default values. */
    void resetAll_frames();
    /** Function 304: Retrieve data from all DMM combobbox. */
    QStringList retrieveDMM_data();

private:
    Ui::Settings_Dialog *ui;


private slots:
    /** Function 700: Slot for Apply pushbutton clicked. */
    void on_pushButton_Apply_clicked();

    /** Function 710: Slot for Rescan push button clicked. */
    void on_pushButton_Rescan_clicked();


signals:
    /** Signal 001: Signal emitted when accept button is clicked. */
    void signal_accept_button_clicked();
};

#endif // C202_SETTINGS_DIALOG_H
