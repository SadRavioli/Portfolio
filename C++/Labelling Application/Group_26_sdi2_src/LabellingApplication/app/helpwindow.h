#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>

namespace Ui {
/**
* @brief Launch the help window
*
*/
class helpwindow;
}

class helpwindow : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the helpwindow class
     * Provides instructions on how to use the app
     *
     * @param parent
     */
    explicit helpwindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor for the helpwindow class
     *
     */
    ~helpwindow();

private:
    Ui::helpwindow *ui;
};

#endif // HELPWINDOW_H
