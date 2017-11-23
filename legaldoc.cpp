#include "legaldoc.h"
#include <QAxWidget>
#include <QAxObject>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>


legalDoc::legalDoc()
{

    // 创建临时文件夹
    strPrintDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDir *temp = new QDir;
    if(!temp->exists(strPrintDir+"/临时案卷文档"))
    {
        temp->mkdir(strPrintDir+"/临时案卷文档");

    }
    strPrintDir += "/临时案卷文档";

}
// 打开输出文件
void legalDoc::openExplor()
{

    QString path = strPrintDir;
    path.replace("/","\\");
    QProcess::startDetached("explorer "+path);
}


// 创建封面
void legalDoc::CreatCaseCoverTest(QString strNameCase, QString strNumCase, QString strNameCrimi, QString strStartCase,
                                  QString strEndCase, QString strUpUnitCase, QString strCheckUnitCase, QString strNamePol)
{
     QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
     if (word->isNull())
     {
         QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
         return ;
     }
     QAxObject *documents = word->querySubObject("Documents");
     QDir dir;
     QString path = dir.currentPath()+"/temple/cover.doc";


     documents->dynamicCall("Add(QString)", path);
     QAxObject *document = word->querySubObject("ActiveDocument");
     // 案件名称
     QAxObject *bookmark_test = document->querySubObject("Bookmarks(QVariant)", "nameOfCase");
     if(!bookmark_test->isNull())
     {
         bookmark_test->dynamicCall("Select(void)");
         bookmark_test->querySubObject("Range")->setProperty("Text", strNameCase);
     }
     // 案件编号
     QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
     if(!bookmark_numberOfCase->isNull())
     {
         bookmark_numberOfCase->dynamicCall("Select(void)");
         bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
     }
     // 违法行为人
     QAxObject*bookmark_crimiOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
     if(!bookmark_crimiOfCase->isNull())
     {
         bookmark_crimiOfCase->dynamicCall("Select(void)");
         bookmark_crimiOfCase->querySubObject("Range")->setProperty("Text",strNameCrimi);
     }
     // 立案时间
     QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");
     if(!bookmark_startOfCase->isNull())
     {
         bookmark_startOfCase->dynamicCall("Select(void)");
         bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strStartCase);
     }
     //结案时间
     QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
     if(!bookmark_endOfCase->isNull())
     {
         bookmark_endOfCase->dynamicCall("Select(void)");
         bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strEndCase);
     }
     // 立卷单位
     QAxObject*bookmark_regUnit=document->querySubObject("Bookmarks(QVariant)","regUnit");
     if(!bookmark_regUnit->isNull())
     {
         bookmark_regUnit->dynamicCall("Select(void)");
         bookmark_regUnit->querySubObject("Range")->setProperty("Text",strUpUnitCase);
     }
     // 审核单位
     QAxObject*bookmark_checkUnit=document->querySubObject("Bookmarks(QVariant)","checkUnit");
     if(!bookmark_checkUnit->isNull())
     {
        bookmark_checkUnit->dynamicCall("Select(void)");
        bookmark_checkUnit->querySubObject("Range")->setProperty("Text",strCheckUnitCase);
     }
     // 插入立卷人
     QAxObject*bookmark_caseOfCop=document->querySubObject("Bookmarks(QVariant)","caseOfCop");
     if(!bookmark_caseOfCop->isNull())
     {
        bookmark_caseOfCop->dynamicCall("Select(void)");
        bookmark_caseOfCop->querySubObject("Range")->setProperty("Text",strNamePol);
     }
     document->dynamicCall("SaveAs(const QString&)", QString(strPrintDir+"/1封面.doc"));
     document->dynamicCall("Close (boolean)", false);
     word->dynamicCall("Quit()");
}

// 创建目录
void legalDoc::CreateCaseContent(QString strUnitAuthor, QString strPolAuthor, QString strFaWenHao, QString strNumCase,QString strStartCase,QString strEndCase)
{
    QAxObject *excel = new QAxObject();
    excel->setControl("Excel.Application");//连接Excel控件
    excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
    QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
    QDir dir;
    QString path = dir.currentPath()+"/temple/content.xls";
    workbooks->dynamicCall("Add(QString)", path);//新建一个工作簿
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1

    // 责任单位
    QAxObject *cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B4");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B3");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B6");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B8");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B10");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B12");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B14");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B16");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B19");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B21");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B32");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B33");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B36");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    cellUnitAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B42");
    cellUnitAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strUnitAuthor));

    // 责任人
    QAxObject *cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B17");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B18");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));


    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B23");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B24");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B25");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B26");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B27");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B28");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B29");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B30");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B31");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B35");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B37");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B38");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B39");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B40");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B41");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    cellPolAuthor = worksheet->querySubObject("Range(QVariant,QVariant)", "B43");
    cellPolAuthor->dynamicCall("SetValue(const QVariant&)", QVariant(strPolAuthor));

    // 发文号
    QAxObject *cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C4");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C6");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C8");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));


    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C10");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C12");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C14");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C21");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    cellFaWenHao = worksheet->querySubObject("Range(QVariant,QVariant)", "C19");
    cellFaWenHao->dynamicCall("SetValue(const QVariant&)", QVariant(strFaWenHao));

    // 发文编号
    QAxObject *cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C5");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C7");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C9");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C11");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C13");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C15");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C20");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    cellFaWenNumber = worksheet->querySubObject("Range(QVariant,QVariant)", "C22");
    cellFaWenNumber->dynamicCall("SetValue(const QVariant&)", QVariant(strNumCase));

    // 案件时间
    strStartCase.replace("年", ".");
    strStartCase.replace("月", ".");
    strStartCase.replace("日", "");

    strEndCase.replace("年", ".");
    strEndCase.replace("月", ".");
    strEndCase.replace("日", "");

    QAxObject *cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F3");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F4");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F6");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F8");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F12");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F14");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F19");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F21");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F26");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F27");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F28");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F29");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F30");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F32");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F33");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F34");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F35");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F36");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F37");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F38");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F39");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F40");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F41");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F43");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strEndCase));

    // 开始时间

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F10");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F16");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F17");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F18");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F23");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));


    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F24");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F25");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F31");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));

    cellTime = worksheet->querySubObject("Range(QVariant,QVariant)", "F42");
    cellTime->dynamicCall("SetValue(const QVariant&)", QVariant(strStartCase));



    workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(strPrintDir+"/2目录.xls"));
    workbook->dynamicCall("Close(boolean)", false);//关闭工作簿
    excel->dynamicCall("Quit()");//关闭excel
    delete excel;
    excel=NULL;


}

