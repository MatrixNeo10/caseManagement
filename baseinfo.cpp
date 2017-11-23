#include "baseinfo.h"
#include "ui_baseinfo.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QFile>



BaseInfo::BaseInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseInfo)
{
    ui->setupUi(this);


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
           ui->csiTimeEdit->setText(readObj.value("strCaseCSITime").toString());
           ui->csiLocEdit->setText(readObj.value("strCaseCSILoc").toString());

           if(readObj.contains("strCaseNum"))
           {
               QJsonValue strCaseNum_value = readObj.take("strCaseNum");
               ui->caseNumberEdit->setText(strCaseNum_value.toString());
           }
           if(readObj.contains("strCaseCop"))
           {
               QJsonValue strCaseCop_value = readObj.take("strCaseCop");
               ui->caseCopEdit->setText(strCaseCop_value.toString());
           }
           if(readObj.contains("strFaWenNum1"))
           {
               QJsonValue strFaWenNum1_value = readObj.take("strFaWenNum1");
               ui->caseFaWenNum1->setText(strFaWenNum1_value.toString());
           }

           if(readObj.contains("strFaWenNum2"))
           {
               QJsonValue strFaWenNum2_value = readObj.take("strFaWenNum2");
               ui->caseFaWenNum2->setText(strFaWenNum2_value.toString());
           }

           if(readObj.contains("strForestUnit"))
           {
               QJsonValue strForestUnit_value = readObj.take("strForestUnit");
               ui->caseForestUnitEdit->setText(strForestUnit_value.toString());
           }

           if(readObj.contains("strLinYeUnit"))
           {
               QJsonValue strLinYeUnit_value = readObj.take("strLinYeUnit");
               ui->caseLinYeUnitEdit->setText(strLinYeUnit_value.toString());
           }

           if(readObj.contains("strCaseNation"))
           {
               QJsonValue strCaseNation_value = readObj.take("strCaseNation");
               ui->caseNationEdit->setText(strCaseNation_value.toString());
           }


           if(readObj.contains("strCaseCulture"))
           {
               QJsonValue strCaseCulture_value = readObj.take("strCaseCulture");
               ui->caseCultureEdit->setText(strCaseCulture_value.toString());
           }

           if(readObj.contains("strCaseJob"))
           {
               QJsonValue strCaseJob_value = readObj.take("strCaseJob");
               ui->caseJobEdit->setText(strCaseJob_value.toString());
           }
           if(readObj.contains("strCaseHumNumber"))
           {
               QJsonValue strCaseHumNumber_value = readObj.take("strCaseHumNumber");
               ui->caseHumNumberEdit->setText(strCaseHumNumber_value.toString());
           }
           if(readObj.contains("strCaseHome"))
           {
               QJsonValue strCaseHome_value = readObj.take("strCaseHome");
               ui->caseHomeEdit->setText(strCaseHome_value.toString());
           }

            // 办案人员
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
           // 复议机构
           if(readObj.contains("strCaseFuYi"))
           {
               QJsonValue strcaseFuYi_value = readObj.take("strCaseFuYi");
               ui->caseFuYiEdit->setText(strcaseFuYi_value.toString());
           }
        }

    }



}

BaseInfo::~BaseInfo()
{
    delete ui;
}

void BaseInfo::on_pushButton_clicked() // 确定保存到配置文件config.json
{


    // 将界面上的内容写入config文件中去
    QJsonObject baseInfoJson;
    baseInfoJson.insert("strCaseNum", ui->caseNumberEdit->text()); // 案件编号
    baseInfoJson.insert("strCaseCop", ui->caseCopEdit->text());    //
    baseInfoJson.insert("strFaWenNum1", ui->caseFaWenNum1->text());
    baseInfoJson.insert("strFaWenNum2", ui->caseFaWenNum2->text());
    baseInfoJson.insert("strForestUnit", ui->caseForestUnitEdit->text());
    baseInfoJson.insert("strLinYeUnit", ui->caseLinYeUnitEdit->text());

    baseInfoJson.insert("strCaseNation", ui->caseNationEdit->text());
    baseInfoJson.insert("strCaseCulture", ui->caseCultureEdit->text());
    baseInfoJson.insert("strCaseJob", ui->caseJobEdit->text());
    baseInfoJson.insert("strCaseHumNumber", ui->caseHumNumberEdit->text());
    baseInfoJson.insert("strCaseHome", ui->caseHomeEdit->text());
    baseInfoJson.insert("strCaseCSITime", ui->csiTimeEdit->text());
    baseInfoJson.insert("strCaseCSILoc", ui->csiLocEdit->text());
    // 办案人员 两名
    baseInfoJson.insert("strCasePol1", ui->casePolEdit1->text());
    baseInfoJson.insert("strCasePol2", ui->casePolEdit2->text());
    // 复议机构
    baseInfoJson.insert("strCaseFuYi", ui->caseFuYiEdit->text());


    QJsonDocument baseInfoDocument;
    baseInfoDocument.setObject(baseInfoJson);
    QByteArray byte_array = baseInfoDocument.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    QFile file("config.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can't not open file for writing.";
    }
    QTextStream streamOut(&file);
    streamOut.setCodec("UTF-8");
    streamOut << json_str;
    file.close();

    emit userJsonChanged(); // 发出该信号
    close();
}

//

void BaseInfo::on_caseNumberEdit_textChanged(const QString &arg1)
{
    strCaseNum = arg1;

}

void BaseInfo::on_caseCopEdit_textChanged(const QString &arg1)
{
    strCaseCop = arg1;
}

void BaseInfo::on_caseFaWenNum1_textChanged(const QString &arg1)
{
    strFaWenNum1 = arg1;
}

void BaseInfo::on_caseFaWenNum2_textChanged(const QString &arg1)
{
    strFaWenNum2 = arg1;
}

void BaseInfo::on_caseForestUnitEdit_textChanged(const QString &arg1)
{
    strForestUnit = arg1;
}

void BaseInfo::on_caseLinYeUnitEdit_textChanged(const QString &arg1)
{
    strLinYeUnit = arg1;
}

void BaseInfo::on_caseNationEdit_textChanged(const QString &arg1)
{
    strCaseNation = arg1;
}

void BaseInfo::on_caseCultureEdit_textChanged(const QString &arg1)
{
    strCaseCulture = arg1;
}

void BaseInfo::on_caseJobEdit_textChanged(const QString &arg1)
{
    strCaseJob = arg1;
}

void BaseInfo::on_caseHumNumberEdit_textChanged(const QString &arg1)
{
    strCaseHumNumber = arg1;
}

void BaseInfo::on_caseHomeEdit_textChanged(const QString &arg1)
{
    strCaseHome = arg1;
}
