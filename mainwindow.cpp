#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lawitem.h"
#include <QApplication>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAxWidget>
#include <QAxObject>
#include <QDebug>
#include <QDir>
#include <QDesktopServices>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include "legaldoc.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 使得界面上的combobox可以编辑
    ui->comboBoxCase->setEditable(true);
    ui->comboBoxDecideUnit->setEditable(true);
    ui->comboBoxFoundationOfCase->setEditable(true);
    // 加载config.json文件信息;
    baseInfoDlg = new BaseInfo(this);
    connect(baseInfoDlg, SIGNAL(userJsonChanged()), this, SLOT(loadJsonInfo()));
    loadJsonInfo();
    // 加载anQing-config.json文件信息，绑定信号，随时更新界面
    anQingInfoDlg = new AnQingInfoDialog(this);
    connect(anQingInfoDlg, SIGNAL(anQingJsonChanged()), this, SLOT(loadAnQingJsonInfo()));
    loadAnQingJsonInfo();
    // 设置日期为当天日期
    ui->dateEditStart->setDate(QDate::currentDate());
    ui->dateEditEnd->setDate(QDate::currentDate());
    setWindowState(Qt::WindowMaximized);

    // 输出目录在桌面
    ui->lineEditPrintDir->setText(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"/临时卷宗文档");
    // 输入检查
    checkInput = false;


   // 判断运行环境是否正确
// 1. 模板目录是否存在
   QDir dir;
   QString path;
   path = dir.currentPath()+"/temple";

   if (QFile::exists(path) == false)
   {

   }


   // 系统信息
  ui->textEditDisplay->setText("***************************准备就绪（请安装微软office后点击生成）***************************");


     // 初始化一下变量
     on_comboBoxSex_currentTextChanged("男");  // birthdayOfCrimi赋值
     on_comboBoxFoundationOfCase_currentTextChanged("群众举报");
     ui->dateEditBir->setDate(QDate::fromString("19000101", "yyyyMd"));


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information( this, tr("还未保存"),tr("你真的想要退出么?"),tr("确认"), tr("取消"),0, 1 ) )
    {
       case 0:
          event->accept();
           break;
       case 1:
       default:
           event->ignore();
           break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}




bool MainWindow::loadJsonInfo()
{
    // 打开并读取config文件信息
    QJsonParseError json_error;
    QByteArray read_byteArray;
    QFile *readFile = new QFile("config.json");
    if(!readFile->exists() || !readFile->open(QIODevice::ReadOnly))
    {
        qDebug() << "配置文件不存在或无法打开";
    }
    else
    {
        read_byteArray = readFile->readAll();
        QJsonDocument parse_document = QJsonDocument::fromJson(read_byteArray, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
           QJsonObject readObj = parse_document.object();
           ui->comboBoxDecideUnit->clear();   // 需要清空combobox中的信息，不然回循环添加

           ui->caseCSITimeEdit->setText(readObj.value("strCaseCSITime").toString());
           ui->caseCSILocEdit->setText(readObj.value("strCaseCSILoc").toString());
           qDebug() << readObj.value("caseCSILoc").toString();
           if(readObj.contains("strCaseNum"))
           {
               QJsonValue strCaseNum_value = readObj.take("strCaseNum");
               ui->numberOfCase_Edit->setText(strCaseNum_value.toString());
           }
           if(readObj.contains("strCaseCop"))
           {
               QJsonValue strCaseCop_value = readObj.take("strCaseCop");
               ui->lineEditCaseCop->setText(strCaseCop_value.toString());
           }
           if(readObj.contains("strFaWenNum1"))
           {
               QJsonValue strFaWenNum1_value = readObj.take("strFaWenNum1");
               ui->comboBoxDecideUnit->insertItem(0, strFaWenNum1_value.toString());
           }

           if(readObj.contains("strFaWenNum2"))
           {
               QJsonValue strFaWenNum2_value = readObj.take("strFaWenNum2");
               ui->comboBoxDecideUnit->insertItem(1, strFaWenNum2_value.toString());
           }

           if(readObj.contains("strForestUnit"))
           {
               QJsonValue strForestUnit_value = readObj.take("strForestUnit");
               ui->lineEditForestUnit->setText(strForestUnit_value.toString());
           }

           if(readObj.contains("strLinYeUnit"))
           {
               QJsonValue strLinYeUnit_value = readObj.take("strLinYeUnit");
               ui->lineEditLinYeUnit->setText(strLinYeUnit_value.toString());
           }

           if(readObj.contains("strCaseNation"))
           {
               QJsonValue strCaseNation_value = readObj.take("strCaseNation");
               ui->lineEditNation->setText(strCaseNation_value.toString());
           }


           if(readObj.contains("strCaseCulture"))
           {
               QJsonValue strCaseCulture_value = readObj.take("strCaseCulture");
               ui->lineEditEdu->setText(strCaseCulture_value.toString());
           }

           if(readObj.contains("strCaseJob"))
           {
               QJsonValue strCaseJob_value = readObj.take("strCaseJob");
               ui->lineEditWork->setText(strCaseJob_value.toString());
           }
           if(readObj.contains("strCaseHumNumber"))
           {
               QJsonValue strCaseHumNumber_value = readObj.take("strCaseHumNumber");

               ui->lineEditCrimiID->setText(strCaseHumNumber_value.toString());
           }
           if(readObj.contains("strCaseHome"))
           {
               QJsonValue strCaseHome_value = readObj.take("strCaseHome");
               ui->lineEditCrimiAddr->setText(strCaseHome_value.toString());
           }
           if(readObj.contains("strCasePol1"))
           {
               QJsonValue strCasePol1_value = readObj.take("strCasePol1");
               ui->casePolEdit1->setText(strCasePol1_value.toString());
           }
           if(readObj.contains("strCasePol2"))
           {
               QJsonValue strCasePol2_value = readObj.take("strCasePol2");
               ui->casePolEdit2->setText(strCasePol2_value.toString());
           }
           if(readObj.contains("strCaseFuYi"))
           {
               QJsonValue strCaseFuYi_value = readObj.take("strCaseFuYi");
               ui->caseFuYiEdit->setText(strCaseFuYi_value.toString());
           }

        }

    }
    return true;
}