// 创建案件调查终结报告
void legalDoc::CreateCaseDoneReport(QString strCaseLaiYuan, QString strCaseBaseInfo, QString strCaseAnQingBig, QString strCaseCrimi, QString strCaseWeiFan, QString strCaseYiJu, QString strLittleName,QString strCaseChuFa, QString strCaseUnit, QString strCasePol, QString strCaseTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDoneReport.doc";


    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    QAxObject *bookmark_caseLaiYuan = document->querySubObject("Bookmarks(QVariant)", "caseLaiYuan");
    if(!bookmark_caseLaiYuan->isNull())
    {
        bookmark_caseLaiYuan->dynamicCall("Select(void)");
        bookmark_caseLaiYuan->querySubObject("Range")->setProperty("Text", strCaseLaiYuan);
    }

    QAxObject *bookmark_caseBaseInfo = document->querySubObject("Bookmarks(QVariant)", "caseBaseInfo");
    if(!bookmark_caseBaseInfo->isNull())
    {
        bookmark_caseBaseInfo->dynamicCall("Select(void)");
        bookmark_caseBaseInfo->querySubObject("Range")->setProperty("Text", strCaseBaseInfo);
    }

    QAxObject *bookmark_caseAnQingBig = document->querySubObject("Bookmarks(QVariant)", "caseAnQingBig");
    if(!bookmark_caseAnQingBig->isNull())
    {
        bookmark_caseAnQingBig->dynamicCall("Select(void)");
        bookmark_caseAnQingBig->querySubObject("Range")->setProperty("Text", strCaseAnQingBig);
    }

    QAxObject *bookmark_caseCrimi = document->querySubObject("Bookmarks(QVariant)", "caseCrimi");
    if(!bookmark_caseCrimi->isNull())
    {
        bookmark_caseCrimi->dynamicCall("Select(void)");
        bookmark_caseCrimi->querySubObject("Range")->setProperty("Text", strCaseCrimi);
    }

    QAxObject *bookmark_caseCrimi2 = document->querySubObject("Bookmarks(QVariant)", "caseCrimi2");
    if(!bookmark_caseCrimi2->isNull())
    {
        bookmark_caseCrimi2->dynamicCall("Select(void)");
        bookmark_caseCrimi2->querySubObject("Range")->setProperty("Text", strCaseCrimi);
    }


    QAxObject *bookmark_caseWeiFan = document->querySubObject("Bookmarks(QVariant)", "caseWeiFan");
    if(!bookmark_caseWeiFan->isNull())
    {
        bookmark_caseWeiFan->dynamicCall("Select(void)");
        bookmark_caseWeiFan->querySubObject("Range")->setProperty("Text", strCaseWeiFan);
    }

    QAxObject *bookmark_caseYiJu = document->querySubObject("Bookmarks(QVariant)", "caseYiJu");
    if(!bookmark_caseYiJu->isNull())
    {
        bookmark_caseYiJu->dynamicCall("Select(void)");
        bookmark_caseYiJu->querySubObject("Range")->setProperty("Text", strCaseYiJu);
    }


    QAxObject *bookmark_caseName = document->querySubObject("Bookmarks(QVariant)", "caseName");
    if(!bookmark_caseName->isNull())
    {
        bookmark_caseName->dynamicCall("Select(void)");
        bookmark_caseName->querySubObject("Range")->setProperty("Text", strLittleName);
    }

    strCaseChuFa += "\n"; // 修正格式
    QAxObject *bookmark_caseChuFa = document->querySubObject("Bookmarks(QVariant)", "caseChuFa");
    if(!bookmark_caseChuFa->isNull())
    {
        bookmark_caseChuFa->dynamicCall("Select(void)");
        bookmark_caseChuFa->querySubObject("Range")->setProperty("Text", strCaseChuFa);
    }

    QAxObject *bookmark_caseUnit = document->querySubObject("Bookmarks(QVariant)", "caseUnit");
    if(!bookmark_caseUnit->isNull())
    {
        bookmark_caseUnit->dynamicCall("Select(void)");
        bookmark_caseUnit->querySubObject("Range")->setProperty("Text", strCaseUnit);
    }

    QAxObject *bookmark_casePol = document->querySubObject("Bookmarks(QVariant)", "casePol");
    if(!bookmark_casePol->isNull())
    {
        bookmark_casePol->dynamicCall("Select(void)");
        bookmark_casePol->querySubObject("Range")->setProperty("Text", strCasePol);
    }

    QAxObject *bookmark_caseTime = document->querySubObject("Bookmarks(QVariant)", "caseTime");
    if(!bookmark_caseTime->isNull())
    {
        bookmark_caseTime->dynamicCall("Select(void)");
        bookmark_caseTime->querySubObject("Range")->setProperty("Text", strCaseTime);
    }


    document->dynamicCall("SaveAs(const QString&)", QString(strPrintDir+"/3案件调查终结报告.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");

}

// 处罚决定书
void legalDoc::CreateCaseDecideBook(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCrimi, QString strSexCrimi, QString strBirDCrimi, QString strID, QString strAddress, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strFuYi, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDecideBook.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }

    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }

    // 插入性别
    QAxObject*bookmark_sexOfCrimi=document->querySubObject("Bookmarks(QVariant)","sexOfCrimi");
    if(!bookmark_sexOfCrimi->isNull()){
    bookmark_sexOfCrimi->dynamicCall("Select(void)");
    bookmark_sexOfCrimi->querySubObject("Range")->setProperty("Text",strSexCrimi);
   }

    // 插入出生日期
    QAxObject*bookmark_birthdayOfCrimi=document->querySubObject("Bookmarks(QVariant)","birthdayOfCrimi");
    if(!bookmark_birthdayOfCrimi->isNull()){
    bookmark_birthdayOfCrimi->dynamicCall("Select(void)");
    bookmark_birthdayOfCrimi->querySubObject("Range")->setProperty("Text",strBirDCrimi);
   }
    // 插入ID
    QAxObject*bookmark_IDOfCrimi=document->querySubObject("Bookmarks(QVariant)","IDOfCrimi");
    if(!bookmark_IDOfCrimi->isNull()){
    bookmark_IDOfCrimi->dynamicCall("Select(void)");
    bookmark_IDOfCrimi->querySubObject("Range")->setProperty("Text",strID);
   }

    // 插入家庭住址
    QAxObject*bookmark_addressOfCrimi=document->querySubObject("Bookmarks(QVariant)","addressOfCrimi");
    if(!bookmark_addressOfCrimi->isNull()){
    bookmark_addressOfCrimi->dynamicCall("Select(void)");
    bookmark_addressOfCrimi->querySubObject("Range")->setProperty("Text",strAddress);
   }
    // 插入案情small
     QAxObject*bookmark_anQingSmall=document->querySubObject("Bookmarks(QVariant)","anQingSmall");
     if(!bookmark_anQingSmall->isNull()){
     bookmark_anQingSmall->dynamicCall("Select(void)");
     bookmark_anQingSmall->querySubObject("Range")->setProperty("Text",strAnQingSmall);
    }
     // 插入处罚违法
     QAxObject*bookmark_strLawItemLanFaWeiFa=document->querySubObject("Bookmarks(QVariant)","strLawItemLanFaWeiFan");
     if(!bookmark_strLawItemLanFaWeiFa->isNull()){
     bookmark_strLawItemLanFaWeiFa->dynamicCall("Select(void)");
     bookmark_strLawItemLanFaWeiFa->querySubObject("Range")->setProperty("Text",strLawItemWeiFan);
    }
    // 插入依据
     QAxObject*bookmark_strLawItemLanFaYiJu=document->querySubObject("Bookmarks(QVariant)","strLawItemLanFaYiJu");
     if(!bookmark_strLawItemLanFaYiJu->isNull()){
     bookmark_strLawItemLanFaYiJu->dynamicCall("Select(void)");
     bookmark_strLawItemLanFaYiJu->querySubObject("Range")->setProperty("Text",strLawItemYiJu);
    }

     // 插入处罚
     QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
     if(!bookmark_strChuFa->isNull()){
     bookmark_strChuFa->dynamicCall("Select(void)");
     bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
    }
     // 插入复议机构
     QAxObject*bookmark_caseDecideUnitFuYi=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitFuYi");
     if(!bookmark_caseDecideUnitFuYi->isNull()){
     bookmark_caseDecideUnitFuYi->dynamicCall("Select(void)");
     bookmark_caseDecideUnitFuYi->querySubObject("Range")->setProperty("Text",strFuYi);
    }
     // 插入调查终结时间
     QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
     if(!bookmark_endOfCase->isNull()){
     bookmark_endOfCase->dynamicCall("Select(void)");
     bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
    }


     document->dynamicCall("SaveAs(const QString&)", QString(strPrintDir+"/4.处罚决定书.doc"));
     document->dynamicCall("Close (boolean)", false);
     word->dynamicCall("Quit()");



}

