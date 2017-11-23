#include "anqinginfodialog.h"
#include "ui_anqinginfodialog.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>

AnQingInfoDialog::AnQingInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnQingInfoDialog)
{
    ui->setupUi(this);
    //初始化
    btextChang = false;
    // 隐藏添加功能的按钮
    ui->label->hide();
    ui->caseInPutEdit->hide();
    ui->okPushButton->hide();
    ui->cancerButton->hide();

   //  读取anQing-config.json文件
    loadAnQingJsonFile();
    QFile fileName("anQing-config.json");
    if(!fileName.exists())
    {
        ui->deleteButton->setDisabled(true);
        ui->modiButton->setDisabled(true);

    }
    fileName.open(QIODevice::ReadOnly);
    QByteArray byteArray = fileName.readAll();
    QJsonParseError json_error;
    QJsonDocument parse_doc = QJsonDocument::fromJson(byteArray, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doc.isObject())
        {
            QJsonObject obj = parse_doc.object();
            if(obj.isEmpty())
            {
                ui->deleteButton->setDisabled(true);
                ui->modiButton->setDisabled(true);

            }
        }
    }




}

AnQingInfoDialog::~AnQingInfoDialog()
{
    delete ui;
}

void AnQingInfoDialog::on_addButton_clicked() //点击增加的时候清空界面上的内容，并初始时界面
{
    // 显示增加按钮的确定和取消，显示文本框d等deng
    ui->label->show();
    ui->caseInPutEdit->show();
    ui->label_2->hide();
    ui->comboBox->hide();
    ui->deleteButton->setDisabled(true);
    ui->modiButton->setDisabled(true);
    ui->quitButton->setDisabled(true);
    ui->okPushButton->show();
    ui->cancerButton->show();
    ui->addButton->setDisabled(true);
    // 清空界面上所有的编辑框的内容
    ui->caseInPutEdit->clear();
    ui->caseWeiFanEdit->clear();
    ui->caseYiJuEdit->clear();
    ui->caseChuFaEdit->clear();
    ui->caseAnQingBigEdit->clear();
    ui->caseAnQingSmallEdit->clear();
    ui->caseFromEdit->clear();
    ui->caseCSIEdit->clear();


}

void AnQingInfoDialog::on_cancerButton_clicked()
{
    ui->cancerButton->hide();
    ui->okPushButton->hide();

    ui->addButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
    ui->modiButton->setEnabled(true);
    ui->quitButton->setEnabled(true);

    ui->label_2->show();
    ui->comboBox->show();

    ui->label->hide();
    ui->caseInPutEdit->hide();


    // 点击取消返回界面
    QFile fileName("anQing-config.json");
    if (fileName.exists()) //配置文件存在
    {
        // 打开并读取anQing-config配置文件信息，并将内容添加到界面上去，设置一个默认显示
        fileName.open(QIODevice::ReadOnly) ;// 以只读模式打开
        QJsonParseError json_error;
        QByteArray read_byte;
        read_byte = fileName.readAll();

        QJsonDocument parse_doc = QJsonDocument::fromJson(read_byte,&json_error);

        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doc.isObject())
            {
                // 遍历所以key值,将内容添加到combobox中去
                QJsonObject obj = parse_doc.object();

                // 写入初始状态下的页面信息
                if (!ui->comboBox->currentText().isEmpty())
                {

                    QJsonObject loadObj = obj.value(ui->comboBox->currentText()).toObject();
                    ui->caseWeiFanEdit->setText(loadObj["caseWeiFan"].toString());
                    ui->caseYiJuEdit->setText(loadObj["caseYiJu"].toString());
                    ui->caseChuFaEdit->setText(loadObj["caseChuFa"].toString());
                    ui->caseFromEdit->setText(loadObj["caseFrom"].toString());
                    ui->caseAnQingBigEdit->setText(loadObj["caseAnQingBig"].toString());
                    ui->caseAnQingSmallEdit->setText(loadObj["caseAnQingSmall"].toString());
                    ui->caseCSIEdit->setText(loadObj["caseCSI"].toString());


                }


            }

        }



    }




}
#include <QDebug>