bool MainWindow::loadAnQingJsonInfo()
{

    QFile file("anQing-config.json");
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QByteArray byteArray = file.readAll();
        file.close();

        QJsonParseError json_error;
        QJsonDocument parse_doc = QJsonDocument::fromJson(byteArray, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doc.isObject())
            {
                QJsonObject obj = parse_doc.object();
                ui->comboBoxCase->clear();
                ui->comboBoxCase->addItems(obj.keys()); // 加入comboboxcase内容
                if (!ui->comboBoxCase->currentText().isEmpty())
                {
                    QJsonObject anQingObj = obj.value(ui->comboBoxCase->currentText()).toObject();

                    ui->textEditCaseFoundation->setText(anQingObj["caseFrom"].toString());
                    ui->lineEditChuFaWeiFan->setText(anQingObj["caseWeiFan"].toString());
                    ui->lineEditChuFaYiJu->setText(anQingObj["caseYiJu"].toString());
                    ui->textEditChuFa->setText(anQingObj["caseChuFa"].toString());
                    ui->textEditAnQingBig->setText(anQingObj["caseAnQingBig"].toString());
                    ui->textEditAnQingSmall->setText(anQingObj["caseAnQingSmall"].toString());
                    ui->textEditCSI->setText(anQingObj["caseCSI"].toString());

                }
                else
                {

                    ui->textEditCaseFoundation->clear();
                    ui->lineEditChuFaWeiFan->clear();
                    ui->lineEditChuFaYiJu->clear();
                    ui->textEditChuFa->clear();
                    ui->textEditAnQingBig->clear();
                    ui->textEditAnQingSmall->clear();
                    ui->textEditCSI->clear();
                }
            }
        }
    }

   return true;

}

bool MainWindow::loadTest()
{
    qDebug() << "界面信息变化，我被加载了";
}

void MainWindow::crimiInfo()
{

    strCrimiInfo = ui->nameOfCrimi_Edit->text()+"，"+ui->comboBoxSex->currentText()+"，"+birthdayOfCrimi+"出生，"+
                   nationOfCrimi+"、"+eduOfCrimi+"文化，"+workOfCrimi+"，"
                   "现住"+addressOfCrimi+"。"+"身份号码:"+IDOfCrimi+"。"+"\n";

}