void legalDoc::CreateCaseSend(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strNameCrimi)
{

    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/SendCaseDecide.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    QAxObject*bookmark_caseDecideUnitHao2=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao2");
    if(!bookmark_caseDecideUnitHao2->isNull()){
    bookmark_caseDecideUnitHao2->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao2->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    QAxObject*bookmark_caseDecideUnitHao3=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao3");
    if(!bookmark_caseDecideUnitHao3->isNull()){
    bookmark_caseDecideUnitHao3->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao3->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    QAxObject*bookmark_caseDecideUnitHao4=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao4");
    if(!bookmark_caseDecideUnitHao4->isNull()){
    bookmark_caseDecideUnitHao4->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao4->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }
    QAxObject*bookmark_numberOfCase2=document->querySubObject("Bookmarks(QVariant)","numberOfCase2");
    if(!bookmark_numberOfCase2->isNull()){
    bookmark_numberOfCase2->dynamicCall("Select(void)");
    bookmark_numberOfCase2->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }
    QAxObject*bookmark_numberOfCase3=document->querySubObject("Bookmarks(QVariant)","numberOfCase3");
    if(!bookmark_numberOfCase3->isNull()){
    bookmark_numberOfCase3->dynamicCall("Select(void)");
    bookmark_numberOfCase3->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }
    QAxObject*bookmark_numberOfCase4=document->querySubObject("Bookmarks(QVariant)","numberOfCase4");
    if(!bookmark_numberOfCase4->isNull()){
    bookmark_numberOfCase4->dynamicCall("Select(void)");
    bookmark_numberOfCase4->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }
    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }
    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strNameCase);
   }
    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/6.送达回执.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

// 立案登记表
void legalDoc::CreateCaseUp(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strFoundation, QString strTime, QString strNameCrimi, QString strSexCrimi, QString strBirDCrimi, QString strAddress, QString strLaiYuan)
{

    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseUpTable.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }
    // 插入举报
    QAxObject*bookmark_foundationOfCase=document->querySubObject("Bookmarks(QVariant)","foundationOfCase");
    if(!bookmark_foundationOfCase->isNull()){
    bookmark_foundationOfCase->dynamicCall("Select(void)");
    bookmark_foundationOfCase->querySubObject("Range")->setProperty("Text",strFoundation);
    }
    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strNameCase);
   }
    // 插入案件开始时间
    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");

    if(!bookmark_startOfCase->isNull()){
    bookmark_startOfCase->dynamicCall("Select(void)");
    bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }
    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }
    // 插入性别
    QAxObject*bookmark_sexOfCrimi=document->querySubObject("Bookmarks(QVariant)","sexOfCrimi");
    if(!bookmark_sexOfCrimi->isNull()){
    bookmark_sexOfCrimi->dynamicCall("Select(void)");
    bookmark_sexOfCrimi->querySubObject("Range")->setProperty("Text",strSexCrimi);
   }

    // 插入出生日期
    QAxObject*bookmark_birthdayOfCrimi=document->querySubObject("Bookmarks(QVariant)","birthdayOfCrimi");
    if(!bookmark_birthdayOfCrimi->isNull()){
    bookmark_birthdayOfCrimi->dynamicCall("Select(void)");
    bookmark_birthdayOfCrimi->querySubObject("Range")->setProperty("Text",strBirDCrimi);
   }
    // 插入家庭住址
    QAxObject*bookmark_addressOfCrimi=document->querySubObject("Bookmarks(QVariant)","addressOfCrimi");
    if(!bookmark_addressOfCrimi->isNull()){
    bookmark_addressOfCrimi->dynamicCall("Select(void)");
    bookmark_addressOfCrimi->querySubObject("Range")->setProperty("Text",strAddress);
   }


    // 案件来源
    QAxObject*bookmark_caseLaiYuan=document->querySubObject("Bookmarks(QVariant)","caseLaiYuan");
    if(!bookmark_caseLaiYuan->isNull()){
    bookmark_caseLaiYuan->dynamicCall("Select(void)");
    bookmark_caseLaiYuan->querySubObject("Range")->setProperty("Text",strLaiYuan);
   }



    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/7.立案登记表（删除简要案情多余部分）.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");

}

