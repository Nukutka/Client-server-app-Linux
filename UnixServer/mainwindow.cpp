#include "mainwindow.h"
#include "ui_mainwindow.h"


Server* server;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WindowHandler* winHand = new WindowHandler();
    tClock_ = new QTimer();
    for (int i = 0; i < 6; i++) {
        timeList_.push_back(0);
    }

    connect(*&winHand,&WindowHandler::setTimeSignal,this,&MainWindow::setTimeSlot);
    connect(*&winHand,&WindowHandler::setTeamOneSignal,this,&MainWindow::setTeamOneSlot);
    connect(*&winHand,&WindowHandler::setTeamTwoSignal,this,&MainWindow::setTeamTwoSlot);
    connect(*&winHand,&WindowHandler::setPeriodSignal,this,&MainWindow::setPeriodSlot);
    connect(*&winHand,&WindowHandler::addGoalOneSignal,this,&MainWindow::addGoalOneSlot);
    connect(*&winHand,&WindowHandler::addGoalTwoSignal,this,&MainWindow::addGoalTwoSlot);
    connect(*&winHand,&WindowHandler::deleteGoalOneSignal,this,&MainWindow::deleteGoalOneSlot);
    connect(*&winHand,&WindowHandler::deleteGoalTwoSignal,this,&MainWindow::deleteGoalTwoSlot);
    connect(*&winHand,&WindowHandler::deletePlayerOneSignal,this,&MainWindow::deletePlayerOneSlot);
    connect(*&winHand,&WindowHandler::deletePlayerTwoSignal,this,&MainWindow::deletePlayerTwoSlot);
    connect(*&winHand,&WindowHandler::cancelDeleteOneSignal,this,&MainWindow::cancelDeleteOneSlot);
    connect(*&winHand,&WindowHandler::cancelDeleteTwoSignal,this,&MainWindow::cancelDeleteTwoSlot);
    connect(*&winHand,&WindowHandler::startSignal,this,&MainWindow::startSlot);
    connect(*&winHand,&WindowHandler::stopSignal,this,&MainWindow::stopSlot);
    connect(*&winHand,&WindowHandler::restartSignal,this,&MainWindow::restartSlot);
    connect(tClock_,SIGNAL(timeout()),this,SLOT(updateTimeSlot()));

    server = new Server(winHand);

    tClock_->setInterval(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tClock_;
}

void MainWindow::startSlot() {
    if (!tClock_->isActive() && clock_ > 0) tClock_->start();
}

void MainWindow::stopSlot() {
    if (tClock_->isActive()) tClock_->stop();
}

void MainWindow::restartSlot() {
    on_clearButton_clicked();
}

void MainWindow::cancelDeleteOneSlot(QString str) {
    int i =-1;
    if (ui->deletedOneOneEdit->text() == str) i = 0; // update
    if (ui->deletedTwoOneEdit->text() == str) i = 1;
    if (ui->deletedThreeOneEdit->text() == str) i = 2;

    switch (i) {
    case 0:
        ui->deletedOneOneEdit->clear();
        ui->deletedTimeOneOneEdit->clear();
        timeList_[i] = 0;
        break;
    case 1:
        ui->deletedTwoOneEdit->clear();
        ui->deletedTimeTwoOneEdit->clear();
        timeList_[i] = 0;
        break;
    case 2:
        ui->deletedThreeOneEdit->clear();
        ui->deletedTimeThreeOneEdit->clear();
        timeList_[i] = 0;
        break;
    default:
        break;
    }
}

void MainWindow::cancelDeleteTwoSlot(QString str) {
    int i = -1;
    if (ui->deletedOneTwoEdit->text() == str) i = 3; // update
    if (ui->deletedTwoTwoEdit->text() == str) i = 4;
    if (ui->deletedThreeTwoEdit->text() == str) i = 5;
    switch (i) {
    case 3:
        ui->deletedOneTwoEdit->clear();
        ui->deletedTimeOneTwoEdit->clear();
        timeList_[i] = 0;
        break;
    case 4:
        ui->deletedTwoTwoEdit->clear();
        ui->deletedTimeTwoTwoEdit->clear();
        timeList_[i] = 0;
        break;
    case 5:
        ui->deletedThreeTwoEdit->clear();
        ui->deletedTimeThreeTwoEdit->clear();
        timeList_[i] = 0;
        break;
    default:
        break;
    }
}