void MainWindow::on_pushButton_clicked()
{

    // 检查xx是否被替换 
   if(checkInPutX())
   {
       return ;
   }
   // 开始生成文书
   legalDoc* myLegDocument = new legalDoc;
   displayTheResult("--------------------正在生成（请稍等）------------------------\n");
   qApp->processEvents();
   // *************************************生成封面*****************************************************
   myLegDocument->CreatCaseCoverTest(strNameCase, strNumCase,strNameCrimi, strStartCase,strEndCase, strUpUnitCase,strCheckUnitCase,strNamePol);  // 创建对象
   displayTheResult("0.封面............................................完成;\n");
   qApp->processEvents();
   // *************************************生成目录***************************************************
   if (strFaWenHao.contains("森公"))
   {
       strUnitAuthor = ui->lineEditForestUnit->text(); // 责任单位
   }
   else
   {
       strUnitAuthor = ui->lineEditLinYeUnit->text();
   }
   strPolAuthor = strCasePol1 + " "+ strCasePol2;    // 责任人联名
   myLegDocument->CreateCaseContent(strUnitAuthor,strPolAuthor, strFaWenHao, strNumCase, strStartCase, strEndCase);
   displayTheResult("1.目录............................................完成;\n");
   qApp->processEvents();
   // ****************************生成案件调查终结报告*************************************************
   crimiInfo();// 合成违法嫌疑人基本信息strCrimiInfo
   myLegDocument->CreateCaseDoneReport(strCaseLaiYuan,strCrimiInfo,anQingBig,strNameCrimi,strChuFaWeiFan,strChuFaYiJu,strLittleName,strChuFa,strUnitAuthor,strPolAuthor,strEndCase);
   displayTheResult("2.案件调查终结报告.................................完成;\n");
   qApp->processEvents();
   // *************************处罚决定书*************************************************************
   // 倒数第二个参数为林业局，根据森林公安办理行政案件程序规定，复议机构为同级林业和园林局
   myLegDocument->CreateCaseDecideBook(strFaWenHao,strNumCase,strNameCrimi,sexOfCrimi,birthdayOfCrimi,IDOfCrimi,addressOfCrimi,anQingSmall,strChuFaWeiFan,strChuFaYiJu,strChuFa,strCheckUnitCase, strEndCase);
   displayTheResult("3.处罚决定书.......................................完成;\n");
   qApp->processEvents();

   // ****************************文书送达回执*******************************************************
   myLegDocument->CreateCaseSend(strFaWenHao,strNumCase,strNameCase,strNameCrimi);
   displayTheResult("4.文书送达回执....................................完成\n");
   qApp->processEvents();
// ******************************立案登记表***************************************************************
   myLegDocument->CreateCaseUp(strFaWenHao,strNumCase,strNameCase,caseFoundation,strStartCase,strNameCrimi,sexOfCrimi,birthdayOfCrimi,addressOfCrimi,strCaseLaiYuan);
   displayTheResult("5.立案登记表.......................................完成\n");
   qApp->processEvents();
// ********************************处罚意见书***************************************************************
   myLegDocument->CreateCaseDecideIdea(strFaWenHao,strNumCase,strNameCase,strStartCase,strNameCrimi,sexOfCrimi,birthdayOfCrimi,IDOfCrimi,addressOfCrimi,anQingBig);
   displayTheResult("7.处罚意见书......................................完成\n");
   qApp->processEvents();
// ********************************延期、分期缴纳罚款决定书********************************************************
   myLegDocument->CreateCaseFenQi(strFaWenHao,strNumCase,strNameCrimi,strEndCase);
   displayTheResult("8.分期缴纳罚款决定书...............................完成\n");
   qApp->processEvents();
// ********************************受理报警登记表*******************************************************************
   myLegDocument->CreateCaseBaoJing(strFaWenHao,strNumCase,strStartCase, strCaseLaiYuan);
   displayTheResult("9.受理报警登记表...............................完成\n");
   qApp->processEvents();
// *******************************权利义务告知书*******************************************************************
   myLegDocument->CreateCaseRight();
   displayTheResult("10.权利义务告知书.............................完成\n");
   qApp->processEvents();
// *******************************先行告知书************************************************************************
   myLegDocument->CreateCaseFirstNotify(strFaWenHao,strNumCase,strNameCrimi,anQingSmall,strChuFaWeiFan,strChuFaYiJu,strChuFa,strEndCase);
   displayTheResult("11.处罚现行告知书.............................完成\n");
   qApp->processEvents();
// ******************************听证告知书*************************************************************************
   myLegDocument->CreateCaseTingZheng(strFaWenHao,strNumCase,strNameCrimi,anQingSmall,strChuFaWeiFan,strChuFaYiJu,strChuFa,strUnitAuthor,strEndCase);
   displayTheResult("12.听证权利告知书.......................................完成\n");
   qApp->processEvents();

// *****************************CSI*********************************
   myLegDocument->CreateCSI(caseCheckTime,caseCheckAddress,strNameCrimi,IDOfCrimi,addressOfCrimi,strCSI,strStartCase);
   displayTheResult("13.现场勘验笔录......................................完成\n");
   qApp->processEvents();
// ****************************呈请调查终结呈批表******************************************
    myLegDocument->CreateCaseDoneOK(strFaWenHao,strNumCase,strNameCase,strCaseLaiYuan,anQingSmall,strLittleName,strChuFaWeiFan,strChuFaYiJu,strChuFa);
    displayTheResult("14.呈批表:调查终结报告..............................完成;\n");
    qApp->processEvents();

// ****************************呈批表：没收物品****************************************
    myLegDocument->CreateCaseMoShou(strFaWenHao,strNumCase,strNameCase,anQingBig,strNameCrimi,strChuFaWeiFan,strLittleName,strChuFaYiJu,strChuFa);
    displayTheResult("15.呈请没收物品呈批表......................................完成\n");
    qApp->processEvents();
// ****************************呈批表：变价处理****************************************
    myLegDocument->CreateCaseBianJia(strFaWenHao,strNumCase,strNameCase,anQingBig,strNameCrimi,strChuFaWeiFan,strLittleName,strChuFaYiJu,strChuFa);
    displayTheResult("16.变价处理呈批表......................................完成\n");
    qApp->processEvents();

// ***************************没收物品清单****************************************
   myLegDocument->CreateMoshouList(strFaWenHao,strNameCrimi,strNumCase);
    displayTheResult("18.没收物品清单...........................................完成\n");
    qApp->processEvents();
// *********************************木材价格表*************************************
    myLegDocument->CreateWoodCost();
    displayTheResult("19.木材价格计算方式......................................完成\n");
    qApp->processEvents();
// ********************************延期申请书**************************************
    myLegDocument->CreateCasePlease(strUnitAuthor,strEndCase,strLittleName);
    displayTheResult("20.延期缴纳罚款申请......................................完成\n");
    qApp->processEvents();
// ********************************变价处理申请书************************************
    myLegDocument->CreateGiveMe(strUnitAuthor,strEndCase);
    displayTheResult("20.申请变价处理木材.........................................完成\n");
    qApp->processEvents();
// ********************************委托代缴罚款申请书*********************************
    myLegDocument->CreateWeiTuo(strUnitAuthor,strFaWenHao,strNumCase,strPolAuthor,strEndCase);
    displayTheResult("21.委托代缴罚款申请书.........................................完成\n");
    qApp->processEvents();
// *******************************案件合议记录*****************************************
    myLegDocument->CreateHeYi(strNameCase,strStartCase,anQingBig,strPolAuthor,strNameCrimi,strChuFaWeiFan,strLittleName,strChuFaYiJu,strChuFa);
    displayTheResult("22.案件合议记录......................................完成\n");
    qApp->processEvents();
// *******************************调取证据清单******************************************
    myLegDocument->CreateDiaoQu(strUnitAuthor);
    displayTheResult("23.调取证据清单......................................完成\n");
    qApp->processEvents();
// ********************************卷内备考表********************************************
    myLegDocument->CreateBackUpTable(strNameCase,strNamePol,strEndCase);
    displayTheResult("15.卷内备考表......................................完成\n");
    qApp->processEvents();

// ********************************鉴定聘请呈批表********************************************
        myLegDocument->CreateJianDingOk(strFaWenHao,strNumCase,strNameCase);
        displayTheResult("25.鉴定聘请呈批表......................................完成\n");
        qApp->processEvents();
// ********************************鉴定聘请书********************************************
        myLegDocument->CreateJianDingWeiTuo(strFaWenHao,strNumCase,strNameCase,strStartCase,strEndCase);
        displayTheResult("26.鉴定聘请书......................................完成\n");
        qApp->processEvents();
// ********************************鉴定证书复印********************************************
        myLegDocument->CreateJianDingFuYing();
        displayTheResult("27.鉴定证书复印......................................完成\n");
        qApp->processEvents();

// ********************************鉴定意见书********************************************
        myLegDocument->CreateJianDingYiJian(strFaWenHao,strNumCase,strEndCase);
        displayTheResult("28.鉴定意见书......................................完成\n");
        qApp->processEvents();

// ********************************调取证据呈批表********************************************
        myLegDocument->CreateDiaoQuOk(strFaWenHao,strNumCase,strNameCase);
        displayTheResult("29.调取证据呈批表......................................完成\n");
        qApp->processEvents();
// ********************************延期缴纳罚款呈批表********************************************
        myLegDocument->CreateYanQiOk(strFaWenHao,strNumCase,strNameCase);
        displayTheResult("30.延期缴纳罚款呈批表......................................完成\n");
        qApp->processEvents();
// ********************************补种树木通知书********************************************
        myLegDocument->CreateBuZhong(strFaWenHao,strNumCase,strNameCrimi,anQingSmall,strChuFaWeiFan,strEndCase);
        displayTheResult("31.补种树木通知书......................................完成\n");
        qApp->processEvents();
// ********************************行政案件阅卷笔录********************************************
        myLegDocument->CreateCaseRead(strNameCase,strPolAuthor,strEndCase);
        displayTheResult("31.补种树木通知书......................................完成\n");
        qApp->processEvents();


// ******************************完成任务***********************************************



    myLegDocument->openExplor(); // 打开生成的文档


   displayTheResult("-------------------完成（By:NeoHunter）---------------------\n");
   qApp->processEvents();




}