// 处罚意见书
void legalDoc::CreateCaseDecideIdea(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strTime, QString strNameCrimi, QString strSexCrimi, QString strBirDCrimi, QString strIDCrimi, QString strAddress,  QString strAnQingBig)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDecideIdea.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseDecideUnitHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumOfCase);
    }


      // 插入案件名称
      QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

      if(!bookmark_nameOfCase->isNull()){
      bookmark_nameOfCase->dynamicCall("Select(void)");
      bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strNameCase);
     }
      // 插入案件开始时间
      QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");

      if(!bookmark_startOfCase->isNull()){
      bookmark_startOfCase->dynamicCall("Select(void)");
      bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strTime);
     }
      // 插入违法行为人名称
      QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
      if(!bookmark_nameOfCrimi->isNull()){
      bookmark_nameOfCrimi->dynamicCall("Select(void)");
      bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
     }
      // 插入性别
      QAxObject*bookmark_sexOfCrimi=document->querySubObject("Bookmarks(QVariant)","sexOfCrimi");
      if(!bookmark_sexOfCrimi->isNull()){
      bookmark_sexOfCrimi->dynamicCall("Select(void)");
      bookmark_sexOfCrimi->querySubObject("Range")->setProperty("Text",strSexCrimi);
     }

      // 插入出生日期
      QAxObject*bookmark_birthdayOfCrimi=document->querySubObject("Bookmarks(QVariant)","birthdayOfCrimi");
      if(!bookmark_birthdayOfCrimi->isNull()){
      bookmark_birthdayOfCrimi->dynamicCall("Select(void)");
      bookmark_birthdayOfCrimi->querySubObject("Range")->setProperty("Text",strBirDCrimi);
     }
      // 插入ID
      QAxObject*bookmark_IDOfCrimi=document->querySubObject("Bookmarks(QVariant)","IDOfCrimi");
      if(!bookmark_IDOfCrimi->isNull()){
      bookmark_IDOfCrimi->dynamicCall("Select(void)");
      bookmark_IDOfCrimi->querySubObject("Range")->setProperty("Text",strIDCrimi);
     }

      // 插入家庭住址
      QAxObject*bookmark_addressOfCrimi=document->querySubObject("Bookmarks(QVariant)","addressOfCrimi");
      if(!bookmark_addressOfCrimi->isNull()){
      bookmark_addressOfCrimi->dynamicCall("Select(void)");
      bookmark_addressOfCrimi->querySubObject("Range")->setProperty("Text",strAddress);
     }


      // 插入案情big
       QAxObject*bookmark_anQingBig=document->querySubObject("Bookmarks(QVariant)","anQingBig");
       if(!bookmark_anQingBig->isNull()){
       bookmark_anQingBig->dynamicCall("Select(void)");
       bookmark_anQingBig->querySubObject("Range")->setProperty("Text",strAnQingBig);
      }


    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/8.处罚意见书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}
// 分期缴纳罚款
void legalDoc::CreateCaseFenQi(QString strCaseHao, QString strNumCase, QString strNameCrimi, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseFengQiJiaoNa.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    QAxObject*bookmark_caseDecideUnitHao2=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao2");
    if(!bookmark_caseDecideUnitHao2->isNull()){
    bookmark_caseDecideUnitHao2->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao2->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    QAxObject*bookmark_caseDecideUnitHao3=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao3");
    if(!bookmark_caseDecideUnitHao3->isNull()){
    bookmark_caseDecideUnitHao3->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao3->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }

    QAxObject*bookmark_numberOfCase2=document->querySubObject("Bookmarks(QVariant)","numberOfCase2");
    if(!bookmark_numberOfCase2->isNull()){
    bookmark_numberOfCase2->dynamicCall("Select(void)");
    bookmark_numberOfCase2->querySubObject("Range")->setProperty("Text",strNumCase);
    }
    QAxObject*bookmark_numberOfCase3=document->querySubObject("Bookmarks(QVariant)","numberOfCase3");
    if(!bookmark_numberOfCase3->isNull()){
    bookmark_numberOfCase3->dynamicCall("Select(void)");
    bookmark_numberOfCase3->querySubObject("Range")->setProperty("Text",strNumCase);
    }

    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }

    // 插入结束时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }
    QAxObject*bookmark_endOfCase2=document->querySubObject("Bookmarks(QVariant)","endOfCase2");
    if(!bookmark_endOfCase2->isNull()){
    bookmark_endOfCase2->dynamicCall("Select(void)");
    bookmark_endOfCase2->querySubObject("Range")->setProperty("Text",strTime);
   }


    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/9.延期缴纳罚款决定书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateCaseBaoJing(QString strCaseHao, QString strNumCase, QString strTime, QString strLaiYuan)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/casePolice.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }

    // 插入案件开始时间
    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");

    if(!bookmark_startOfCase->isNull()){
    bookmark_startOfCase->dynamicCall("Select(void)");
    bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }

    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }

    // 案件来源
    QAxObject*bookmark_foundationOfCase=document->querySubObject("Bookmarks(QVariant)","foundationOfCase");
    if(!bookmark_foundationOfCase->isNull()){
    bookmark_foundationOfCase->dynamicCall("Select(void)");
    bookmark_foundationOfCase->querySubObject("Range")->setProperty("Text",strLaiYuan);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/10.受理报警登记表（删除接警内容多余部分）.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateCaseRight()
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseRightNotify.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");




    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/11.权利义务告知书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateCaseFirstNotify(QString strCaseHao, QString strNumCase, QString strNameCrimi, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseFirstNotity.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");



    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }
    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }
    // 案情small
    QAxObject*bookmark_anQingSmall=document->querySubObject("Bookmarks(QVariant)","anQingSmall");
    if(!bookmark_anQingSmall->isNull()){
    bookmark_anQingSmall->dynamicCall("Select(void)");
    bookmark_anQingSmall->querySubObject("Range")->setProperty("Text",strAnQingSmall);
   }

    // 插入处罚违法
    QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
    if(!bookmark_strChuFaWeiFan->isNull()){
    bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
    bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strLawItemWeiFan);
   }
   // 插入依据
    QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu");
    if(!bookmark_strChuFaYiJu->isNull()){
    bookmark_strChuFaYiJu->dynamicCall("Select(void)");
    bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strLawItemYiJu);
   }

    // 插入处罚
    strChuFa += "\n";
    QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
    if(!bookmark_strChuFa->isNull()){
    bookmark_strChuFa->dynamicCall("Select(void)");
    bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
   }

    // 插入调查终结时间

    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");

    if(!bookmark_startOfCase->isNull())
    {
    bookmark_startOfCase->dynamicCall("Select(void)");
    bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }



    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/12.先行告知书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


}
// 听证权利
void legalDoc::CreateCaseTingZheng(QString strCaseHao, QString strNumCase, QString strNameCrimi, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strTingZheng, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseTingZheng.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }

    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }
    // 案情small
    strAnQingSmall += "\n";
    QAxObject*bookmark_anQingSmall=document->querySubObject("Bookmarks(QVariant)","anQingSmall");
    if(!bookmark_anQingSmall->isNull()){
    bookmark_anQingSmall->dynamicCall("Select(void)");
    bookmark_anQingSmall->querySubObject("Range")->setProperty("Text",strAnQingSmall);
   }

    // 插入处罚违法
    QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
    if(!bookmark_strChuFaWeiFan->isNull()){
    bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
    bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strLawItemWeiFan);
   }
   // 插入依据
    QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu");
    if(!bookmark_strChuFaYiJu->isNull()){
    bookmark_strChuFaYiJu->dynamicCall("Select(void)");
    bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strLawItemYiJu);
   }

    // 插入处罚
    QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
    if(!bookmark_strChuFa->isNull()){
    bookmark_strChuFa->dynamicCall("Select(void)");
    bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
   }

    // 插入调查终结时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }
    // 插入


    QAxObject*bookmark_strTingZheng=document->querySubObject("Bookmarks(QVariant)","strTingZheng");
    if(!bookmark_strTingZheng->isNull()){
    bookmark_strTingZheng->dynamicCall("Select(void)");
    bookmark_strTingZheng->querySubObject("Range")->setProperty("Text",strTingZheng);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/13.听证权利义务告知书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


}

