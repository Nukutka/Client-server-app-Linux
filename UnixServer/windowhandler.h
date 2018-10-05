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
        void setTimeSignal(QString str);
        void setTeamOneSignal(QString str);
        void setTeamTwoSignal(QString str);
        void setPeriodSignal(QString str);
        void addGoalOneSignal(QString str);
        void addGoalTwoSignal(QString str);
        void deleteGoalOneSignal(QString str);
        void deleteGoalTwoSignal(QString str);
        void deletePlayerOneSignal(QString name, QString time);
        void deletePlayerTwoSignal(QString name, QString time);
        void cancelDeleteOneSignal(QString str);
        void cancelDeleteTwoSignal(QString str);
        void startSignal();
        void stopSignal();
        void restartSignal();

    private:

};

#endif // WINDOWHANDLER_H
