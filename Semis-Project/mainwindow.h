#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTimer();
    void addOrder();
    void startQueue();
    void serveOrder();
    void deleteOrder();
    void updateCompletedOrdersCount();  
    void updatePendingOrdersCount();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int timerDuration; 
    int timeLeft;      

    void updateLCD(int timeInSeconds);
};

#endif 
