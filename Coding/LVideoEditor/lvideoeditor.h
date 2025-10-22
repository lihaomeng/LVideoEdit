#ifndef LVIDEOEDITOR_H
#define LVIDEOEDITOR_H

#include <QMainWindow>
#include <QSplitter>

class QWidget;
class QString;
class LLibraryTopButtonPannel;
class LTimelineWidget;

class LVideoEditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LVideoEditorMainWindow(QWidget *parent = nullptr);

private slots:
    void onPlayheadChanged(qint64 positionMs);

private:
    void setupUi();
    QWidget *createPanel(const QString &title);

private:
    QSplitter *pContentSplitter = nullptr;

    QWidget *pLibraryFrame = nullptr;
    QWidget *pPrevieFrame  = nullptr;
    QWidget *pPropertyFrame  = nullptr;
    LTimelineWidget *pTimelineWidget  = nullptr;
};

#endif // LVIDEOEDITOR_H