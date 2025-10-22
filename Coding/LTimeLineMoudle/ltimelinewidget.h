#ifndef LTIMELINEWIDGET_H
#define LTIMELINEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "ltimelineexport.h"

class LTimelineRuler;
class QScrollBar;

class LTIMELINEEXPORT LTimelineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LTimelineWidget(QWidget *parent = nullptr);
    void addVideoClip(const QString &filePath, int track, qint64 startTimeMs, qint64 durationMs);
    void setZoomLevel(qreal level);
    qreal zoomLevel() const { return m_pixelsPerSecond; }
    void setPlayheadPosition(qint64 posMs);
    qint64 playheadPosition() const { return m_playheadPosition; }

signals:
    void playheadPositionChanged(qint64 positionMs);
    void clipSelected(int clipId);
    void clipMoved(int clipId, qint64 newStartMs);

public slots:
    void onPlayheadClicked(qint64 posMs);
    void onZoomIn();
    void onZoomOut();

private:
    void setupUi();
    void updatePlayhead();

private:
    LTimelineRuler *m_ruler;           // 时间标尺
    QGraphicsView *m_tracksView;       // 轨道视图
    QGraphicsScene *m_scene;           // 场景
    QScrollBar *m_horizontalScrollBar; // 水平滚动条
    
    qreal m_pixelsPerSecond;           // 时间缩放比例（像素/秒）
    qint64 m_playheadPosition;         // 播放头位置（毫秒）
    QGraphicsLineItem *m_playheadLine; // 播放头线条
    
    static constexpr int TRACK_HEIGHT = 80;
    static constexpr int TRACK_COUNT = 5;
};

#endif // LTIMELINEWIDGET_H
