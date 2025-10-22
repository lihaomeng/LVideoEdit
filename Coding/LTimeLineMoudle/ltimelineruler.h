#ifndef LTIMELINERULER_H
#define LTIMELINERULER_H

#include <QWidget>
#include "ltimelineexport.h"

class LTIMELINEEXPORT LTimelineRuler : public QWidget
{
    Q_OBJECT
public:
    explicit LTimelineRuler(QWidget *parent = nullptr);
    
    void setPixelsPerSecond(qreal pps);
    void setPlayheadPosition(qint64 posMs);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    
signals:
    void playheadClicked(qint64 posMs);

private:
    QString formatTime(int totalSeconds) const;

private:
    qreal m_pixelsPerSecond;
    qint64 m_playheadPos;
};

#endif // LTIMELINERULER_H
