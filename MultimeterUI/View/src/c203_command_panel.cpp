/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 14/03/2019
 * Last modify date: 14/03/2019
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
 * Last modify date: 14/03/2019
 *      Description: Construction function.
 ******************************************************************************/
Command_Panel::Command_Panel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Command_Panel)
{
    ui->setupUi(this);

    setWindowTitle("Command Panel");
    setFixedSize(480,465);
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
