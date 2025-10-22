#ifndef LLIBRARYTOPBUTTONPANNEL_H
#define LLIBRARYTOPBUTTONPANNEL_H

#include <QWidget>
#include <QPushButton>
#include "llibraryexport.h"

namespace Ui {
class LLibraryTopButtonPannel;
}

class LLIBARYEXPORT LLibraryTopButtonPannel : public QWidget
{
    Q_OBJECT
public:
    explicit LLibraryTopButtonPannel(QWidget *parent = nullptr);
    ~LLibraryTopButtonPannel();

signals:
    void pageChanged(int index);  // 发送页面切换信号

private slots:
    void onImportClicked();
    void onLibraryClicked();
    void onPreviewClicked();
    void onPropertyClicked();
    void onTimelineClicked();

private:
    void setupUI();
    void createConnections();
    void setActiveButton(QPushButton *activeBtn);

private:
    Ui::LLibraryTopButtonPannel *ui;
    QPushButton *m_currentActiveButton;
};

#endif // LLIBRARYTOPBUTTONPANNEL_H