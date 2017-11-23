#ifndef BASEINFO_H
#define BASEINFO_H

//#include <QWidget>

#include <QDialog>

namespace Ui {
class BaseInfo;
}

class BaseInfo :  public QDialog//public QWidget
{
    Q_OBJECT

public:
   // explicit BaseInfo(QWidget *parent = 0);
    BaseInfo(QWidget *parent = 0);
    ~BaseInfo();
signals:
    void userJsonChanged();

private slots:
    void on_pushButton_clicked();

    void on_caseNumberEdit_textChanged(const QString &arg1);

    void on_caseCopEdit_textChanged(const QString &arg1);

    void on_caseFaWenNum1_textChanged(const QString &arg1);

    void on_caseFaWenNum2_textChanged(const QString &arg1);

    void on_caseForestUnitEdit_textChanged(const QString &arg1);

    void on_caseLinYeUnitEdit_textChanged(const QString &arg1);

    void on_caseNationEdit_textChanged(const QString &arg1);

    void on_caseCultureEdit_textChanged(const QString &arg1);

    void on_caseJobEdit_textChanged(const QString &arg1);

    void on_caseHumNumberEdit_textChanged(const QString &arg1);

    void on_caseHomeEdit_textChanged(const QString &arg1);

private:
    Ui::BaseInfo *ui;
public:
    QString strCaseCop;  // 立卷人
    QString strCaseNum;  // 案件编号
    QString strFaWenNum1, strFaWenNum2; // 发文号
    QString strForestUnit;  // 森公单位
    QString strLinYeUnit;   // 林业单位

    QString strCaseNation;  // 民族
    QString strCaseCulture; // 文化
    QString strCaseJob;     // 职业
    QString strCaseHumNumber; // 身份证号码
    QString strCaseHome; // 家庭住址

};



#endif // BASEINFO_H
