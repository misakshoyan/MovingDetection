#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class App;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = NULL);

private slots:
    void setGaussianBlur(bool enabled);
    void setMedianBlur(bool enabled);
    void setMinBoundingRectArea(int area);
    void setMinBoundingRectAspectRatio(double minAspectRatio);
    void setMaxBoundingRectAspectRatio(double maxAspectRatio);
    void setMinBoundingRectWidth(int width);
    void setMinBoundingRectHeight(int height);
    void setMinBoundingRectDiagonalSize(double diagonalSize);
    void setMinContourSizeDivBoundingRect(double coefficient);
    void setDrawDirectionLine(bool enabled);
    void setObjectNumber(bool enabled);
    void setMaxDistanceCoefficient(double coefficient);
    void setSpeedLevel(int level);

private:
    App* m_app;
};

#endif // SETTINGSDIALOG_H
