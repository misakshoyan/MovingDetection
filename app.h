#ifndef APP_H
#define APP_H

#include <QObject>
#include "Settings.h"
#include "Blob.h"

class App : public QObject
{
    Q_OBJECT

private:
    App();

public:
    void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);

    void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);

    void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);

    double distanceBetweenPoints(cv::Point point1, cv::Point point2);

    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);

    void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName);

    void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);

    std::pair<cv::Point, cv::Point> getDirectionLineStartEndPoints(Blob &blob);

    void drawDirectionLine(cv::Mat &img, std::pair<cv::Point, cv::Point> startEndPositions);

    static App* createApp();

    void setVideoFileName(QString fileName);

public slots:
    void StartApp();

public:
    Settings* m_settings;
    QString m_videoFileName;

private:
    static App* s_instance;
};

#endif // APP_H
