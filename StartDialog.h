#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

class App;

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    StartDialog(QWidget *parent = NULL);

private slots:
    void setHistoryLength(int historyLength);
    void setDetectShadows(bool enabled);
    void selectVideoFile();
    void openSettingsDialog();
    void startMovementDetection();

private:
    App* m_app;
};

#endif // STARTDIALOG_H
