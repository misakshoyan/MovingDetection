#include "SettingsDialog.h"
#include <QtGui>
#include <QtWidgets>
#include "Settings.h"
#include "app.h"
#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Settings");
    m_app = App::createApp();
    QRadioButton* gaussianRadioBtn = new QRadioButton(tr("Gaussian Blur"));
    QRadioButton* medianRadioBtn = new QRadioButton(tr("Median blur"));
    medianRadioBtn->setChecked(true);

    QGroupBox* blurGroupBox = new QGroupBox(tr("Blur types"));
    QVBoxLayout* blurVBLayout = new QVBoxLayout();
    blurVBLayout->addWidget(gaussianRadioBtn);
    blurVBLayout->addWidget(medianRadioBtn);
    blurGroupBox->setLayout(blurVBLayout);

    connect(gaussianRadioBtn, SIGNAL(clicked(bool)), this, SLOT(setGaussianBlur(bool)));
    connect(medianRadioBtn, SIGNAL(clicked(bool)), this, SLOT(setMedianBlur(bool)));


    QSpinBox* minAreaSpinBox = new QSpinBox();
    minAreaSpinBox->setMinimum(1);
    minAreaSpinBox->setMaximum(100000);
    minAreaSpinBox->setFixedWidth(80);
    minAreaSpinBox->setValue(100);
    minAreaSpinBox->setSingleStep(100);
    QLabel* minAreaLabel = new QLabel(tr("Min Area"));
    QHBoxLayout* minAreaHBLayout = new QHBoxLayout();
    minAreaHBLayout->addWidget(minAreaLabel);
    minAreaHBLayout->addWidget(minAreaSpinBox);
    connect(minAreaSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMinBoundingRectArea(int)));


    QSpinBox* minWidthSpinBox = new QSpinBox();
    minWidthSpinBox->setMinimum(1);
    minWidthSpinBox->setMaximum(500);
    minWidthSpinBox->setFixedWidth(80);
    minWidthSpinBox->setValue(20);
    minWidthSpinBox->setSingleStep(10);
    QLabel* minWidthLabel = new QLabel(tr("Min Width"));
    QHBoxLayout* minWidthHBLayout = new QHBoxLayout();
    minWidthHBLayout->addWidget(minWidthLabel);
    minWidthHBLayout->addWidget(minWidthSpinBox);
    connect(minWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMinBoundingRectWidth(int)));


    QSpinBox* minHeightSpinBox = new QSpinBox();
    minHeightSpinBox->setMinimum(1);
    minHeightSpinBox->setMaximum(500);
    minHeightSpinBox->setFixedWidth(80);
    minHeightSpinBox->setValue(20);
    minHeightSpinBox->setSingleStep(10);
    QLabel* minHeightLabel = new QLabel(tr("Min Height"));
    QHBoxLayout* minHeightHBLayout = new QHBoxLayout();
    minHeightHBLayout->addWidget(minHeightLabel);
    minHeightHBLayout->addWidget(minHeightSpinBox);
    connect(minHeightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMinBoundingRectHeight(int)));


    QDoubleSpinBox* minDiagonalSizeSpinBox = new QDoubleSpinBox();
    minDiagonalSizeSpinBox->setMinimum(1);
    minDiagonalSizeSpinBox->setMaximum(800);
    minDiagonalSizeSpinBox->setFixedWidth(80);
    minDiagonalSizeSpinBox->setValue(30);
    minDiagonalSizeSpinBox->setSingleStep(10);
    QLabel* minDiagonalSizeLabel = new QLabel(tr("Min Diagonal Size"));
    QHBoxLayout* minDiagonalSizeHBLayout = new QHBoxLayout();
    minDiagonalSizeHBLayout->addWidget(minDiagonalSizeLabel);
    minDiagonalSizeHBLayout->addWidget(minDiagonalSizeSpinBox);
    connect(minDiagonalSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMinBoundingRectDiagonalSize(double)));


    QDoubleSpinBox* minAspectRatioSpinBox = new QDoubleSpinBox();
    minAspectRatioSpinBox->setMinimum(0.01);
    minAspectRatioSpinBox->setFixedWidth(80);
    minAspectRatioSpinBox->setValue(0.2);
    minAspectRatioSpinBox->setSingleStep(0.1);
    QLabel* minAspectRatioLabel = new QLabel(tr("Min Aspect Ratio"));
    QHBoxLayout* minAspectRatioHBLayout = new QHBoxLayout();
    minAspectRatioHBLayout->addWidget(minAspectRatioLabel);
    minAspectRatioHBLayout->addWidget(minAspectRatioSpinBox);
    connect(minAspectRatioSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMinBoundingRectAspectRatio(double)));


    QDoubleSpinBox* maxAspectRatioSpinBox = new QDoubleSpinBox();
    maxAspectRatioSpinBox->setMinimum(0.01);
    maxAspectRatioSpinBox->setMaximum(10000);
    maxAspectRatioSpinBox->setFixedWidth(80);
    maxAspectRatioSpinBox->setValue(1.25);
    maxAspectRatioSpinBox->setSingleStep(0.1);
    QLabel* maxAspectRatioLabel = new QLabel(tr("Max Aspect Ratio"));
    QHBoxLayout* maxAspectRatioHBLayout = new QHBoxLayout();
    maxAspectRatioHBLayout->addWidget(maxAspectRatioLabel);
    maxAspectRatioHBLayout->addWidget(maxAspectRatioSpinBox);
    connect(maxAspectRatioSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMaxBoundingRectAspectRatio(double)));


    QVBoxLayout* boundingRectVBLayout = new QVBoxLayout();
    boundingRectVBLayout->addLayout(minAreaHBLayout);
    boundingRectVBLayout->addLayout(minWidthHBLayout);
    boundingRectVBLayout->addLayout(minHeightHBLayout);
    boundingRectVBLayout->addLayout(minDiagonalSizeHBLayout);
    boundingRectVBLayout->addLayout(minAspectRatioHBLayout);
    boundingRectVBLayout->addLayout(maxAspectRatioHBLayout);

    QGroupBox* boundingRectGroupBox = new QGroupBox(tr("Object's Bounding Rect"));
    boundingRectGroupBox->setLayout(boundingRectVBLayout);


    QLabel* predictionLabel = new QLabel(tr("Object's max distance between current position"
                                                " and predicted position of previous frame "));
    QLabel* diagSizeMultByLabel = new QLabel(tr("[min diagonal size of object's bounding rect] multiplied by: "));
    QDoubleSpinBox* multipliedValueSpinBox = new QDoubleSpinBox();
    multipliedValueSpinBox->setMinimum(0.01);
    multipliedValueSpinBox->setFixedWidth(80);
    multipliedValueSpinBox->setValue(1.25);
    multipliedValueSpinBox->setSingleStep(0.05);
    QHBoxLayout* predictionHBLayout = new QHBoxLayout();
    predictionHBLayout->addWidget(diagSizeMultByLabel);
    predictionHBLayout->addWidget(multipliedValueSpinBox);

    QVBoxLayout* predictionVBMainLayout = new QVBoxLayout();
    predictionVBMainLayout->addWidget(predictionLabel);
    predictionVBMainLayout->addLayout(predictionHBLayout);

    QGroupBox* predictionGroupBox = new QGroupBox(tr("Prediction of object's next position"));
    predictionGroupBox->setLayout(predictionVBMainLayout);
    connect(multipliedValueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMaxDistanceCoefficient(double)));


    QLabel* contourAreaComparedWithBoundRectAreaLabel = new QLabel(tr("Minimum coefficient of object's area "
                                                                      "divided by its bounding rect area"));
    QDoubleSpinBox* areaCoefficientSpinBox = new QDoubleSpinBox();
    areaCoefficientSpinBox->setMinimum(0.01);
    areaCoefficientSpinBox->setMaximum(1);
    areaCoefficientSpinBox->setFixedWidth(80);
    areaCoefficientSpinBox->setValue(0.4);
    areaCoefficientSpinBox->setSingleStep(0.05);
    QHBoxLayout* coefficientHBLayout = new QHBoxLayout();
    coefficientHBLayout->addWidget(contourAreaComparedWithBoundRectAreaLabel);
    coefficientHBLayout->addWidget(areaCoefficientSpinBox);

    QGroupBox* areaCoefficientGroupBox = new QGroupBox(tr("Area of object compared with "
                                                          "area of object's bounding box"));
    areaCoefficientGroupBox->setLayout(coefficientHBLayout);
    connect(areaCoefficientSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMinContourSizeDivBoundingRect(double)));

    //Drawing settings
    QCheckBox* drawDirectionLineCheckBox = new QCheckBox(tr("Draw direction line"));
    drawDirectionLineCheckBox->setChecked(true);
    QCheckBox* showObjectNumberCheckBox = new QCheckBox(tr("Show object's number"));
    showObjectNumberCheckBox->setChecked(true);

    QHBoxLayout* drawingHBLayout = new QHBoxLayout();
    drawingHBLayout->addWidget(drawDirectionLineCheckBox);
    drawingHBLayout->addWidget(showObjectNumberCheckBox);

    QGroupBox* drawingGroupBox = new QGroupBox(tr("Drawing settings"));
    drawingGroupBox->setLayout(drawingHBLayout);

    connect(drawDirectionLineCheckBox, SIGNAL(clicked(bool)), this, SLOT(setDrawDirectionLine(bool)));
    connect(showObjectNumberCheckBox, SIGNAL(clicked(bool)), this, SLOT(setObjectNumber(bool)));

    //Video settings
    QLabel* pauseLabel    = new QLabel(tr("   \"p\"     key  -  pause video"));
    QLabel* continueLabel = new QLabel(tr("\"Enter\" key  -  continue video after pause"));

    QLabel* speedLevelLabel = new QLabel(tr("Speed level"));
    QSpinBox* speedLevelSpinBox = new QSpinBox();
    speedLevelSpinBox->setMinimum(1);
    speedLevelSpinBox->setMaximum(6);
    speedLevelSpinBox->setFixedWidth(80);
    speedLevelSpinBox->setValue(1);
    QHBoxLayout* speedLevelHBLayout = new QHBoxLayout();
    speedLevelHBLayout->addWidget(speedLevelLabel);
    speedLevelHBLayout->addWidget(speedLevelSpinBox);

    QVBoxLayout* pauseSettingsVBLayout = new QVBoxLayout();
    pauseSettingsVBLayout->addWidget(pauseLabel);
    pauseSettingsVBLayout->addWidget(continueLabel);

    QHBoxLayout* videoSettingsHBLayout = new QHBoxLayout();
    videoSettingsHBLayout->addLayout(pauseSettingsVBLayout);
    videoSettingsHBLayout->addSpacing(100);
    videoSettingsHBLayout->addLayout(speedLevelHBLayout);

    QGroupBox* videoSettingsGroupBox = new QGroupBox(tr("Video settings"));
    videoSettingsGroupBox->setLayout(videoSettingsHBLayout);

    connect(speedLevelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSpeedLevel(int)));


    QHBoxLayout* firstLayout = new QHBoxLayout();
    firstLayout->addWidget(blurGroupBox);
    firstLayout->addWidget(boundingRectGroupBox);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(firstLayout);
    mainLayout->addWidget(predictionGroupBox);
    mainLayout->addWidget(areaCoefficientGroupBox);
    mainLayout->addWidget(drawingGroupBox);
    mainLayout->addWidget(videoSettingsGroupBox);

    setLayout(mainLayout);
}

