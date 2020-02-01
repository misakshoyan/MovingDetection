#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QListWidget;
class QRadioButton;
class QStackedLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGroupBox* m_bgSubtrGroupBox;
    QLabel*    m_historyLabel;
    QLineEdit* m_historyLineEdit;
    QLabel*    m_detectShadowLabel;
    QLineEdit* m_detectShadowLineEdit;


};

#endif // MAINWINDOW_H
