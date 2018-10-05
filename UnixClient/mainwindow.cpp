#include "mainwindow.h"
#include "ui_mainwindow.h"

Client* client;
WindowHandler* winHand;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    winHand = new WindowHandler();
    connect(*&winHand,&WindowHandler::serverOffSignal,this,&MainWindow::serverOffSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverOffSlot() {
    ui->connectButton->setEnabled(true);
    ui->diconnectButton->setEnabled(false);
     ui->setTimeButton->setEnabled(false);
    ui->setTeamOneButton->setEnabled(false);
    ui->setTeamTwoButton->setEnabled(false);
    ui->setPeriodButton->setEnabled(false);
    ui->addGoalOneButton->setEnabled(false);
    ui->addGoalTwoButton->setEnabled(false);
    ui->deleteGoalOneButton->setEnabled(false);
    ui->deleteGoalTwoButton->setEnabled(false);
    ui->deletePlayerOneButton->setEnabled(false);
    ui->cancelDeletionOneButton->setEnabled(false);
    ui->deletePlayerTwoButton->setEnabled(false);
    ui->cancelDeletionTwoButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->restartButton->setEnabled(false);
}

void MainWindow::on_connectButton_clicked()
{
    client = new Client(winHand);
    if (client->startClient() == 0) {
    ui->connectButton->setEnabled(false);
    ui->diconnectButton->setEnabled(true);
    ui->setTimeButton->setEnabled(true);
    ui->setTeamOneButton->setEnabled(true);
    ui->setTeamTwoButton->setEnabled(true);
    ui->setPeriodButton->setEnabled(true);
    ui->addGoalOneButton->setEnabled(true);
    ui->addGoalTwoButton->setEnabled(true);
    ui->deleteGoalOneButton->setEnabled(true);
    ui->deleteGoalTwoButton->setEnabled(true);
    ui->deletePlayerOneButton->setEnabled(true);
    ui->cancelDeletionOneButton->setEnabled(true);
    ui->deletePlayerTwoButton->setEnabled(true);
    ui->cancelDeletionTwoButton->setEnabled(true);
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
    ui->restartButton->setEnabled(true);
    }
}

void MainWindow::on_diconnectButton_clicked()
{
    client->stopClient();
    ui->connectButton->setEnabled(true);
    ui->diconnectButton->setEnabled(false);
    ui->setTimeButton->setEnabled(false);
    ui->setTeamOneButton->setEnabled(false);
    ui->setTeamTwoButton->setEnabled(false);
    ui->setPeriodButton->setEnabled(false);
    ui->addGoalOneButton->setEnabled(false);
    ui->addGoalTwoButton->setEnabled(false);
    ui->deleteGoalOneButton->setEnabled(false);
    ui->deleteGoalTwoButton->setEnabled(false);
    ui->deletePlayerOneButton->setEnabled(false);
    ui->cancelDeletionOneButton->setEnabled(false);
    ui->deletePlayerTwoButton->setEnabled(false);
    ui->cancelDeletionTwoButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->restartButton->setEnabled(false);
}

bool isNumber(QString input) {
    std::string  str = input.toStdString();
    std::size_t found =str.find_first_not_of("0123456789");
    return found == std::string::npos;
}

void MainWindow::on_setPeriodButton_clicked()
{
    if (ui->periodEdit->text().length() > 0) {
        if (isNumber(ui->periodEdit->text())) {
            char serverMsg[3];
            client->sendData(client->getSock(),"setPeriod");
            client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
            client->sendData(client->getSock(),ui->periodEdit->text().toStdString().c_str());
            client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        }
    }
}

void MainWindow::on_setTeamOneButton_clicked()
{
    char serverMsg[3];
    if (ui->teamOneEdit->text().length() > 0) {
        client->sendData(client->getSock(),"setTeamOne");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->teamOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_setTeamTwoButton_clicked()
{
    char serverMsg[3];
    if (ui->teamTwoEdit->text().length() > 0) {
        client->sendData(client->getSock(),"setTeamTwo");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->teamTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}



void MainWindow::on_addGoalOneButton_clicked()
{
    char serverMsg[3];
    if (ui->goalOneEdit->text().length() > 0) {
        client->sendData(client->getSock(),"addGoalOne");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->goalOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_addGoalTwoButton_clicked()
{
    char serverMsg[3];
    if (ui->goalTwoEdit->text().length() > 0) {
        client->sendData(client->getSock(),"addGoalTwo");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->goalTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_deleteGoalOneButton_clicked()
{
    char serverMsg[3];
    if (ui->goalOneEdit->text().length() > 0) {
        client->sendData(client->getSock(),"deleteGoalOne");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->goalOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_deleteGoalTwoButton_clicked()
{
    char serverMsg[3];
    if (ui->goalTwoEdit->text().length() > 0) {
        client->sendData(client->getSock(),"deleteGoalTwo");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->goalTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_deletePlayerOneButton_clicked()
{
    char serverMsg[3];
    if (ui->deletePlayerOneEdit->text().length() > 0 &&
            ui->deletePlayerTimeOneEdit->text().length() > 0 &&
            isNumber(ui->deletePlayerTimeOneEdit->text())) {
        client->sendData(client->getSock(),"deletePlayerOne");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerTimeOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_cancelDeletionOneButton_clicked()
{
    char serverMsg[3];
    if (ui->deletePlayerOneEdit->text().length() > 0) {
        client->sendData(client->getSock(),"cancelDeleteOne");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerOneEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_deletePlayerTwoButton_clicked()
{
    char serverMsg[3];
    if (ui->deletePlayerTwoEdit->text().length() > 0 &&
            ui->deletePlayerTimeTwoEdit->text().length() > 0 &&
            isNumber(ui->deletePlayerTimeTwoEdit->text())) {
        client->sendData(client->getSock(),"deletePlayerTwo");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerTimeTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_cancelDeletionTwoButton_clicked()
{
    char serverMsg[3];
    if (ui->deletePlayerTwoEdit->text().length() > 0) {
        client->sendData(client->getSock(),"cancelDeleteTwo");
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        client->sendData(client->getSock(),ui->deletePlayerTwoEdit->text().toStdString().c_str());
        client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
    }
}

void MainWindow::on_setTimeButton_clicked()
{
    if (ui->timeEdit->text().length() > 0) {
        if (isNumber(ui->timeEdit->text())) {
            char serverMsg[3];
            client->sendData(client->getSock(),"setTime");
            client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
            client->sendData(client->getSock(),ui->timeEdit->text().toStdString().c_str());
            client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
        }
    }
}

void MainWindow::on_startButton_clicked()
{
    char serverMsg[3];
    client->sendData(client->getSock(),"start");
    client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
}

void MainWindow::on_stopButton_clicked()
{
    char serverMsg[3];
    client->sendData(client->getSock(),"stop");
    client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
}

void MainWindow::on_restartButton_clicked()
{
    char serverMsg[3];
    client->sendData(client->getSock(),"restart");
    client->recvData(client->getSock(), serverMsg, sizeof(serverMsg));
}