void legalDoc::CreateCSI(QString strCheckTime, QString strCheckAddr, QString strNameCrimi, QString strIDCrimi, QString strCrimiAddr, QString strCSI, QString strTime)
{

    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseCSI.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");



    // 检查时间
    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","checkTime");

    if(!bookmark_startOfCase->isNull())
    {
       bookmark_startOfCase->dynamicCall("Select(void)");
       bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strCheckTime);
    }


    // 检查地点
    QAxObject*bookmark_checkAddr=document->querySubObject("Bookmarks(QVariant)","checkAddress");
    if(!bookmark_checkAddr->isNull()){
    bookmark_checkAddr->dynamicCall("Select(void)");
    bookmark_checkAddr->querySubObject("Range")->setProperty("Text",strCheckAddr);
   }


    // 插入违法行为人名称
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
   }

    // 插入ID
    QAxObject*bookmark_IDOfCrimi=document->querySubObject("Bookmarks(QVariant)","IDOfCrimi");
    if(!bookmark_IDOfCrimi->isNull()){
    bookmark_IDOfCrimi->dynamicCall("Select(void)");
    bookmark_IDOfCrimi->querySubObject("Range")->setProperty("Text",strIDCrimi);
   }
    // address_crimi
    QAxObject*bookmark_addressOfCrimi=document->querySubObject("Bookmarks(QVariant)","addressOfCrimi");
    if(!bookmark_addressOfCrimi->isNull()){
    bookmark_addressOfCrimi->dynamicCall("Select(void)");
    bookmark_addressOfCrimi->querySubObject("Range")->setProperty("Text",strCrimiAddr);
   }

    // 插入CSI
    QAxObject*bookmark_strCSI=document->querySubObject("Bookmarks(QVariant)","strCSI");
    if(!bookmark_strCSI->isNull()){
    bookmark_strCSI->dynamicCall("Select(void)");
    bookmark_strCSI->querySubObject("Range")->setProperty("Text",strCSI);
   }

   QAxObject*bookmark_startOfCase3=document->querySubObject("Bookmarks(QVariant)","startOfCase");

    if(!bookmark_startOfCase3->isNull()){
    bookmark_startOfCase3->dynamicCall("Select(void)");
    bookmark_startOfCase3->querySubObject("Range")->setProperty("Text",strTime);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/14.现场勘验笔录.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


}

void legalDoc::CreateCaseDoneOK(QString strCaseHao, QString strNumCase, QString strCaseName, QString strLaiYuan, QString strAnQingSmall, QString strCaseLittleName, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDoneReportOk.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseDecideUnitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    // 插入案件编号
      QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");

      if(!bookmark_numberOfCase->isNull()){
      bookmark_numberOfCase->dynamicCall("Select(void)");
      bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
     }
      // 插入案件名称
      QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

      if(!bookmark_nameOfCase->isNull()){
      bookmark_nameOfCase->dynamicCall("Select(void)");
      bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
     }
      // 案件来源
      QAxObject*bookmark_foundationOfCase=document->querySubObject("Bookmarks(QVariant)","foundationOfCase");
      if(!bookmark_foundationOfCase->isNull()){
      bookmark_foundationOfCase->dynamicCall("Select(void)");
      bookmark_foundationOfCase->querySubObject("Range")->setProperty("Text",strLaiYuan);
     }


      // 插入案情small
       QAxObject*bookmark_anQingSmall=document->querySubObject("Bookmarks(QVariant)","anQingSmall");
       if(!bookmark_anQingSmall->isNull()){
       bookmark_anQingSmall->dynamicCall("Select(void)");
       bookmark_anQingSmall->querySubObject("Range")->setProperty("Text",strAnQingSmall);
      }

       // 插入处罚违法
       QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
       if(!bookmark_strChuFaWeiFan->isNull()){
       bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
       bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strLawItemWeiFan);
      }
      // 插入依据
       QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu");
       if(!bookmark_strChuFaYiJu->isNull()){
       bookmark_strChuFaYiJu->dynamicCall("Select(void)");
       bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strLawItemYiJu);
      }
       // 插入属于XX（滥伐林木）这里把案件类别删除掉案 这个字
       QAxObject*bookmark_caseName=document->querySubObject("Bookmarks(QVariant)","caseName");
       if(!bookmark_caseName->isNull()){
       bookmark_caseName->dynamicCall("Select(void)");
       bookmark_caseName->querySubObject("Range")->setProperty("Text",strCaseLittleName);
      }

       // 插入处罚
       QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
       if(!bookmark_strChuFa->isNull()){
       strChuFa += '\n';
       bookmark_strChuFa->dynamicCall("Select(void)");
       bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
      }



      // 将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
      document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/15.调查终结呈批表.doc"));
      document->dynamicCall("Close (boolean)", false);
      word->dynamicCall("Quit()");

}

