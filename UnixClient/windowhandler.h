#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H
#include <QObject>
#include <string>

class WindowHandler:public QObject
{
    Q_OBJECT
public:
    WindowHandler()
    {

    }
    ~WindowHandler()
    {

    }
    signals:
        void serverOffSignal();

    private:

};

#endif // WINDOWHANDLER_H
