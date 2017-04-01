#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_actionKaijianghaoma_triggered();

    void on_actionView_triggered();

    void on_btnAnalysis_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