bool MainWindow::checkInPutX()
{
    if(checkInput)  // 是否验证输入
   {
     if(caseLaiYuan.contains("x"))
     {
        QMessageBox::warning(NULL, "警告：文书未填写完成，无法生成", "请将编号①的内容填写完整，替换所有的x符号", QMessageBox::Yes);
        return true;
     }
     if(strChuFa.contains("x"))
     {
        QMessageBox::warning(NULL, "警告：文书未填写完成，无法生成", "请将编号②的内容填写完整，替换所有的x符号", QMessageBox::Yes);
        return true;
     }
     if(anQingBig.contains("x"))
     {
        QMessageBox::warning(NULL, "警告：文书未填写完成，无法生成", "请将编号③的内容填写完整，替换所有的x符号", QMessageBox::Yes);
        return true;
     }
     if(anQingSmall.contains("x"))
     {
        QMessageBox::warning(NULL, "警告：文书未填写完成，无法生成", "请将编号④的内容填写完整，替换所有的x符号", QMessageBox::Yes);
        return true;
     }

     if(strCSI.contains("x"))
     {
        QMessageBox::warning(NULL, "警告：文书未填写完成，无法生成", "请将编号⑤的内容填写完整，替换所有的x符号", QMessageBox::Yes);
        return true;
     }
   }
    return false;

}






