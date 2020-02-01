#include "StartDialog.h"
#include "SettingsDialog.h"
#include <QtGui>
#include <QtWidgets>

#include "Settings.h"
#include "app.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Movement detection");
    m_app = App::createApp();
    QGroupBox* bgSubtrGroupBox = new QGroupBox(tr("Background Subtraction"));
    QLabel* historyLabel = new QLabel(tr("History length"));

    QSpinBox* historySpinBox = new QSpinBox();
    historySpinBox->setMinimum(10);
    historySpinBox->setMaximum(5000);
    historySpinBox->setFixedWidth(80);
    historySpinBox->setSingleStep(100);
    historySpinBox->setValue(500);
    connect(historySpinBox, SIGNAL(valueChanged(int)), this, SLOT(setHistoryLength(int)));

    QCheckBox* detectShadowCheckBox = new QCheckBox(tr("Detect Shadows"));
    detectShadowCheckBox->setChecked(true);
    connect(detectShadowCheckBox, SIGNAL(clicked(bool)), this, SLOT(setDetectShadows(bool)));

    QHBoxLayout* historyHLayout = new QHBoxLayout();
    historyHLayout->addWidget(historyLabel);
    historyHLayout->addWidget(historySpinBox);
    QPushButton* startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startMovementDetection()));

    QPushButton* browseButton = new QPushButton(tr("Browse"), this);
    connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(selectVideoFile()));

    QPushButton* settingsButton = new QPushButton(tr("Settings"));
    QVBoxLayout* buttonsVBLayout = new QVBoxLayout();
    buttonsVBLayout->addWidget(browseButton);
    buttonsVBLayout->addWidget(startButton);
    buttonsVBLayout->addWidget(settingsButton);
    connect(settingsButton, SIGNAL(clicked(bool)), this, SLOT(openSettingsDialog()));

    QVBoxLayout* bgSubVLayout = new QVBoxLayout();
    bgSubVLayout->addLayout(historyHLayout);
    bgSubVLayout->addWidget(detectShadowCheckBox);

    bgSubtrGroupBox->setLayout(bgSubVLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(bgSubtrGroupBox);
    mainLayout->addLayout(buttonsVBLayout);

    setLayout(mainLayout);
}

void StartDialog::setHistoryLength(int historyLength)
{
    m_app->m_settings->m_historyLength = historyLength;
}

void StartDialog::setDetectShadows(bool enabled)
{
    m_app->m_settings->m_detectShadows = enabled;
}

void StartDialog::openSettingsDialog()
{
    SettingsDialog* settingsDialog = new SettingsDialog();
    settingsDialog->show();
}

void StartDialog::startMovementDetection()
{
    if (m_app->m_videoFileName.isEmpty()) {
        QMessageBox::warning(this, tr("Movement Detection"), tr("Please select the video file!"),
                                        QMessageBox::Ok);
    } else {
        m_app->StartApp();
    }
}

void StartDialog::selectVideoFile()
{
    QString fileName =  QFileDialog::getOpenFileName(this,
                                        tr("Open Video File"), "/home", tr("Video Files (*.mp4 *.avi)"));

    if (!fileName.isEmpty()) {
        m_app->setVideoFileName(fileName);
    }
}