void legalDoc::CreateCaseMoShou(QString strCaseHao, QString strNumCase, QString strCaseName, QString strAnQingBig, QString strNameCrimi, QString strWeiFan, QString strCaseLittleName, QString strYiJu, QString strChuFa)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseIsMoShou.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }

    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }


    // 插入案情big
     QAxObject*bookmark_anQingBig=document->querySubObject("Bookmarks(QVariant)","anQingBig");
     if(!bookmark_anQingBig->isNull()){
     bookmark_anQingBig->dynamicCall("Select(void)");
     bookmark_anQingBig->querySubObject("Range")->setProperty("Text",strAnQingBig);
    }

     // 插入违法行为人名称
     QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
     if(!bookmark_nameOfCrimi->isNull()){
     bookmark_nameOfCrimi->dynamicCall("Select(void)");
     bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
    }



      // 插入处罚违法
      QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strWeiFan");
      if(!bookmark_strChuFaWeiFan->isNull()){
      bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
      bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strWeiFan);
     }
     // 插入依据
      QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strYiJu");
      if(!bookmark_strChuFaYiJu->isNull()){
      bookmark_strChuFaYiJu->dynamicCall("Select(void)");
      bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strYiJu);
     }
      // 案件类别
      QAxObject*bookmark_caseName=document->querySubObject("Bookmarks(QVariant)","strCase");
      if(!bookmark_caseName->isNull()){
      bookmark_caseName->dynamicCall("Select(void)");
      bookmark_caseName->querySubObject("Range")->setProperty("Text",strCaseLittleName);
     }

      // 插入处罚
      strChuFa += "\n";
      QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
      if(!bookmark_strChuFa->isNull()){
      bookmark_strChuFa->dynamicCall("Select(void)");
      bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
     }


     document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/16.没收物品呈批表.doc"));
     document->dynamicCall("Close (boolean)", false);
     word->dynamicCall("Quit()");
}

void legalDoc::CreateCaseBianJia(QString strCaseHao, QString strNumCase, QString strCaseName, QString strAnQingBig, QString strNameCrimi, QString strWeiFan, QString strCaseLittleName, QString strYiJu, QString strChuFa)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseBianJia.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }

    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
    }


    // 插入案情big
     QAxObject*bookmark_anQingBig=document->querySubObject("Bookmarks(QVariant)","anQingBig");
     if(!bookmark_anQingBig->isNull()){
     bookmark_anQingBig->dynamicCall("Select(void)");
     bookmark_anQingBig->querySubObject("Range")->setProperty("Text",strAnQingBig);
    }

     // 插入违法行为人名称
     QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
     if(!bookmark_nameOfCrimi->isNull()){
     bookmark_nameOfCrimi->dynamicCall("Select(void)");
     bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
    }



      // 插入处罚违法
      QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
      if(!bookmark_strChuFaWeiFan->isNull()){
      bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
      bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strWeiFan);
     }
     // 插入依据
      QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu");
      if(!bookmark_strChuFaYiJu->isNull()){
      bookmark_strChuFaYiJu->dynamicCall("Select(void)");
      bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strYiJu);
     }
      // 插入属于XX（滥伐林木）这里把案件类别删除掉案 这个字
      QAxObject*bookmark_caseName=document->querySubObject("Bookmarks(QVariant)","caseName");
      if(!bookmark_caseName->isNull()){
      bookmark_caseName->dynamicCall("Select(void)");
      bookmark_caseName->querySubObject("Range")->setProperty("Text",strCaseLittleName);
     }

      // 插入处罚
      strChuFa += "\n";
      QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
      if(!bookmark_strChuFa->isNull()){
      bookmark_strChuFa->dynamicCall("Select(void)");
      bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
     }


     document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/17.变价处理呈批表.doc"));
     document->dynamicCall("Close (boolean)", false);
     word->dynamicCall("Quit()");
}

void legalDoc::CreateMoshouList(QString strCaseHao, QString strNameCrimi, QString strNumCase)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseMoShouList.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }

    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");

    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
   }
    // 插入违法行为人姓名
    QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
    if(!bookmark_nameOfCrimi->isNull()){
    bookmark_nameOfCrimi->dynamicCall("Select(void)");
    bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/24.没收物品清单.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateWoodCost()
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseWoodCost.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");



    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/25.木材价格计算方式.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateCasePlease(QString strUnitAuthor, QString strTime, QString strLittleName)
{

    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/casePlease.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    QAxObject*bookmark_caseName=document->querySubObject("Bookmarks(QVariant)","caseName");
    if(!bookmark_caseName->isNull()){
    bookmark_caseName->dynamicCall("Select(void)");
    bookmark_caseName->querySubObject("Range")->setProperty("Text",strLittleName);
   }

    // 申请单位

    QAxObject*bookmark_caseUnit=document->querySubObject("Bookmarks(QVariant)","caseUnit");
    if(!bookmark_caseUnit->isNull()){
    bookmark_caseUnit->dynamicCall("Select(void)");
    bookmark_caseUnit->querySubObject("Range")->setProperty("Text",strUnitAuthor);
   }
    // 插入申请时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/26.延期缴纳罚款申请书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateGiveMe(QString strUnitAuthor, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/casePleaseGiveMe.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 申请单位

    QAxObject*bookmark_caseUnit=document->querySubObject("Bookmarks(QVariant)","caseUnit");
    if(!bookmark_caseUnit->isNull()){
    strUnitAuthor += "\n";
    bookmark_caseUnit->dynamicCall("Select(void)");
    bookmark_caseUnit->querySubObject("Range")->setProperty("Text",strUnitAuthor);
   }
    // 插入申请时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/27.申请变价处理.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");





}

void legalDoc::CreateWeiTuo(QString strUnitAuthor, QString strCaseHao, QString strNumCase, QString strUnitAuthorPol, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseWeiTuo.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 委托单位
    QAxObject*bookmark_strTingZheng=document->querySubObject("Bookmarks(QVariant)","caseUnitAuthor");
    if(!bookmark_strTingZheng->isNull()){
    bookmark_strTingZheng->dynamicCall("Select(void)");
    bookmark_strTingZheng->querySubObject("Range")->setProperty("Text",strUnitAuthor);
   }


    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","unitHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }

    // 插入案件编号
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","unitNumber");

    if(!bookmark_numberOfCase->isNull()){
    bookmark_numberOfCase->dynamicCall("Select(void)");
    bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strNumCase);
   }

    QAxObject *bookmark_casePol = document->querySubObject("Bookmarks(QVariant)", "unitAuthorPol");
    if(!bookmark_casePol->isNull())
    {
        bookmark_casePol->dynamicCall("Select(void)");
        bookmark_casePol->querySubObject("Range")->setProperty("Text", strUnitAuthorPol);
    }

    // 插入结束时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","strTime");
    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }


    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/28.代缴罚款申请书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


}