void MainWindow::setTimeSlot(QString str) {
    clock_ = str.toInt();
    ui->clockLabel->setText(intToTime(clock_));
//    if (clock_ > 0 && !tClock_->isActive()) {
//        tClock_->start();
//    }
}

void MainWindow::updateTimeSlot() {
    if (clock_ > 0) clock_--;
    else {
        clock_=0;
        tClock_->stop();
    }
    ui->clockLabel->setText(intToTime(clock_));
    for (int i = 0; i < 6; i++) {
        if (timeList_[i] > 0) {
            timeList_[i]--;
            switch (i) {
            case 0:
                ui->deletedTimeOneOneEdit->setText(intToTime(timeList_[i]));
                break;
            case 1:
                ui->deletedTimeTwoOneEdit->setText(intToTime(timeList_[i]));
                break;
            case 2:
                ui->deletedTimeThreeOneEdit->setText(intToTime(timeList_[i]));
                break;
            case 3:
                ui->deletedTimeOneTwoEdit->setText(intToTime(timeList_[i]));
                break;
            case 4:
                ui->deletedTimeTwoTwoEdit->setText(intToTime(timeList_[i]));
                break;
            case 5:
                ui->deletedTimeThreeTwoEdit->setText(intToTime(timeList_[i]));
                break;
            default:
                break;
            }
        }
        else {
            switch (i) {
            case 0:
                timeList_[0] = timeList_[1];
                ui->deletedOneOneEdit->setText(ui->deletedTwoOneEdit->text());
                ui->deletedTimeOneOneEdit->setText(ui->deletedTimeTwoOneEdit->text());
                timeList_[1] = timeList_[2];
                ui->deletedTwoOneEdit->setText(ui->deletedThreeOneEdit->text());
                ui->deletedTimeTwoOneEdit->setText(ui->deletedTimeThreeOneEdit->text());
                timeList_[2] = 0;
                ui->deletedThreeOneEdit->clear();
                ui->deletedTimeThreeOneEdit->clear();
                break;
            case 1:
                timeList_[1] = timeList_[2];
                ui->deletedTwoOneEdit->setText(ui->deletedThreeOneEdit->text());
                ui->deletedTimeTwoOneEdit->setText(ui->deletedTimeThreeOneEdit->text());
                timeList_[2] = 0;
                ui->deletedThreeOneEdit->clear();
                ui->deletedTimeThreeOneEdit->clear();
                break;
            case 2:
                ui->deletedThreeOneEdit->clear();
                ui->deletedTimeThreeOneEdit->clear();
                break;
            case 3:
                timeList_[3] = timeList_[4];
                ui->deletedOneTwoEdit->setText(ui->deletedTwoTwoEdit->text());
                ui->deletedTimeOneTwoEdit->setText(ui->deletedTimeTwoTwoEdit->text());
                timeList_[4] = timeList_[5];
                ui->deletedTwoTwoEdit->setText(ui->deletedThreeTwoEdit->text());
                ui->deletedTimeTwoTwoEdit->setText(ui->deletedTimeThreeTwoEdit->text());
                timeList_[5] = 0;
                ui->deletedThreeTwoEdit->clear();
                ui->deletedTimeThreeTwoEdit->clear();
                break;
            case 4:
                timeList_[4] = timeList_[5];
                ui->deletedTwoTwoEdit->setText(ui->deletedThreeTwoEdit->text());
                ui->deletedTimeTwoTwoEdit->setText(ui->deletedTimeThreeTwoEdit->text());
                timeList_[5] = 0;
                ui->deletedThreeTwoEdit->clear();
                ui->deletedTimeThreeTwoEdit->clear();
                break;
            case 5:
                ui->deletedThreeTwoEdit->clear();
                ui->deletedTimeThreeTwoEdit->clear();
                break;
            default:
                break;
            }
        }
    }
}

