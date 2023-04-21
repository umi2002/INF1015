#include "libraries.hpp"
#include "maingui.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainGui      window;
    return app.exec();
}
