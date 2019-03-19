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
#ifndef C203_COMMAND_PANEL_H
#define C203_COMMAND_PANEL_H

#define COMMAND_PANEL_TARGET_CURRENT    0
#define COMMAND_PANEL_TARGET_VOLTAGE    1
#define COMMAND_PANEL_TARGET_RESISTANCE 2

#define COMMAND_PANEL_TYPE_SINGLE_DATA       0
#define COMMAND_PANEL_TYPE_PERIODIC_SAMPLING 1

#define COMMAND_PANEL_SAVE_FILE_UNCHECKED 0
#define COMMAND_PANEL_SAVE_FILE_CHECKED   1
/**************** Parameters index ****************/
#define COMMAND_PANEL_TARGET_INDEX    0
#define COMMAND_PANEL_TYPE_INDEX      1
#define COMMAND_PANEL_PERIOD_INDEX    2
#define COMMAND_PANEL_SAVE_FLAG_INDEX 3
#define COMMAND_PANEL_SAVE_PATH_INDEX 4
/**************** Default values ****************/
#define COMMAND_PANEL_MINIMUM_SAMPLING_PERIOD 0.7
#define COMMAND_PANEL_DEFAULT_SAMPLING_PERIOD 1.00

#include <QDialog>

namespace Ui {
class Command_Panel;
}

class Command_Panel : public QDialog
{
    Q_OBJECT

public:
    /** Function 000: Construction function. */
    explicit Command_Panel(QWidget *parent = nullptr);
    /** Function 001: Destruction function. */
    ~Command_Panel();

    /** Function 300: Show window and record its postion. */
    void showDialog();
    /** Function 301: Set all options in command window as default value. */
    void setDefault(QString output_file);
    /** Function 302: Update all options in command window. */
    void updateInformation(int target, int type, double sampling_period, int save_flag, QString save_path);

    /** Function 800: Get measurement settings. */
    QStringList getMeasurementSettings();
    /** Function 801: Set measurement target. */
    void setMeasurementTarget(int target);
    /** Function 802: Set measurement type. */
    void setMeasurementType(int type);
    /** Function 803: Set sampling period. */
    void setSamplingPeriod(double period);
    /** Function 804: Set save flag. */
    void setSaveFlag(int flag);
    /** Function 805: Set save path. */
    void setSavePath(QString save_path);

private:
    /** Function 002: Set display logic for measurement target. */
    void setLogic_target(int target);
    /** Function 003: Set check boxes for measurement type. */
    void setChecked_type(int type);
    /** Function 004: Set display logic for measurement type. */
    void setLogic_type(int type);
    /** Function 005: Set display logic for save file. */
    void setLogic_save_file(int save_flag);

    Ui::Command_Panel *ui;
};

#endif // C203_COMMAND_PANEL_H