void MainWindow::deletePlayerOneSlot(QString name, QString time)
{
    int i = -1;
    if (ui->deletedOneOneEdit->text() == name) i = 0; // update
    if (ui->deletedTwoOneEdit->text() == name) i = 1;
    if (ui->deletedThreeOneEdit->text() == name) i = 2;
    int tmp = time.toInt();
    if (i == -1)  { // add new
        for (i = 0; i < 3; i++) {
            if (timeList_[i] == 0) break;
        }
    }
    switch (i) {
    case 0:
        ui->deletedOneOneEdit->setText(name);
        ui->deletedTimeOneOneEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    case 1:
        ui->deletedTwoOneEdit->setText(name);
        ui->deletedTimeTwoOneEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    case 2:
        ui->deletedThreeOneEdit->setText(name);
        ui->deletedTimeThreeOneEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    default:
        break;
    }
//    if (ui->deletedOneOneEdit->text().length() == 0) {
//        ui->deletedOneOneEdit->setText(name);
//        timeList_[0] = tmp;
//        ui->deletedTimeOneOneEdit->setText(intToTime(tmp));
//        qTimerList_[0]->start();
//    }
//    else if (ui->deletedTwoOneEdit->text().length() == 0) {
//        ui->deletedTwoOneEdit->setText(name);
//        timeList_[1] = tmp;
//        ui->deletedTimeTwoOneEdit->setText(intToTime(tmp));
//        qTimerList_[1]->start();
//    }
//    else if (ui->deletedThreeOneEdit->text().length() == 0) {
//        ui->deletedThreeOneEdit->setText(name);
//        timeList_[2] = tmp;
//        ui->deletedTimeThreeOneEdit->setText(intToTime(tmp));
//        qTimerList_[2]->start();
//    }
}

void MainWindow::deletePlayerTwoSlot(QString name, QString time)
{
    int i = -1;
    int tmp = time.toInt();
    if (ui->deletedOneTwoEdit->text() == name) i = 3; // update
    if (ui->deletedTwoTwoEdit->text() == name) i = 4;
    if (ui->deletedThreeTwoEdit->text() == name) i = 5;
    if (i == -1) {
        for (i = 3; i < 6; i++) {
            if (timeList_[i] == 0) break;
        }
    }
    switch (i) {
    case 3:
        ui->deletedOneTwoEdit->setText(name);
        ui->deletedTimeOneTwoEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    case 4:
        ui->deletedTwoTwoEdit->setText(name);
        ui->deletedTimeTwoTwoEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    case 5:
        ui->deletedThreeTwoEdit->setText(name);
        ui->deletedTimeThreeTwoEdit->setText(intToTime(tmp));
        timeList_[i] = tmp;
        break;
    default:
        break;
    }
}

void MainWindow::addGoalOneSlot(QString str)
{
    ui->goalOneListView->addItem(str);
    int tmp = ui->scoreOneEdit->text().toInt() + 1;
    ui->scoreOneEdit->setText(QString::number(tmp));
}

void MainWindow::addGoalTwoSlot(QString str)
{
    ui->goalTwoListView->addItem(str);
    int tmp = ui->scoreTwoEdit->text().toInt() + 1;
    ui->scoreTwoEdit->setText(QString::number(tmp));
}

void MainWindow::deleteGoalOneSlot(QString str)
{
    QListWidgetItem *item;
    QList<QListWidgetItem *> found = ui->goalOneListView->findItems(str, Qt::MatchExactly);
    if(found.count() > 0)
    {
        item = found.at(0);
        ui->goalOneListView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->goalOneListView->clearSelection();
        ui->goalOneListView->setItemSelected(item,true);
        qDeleteAll(ui->goalOneListView->selectedItems());
        ui->goalOneListView->setSelectionMode(QAbstractItemView::NoSelection);
        int tmp = ui->scoreOneEdit->text().toInt() - 1;
        ui->scoreOneEdit->setText(QString::number(tmp));
    }
}

void MainWindow::deleteGoalTwoSlot(QString str)
{
    QListWidgetItem *item;
    QList<QListWidgetItem *> found = ui->goalTwoListView->findItems(str, Qt::MatchExactly);
    if(found.count() > 0)
    {
        item = found.at(0);
        ui->goalTwoListView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->goalTwoListView->clearSelection();
        ui->goalTwoListView->setItemSelected(item,true);
        qDeleteAll(ui->goalTwoListView->selectedItems());
        ui->goalTwoListView->setSelectionMode(QAbstractItemView::NoSelection);
        int tmp = ui->scoreTwoEdit->text().toInt() - 1;
        ui->scoreTwoEdit->setText(QString::number(tmp));
    }
}

void MainWindow::setPeriodSlot(QString str){
    ui->periodEdit->setText(str);
}

void MainWindow::setTeamOneSlot(QString str){
    ui->teamOneEdit->setText(str);
}

void MainWindow::setTeamTwoSlot(QString str){
    ui->teamTwoEdit->setText(str);
}

