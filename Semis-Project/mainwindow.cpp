#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QIcon>
#include <QStack>
#include <QQueue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timerDuration = 3 * 60;  
    timeLeft = timerDuration;

    ui->lcdNumber->setDigitCount(5);
    updateLCD(timeLeft);

    connect(ui->Order, &QPushButton::clicked, this, &MainWindow::enqueueOrder);
    connect(ui->Queue, &QPushButton::clicked, this, &MainWindow::startQueue);
    connect(ui->Serve, &QPushButton::clicked, this, &MainWindow::dequeueOrder);
    connect(ui->Delete, &QPushButton::clicked, this, &MainWindow::deleteOrder);
    connect(ui->RecentOrders, &QPushButton::clicked, this, &MainWindow::updatePendingOrdersCount);

    orderQueue = new QQueue<QString>();
    orderStack = new QStack<QString>();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete orderQueue;
    delete orderStack;
}

void MainWindow::updateLCD(int timeInSeconds)
{
    int minutes = timeInSeconds / 60;
    int seconds = timeInSeconds % 60;
    QString timeString = QString::asprintf("%02d:%02d", minutes, seconds);
    ui->lcdNumber->display(timeString);
}

void MainWindow::updateTimer()
{
    if (timeLeft > 0) {
        timeLeft--;
        updateLCD(timeLeft);
    } else {
        timer->stop();
        if (!orderQueue->isEmpty()) {
            QString order = orderQueue->dequeue();
            ui->completed_orders->addItem(order);
            updateCompletedOrdersCount();

            timeLeft = timerDuration;
            updateLCD(timeLeft);

            if (!orderQueue->isEmpty()) {
                timer->start(1000);
            }
        }
    }
}

void MainWindow::enqueueOrder()
{
    QString orderText = ui->lineEdit->text();
    if (!orderText.isEmpty()) {
        QString orderNumber = QString::asprintf("#%03d", orderQueue->size() + 1);
        QString orderWithNumber = orderNumber + ": " + orderText;
        orderQueue->enqueue(orderWithNumber);
        ui->pending_orders->addItem(orderWithNumber);
        ui->lineEdit->clear();
    }
}

void MainWindow::dequeueOrder()
{
    if (!orderQueue->isEmpty()) {
        QString order = orderQueue->dequeue();
        ui->completed_orders->addItem(order);
        updateCompletedOrdersCount();

        timeLeft = timerDuration;
        updateLCD(timeLeft);

        if (!orderQueue->isEmpty()) {
            timer->start(1000);
        } else {
            timer->stop();
        }
    }
}

void MainWindow::pushOrderToStack()
{
    QString orderText = ui->lineEdit->text();
    if (!orderText.isEmpty()) {
        orderStack->push(orderText);
        ui->pending_orders->addItem("Stack Order: " + orderText);
        ui->lineEdit->clear();
    }
}

void MainWindow::popOrderFromStack()
{
    if (!orderStack->isEmpty()) {
        QString order = orderStack->pop();
        ui->completed_orders->addItem("Completed Stack Order: " + order);
        updateCompletedOrdersCount();
    }
}

void MainWindow::deleteOrder()
{
    QListWidgetItem* item = ui->pending_orders->currentItem();
    if (item) {
        delete item;
    }
}

void MainWindow::updateCompletedOrdersCount()
{
    int completedOrderCount = ui->completed_orders->count();
    QString countText = QString("Completed Orders: %1").arg(completedOrderCount);
    ui->completed_orders_2->clear();
    ui->completed_orders_2->addItem(countText);
}

void MainWindow::updatePendingOrdersCount()
{
    int pendingOrderCount = ui->pending_orders->count();
    QString countText = QString("Pending Orders: %1").arg(pendingOrderCount);
    ui->completed_orders_3->clear();
    ui->completed_orders_3->addItem(countText);
}