void legalDoc::CreateHeYi(QString strNameCase, QString strTime, QString strAnQingBig, QString strCasePol, QString strNameCrimi, QString strLawWeiFan, QString strCaseLittleName, QString strLawYiJu, QString strChuFa)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseHeYi.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    QAxObject *bookmark_casePol = document->querySubObject("Bookmarks(QVariant)", "casePol");
    if(!bookmark_casePol->isNull())
    {
        bookmark_casePol->dynamicCall("Select(void)");
        bookmark_casePol->querySubObject("Range")->setProperty("Text", strCasePol);
    }


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strNameCase);
   }
    // 插入案件开始时间
    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");

    if(!bookmark_startOfCase->isNull()){
    bookmark_startOfCase->dynamicCall("Select(void)");
    bookmark_startOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }

    // 插入案情big
     QAxObject*bookmark_anQingBig=document->querySubObject("Bookmarks(QVariant)","anQingBig");
     if(!bookmark_anQingBig->isNull()){
     strAnQingBig += "\n";
     bookmark_anQingBig->dynamicCall("Select(void)");
     bookmark_anQingBig->querySubObject("Range")->setProperty("Text",strAnQingBig);
    }

     // 插入违法行为人名称
     QAxObject*bookmark_nameOfCrimi=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
     if(!bookmark_nameOfCrimi->isNull()){
     bookmark_nameOfCrimi->dynamicCall("Select(void)");
     bookmark_nameOfCrimi->querySubObject("Range")->setProperty("Text",strNameCrimi);
    }


     // 插入依据
      QAxObject*bookmark_strChuFaYiJu=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu");
      if(!bookmark_strChuFaYiJu->isNull()){
      bookmark_strChuFaYiJu->dynamicCall("Select(void)");
      bookmark_strChuFaYiJu->querySubObject("Range")->setProperty("Text",strLawYiJu);
     }

      // 插入处罚
      QAxObject*bookmark_strChuFa=document->querySubObject("Bookmarks(QVariant)","strChuFa");
      if(!bookmark_strChuFa->isNull()){
      bookmark_strChuFa->dynamicCall("Select(void)");
      strChuFa += "\n";
      bookmark_strChuFa->querySubObject("Range")->setProperty("Text",strChuFa);
     }

      //-------------------------------------------------------
      // 插入处罚违法
      QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
      if(!bookmark_strChuFaWeiFan->isNull()){
      bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
      bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strLawWeiFan);
     }
     // 插入依据
      QAxObject*bookmark_strChuFaYiJu2=document->querySubObject("Bookmarks(QVariant)","strChuFaYiJu2");
      if(!bookmark_strChuFaYiJu2->isNull()){
      bookmark_strChuFaYiJu2->dynamicCall("Select(void)");
      bookmark_strChuFaYiJu2->querySubObject("Range")->setProperty("Text",strLawYiJu);
     }
      // 案件类别
      QAxObject*bookmark_caseName=document->querySubObject("Bookmarks(QVariant)","caseName");
      if(!bookmark_caseName->isNull()){
      bookmark_caseName->dynamicCall("Select(void)");
      bookmark_caseName->querySubObject("Range")->setProperty("Text",strCaseLittleName);
     }

      // 插入处罚
      QAxObject*bookmark_strChuFa2=document->querySubObject("Bookmarks(QVariant)","strChuFa2");
      if(!bookmark_strChuFa2->isNull()){
      bookmark_strChuFa2->dynamicCall("Select(void)");
      bookmark_strChuFa2->querySubObject("Range")->setProperty("Text",strChuFa);
     }




    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/30.案件合议记录.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");


}

void legalDoc::CreateDiaoQu(QString strUnitAuthor)
{

    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDiaoQu.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");





    QAxObject*bookmark_strTingZheng=document->querySubObject("Bookmarks(QVariant)","strTingZheng");
    if(!bookmark_strTingZheng->isNull()){
    bookmark_strTingZheng->dynamicCall("Select(void)");
    bookmark_strTingZheng->querySubObject("Range")->setProperty("Text",strUnitAuthor);
   }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/31.调取证据清单.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateBackUpTable(QString strCaseName, QString strUpPol, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseBackUp.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }

    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");

    if(!bookmark_endOfCase->isNull()){
    bookmark_endOfCase->dynamicCall("Select(void)");
    bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
   }

    QAxObject*bookmark_caseOfCop=document->querySubObject("Bookmarks(QVariant)","upCasePol");
    if(!bookmark_caseOfCop->isNull())
    {
       bookmark_caseOfCop->dynamicCall("Select(void)");
       bookmark_caseOfCop->querySubObject("Range")->setProperty("Text",strUpPol);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/32.卷内备考表.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");

}
// 鉴定聘请呈批表
void legalDoc::CreateJianDingOk(QString strCaseHao, QString strCaseNum, QString strCaseName)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseJianDingOk.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    QAxObject*bookmark_nameOfCase2=document->querySubObject("Bookmarks(QVariant)","nameOfCase2");

    if(!bookmark_nameOfCase2->isNull()){
    bookmark_nameOfCase2->dynamicCall("Select(void)");
    bookmark_nameOfCase2->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }


    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/20.鉴定聘请呈批表.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}
// 鉴定委托
void legalDoc::CreateJianDingWeiTuo(QString strCaseHao, QString strCaseNum, QString strCaseName, QString timeStart, QString timeEnd)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseJianDingWeiTuo.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }


    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }

    // 立案时间
    QAxObject*bookmark_startOfCase=document->querySubObject("Bookmarks(QVariant)","startOfCase");
    if(!bookmark_startOfCase->isNull())
    {
        bookmark_startOfCase->dynamicCall("Select(void)");
        bookmark_startOfCase->querySubObject("Range")->setProperty("Text",timeStart);
    }
    QAxObject*bookmark_startOfCase1=document->querySubObject("Bookmarks(QVariant)","startOfCase1");
    if(!bookmark_startOfCase1->isNull())
    {
        bookmark_startOfCase1->dynamicCall("Select(void)");
        bookmark_startOfCase1->querySubObject("Range")->setProperty("Text",timeStart);
    }
    //结案时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull())
    {
        bookmark_endOfCase->dynamicCall("Select(void)");
        bookmark_endOfCase->querySubObject("Range")->setProperty("Text",timeEnd);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/21.鉴定聘请书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}