QString MainWindow::intToTime(int tmp) {
    int min =  tmp / 60;
    int sec = tmp % 60;
    QString m = min > 9 ? QString::number(min) : "0" + QString::number(min);
    QString s = sec > 9 ? QString::number(sec) : "0" + QString::number(sec);
    return m + ":" + s;
}

void MainWindow::saveCache() {
    QSettings* cache = new QSettings("cache.conf",QSettings::NativeFormat);

    cache->setValue("cache/clock",clock_);
    cache->setValue("cache/teamOneName",ui->teamOneEdit->text());
    cache->setValue("cache/teamTwoName",ui->teamTwoEdit->text());
    cache->setValue("cache/periodNumber",ui->periodEdit->text());
    cache->setValue("cache/teamOneScore",ui->scoreOneEdit->text());
    cache->setValue("cache/teamTwoScore",ui->scoreTwoEdit->text());

    cache->setValue("cache/deletedOneOne",      ui->deletedOneOneEdit->text());
    cache->setValue("cache/deletedTwoOne",      ui->deletedTwoOneEdit->text());
    cache->setValue("cache/deletedThreeOne",    ui->deletedThreeOneEdit->text());
    cache->setValue("cache/deletedOneTwo",      ui->deletedOneTwoEdit->text());
    cache->setValue("cache/deletedTwoTwo",      ui->deletedTwoTwoEdit->text());
    cache->setValue("cache/deletedThreeTwo",    ui->deletedThreeTwoEdit->text());
    cache->setValue("cache/deletedTimeOneOne",timeList_[0]);
    cache->setValue("cache/deletedTimeTwoOne",timeList_[1]);
    cache->setValue("cache/deletedTimeThreeOne",timeList_[2]);
    cache->setValue("cache/deletedTimeOneTwo",timeList_[3]);
    cache->setValue("cache/deletedTimeTwoTwo",timeList_[4]);
    cache->setValue("cache/deletedTimeThreeTwo",timeList_[5]);

    for (int i = 0; i < ui->scoreOneEdit->text().toInt(); i++) {
        cache->setValue("cache/goalOneList" + i,ui->goalOneListView->item(i)->text());
    }

    for (int i = 0; i < ui->scoreTwoEdit->text().toInt(); i++) {
        cache->setValue("cache/goalTwoList" + i,ui->goalTwoListView->item(i)->text());
    }
}