void AnQingInfoDialog::on_quitButton_clicked()
{
    emit anQingJsonChanged();


    close();
}

void AnQingInfoDialog::on_okPushButton_clicked()
{
    if(ui->caseInPutEdit->text() != NULL)
    {


        // 数据形如 var txt = {”caseClassName“:{littleName    ,   , ,,, }, "caseClassName2":{little,,,,,} }
        QJsonObject caseClassName;
        QJsonObject littleName;

        littleName.insert("caseWeiFan", ui->caseWeiFanEdit->text());
        littleName.insert("caseYiJu", ui->caseYiJuEdit->text());
        littleName.insert("caseChuFa", ui->caseChuFaEdit->toPlainText());
        littleName.insert("caseFrom", ui->caseFromEdit->toPlainText());
        littleName.insert("caseAnQingBig", ui->caseAnQingBigEdit->toPlainText());
        littleName.insert("caseAnQingSmall", ui->caseAnQingSmallEdit->toPlainText());
        littleName.insert("caseCSI", ui->caseCSIEdit->toPlainText());




       QFile fileName("anQing-config.json");
       if (fileName.exists())
       {
           fileName.open(QIODevice::ReadOnly);
           QByteArray byte_array;
           byte_array = fileName.readAll();
           fileName.close();
           QJsonParseError json_error;
           QJsonDocument parse_document = QJsonDocument::fromJson(byte_array, &json_error);
           qDebug() << json_error.error;
           if (json_error.error == QJsonParseError::NoError)
           {
               if (parse_document.isObject())
               {
                   QJsonObject obj = parse_document.object();
                   obj.insert(ui->caseInPutEdit->text(), littleName);
                   // 写入新值
                   fileName.open(QIODevice::WriteOnly);
                   QTextStream streamOut(&fileName);
                   streamOut.setCodec("UTF-8");
                   QJsonDocument doc;
                   doc.setObject(obj);
                   QByteArray byte = doc.toJson(QJsonDocument::Compact);
                   QString json_str(byte);
                   streamOut << json_str;
                   fileName.close();
                   ui->comboBox->addItem(ui->caseInPutEdit->text());

                   int ret =  QMessageBox::warning(this, "添加成功提醒", "恭喜你，年轻人，你已经成功的添加了一条新的案件类别，你继续添加吗？", QMessageBox::Ok | QMessageBox::Cancel);
                   qDebug() << ret << QMessageBox::Ok;
                   if (ret == QMessageBox::Ok) // 清空界面内容
                   {
                       ui->caseInPutEdit->clear();
                       ui->caseWeiFanEdit->clear();
                       ui->caseYiJuEdit->clear();
                       ui->caseChuFaEdit->clear();
                       ui->caseAnQingBigEdit->clear();
                       ui->caseAnQingSmallEdit->clear();
                       ui->caseFromEdit->clear();
                       ui->caseCSIEdit->clear();
                   }
                   else   // 取消返回主界面
                   {
                       on_cancerButton_clicked();
                   }

               }
           }



       }
       else
       {

           caseClassName.insert(ui->caseInPutEdit->text(), littleName);
           fileName.open(QIODevice::WriteOnly);

           QJsonDocument jsonDoc;
           jsonDoc.setObject(caseClassName);
           QByteArray byte_array = jsonDoc.toJson(QJsonDocument::Compact);
           QString json_str(byte_array);

           QTextStream streamOut(&fileName);
           streamOut.setCodec("UTF-8");
           streamOut << json_str;
           fileName.close();
           ui->comboBox->addItem(ui->caseInPutEdit->text());

           int ret =  QMessageBox::warning(this, "添加成功提醒", "恭喜你，年轻人，你已经成功的添加了一条新的案件类别，你继续添加吗？", QMessageBox::Ok | QMessageBox::Cancel);
           qDebug() << ret << QMessageBox::Ok;
           if (ret == QMessageBox::Ok) // 清空界面内容
           {
               ui->caseInPutEdit->clear();
               ui->caseWeiFanEdit->clear();
               ui->caseYiJuEdit->clear();
               ui->caseChuFaEdit->clear();
               ui->caseAnQingBigEdit->clear();
               ui->caseAnQingSmallEdit->clear();
               ui->caseFromEdit->clear();
               ui->caseCSIEdit->clear();
           }
           else   // 取消返回主界面
           {
               on_cancerButton_clicked();
           }

           // 清空页面所有内容


       }

    }

    else
    {
        QMessageBox::warning(this, "警告提示：", "请输入新增案件类别！", QMessageBox::Ok);
    // 情况页面内容
    }

}