void MainWindow::displayTheResult(QString str)
{
    strDisplay += str;
    ui->textEditDisplay->setText(strDisplay);
}





void MainWindow::on_nameOfCase_Edit_textEdited(const QString &arg1)
{
    nameOfCase = arg1;
}


void MainWindow::on_comboBoxCase_currentTextChanged(const QString &arg1)
{
   // 获取当前字符串并设置案件名称；
    strLittleName = arg1;
    QString strCase = ui->nameOfCrimi_Edit->text()+ arg1;
    ui->nameOfCase_Edit->setText(strCase);
    // 判断是哪一个类别的案件，并设置相应的文本内容
    QFile file("anQing-config.json");
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QByteArray byteArray = file.readAll();
        file.close();

        QJsonParseError json_error;
        QJsonDocument parse_doc = QJsonDocument::fromJson(byteArray, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doc.isObject())
            {
                QJsonObject obj = parse_doc.object();
                QJsonObject anQingObj = obj.value(ui->comboBoxCase->currentText()).toObject();
                if(!anQingObj.isEmpty())
                {
                    ui->textEditCaseFoundation->setText(anQingObj["caseFrom"].toString());
                    ui->lineEditChuFaWeiFan->setText(anQingObj["caseWeiFan"].toString());
                    ui->lineEditChuFaYiJu->setText(anQingObj["caseYiJu"].toString());
                    ui->textEditChuFa->setText(anQingObj["caseChuFa"].toString());
                    ui->textEditAnQingBig->setText(anQingObj["caseAnQingBig"].toString());
                    ui->textEditAnQingSmall->setText(anQingObj["caseAnQingSmall"].toString());
                    ui->textEditCSI->setText(anQingObj["caseCSI"].toString());

                }
            }
        }
    }



}

