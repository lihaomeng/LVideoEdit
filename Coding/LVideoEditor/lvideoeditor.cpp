#include <QFrame>
#include <QLabel>
#include <QString>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include "lvideoeditor.h"
#include "llibrarytopbuttonpannel.h"
#include "ltimelinewidget.h"

namespace {
constexpr int kDefaultWidth = 2000;
constexpr int kDefaultHeight = 1240;
constexpr int kContentMargin = 12;
}

LVideoEditorMainWindow::LVideoEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("LVideoEditor"));
    resize(kDefaultWidth, kDefaultHeight);
    setupUi();
}

// void LVideoEditorMainWindow::setupUi()
// {
//     auto *mainToolBar = addToolBar(tr("MainBar"));
//     mainToolBar->setMovable(false);
//     mainToolBar->addAction(tr("importVideo"));
//     mainToolBar->addAction(tr("exportVideo"));

//     auto *central = new QWidget(this);
//     auto *mainLayout = new QVBoxLayout(central);
//     mainLayout->setContentsMargins(kContentMargin, kContentMargin, kContentMargin, kContentMargin);
//     mainLayout->setSpacing(8);

//     pContentSplitter = new QSplitter(Qt::Horizontal, central);
//     pContentSplitter->setChildrenCollapsible(false);
//     //TODO
//     pLibraryFrame = new LLibraryTopButtonPannel(this);
//     pLibraryFrame->setFixedSize(850, 300);

//     pPrevieFrame = createPanel(tr("previewPanel"));
//     pPrevieFrame->setFixedSize(850, 300);

//     pPropertyFrame = createPanel(tr("propertyPanel"));
//     pPropertyFrame->setFixedSize(850, 300);

//     pContentSplitter->setHandleWidth(6);
//     pContentSplitter->addWidget(pLibraryFrame);
//     pContentSplitter->addWidget(pPrevieFrame);
//     pContentSplitter->addWidget(pPropertyFrame);
//     pContentSplitter->setStretchFactor(0, 1);
//     pContentSplitter->setStretchFactor(1, 2);
//     pContentSplitter->setStretchFactor(2, 1);

//     pTimelineFrame = createPanel(tr("timelinePanel"));
//     pTimelineFrame->setMinimumHeight(320);
//     pTimelineFrame->setMaximumHeight(320);
//     auto *verticalSplitter = new QSplitter(Qt::Vertical, central);
//     verticalSplitter->setChildrenCollapsible(false);
//     verticalSplitter->setHandleWidth(6);
//     verticalSplitter->addWidget(pContentSplitter); //3 content 
//     verticalSplitter->addWidget(pTimelineFrame);   //timeLine
//     verticalSplitter->setStretchFactor(0, 7);
//     verticalSplitter->setStretchFactor(1, 3);
//     mainLayout->addWidget(verticalSplitter);
//     setCentralWidget(central);
// }

void LVideoEditorMainWindow::setupUi()
{
    auto *mainToolBar = addToolBar(tr("MainBar"));
    mainToolBar->setMovable(false);
    mainToolBar->addAction(tr("importVideo"));
    mainToolBar->addAction(tr("exportVideo"));

    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(kContentMargin, kContentMargin, kContentMargin, kContentMargin);
    mainLayout->setSpacing(8);

    pContentSplitter = new QSplitter(Qt::Horizontal, central);
    pContentSplitter->setChildrenCollapsible(false);
    pContentSplitter->setHandleWidth(6);

    pLibraryFrame = new QWidget(this);
    auto *libraryLayout = new QVBoxLayout(pLibraryFrame);
    libraryLayout->setContentsMargins(0, 0, 0, 0);
    libraryLayout->setSpacing(0);
    
    auto *libraryTopButtons = new LLibraryTopButtonPannel(this);
    auto *libraryStack = new QStackedWidget(this);
    libraryStack->addWidget(createPanel(tr("导入")));
    libraryStack->addWidget(createPanel(tr("媒体库")));
    libraryStack->addWidget(createPanel(tr("效果")));
    
    libraryLayout->addWidget(libraryTopButtons);
    libraryLayout->addWidget(libraryStack);
    
    connect(libraryTopButtons, &LLibraryTopButtonPannel::pageChanged, 
            libraryStack, &QStackedWidget::setCurrentIndex);

    pPrevieFrame = createPanel(tr("预览窗口"));
    pPrevieFrame->setMinimumSize(480, 270);  // 最小 16:9 预览尺寸

    pPropertyFrame = createPanel(tr("属性面板"));
    pPropertyFrame->setMinimumWidth(220);

    pContentSplitter->addWidget(pLibraryFrame);
    pContentSplitter->addWidget(pPrevieFrame);
    pContentSplitter->addWidget(pPropertyFrame);
    
    // ✅ 设置初始宽度比例：素材库(1) : 预览(3) : 属性(1)
    pContentSplitter->setStretchFactor(0, 1);
    pContentSplitter->setStretchFactor(1, 3);
    pContentSplitter->setStretchFactor(2, 1);
    auto *verticalSplitter = new QSplitter(Qt::Vertical, central);
    verticalSplitter->setChildrenCollapsible(false);
    verticalSplitter->setHandleWidth(6);

    // timeline
    pTimelineWidget = new LTimelineWidget(this);
    pTimelineWidget->setMinimumHeight(200);
    pTimelineWidget->setMaximumHeight(400);
    
    connect(pTimelineWidget, &LTimelineWidget::playheadPositionChanged,this, &LVideoEditorMainWindow::onPlayheadChanged);
    
    pTimelineWidget->addVideoClip("example1.mp4", 0, 0, 5000);
    pTimelineWidget->addVideoClip("example2.mp4", 0, 6000, 3000);
    pTimelineWidget->addVideoClip("audio.mp3", 1, 2000, 8000);
    // timeline

    verticalSplitter->addWidget(pContentSplitter);
    verticalSplitter->addWidget(pTimelineWidget);
    
    
    verticalSplitter->setStretchFactor(0, 7);
    verticalSplitter->setStretchFactor(1, 3);

    mainLayout->addWidget(verticalSplitter);
    setCentralWidget(central);
}

void LVideoEditorMainWindow::onPlayheadChanged(qint64 positionMs)
{
    // 这里可以更新预览窗口、播放视频等
    // qDebug() << "Playhead position:" << positionMs << "ms";
}

QWidget *LVideoEditorMainWindow::createPanel(const QString &title)
{
    auto *panel = new QFrame(this);
    
    panel->setFrameShape(QFrame::StyledPanel);
    panel->setObjectName(QStringLiteral("panel_%1").arg(title));

    auto *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setSpacing(6);

    auto *label = new QLabel(title, panel);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addStretch();

    return panel;
}
