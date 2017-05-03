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

    void on_pushButton_zdd1_clicked();

    void on_pushButton_zdd2_clicked();

    void on_pushButton_zdd3_clicked();

    void on_pushButton_bdd1_clicked();

    void on_pushButton_bdd2_clicked();

    void on_pushButton_bdd3_clicked();

    void on_pushButton_zdz1_clicked();

    void on_pushButton_zdz2_clicked();

    void on_pushButton_zdz3_clicked();

    void on_pushButton_bdz1_clicked();

    void on_pushButton_bdz2_clicked();

    void on_pushButton_bdz3_clicked();

    void on_pushButton_filter_clicked();

    void on_chart_zdd_1_clicked();

    void on_chart_zdd_2_clicked();

    void on_chart_zdd_3_clicked();

    void on_chart_zdd_4_clicked();

    void on_chart_zdd_5_clicked();

    void on_chart_bdd_1_clicked();

    void on_chart_bdd_2_clicked();

    void on_chart_bdd_3_clicked();

    void on_chart_bdd_4_clicked();

    void on_chart_bdd_5_clicked();

    void on_chart_zdz_1_clicked();

    void on_chart_zdz_2_clicked();

    void on_chart_zdz_3_clicked();

    void on_chart_zdz_4_clicked();

    void on_chart_zdz_5_clicked();

    void on_chart_bdz_1_clicked();

    void on_chart_bdz_2_clicked();

    void on_chart_bdz_3_clicked();

    void on_chart_bdz_4_clicked();

    void on_chart_bdz_5_clicked();

private:
    Ui::MainWindow *ui;

    void chart_view(int position);
};

#endif // MAINWINDOW_H