void MainWindow::on_nameOfCrimi_Edit_textChanged(const QString &arg1)
{

    strNameCrimi = arg1;
    QString strCase = arg1+ui->comboBoxCase->currentText();
    ui->nameOfCase_Edit->setText(strCase);
    on_nameOfCase_Edit_textEdited(strCase);  // 触发一下给nameOfCase赋值

}


// 选择案件类别以及处罚

void MainWindow::on_dateEditStart_dateChanged(const QDate &date)
{
    strStartCase = date.toString("yyyy年MM月dd日");
    startOfCaseDot = date.toString("yyyy.MM.dd");
}

void MainWindow::on_dateEditEnd_dateChanged(const QDate &date)
{
    strEndCase = date.toString("yyyy年MM月dd日");
    endOfCaseDot = date.toString("yyyy.MM.dd");
}

void MainWindow::on_dateEditBir_dateChanged(const QDate &date)
{
    birthdayOfCrimi = date.toString("yyyy年MM月dd日");
}

void MainWindow::on_lineEditCheckUnit_textChanged(const QString &arg1)
{
    checkUnit = arg1;

}

void MainWindow::on_lineEditRegUnit_textChanged(const QString &arg1)
{
    regUnit = arg1;
}

void MainWindow::on_numberOfCase_Edit_textChanged(const QString &arg1)
{

    strNumCase = arg1;

}

void MainWindow::on_lineEditCaseCop_textChanged(const QString &arg1)
{
    strNamePol = arg1;
}

void MainWindow::on_nameOfCase_Edit_textChanged(const QString &arg1)
{

    strNameCase = arg1;
}



void MainWindow::on_textEditAnQingBig_textChanged()
{
    anQingBig = ui->textEditAnQingBig->toPlainText();
}

void MainWindow::on_textEditAnQingSmall_textChanged()
{
    anQingSmall = ui->textEditAnQingSmall->toPlainText();

}

void MainWindow::on_comboBoxSex_currentTextChanged(const QString &arg1)
{
    sexOfCrimi = arg1;
}

void MainWindow::on_lineEditNation_textChanged(const QString &arg1)
{
    nationOfCrimi = arg1;
}

void MainWindow::on_lineEditEdu_textChanged(const QString &arg1)
{
    eduOfCrimi = arg1;
}

void MainWindow::on_lineEditWork_textChanged(const QString &arg1)
{
    workOfCrimi = arg1;
}

void MainWindow::on_lineEditCrimiAddr_textChanged(const QString &arg1)
{
    addressOfCrimi= arg1;


}




void MainWindow::on_lineEditCrimiID_textChanged(const QString &arg1)
{
    IDOfCrimi = arg1;
    if (IDOfCrimi.length() == 18)
    {
        strAutoBir = IDOfCrimi.mid(6, 8); // 从 第6个字符处，依次截取8个字符 样式：19900912
        int Y = strAutoBir.mid(0, 4).toInt();
        int M = strAutoBir.mid(4, 2).toInt();
        int D = strAutoBir.mid(6, 2).toInt();

        ui->dateEditBir->setDate(QDate(Y,M,D));  // 自动设置生日控件

    }
}

void MainWindow::on_textEditCaseFoundation_textChanged()
{

    strCaseLaiYuan = ui->textEditCaseFoundation->toPlainText();
}




void MainWindow::on_comboBoxFoundationOfCase_currentTextChanged(const QString &arg1)
{
    caseFoundation = arg1;

}

void MainWindow::on_textEditCSI_textChanged()
{
    strCSI = ui->textEditCSI->toPlainText();

}

void MainWindow::on_lineEditChuFaWeiFan_textChanged(const QString &arg1)
{
    strChuFaWeiFan = arg1;
}

void MainWindow::on_lineEditChuFaYiJu_textChanged(const QString &arg1)
{
    strChuFaYiJu = arg1;
}

void MainWindow::on_textEditChuFa_textChanged()
{
    strChuFa = ui->textEditChuFa->toPlainText();
}


void MainWindow::on_checkBoxInput_stateChanged(int arg1)
{
    checkInput = arg1;

}