void MainWindow::loadCache() {
    QSettings* cache = new QSettings("cache.conf",QSettings::NativeFormat);

    clock_ = cache->value("cache/clock",60*20).toInt();
    ui->clockLabel->setText(intToTime(clock_));
    ui->teamOneEdit->setText(cache->value("cache/teamOneName","").toString());
    ui->teamTwoEdit->setText(cache->value("cache/teamTwoName","").toString());
    ui->periodEdit->setText(cache->value("cache/periodNumber",1).toString());
    ui->scoreOneEdit->setText(cache->value("cache/teamOneScore","0").toString());
    ui->scoreTwoEdit->setText(cache->value("cache/teamTwoScore","0").toString());
    if (cache->value("cache/deletedTimeOneOne",0).toInt() > 0) {
        ui->deletedOneOneEdit->setText(cache->value("cache/deletedOneOne",0).toString());
        timeList_[0] = cache->value("cache/deletedTimeOneOne",0).toInt();
        ui->deletedTimeOneOneEdit->setText(intToTime(timeList_[0]));
    }
    if (cache->value("cache/deletedTimeTwoOne",0).toInt()> 0) {
        ui->deletedTwoOneEdit->setText(cache->value("cache/deletedTwoOne",0).toString());
        timeList_[1] = cache->value("cache/deletedTimeTwoOne",0).toInt();
        ui->deletedTimeTwoOneEdit->setText(intToTime(timeList_[1]));
    }
    if (cache->value("cache/deletedTimeThreeOne",0).toInt()> 0) {
        ui->deletedThreeOneEdit->setText(cache->value("cache/deletedThreeOne",0).toString());
        timeList_[2] = cache->value("cache/deletedTimeThreeOne",0).toInt();
        ui->deletedTimeThreeOneEdit->setText(intToTime(timeList_[2]));
    }
    if (cache->value("cache/deletedTimeOneTwo",0).toInt()> 0) {
        ui->deletedOneTwoEdit->setText(cache->value("cache/deletedOneTwo",0).toString());
        timeList_[3] = cache->value("cache/deletedTimeOneTwo",0).toInt();
        ui->deletedTimeOneTwoEdit->setText(intToTime(timeList_[3]));
    }
    if (cache->value("cache/deletedTimeTwoTwo",0).toInt()> 0) {
        ui->deletedTwoTwoEdit->setText(cache->value("cache/deletedTwoTwo",0).toString());
        timeList_[4] = cache->value("cache/deletedTimeTwoTwo",0).toInt();
        ui->deletedTimeTwoTwoEdit->setText(intToTime(timeList_[4]));
    }
    if (cache->value("cache/deletedTimeThreeTwo",0).toInt()> 0) {
        ui->deletedThreeTwoEdit->setText(cache->value("cache/deletedThreeTwo",0).toString());
        timeList_[5] = cache->value("cache/deletedTimeThreeTwo",0).toInt();
        ui->deletedTimeThreeTwoEdit->setText(intToTime(timeList_[5]));
    }
    for (int i = 0; i < ui->scoreOneEdit->text().toInt(); i++) {
        ui->goalOneListView->addItem(cache->value("cache/goalOneList"+ i,"error").toString());
    }
    for (int i = 0; i < ui->scoreTwoEdit->text().toInt(); i++) {
        ui->goalTwoListView->addItem(cache->value("cache/goalTwoList"+ i,"error").toString());
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    /*QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }*/
    server->stopServer();
    tClock_->stop();
    saveCache();
}

void MainWindow::on_startButton_clicked()
{
    server->startServer();
    ui->goalOneListView->clear();
    ui->goalTwoListView->clear();
    loadCache();
    //tClock_->start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->clearButton->setEnabled(true);
}

void MainWindow::on_stopButton_clicked()
{
    server->stopServer();
    saveCache();
    tClock_->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void MainWindow::on_clearButton_clicked()
{
    tClock_->stop();
    QSettings* cache = new QSettings("cache.conf",QSettings::NativeFormat);
    cache->setValue("cache/clock",60*20);
    cache->setValue("cache/teamOneName","");
    cache->setValue("cache/teamTwoName","");
    cache->setValue("cache/periodNumber",1);
    for (int i = 0; i < ui->scoreOneEdit->text().toInt(); i++) {
        cache->setValue("cache/goalOneList" + i,"");
    }
    for (int i = 0; i < ui->scoreTwoEdit->text().toInt(); i++) {
        cache->setValue("cache/goalTw0List" + i,"");
    }
    cache->setValue("cache/teamOneScore","0");
    cache->setValue("cache/teamTwoScore","0");

    cache->setValue("cache/deletedOneOne","");
    cache->setValue("cache/deletedTwoOne","");
    cache->setValue("cache/deletedThreeOne","");
    cache->setValue("cache/deletedOneTwo","");
    cache->setValue("cache/deletedTwoTwo","");
    cache->setValue("cache/deletedThreeTwo","");
    cache->setValue("cache/deletedTimeOneOne",0);
    cache->setValue("cache/deletedTimeTwoOne",0);
    cache->setValue("cache/deletedTimeThreeOne",0);
    cache->setValue("cache/deletedTimeOneTwo",0);
    cache->setValue("cache/deletedTimeTwoTwo",0);
    cache->setValue("cache/deletedTimeThreeTwo",0);
    for (int i = 0; i < 6; i++) {
        timeList_[i] = 0;
    }

    clock_ = 60*20;
    ui->clockLabel->setText(intToTime(60*20));
    //tClock_->start();
    ui->teamOneEdit->clear();
    ui->teamTwoEdit->clear();
    ui->periodEdit->setText("1");
    ui->scoreOneEdit->setText("0");
    ui->scoreTwoEdit->setText("0");
    ui->goalOneListView->clear();
    ui->goalTwoListView->clear();

    ui->deletedOneOneEdit->clear();
    ui->deletedTwoOneEdit->clear();
    ui->deletedThreeOneEdit->clear();
    ui->deletedOneTwoEdit->clear();
    ui->deletedTwoTwoEdit->clear();
    ui->deletedThreeTwoEdit->clear();
    ui->deletedTimeOneOneEdit->clear();
    ui->deletedTimeTwoOneEdit->clear();
    ui->deletedTimeThreeOneEdit->clear();
    ui->deletedTimeOneTwoEdit->clear();
    ui->deletedTimeTwoTwoEdit->clear();
    ui->deletedTimeThreeTwoEdit->clear();

}
