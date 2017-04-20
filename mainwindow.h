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
    void on_btn_update_number_clicked();

    void on_btn_view_number_clicked();

    void on_btn_view_number_desc_clicked();

    void on_slider_base_valueChanged(int value);

    void on_slider_ana_valueChanged(int value);

    void on_comboBox_base_currentTextChanged(const QString &arg1);

    void on_comboBox_ana_currentTextChanged(const QString &arg1);

    void on_slider_chart_valueChanged(int value);

    void on_comboBox_chart_currentTextChanged(const QString &arg1);

    void on_btn_update_manual_clicked();

    void on_btn_test_analysis_clicked();

    void on_btn_data_refresh_clicked();

    void on_btn_show_chart_clicked();

    void on_btn_show_ana_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