void AnQingInfoDialog::loadAnQingJsonFile()
{

    QFile fileName("anQing-config.json");
    if (fileName.exists()) //配置文件存在
    {
        // 打开并读取anQing-config配置文件信息，并将内容添加到界面上去，设置一个默认显示
        fileName.open(QIODevice::ReadOnly) ;// 以只读模式打开
        QJsonParseError json_error;
        QByteArray read_byte;
        read_byte = fileName.readAll();

        QJsonDocument parse_doc = QJsonDocument::fromJson(read_byte,&json_error);

        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doc.isObject())
            {
                // 遍历所以key值,将内容添加到combobox中去
                QJsonObject obj = parse_doc.object();
                ui->comboBox->addItems(obj.keys());
                // 写入初始状态下的页面信息
                if (!ui->comboBox->currentText().isEmpty())
                {

                    QJsonObject loadObj = obj.value(ui->comboBox->currentText()).toObject();
                    ui->caseWeiFanEdit->setText(loadObj["caseWeiFan"].toString());
                    ui->caseYiJuEdit->setText(loadObj["caseYiJu"].toString());
                    ui->caseChuFaEdit->setText(loadObj["caseChuFa"].toString());
                    ui->caseFromEdit->setText(loadObj["caseFrom"].toString());
                    ui->caseAnQingBigEdit->setText(loadObj["caseAnQingBig"].toString());
                    ui->caseAnQingSmallEdit->setText(loadObj["caseAnQingSmall"].toString());
                    ui->caseCSIEdit->setText(loadObj["caseCSI"].toString());


                }


            }

        }



    }
}

void AnQingInfoDialog::closeEvent(QCloseEvent *event)
{
    emit anQingJsonChanged();
}

void AnQingInfoDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{

    QFile readFile("anQing-config.json");
    if (!readFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "commbox 变更读取文件不存在";
    }
    QJsonParseError json_error;
    QByteArray read_byte;
    read_byte = readFile.readAll();

    QJsonDocument parse_doc = QJsonDocument::fromJson(read_byte,&json_error);

    if (json_error.error == QJsonParseError::NoError)
    {
        if (parse_doc.isObject())
        {
            QJsonObject obj = parse_doc.object();
            QJsonObject loadObj = obj.value(arg1).toObject();

            ui->caseWeiFanEdit->setText(loadObj["caseWeiFan"].toString());
            ui->caseYiJuEdit->setText(loadObj["caseYiJu"].toString());
            ui->caseChuFaEdit->setText(loadObj["caseChuFa"].toString());
            ui->caseFromEdit->setText(loadObj["caseFrom"].toString());
            ui->caseAnQingBigEdit->setText(loadObj["caseAnQingBig"].toString());
            ui->caseAnQingSmallEdit->setText(loadObj["caseAnQingSmall"].toString());
            ui->caseCSIEdit->setText(loadObj["caseCSI"].toString());
        }
    }

}
// 删除选择的项目
void AnQingInfoDialog::on_deleteButton_clicked()
{
    if(!ui->comboBox->currentText().isEmpty())
    {
        // 解析文件获取当前项目的对象
        QFile fileName("anQing-config.json");
        fileName.open(QIODevice::ReadOnly);
        QByteArray byteArray = fileName.readAll();
        fileName.close();

        QJsonParseError json_error;

        QJsonDocument parse_doc = QJsonDocument::fromJson(byteArray, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doc.isObject())
            {

                int ret =  QMessageBox::warning(this, "提示", "你确定要删除:"+ui->comboBox->currentText()+"选项吗?", QMessageBox::Ok | QMessageBox::Cancel);

                if (ret == QMessageBox::Ok) // 清空界面内容
                {
                    QJsonObject obj = parse_doc.object();
                    obj.remove(ui->comboBox->currentText());

                    QFile fileName("anQing-config.json");
                    fileName.open(QIODevice::WriteOnly);

                    QJsonDocument jsonDoc;
                    jsonDoc.setObject(obj);
                    QByteArray byte_array = jsonDoc.toJson(QJsonDocument::Compact);
                    QString json_str(byte_array);

                    QTextStream streamOut(&fileName);
                    streamOut.setCodec("UTF-8");
                    streamOut << json_str;
                    fileName.close();

                    ui->comboBox->clear();
                    loadAnQingJsonFile();
                }
                else   // 取消返回主界面
                {
                    on_cancerButton_clicked();
                }


            }
        }
    }
    else
    {
        ui->deleteButton->setEnabled(true);
        ui->modiButton->setEnabled(true);
    }
}