bool MainWindow::saveAsFile(QString myFileName)
{
    QFile file(myFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text|QIODevice::Append))
    {
       QMessageBox::warning(this,tr("案件管理系统"),tr("不能写入文件 %1:\n%2.")
                            .arg(file.fileName()).arg(file.errorString()));
       return false;
    }
    QTextStream in(&file);

    in << strNameCrimi +"|" +sexOfCrimi+"|" +eduOfCrimi+"|" +workOfCrimi+"|" +IDOfCrimi+"|" +nationOfCrimi+"|" + addressOfCrimi+"|" +
          caseFoundation+"|" +strCaseLaiYuan+"|" +strLittleName+"|" +strChuFa+"|" +anQingBig+"|" +anQingSmall+"|" +
          numberOfCase+"|" +strCSI+"|"+
          strChuFaWeiFan+"|"+strChuFaYiJu+"|"+strNameCase+"|"+strNumCase+"|"+strStartCase+"|"+strEndCase+"|"+strFaWenHao+"|"+strNamePol+"|"+
          strUpUnitCase+"|"+strCheckUnitCase+"|"+strFuYi+"|"+strCasePol1+"|"+strCasePol2+"|"+caseCheckAddress+"|"+caseCheckTime;
          ;
   file.close();

    return true;
}
// 自动保存
void MainWindow::timerEvent(QTimerEvent *event)
{
    if (!nameOfCase.isEmpty())
    {
      QDir dir;
      QString path = dir.currentPath()+"/save/";
      QString myFile = path+nameOfCase+".txt";

      QFile file(myFile);
      file.open(QIODevice::WriteOnly);
      file.close();
      saveAsFile(myFile);
    }
    else
    {
        QMessageBox::warning(NULL, "警告", "不能自动保存，请至少填写案件名称", QMessageBox::Yes);
        ui->checkBoxAutoSave->setCheckState(Qt::Unchecked);
        return ;
    }
}

void MainWindow::on_checkBoxAutoSave_stateChanged(int arg1)
{
    checkAutoSave = arg1;
    if (checkAutoSave)
    {

          m_nTimerID = startTimer(9000);  // 9秒保存1次内容

    }
    else
    {
        if (m_nTimerID != 0)
            killTimer(m_nTimerID);
    }

}

void MainWindow::on_pushButtonLoad_clicked()
{

    QDir dir;
    QString path = dir.currentPath()+"/save/";
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开保存的模板"),path,tr(" 已存模板(*.txt)"));

    if(!fileName.isEmpty())
    {
          QFile file(fileName);
          if(!file.open(QIODevice::ReadOnly))
          {
              QMessageBox::warning(this,tr("Spreadsheet"),tr("Cannot read file %1:\n%2.")
                                   .arg(file.fileName()).arg(file.errorString()));
              return ;
          }
           QTextStream out(&file);
           QString temp;
           temp = out.readAll();
           file.close();
           ui->nameOfCrimi_Edit->setText(temp.section('|', 0,0).trimmed());
           ui->comboBoxSex->setCurrentText(temp.section('|', 1,1).trimmed());
           ui->lineEditEdu->setText(temp.section('|', 2,2).trimmed());
           ui->lineEditWork->setText(temp.section('|', 3,3).trimmed());
           ui->lineEditCrimiID->setText(temp.section('|', 4,4).trimmed());
           ui->lineEditNation->setText(temp.section('|', 5,5).trimmed());
           ui->lineEditCrimiAddr->setText(temp.section('|', 6,6).trimmed());
           ui->comboBoxFoundationOfCase->setCurrentText(temp.section('|', 7,7).trimmed());
           ui->textEditCaseFoundation->setText(temp.section('|', 8,8).trimmed());
           ui->comboBoxCase->setCurrentText(temp.section('|', 9,9).trimmed());
           ui->textEditChuFa->setText(temp.section('|', 10,10).trimmed());
           ui->textEditAnQingBig->setText(temp.section('|', 11,11).trimmed());
           ui->textEditAnQingSmall->setText(temp.section('|', 12,12).trimmed());
           ui->numberOfCase_Edit->setText(temp.section('|', 13,13).trimmed());
           ui->textEditCSI->setText(temp.section('|', 14,14).trimmed());

           ui->lineEditChuFaWeiFan->setText(temp.section('|',15,15).trimmed());
           ui->lineEditChuFaYiJu->setText(temp.section('|',16,16).trimmed());

           ui->nameOfCase_Edit->setText(temp.section('|',17,17).trimmed());
           ui->numberOfCase_Edit->setText((temp.section('|',18,18).trimmed()));


           QString dateStart = temp.section('|',19,19).trimmed();
           dateStart.replace("年","");
           dateStart.replace("月","");
           dateStart.replace("日","");
           ui->dateEditStart->setDate(QDate::fromString(dateStart,"yyyyMMdd"));

           QString dateEnd = temp.section('|',20,20).trimmed();
           dateEnd.replace("年","");
           dateEnd.replace("月","");
           dateEnd.replace("日","");
           ui->dateEditEnd->setDate(QDate::fromString(dateEnd,"yyyyMMdd"));

           ui->comboBoxDecideUnit->setCurrentText(temp.section('|',21,21).trimmed());
           ui->lineEditCaseCop->setText(temp.section('|',22,22).trimmed());
           ui->lineEditForestUnit->setText(temp.section('|',23,23).trimmed());
           ui->lineEditLinYeUnit->setText(temp.section('|',24,24).trimmed());
           ui->caseFuYiEdit->setText(temp.section('|',25,25).trimmed());
           ui->casePolEdit1->setText(temp.section('|',26,26).trimmed());
           ui->casePolEdit2->setText(temp.section('|',27,27).trimmed());
           ui->caseCSILocEdit->setText(temp.section('|',28,28).trimmed());
           ui->caseCSITimeEdit->setText(temp.section('|',29,29).trimmed());



    }
}

