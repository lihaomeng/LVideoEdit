#include "ltimelineruler.h"
#include <QPainter>
#include <QMouseEvent>

LTimelineRuler::LTimelineRuler(QWidget *parent)
    : QWidget(parent)
    , m_pixelsPerSecond(100.0)
    , m_playheadPos(0)
{
    setFixedHeight(30);
    setMinimumWidth(1000);
    setCursor(Qt::PointingHandCursor);
}

void LTimelineRuler::setPixelsPerSecond(qreal pps)
{
    m_pixelsPerSecond = pps;
    update();
}

void LTimelineRuler::setPlayheadPosition(qint64 posMs)
{
    m_playheadPos = posMs;
    update();
}

void LTimelineRuler::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(30, 30, 30));
    painter.setPen(QColor(180, 180, 180));
    QFont font = painter.font();
    font.setPixelSize(9);
    painter.setFont(font);
    int totalSeconds = width() / m_pixelsPerSecond + 1;
    for (int sec = 0; sec <= totalSeconds; ++sec)
    {
        int x = sec * m_pixelsPerSecond;
        if (x > width())
            break;
        
        painter.setPen(QColor(150, 150, 150));
        painter.drawLine(x, height() - 8, x, height());
        if (sec % 5 == 0)
        {
            painter.setPen(QColor(200, 200, 200));
            QString timeText = formatTime(sec);
            painter.drawText(x + 3, 14, timeText);
        }
        painter.setPen(QColor(100, 100, 100));
        int halfX = x + m_pixelsPerSecond / 2;
        if (halfX < width())
            painter.drawLine(halfX, height() - 4, halfX, height());
        if (m_pixelsPerSecond >= 100) 
        {
            for (int i = 1; i < 10; ++i)
            {
                if (i == 5)
                    continue;

                int smallX = x + (m_pixelsPerSecond * i / 10);
                if (smallX < width())
                    painter.drawLine(smallX, height() - 2, smallX, height());
            }
        }
    }
    
    int playheadX = (m_playheadPos / 1000.0) * m_pixelsPerSecond;
    if (playheadX >= 0 && playheadX <= width())
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255, 0, 0));
        QPolygon triangle;
        triangle << QPoint(playheadX, height()) << QPoint(playheadX - 6, height() - 10) << QPoint(playheadX + 6, height() - 10);
        painter.drawPolygon(triangle);
        painter.setPen(Qt::white);
        QString timeText = formatTime(m_playheadPos / 1000);
        QRect textRect(playheadX - 30, 0, 60, 12);
        painter.fillRect(textRect, QColor(255, 0, 0, 200));
        painter.drawText(textRect, Qt::AlignCenter, timeText);
    }
}

void LTimelineRuler::mousePressEvent(QMouseEvent *event)
{
    int clickX = event->pos().x();
    qint64 timeMs = (clickX / m_pixelsPerSecond) * 1000;
    emit playheadClicked(timeMs);
}

void LTimelineRuler::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int clickX = event->pos().x();
        qint64 timeMs = (clickX / m_pixelsPerSecond) * 1000;
        emit playheadClicked(timeMs);
    }
}

QString LTimelineRuler::formatTime(int totalSeconds) const
{
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    
    if (hours > 0)
    {
        return QString("%1:%2:%3")
            .arg(hours)
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    }
    else
    {
        return QString("%1:%2")
            .arg(minutes)
            .arg(seconds, 2, 10, QChar('0'));
    }
}
