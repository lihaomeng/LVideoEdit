#include "llibrarytopbuttonpannel.h"
#include "ui_llibrarytopbuttonpannel.h"

LLibraryTopButtonPannel::LLibraryTopButtonPannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LLibraryTopButtonPannel)
    , m_currentActiveButton(nullptr)
{
    ui->setupUi(this);
    setupUI();
    createConnections();
}

LLibraryTopButtonPannel::~LLibraryTopButtonPannel()
{
    delete ui;
}

void LLibraryTopButtonPannel::setupUI()
{
    // 设置按钮样式（可选）
    QString normalStyle = "QPushButton { "
                         "background-color: #f0f0f0; "
                         "border: 1px solid #c0c0c0; "
                         "border-radius: 4px; "
                         "padding: 5px; "
                         "} "
                         "QPushButton:hover { "
                         "background-color: #e0e0e0; "
                         "}";
    
    QString activeStyle = "QPushButton { "
                         "background-color: #0078d7; "
                         "color: white; "
                         "border: 1px solid #0078d7; "
                         "border-radius: 4px; "
                         "padding: 5px; "
                         "}";
    ui->btn_import->setStyleSheet(normalStyle);
    ui->btn_library->setStyleSheet(normalStyle);
    ui->btn_preview->setStyleSheet(normalStyle);
    ui->btn_property->setStyleSheet(normalStyle);
    ui->btn_timeline->setStyleSheet(normalStyle);
    setActiveButton(ui->btn_library);
}

void LLibraryTopButtonPannel::createConnections()
{
    connect(ui->btn_import, &QPushButton::clicked, this, &LLibraryTopButtonPannel::onImportClicked);
    connect(ui->btn_library, &QPushButton::clicked, this, &LLibraryTopButtonPannel::onLibraryClicked);
    connect(ui->btn_preview, &QPushButton::clicked, this, &LLibraryTopButtonPannel::onPreviewClicked);
    connect(ui->btn_property, &QPushButton::clicked, this, &LLibraryTopButtonPannel::onPropertyClicked);
    connect(ui->btn_timeline, &QPushButton::clicked, this, &LLibraryTopButtonPannel::onTimelineClicked);
}

void LLibraryTopButtonPannel::setActiveButton(QPushButton *activeBtn)
{
    //QString normalStyle = "QPushButton { "
    //                     "background-color: #f0f0f0; "
    //                     "border: 1px solid #c0c0c0; "
    //                     "border-radius: 4px; "
    //                     "padding: 5px; "
    //                     "} "
    //                     "QPushButton:hover { "
    //                     "background-color: #e0e0e0; "
    //                     "}";
    //
    //QString activeStyle = "QPushButton { "
    //                     "background-color: #0078d7; "
    //                     "color: white; "
    //                     "border: 1px solid #0078d7; "
    //                     "border-radius: 4px; "
    //                     "padding: 5px; "
    //                     "}";

    //// 恢复之前激活按钮的样式
    //if (m_currentActiveButton) {
    //    m_currentActiveButton->setStyleSheet(normalStyle);
    //}

    //// 设置新的激活按钮
    //if (activeBtn) {
    //    activeBtn->setStyleSheet(activeStyle);
    //    m_currentActiveButton = activeBtn;
    //}
}

void LLibraryTopButtonPannel::onImportClicked()
{
    setActiveButton(ui->btn_import);
    emit pageChanged(0);  // 切换到导入页面
}

void LLibraryTopButtonPannel::onLibraryClicked()
{
    setActiveButton(ui->btn_library);
    emit pageChanged(1);  // 切换到媒体库页面
}

void LLibraryTopButtonPannel::onPreviewClicked()
{
    setActiveButton(ui->btn_preview);
    emit pageChanged(2);  // 切换到预览页面
}

void LLibraryTopButtonPannel::onPropertyClicked()
{
    setActiveButton(ui->btn_property);
    emit pageChanged(3);  // 切换到属性页面
}

void LLibraryTopButtonPannel::onTimelineClicked()
{
    setActiveButton(ui->btn_timeline);
    emit pageChanged(4);  // 切换到时间轴页面
}