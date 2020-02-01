#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    Settings() {}

    static Settings* createSettings();

public:
    bool    m_detectShadows = true;
    int     m_historyLength = 500;
    bool    m_isGaussianBlur = false;
    bool    m_isMedianBlur = true;
    int     m_minBoundingRectArea = 100;
    double  m_minBoundingRectAspectRatio = 0.2;
    double  m_maxBoundingRectAspectRatio = 1.25;
    int     m_minBoundingRectWidth = 20;
    int     m_minBoundingRectHeight = 20;
    double  m_minBoundingRectDiagonalSize = 30.0;
    double  m_minContourSizeDivBoundingRect = 0.4;
    double  m_maxDistanceCoefficient = 1.15;
    bool    m_drawDirectionLine = true;
    bool    m_showObjectNumber = true;
    int     m_speedLevel = 1;

private:
    static Settings* s_instance;
};

#endif // SETTINGS_H

