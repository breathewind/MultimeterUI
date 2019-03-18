/******************************************************************************
 *           Author: Wenlong Wang
 *      Create date: 22/02/2019
 * Last modify date: 18/03/2019
 *      Description: Main window controller.
 *                   - Functional slots.
 ******************************************************************************/
#include "../inc/c999_maincontroller.h"

/******************************************************************************
 *             Name: slot_update_data_from_settings
 *      Function ID: 750
 *      Create date: 22/02/2019
 * Last modify date: 18/03/2019
 *      Description: Slot for updating data from settings dialog to main
 *                   controller.
 ******************************************************************************/
void MainController::slot_update_data_from_settings()
{
    QStringList data_set = _settings_dialog->retrieveDMM_data();

    _dmm_baudrate = data_set.at(SERIAL_INDEX_BAUDRATE);
    _dmm_databits = data_set.at(SERIAL_INDEX_DATABITS);
    _dmm_stopbits = data_set.at(SERIAL_INDEX_STOPBITS);
    _dmm_parity = data_set.at(SERIAL_INDEX_PARITY);
    _dmm_flowcontrol = data_set.at(SERIAL_INDEX_FLOWCONTROL);
    _dmm_port = data_set.at(SERIAL_INDEX_PORT);

#ifdef MAINCONTROLLER_DEBUG
    debug_printSerial_information();
#endif
}
