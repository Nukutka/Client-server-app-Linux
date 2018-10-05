#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "includes.h"
#include "client.h"
#include "windowhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void serverOffSlot();

private slots:
    void on_connectButton_clicked();

    void on_setPeriodButton_clicked();

    void on_setTeamOneButton_clicked();

    void on_setTeamTwoButton_clicked();

    void on_diconnectButton_clicked();

    void on_addGoalOneButton_clicked();

    void on_addGoalTwoButton_clicked();

    void on_deleteGoalOneButton_clicked();

    void on_deleteGoalTwoButton_clicked();

    void on_deletePlayerOneButton_clicked();

    void on_cancelDeletionOneButton_clicked();

    void on_deletePlayerTwoButton_clicked();

    void on_cancelDeletionTwoButton_clicked();

    void on_setTimeButton_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_restartButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