// 证书复印（鉴定）
void legalDoc::CreateJianDingFuYing()
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseJianDingFuYing.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");



    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/23.鉴定资质复印件.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

// 鉴定意见书
void legalDoc::CreateJianDingYiJian(QString strCaseHao, QString strCaseNum, QString timeEnd)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseJianDingYiJian.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }


    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }


    //结案时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull())
    {
        bookmark_endOfCase->dynamicCall("Select(void)");
        bookmark_endOfCase->querySubObject("Range")->setProperty("Text",timeEnd);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/22.鉴定意见书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}
// 调取证据呈批表
void legalDoc::CreateDiaoQuOk(QString strCaseHao, QString strCaseNum, QString strCaseName)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseDiaoQuOk.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    QAxObject*bookmark_nameOfCase2=document->querySubObject("Bookmarks(QVariant)","nameOfCase2");

    if(!bookmark_nameOfCase2->isNull()){
    bookmark_nameOfCase2->dynamicCall("Select(void)");
    bookmark_nameOfCase2->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }


    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/19.调取证据呈批表.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}
// 延期缴纳罚款呈批表
void legalDoc::CreateYanQiOk(QString strCaseHao, QString strCaseNum, QString strCaseName)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseYanQiOk.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    QAxObject*bookmark_nameOfCase2=document->querySubObject("Bookmarks(QVariant)","nameOfCase2");

    if(!bookmark_nameOfCase2->isNull()){
    bookmark_nameOfCase2->dynamicCall("Select(void)");
    bookmark_nameOfCase2->querySubObject("Range")->setProperty("Text",strCaseName);
   }
    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }


    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/18.延期缴纳罚款呈批表.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

// 补种树木通知书
void legalDoc::CreateBuZhong(QString strCaseHao, QString strCaseNum, QString strNameCrimi, QString strAnQingSmall, QString strWeiFan, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseBuZhong.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");

    // 插入文号
    QAxObject*bookmark_caseDecideUnitHao=document->querySubObject("Bookmarks(QVariant)","caseHao");
    if(!bookmark_caseDecideUnitHao->isNull()){
    bookmark_caseDecideUnitHao->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    QAxObject*bookmark_caseDecideUnitHao1=document->querySubObject("Bookmarks(QVariant)","caseHao1");
    if(!bookmark_caseDecideUnitHao1->isNull()){
    bookmark_caseDecideUnitHao1->dynamicCall("Select(void)");
    bookmark_caseDecideUnitHao1->querySubObject("Range")->setProperty("Text",strCaseHao);
    }
    QAxObject*bookmark_numberOfCase=document->querySubObject("Bookmarks(QVariant)","numberOfCase");
    if(!bookmark_numberOfCase->isNull())
    {
        bookmark_numberOfCase->dynamicCall("Select(void)");
        bookmark_numberOfCase->querySubObject("Range")->setProperty("Text",strCaseNum);
    }
    QAxObject*bookmark_numberOfCase1=document->querySubObject("Bookmarks(QVariant)","numberOfCase1");
    if(!bookmark_numberOfCase1->isNull())
    {
        bookmark_numberOfCase1->dynamicCall("Select(void)");
        bookmark_numberOfCase1->querySubObject("Range")->setProperty("Text",strCaseNum);
    }
    // 插入案情small
     QAxObject*bookmark_anQingSmall=document->querySubObject("Bookmarks(QVariant)","anQingSmall");
     if(!bookmark_anQingSmall->isNull()){
     bookmark_anQingSmall->dynamicCall("Select(void)");
     bookmark_anQingSmall->querySubObject("Range")->setProperty("Text",strAnQingSmall);
    }

     //结案时间
     QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
     if(!bookmark_endOfCase->isNull())
     {
         bookmark_endOfCase->dynamicCall("Select(void)");
         bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
     }

     // 违法行为人
     QAxObject*bookmark_crimiOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCrimi");
     if(!bookmark_crimiOfCase->isNull())
     {
         bookmark_crimiOfCase->dynamicCall("Select(void)");
         bookmark_crimiOfCase->querySubObject("Range")->setProperty("Text",strNameCrimi);
     }

     // 插入处罚违法
     QAxObject*bookmark_strChuFaWeiFan=document->querySubObject("Bookmarks(QVariant)","strChuFaWeiFan");
     if(!bookmark_strChuFaWeiFan->isNull()){
     bookmark_strChuFaWeiFan->dynamicCall("Select(void)");
     bookmark_strChuFaWeiFan->querySubObject("Range")->setProperty("Text",strWeiFan);
    }

    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/5.补种树木通知书.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

void legalDoc::CreateCaseRead(QString strCaseName, QString strPol, QString strTime)
{
    QAxWidget *word = new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
    if (word->isNull())
    {
        QMessageBox::critical(0, "错误信息", "没有找到OFFICE应用程序");
        return ;
    }
    QAxObject *documents = word->querySubObject("Documents");
    QDir dir;
    QString path = dir.currentPath()+"/temple/caseRead.doc";
    documents->dynamicCall("Add(QString)", path);
    QAxObject *document = word->querySubObject("ActiveDocument");


    // 插入案件名称
    QAxObject*bookmark_nameOfCase=document->querySubObject("Bookmarks(QVariant)","nameOfCase");

    if(!bookmark_nameOfCase->isNull()){
    bookmark_nameOfCase->dynamicCall("Select(void)");
    bookmark_nameOfCase->querySubObject("Range")->setProperty("Text",strCaseName);
   }

    //结案时间
    QAxObject*bookmark_endOfCase=document->querySubObject("Bookmarks(QVariant)","endOfCase");
    if(!bookmark_endOfCase->isNull())
    {
        bookmark_endOfCase->dynamicCall("Select(void)");
        bookmark_endOfCase->querySubObject("Range")->setProperty("Text",strTime);
    }

    // 插入承办人
    QAxObject*bookmark_caseOfCop=document->querySubObject("Bookmarks(QVariant)","casePol");
    if(!bookmark_caseOfCop->isNull())
    {
       bookmark_caseOfCop->dynamicCall("Select(void)");
       bookmark_caseOfCop->querySubObject("Range")->setProperty("Text",strPol);
    }




    document->dynamicCall("SaveAs (const QString&)", QString(strPrintDir+"/33.阅卷笔录.doc"));
    document->dynamicCall("Close (boolean)", false);
    word->dynamicCall("Quit()");
}