// 设置界面基本信息
#include "baseinfo.h"
void MainWindow::on_UnitInfo_Case_triggered()
{

    baseInfoDlg->setModal(true);
    baseInfoDlg->show();


}

void MainWindow::on_pushButton_2_clicked()
{
    loadJsonInfo();
}

#include "anqinginfodialog.h"
void MainWindow::on_AnQingInfo_triggered()
{

    anQingInfoDlg->setModal(true);
    anQingInfoDlg->show();
}

void MainWindow::on_lineEditForestUnit_textChanged(const QString &arg1)
{
    strUpUnitCase = arg1;
}

void MainWindow::on_lineEditLinYeUnit_textChanged(const QString &arg1)
{
    strCheckUnitCase = arg1;
}

void MainWindow::on_comboBoxDecideUnit_currentIndexChanged(const QString &arg1)
{
    strFaWenHao = arg1;

}


void MainWindow::on_casePolEdit1_textChanged(const QString &arg1)
{
    strCasePol1 = arg1;
}

void MainWindow::on_casePolEdit2_textChanged(const QString &arg1)
{
    strCasePol2 = arg1;
}

void MainWindow::on_caseFuYiEdit_textChanged(const QString &arg1)
{
    strFuYi = arg1;
}

void MainWindow::on_caseCSILocEdit_textChanged(const QString &arg1)
{
    caseCheckAddress = arg1;
}

void MainWindow::on_caseCSITimeEdit_textChanged(const QString &arg1)
{
    caseCheckTime = arg1;
}

void MainWindow::on_Develop_triggered() // 开发人员
{
    QMessageBox::warning(this,tr("基本信息"),tr("*****************************************************************\n"
                                          "** 文件名:一键生成所有林业行政案件法律文书\n"
                                          "** Copyright (c) 2016 Matrix-Neo\n"
                                          "** 创 建 人:敬正帅（苍溪县森林公安局-08395221693）\n"
                                          "** 日    期: 2016-4-26 | 2017-2-7 |……\n"
                                          "** 描    述:主要用于办理林业行政案件，按照相应的类别选择不同的处罚。\n"
                                          "** 其    他:\n"
                                          "**           1.请于Temple文件夹内修改模板;\n"
                                          "**           2.软件需要安装微软办公套件MSOffice2003以上版本;\n"
                                          "**           3.生成的卷宗在桌面-临时案卷文档;\n"
                                          "**           4.重新生成的将覆盖掉以前的文档，请及时保存;\n"
                                          "**           5.自动保存文件存于：saveAs\\目录;\n"
                                          "*******************************************************************"));
}

void MainWindow::on_photo_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}

void MainWindow::on_draw_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}

void MainWindow::on_caseInfo_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}

void MainWindow::on_upCaseTable_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}

void MainWindow::on_rightNotify_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}

void MainWindow::on_blank_triggered()
{
    QMessageBox::warning(this,tr("提示"),tr("功能开发中，如有问题请联系：QQ：836544079（敬正帅）"));
}
