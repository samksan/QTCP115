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
    void on_btnAnalysis_clicked();

    void on_btn_update_number_clicked();

    void on_btn_view_number_clicked();

    void on_btn_view_number_desc_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
