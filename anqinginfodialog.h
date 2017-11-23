#ifndef ANQINGINFODIALOG_H
#define ANQINGINFODIALOG_H

#include <QDialog>

namespace Ui {
class AnQingInfoDialog;
}

class QJsonArray;

class AnQingInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnQingInfoDialog(QWidget *parent = 0);
    ~AnQingInfoDialog();

private slots:
    void on_addButton_clicked();

    void on_cancerButton_clicked();

    void on_quitButton_clicked();

    void on_okPushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_deleteButton_clicked();

    void on_modiButton_clicked();

    void on_caseWeiFanEdit_textChanged(const QString &arg1);

    void on_caseYiJuEdit_textChanged(const QString &arg1);

    void on_caseChuFaEdit_textChanged();

    void on_caseFromEdit_textChanged();

    void on_caseAnQingBigEdit_textChanged();

    void on_caseAnQingSmallEdit_textChanged();

    void on_caseCSIEdit_textChanged();

private:
    Ui::AnQingInfoDialog *ui;
    bool btextChang;
    QString strCgWeiFan, strCgYiJu, strCgCf,strCgFrom, strCgAqBig, strCgAqSmall,strCgCSI;
private:
    void loadAnQingJsonFile();
signals:
    void anQingJsonChanged(); // 退出的时候发射该信号更新界面上的main上的comboBoxCase
protected:
    void closeEvent(QCloseEvent *event);


};

#endif // ANQINGINFODIALOG_H
