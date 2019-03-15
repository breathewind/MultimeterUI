/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 15/03/2019
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
private:
    Ui::Command_Panel *ui;
};

#endif // C203_COMMAND_PANEL_H
