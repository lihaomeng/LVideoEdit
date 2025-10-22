#include "lvideoeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LVideoEditorMainWindow window;
    window.show();
    return app.exec();
}
