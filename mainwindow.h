#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "baseinfo.h"
#include "anqinginfodialog.h"

namespace Ui {
class MainWindow;
}

class QString;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    bool loadJsonInfo();
    bool loadAnQingJsonInfo();
    bool loadTest();
private:
    // 读取config.json文件信息并更新界面
    BaseInfo *baseInfoDlg;
    AnQingInfoDialog *anQingInfoDlg;
    // 合成crimi基本信息发送给文书
    void crimiInfo();
    //////////////////
    bool checkInPutX();

    // 显示
    void displayTheResult(QString str);
    // 保存模板
    bool saveAsFile(QString myFileName);
private slots:
    void on_pushButton_clicked();
    void on_nameOfCase_Edit_textEdited(const QString &arg1);
    void on_comboBoxCase_currentTextChanged(const QString &arg1);
    void on_nameOfCrimi_Edit_textChanged(const QString &arg1);

    void on_dateEditStart_dateChanged(const QDate &date);
    void on_dateEditEnd_dateChanged(const QDate &date);
    void on_dateEditBir_dateChanged(const QDate &date);
    void on_lineEditCheckUnit_textChanged(const QString &arg1);
    void on_lineEditRegUnit_textChanged(const QString &arg1);
    void on_numberOfCase_Edit_textChanged(const QString &arg1);
    void on_lineEditCaseCop_textChanged(const QString &arg1);
    void on_nameOfCase_Edit_textChanged(const QString &arg1);
    void on_textEditAnQingBig_textChanged();
    void on_textEditAnQingSmall_textChanged();
    void on_comboBoxSex_currentTextChanged(const QString &arg1);
    void on_lineEditNation_textChanged(const QString &arg1);
    void on_lineEditEdu_textChanged(const QString &arg1);
    void on_lineEditWork_textChanged(const QString &arg1);
    void on_lineEditCrimiAddr_textChanged(const QString &arg1);
  //  void on_comboBoxDecideUnit_currentIndexChanged(int index);
    void on_lineEditCrimiID_textChanged(const QString &arg1);
    void on_textEditCaseFoundation_textChanged();
    void on_comboBoxFoundationOfCase_currentTextChanged(const QString &arg1);
    void on_textEditCSI_textChanged();

    void on_lineEditChuFaWeiFan_textChanged(const QString &arg1);

    void on_lineEditChuFaYiJu_textChanged(const QString &arg1);

    void on_textEditChuFa_textChanged();



    void on_checkBoxInput_stateChanged(int arg1);
    void on_checkBoxAutoSave_stateChanged(int arg1);

    void on_pushButtonLoad_clicked();

    void on_UnitInfo_Case_triggered();

    void on_pushButton_2_clicked();

    void on_AnQingInfo_triggered();

    void on_lineEditForestUnit_textChanged(const QString &arg1);

    void on_lineEditLinYeUnit_textChanged(const QString &arg1);

    void on_comboBoxDecideUnit_currentIndexChanged(const QString &arg1);



    void on_casePolEdit1_textChanged(const QString &arg1);

    void on_casePolEdit2_textChanged(const QString &arg1);

    void on_caseFuYiEdit_textChanged(const QString &arg1);

    void on_caseCSILocEdit_textChanged(const QString &arg1);

    void on_caseCSITimeEdit_textChanged(const QString &arg1);

    void on_Develop_triggered();

    void on_photo_triggered();

    void on_draw_triggered();

    void on_caseInfo_triggered();

    void on_upCaseTable_triggered();

    void on_rightNotify_triggered();

    void on_blank_triggered();

protected:
    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);
    int m_nTimerID;

private:
    Ui::MainWindow *ui;
    // 当事人基本情况：

    // 简要案情及其处罚


    QString detailsOFCaseBig;
    QString detailsOFCaseSmall;

    // 案件基本情况
    QString caseName; //(属于 滥伐林木案)
    QString nameOfCase;
    QString numberOfCase;
    QString startOfCase;
    QString startOfCaseDot;
    QString EndOfCase;   // 注释掉
    QString endOfCaseDot;
    QString checkUnit;
    QString regUnit;
    QString caseOfCop;
    QString strAutoBir;
    // 处罚主体
    QString caseDecideUnitHao;
    QString caseDecideUnitFuYi;


    // 听证
    QString strTingZheng;
    // CSI

    QString strDisplay;
    // 输出目录
    QString strPrintDir;
    bool checkInput;
    bool checkAutoSave;
    int numberID; // from 0 - .... ex: Case; 0 means : 滥伐林木;
    // 重新定义的变量
    // 封面上用到的变量
    QString strNameCase;  // 案件名
    QString strNumCase;   // 编号
    QString strNameCrimi;  //嫌疑人姓名
    QString strStartCase;   // 立案时间
    QString strEndCase;     // 结案时间
    QString strUpUnitCase;  // 立案单位
    QString strCheckUnitCase; // 审核单位
    QString strNamePol;       // 立卷人
    // 目录中用到的变量
    QString strFaWenHao, strUnitAuthor, strPolAuthor;  // 发文号：苍森公 单位责任者：苍溪县森林公安局 办案人员：权亮、何宗欣
    QString strCasePol1, strCasePol2;
    // 案件调查终结报告用到的变量
    QString strCaseLaiYuan;
    QString strCrimiInfo;
        QString birthdayOfCrimi;
        QString nameOfCrimi;  // 可以注释掉
        QString sexOfCrimi;
        QString eduOfCrimi;
        QString nationOfCrimi;
        QString workOfCrimi;
        QString IDOfCrimi;
        QString addressOfCrimi;
    QString anQingBig;
    QString anQingSmall;
    QString strChuFaWeiFan;
    QString strChuFaYiJu;
    QString strChuFa;
    QString strLittleName;  // 案件小类别：滥伐林木
    QString strFuYi;        // 复议机构
    // 案件来源
    QString caseLaiYuan;
    QString caseFoundation;
    QString caseCheckAddress, caseCheckTime; // 勘验地点和时间
    QString strCSI;

};


#endif // MAINWINDOW_H
