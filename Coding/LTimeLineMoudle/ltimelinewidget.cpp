#include "ltimelinewidget.h"
#include "ltimelineruler.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QGraphicsLineItem>
#include <QPen>

LTimelineWidget::LTimelineWidget(QWidget *parent)
    : QWidget(parent)
    , m_ruler(nullptr)
    , m_tracksView(nullptr)
    , m_scene(nullptr)
    , m_horizontalScrollBar(nullptr)
    , m_pixelsPerSecond(100.0)
    , m_playheadPosition(0)
    , m_playheadLine(nullptr)
{
    setupUi();
}

void LTimelineWidget::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_ruler = new LTimelineRuler(this);
    m_ruler->setPixelsPerSecond(m_pixelsPerSecond);
    connect(m_ruler, &LTimelineRuler::playheadClicked, this, &LTimelineWidget::onPlayheadClicked);
    m_scene = new QGraphicsScene(this);
    m_scene->setBackgroundBrush(QColor(45, 45, 48));
    int sceneWidth = 60 * m_pixelsPerSecond;
    int sceneHeight = TRACK_COUNT * TRACK_HEIGHT;
    m_scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    QPen trackLinePen(QColor(80, 80, 80), 1);
    for (int i = 0; i <= TRACK_COUNT; ++i)
    {
        int y = i * TRACK_HEIGHT;
        m_scene->addLine(0, y, sceneWidth, y, trackLinePen);
    }
    m_playheadLine = m_scene->addLine(0, 0, 0, sceneHeight, QPen(QColor(255, 0, 0), 2));
    m_playheadLine->setZValue(1000);

    m_tracksView = new QGraphicsView(m_scene, this);
    m_tracksView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_tracksView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tracksView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_tracksView->setDragMode(QGraphicsView::RubberBandDrag);

    m_horizontalScrollBar = new QScrollBar(Qt::Horizontal, this);
    m_horizontalScrollBar->setRange(0, sceneWidth - m_tracksView->viewport()->width());
    connect(m_horizontalScrollBar, &QScrollBar::valueChanged, m_tracksView->horizontalScrollBar(), &QScrollBar::setValue);
    connect(m_tracksView->horizontalScrollBar(), &QScrollBar::valueChanged, m_horizontalScrollBar, &QScrollBar::setValue);
    mainLayout->addWidget(m_ruler);
    mainLayout->addWidget(m_tracksView);
    mainLayout->addWidget(m_horizontalScrollBar);
}

void LTimelineWidget::addVideoClip(const QString &filePath, int track, qint64 startTimeMs, qint64 durationMs)
{
    if (track < 0 || track >= TRACK_COUNT)
        return;

    qreal x = (startTimeMs / 1000.0) * m_pixelsPerSecond;
    qreal y = track * TRACK_HEIGHT;
    qreal width = (durationMs / 1000.0) * m_pixelsPerSecond;
    qreal height = TRACK_HEIGHT - 4;
    auto *clipRect = m_scene->addRect(x, y + 2, width, height, QPen(QColor(100, 150, 200)), QBrush(QColor(60, 90, 120)));
    clipRect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    QString fileName = filePath.section('/', -1);
    auto *text = m_scene->addText(fileName);
    text->setDefaultTextColor(Qt::white);
    text->setPos(x + 5, y + 10);
    text->setParentItem(clipRect);
}

void LTimelineWidget::setZoomLevel(qreal level)
{
    m_pixelsPerSecond = qBound(20.0, level, 500.0);
    m_ruler->setPixelsPerSecond(m_pixelsPerSecond);
    int sceneWidth = 60 * m_pixelsPerSecond;
    m_scene->setSceneRect(0, 0, sceneWidth, TRACK_COUNT * TRACK_HEIGHT);
    updatePlayhead();
}

void LTimelineWidget::setPlayheadPosition(qint64 posMs)
{
    m_playheadPosition = posMs;
    updatePlayhead();
    emit playheadPositionChanged(posMs);
}

void LTimelineWidget::onPlayheadClicked(qint64 posMs)
{
    setPlayheadPosition(posMs);
}

void LTimelineWidget::onZoomIn()
{
    setZoomLevel(m_pixelsPerSecond * 1.2);
}

void LTimelineWidget::onZoomOut()
{
    setZoomLevel(m_pixelsPerSecond / 1.2);
}

void LTimelineWidget::updatePlayhead()
{
    qreal x = (m_playheadPosition / 1000.0) * m_pixelsPerSecond;
    m_playheadLine->setLine(x, 0, x, TRACK_COUNT * TRACK_HEIGHT);
    m_ruler->setPlayheadPosition(m_playheadPosition);
}
