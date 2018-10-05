#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes.h"
#include "server.h"
#include "windowhandler.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void closeEvent (QCloseEvent *event);

public slots:
    void setTimeSlot(QString str);
    void setTeamOneSlot(QString str);
    void setTeamTwoSlot(QString str);
    void setPeriodSlot(QString str);
    void addGoalOneSlot(QString str);
    void addGoalTwoSlot(QString str);
    void deleteGoalOneSlot(QString str);
    void deleteGoalTwoSlot(QString str);
    void deletePlayerOneSlot(QString name, QString time);
    void deletePlayerTwoSlot(QString name, QString time);
    void cancelDeleteOneSlot(QString str);
    void cancelDeleteTwoSlot(QString str);
    void startSlot();
    void stopSlot();
    void restartSlot();


private slots:
    void updateTimeSlot();

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_clearButton_clicked();

signals:
    void updateTimeSignal();

private:
    Ui::MainWindow *ui;
    QTimer* tClock_;
    int clock_;
    std::vector<QTimer*> qTimerList_;
    std::vector<int> timeList_;

    QString intToTime(int tmp);
    void saveCache();
    void loadCache();
};

#endif // MAINWINDOW_H