void AnQingInfoDialog::on_modiButton_clicked()
{
    if(btextChang && !ui->comboBox->currentText().isEmpty())
    {
        QFile file("anQing-config.json");
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
                QJsonObject modifiObj = obj.value(ui->comboBox->currentText()).toObject();

                modifiObj["caseWeiFan"] = strCgWeiFan;
                modifiObj["caseYiJu"] = strCgYiJu;
                modifiObj["caseChuFa"] = strCgCf;
                modifiObj["caseAnQingBig"] = strCgAqBig;
                modifiObj["caseAnQingSmall"] = strCgAqSmall;
                modifiObj["caseCSI"] = strCgCSI;
                modifiObj["caseFrom"] = strCgFrom;

                obj[ui->comboBox->currentText()] = modifiObj;

                QFile file("anQing-config.json");
                file.open(QIODevice::WriteOnly);
                QJsonDocument doc;
                doc.setObject(obj);
                QByteArray modiByte = doc.toJson(QJsonDocument::Compact);
                QString json_str(modiByte);

                QTextStream out(&file);
                out.setCodec("UTF-8");
                out << json_str;
                file.close();
                QMessageBox::about(this, "修改成功提示", "恭喜你，年轻人，你已经成功修改了"+ui->comboBox->currentText()+"继续加油");

            }
        }
    }
}

// 界面上发生修改以后进行判断并保存 btextChang  strCg...
void AnQingInfoDialog::on_caseWeiFanEdit_textChanged(const QString &arg1)
{
    btextChang = true;
    strCgWeiFan = arg1;

}

void AnQingInfoDialog::on_caseYiJuEdit_textChanged(const QString &arg1)
{
      btextChang = true;
      strCgYiJu = arg1;
}

void AnQingInfoDialog::on_caseChuFaEdit_textChanged()
{
      btextChang = true;
      strCgCf = ui->caseChuFaEdit->toPlainText();
}

void AnQingInfoDialog::on_caseFromEdit_textChanged()
{
      btextChang = true;
      strCgFrom = ui->caseFromEdit->toPlainText();
}

void AnQingInfoDialog::on_caseAnQingBigEdit_textChanged()
{
      btextChang = true;
      strCgAqBig = ui->caseAnQingBigEdit->toPlainText();
}

void AnQingInfoDialog::on_caseAnQingSmallEdit_textChanged()
{
      btextChang = true;
      strCgAqSmall = ui->caseAnQingSmallEdit->toPlainText();
}

void AnQingInfoDialog::on_caseCSIEdit_textChanged()
{
      btextChang = true;
      strCgCSI = ui->caseCSIEdit->toPlainText();
}