void SettingsDialog::setGaussianBlur(bool enabled)
{
    m_app->m_settings->m_isGaussianBlur = enabled;
    m_app->m_settings->m_isMedianBlur = !enabled;
}

void SettingsDialog::setMedianBlur(bool enabled)
{
    m_app->m_settings->m_isMedianBlur = enabled;
    m_app->m_settings->m_isGaussianBlur = !enabled;
}

void SettingsDialog::setMinBoundingRectArea(int area)
{
    m_app->m_settings->m_minBoundingRectArea = area;
}

void SettingsDialog::setMinBoundingRectAspectRatio(double minAspectRatio)
{
    m_app->m_settings->m_minBoundingRectAspectRatio = minAspectRatio;
}

void SettingsDialog::setMaxBoundingRectAspectRatio(double maxAspectRatio)
{
    m_app->m_settings->m_maxBoundingRectAspectRatio = maxAspectRatio;
}

void SettingsDialog::setMinBoundingRectWidth(int width)
{
    m_app->m_settings->m_minBoundingRectWidth = width;
}

void SettingsDialog::setMinBoundingRectHeight(int height)
{
    m_app->m_settings->m_minBoundingRectHeight = height;
}

void SettingsDialog::setMinBoundingRectDiagonalSize(double diagonalSize)
{
    m_app->m_settings->m_minBoundingRectDiagonalSize = diagonalSize;
}

void SettingsDialog::setMinContourSizeDivBoundingRect(double coefficient)
{
    m_app->m_settings->m_minContourSizeDivBoundingRect = coefficient;
}

void SettingsDialog::setDrawDirectionLine(bool enabled)
{
    m_app->m_settings->m_drawDirectionLine = enabled;
}

void SettingsDialog::setObjectNumber(bool enabled)
{
    m_app->m_settings->m_showObjectNumber = enabled;
}

void SettingsDialog::setMaxDistanceCoefficient(double coefficient)
{
    m_app->m_settings->m_maxDistanceCoefficient = coefficient;
}

void SettingsDialog::setSpeedLevel(int level)
{
    m_app->m_settings->m_speedLevel = level;
}

