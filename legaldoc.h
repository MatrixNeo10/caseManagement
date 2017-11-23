#ifndef LEGALDOC_H
#define LEGALDOC_H
#include <QString>
/* 本类用于创建法律文书用*/



class legalDoc
{
public:
    legalDoc();
    void openExplor();
    // 创建封面
    void  CreatCaseCoverTest(QString strNameCase, QString strNumCase, QString strNameCrimi, QString strStartCase,QString strEndCase, QString strUpUnitCase, QString strCheckUnitCase, QString strNamePol);
    // 创建目录
    void CreateCaseContent(QString strUnitAuthor, QString strPolAuthor, QString strFaWenHao, QString strNumCase, QString strStartCase,QString strEndCase );
    // 案件调查终结报告
    void CreateCaseDoneReport(QString strCaseLaiYuan, QString strCaseBaseInfo, QString strCaseAnQingBig, QString strCaseCrimi, QString strCaseWeiFan, QString strCaseYiJu, QString strLittleName,QString strCaseChuFa, QString strCaseUnit, QString strCasePol, QString strCaseTime);
    // 处罚决定书
    void CreateCaseDecideBook(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCrimi, QString strSexCrimi, QString strBirDCrimi, QString strID, QString strAddress, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strFuYi, QString strTime);
    // 文书送达回证
    void CreateCaseSend(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strNameCrimi );
    // 立案登记表
    void CreateCaseUp(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strFoundation, QString strTime, QString strNameCrimi, QString strSexCrimi, QString strBirDCrimi, QString strAddress, QString strLaiYuan);
    // 处罚意见书
    void CreateCaseDecideIdea(QString strCaseDecideUnitHao, QString strNumOfCase, QString strNameCase, QString strTime,QString strNameCrimi,QString strSexCrimi,QString strBirDCrimi, QString strIDCrimi, QString strAddress,  QString strAnQingBig);
    // 延期缴纳
    void CreateCaseFenQi(QString strCaseHao, QString strNumCase,QString strNameCrimi,QString strTime);
    // 受理报警登记表
    void CreateCaseBaoJing(QString strCaseHao, QString strNumCase, QString strTime, QString strLaiYuan);
    // 权利义务告知书
    void CreateCaseRight();
    // 先行告知书
    void CreateCaseFirstNotify(QString strCaseHao, QString strNumCase, QString strNameCrimi, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strTime);
    // 听证告知书
    void CreateCaseTingZheng(QString strCaseHao, QString strNumCase, QString strNameCrimi, QString strAnQingSmall, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa, QString strTingZheng, QString strTime);
    // CSI
    void CreateCSI(QString strCheckTime, QString strCheckAddr, QString strNameCrimi, QString strIDCrimi, QString strCrimiAddr, QString strCSI, QString strTime);
    // 呈批表：调查终结
    void CreateCaseDoneOK(QString strCaseHao, QString strNumCase, QString strCaseName,QString strLaiYuan, QString strAnQingSmall, QString strCaseLittleName, QString strLawItemWeiFan, QString strLawItemYiJu, QString strChuFa);
    // 呈批表：没收物品
    void CreateCaseMoShou(QString strCaseHao, QString strNumCase, QString strCaseName, QString strAnQingBig, QString strNameCrimi, QString strWeiFan, QString strCaseLittleName, QString strYiJu, QString ChuFa);
    // 呈批表：变价处理
    void CreateCaseBianJia(QString strCaseHao, QString strNumCase, QString strCaseName, QString strAnQingBig, QString strNameCrimi, QString strWeiFan, QString strCaseLittleName, QString strYiJu, QString ChuFa);
//   没收物品清单
    void CreateMoshouList(QString strCaseHao, QString strNameCrimi, QString strNumCase);
    // 木材价格表
    void CreateWoodCost();
    // 申请缓交
    void CreateCasePlease(QString strUnitAuthor, QString strTime, QString strLittleName);
    // 申请变价处理
    void CreateGiveMe(QString strUnitAuthor,QString strTime);
    // 代缴罚款申请
    void CreateWeiTuo(QString strUnitAuthor, QString strCaseHao, QString strNumCase, QString strUnitAuthorPol, QString strTime);
    // 合议记录
    void CreateHeYi(QString strNameCase, QString strTime, QString strAnQingBig, QString strCasePol, QString strNameCrimi, QString strLawWeiFan, QString strCaseLittleName, QString strLawYiJu, QString strChuFa);
    // 调取证据清单
    void CreateDiaoQu(QString strUnitAuthor);
    // 卷内备考表
    void CreateBackUpTable(QString strCaseName, QString strUpPol, QString strTime);
    // 鉴定聘请呈批表
    void CreateJianDingOk( QString strCaseHao,QString strCaseNum, QString strCaseName);
    // 鉴定委托
    void CreateJianDingWeiTuo(QString strCaseHao, QString strCaseNum, QString strCaseName, QString timeStart, QString timeEnd);
    // 资格复印
    void CreateJianDingFuYing();
    // 鉴定意见
    void CreateJianDingYiJian(QString strCaseHao, QString strCaseNum, QString timeEnd);
    // 调取证据呈批表
    void CreateDiaoQuOk( QString strCaseHao,QString strCaseNum, QString strCaseName);
    // 延期缴纳罚款呈批表
    void CreateYanQiOk(QString strCaseHao,QString strCaseNum, QString strCaseName);
    // 补种树木通知书
    void CreateBuZhong(QString strCaseHao,QString strCaseNum,QString strNameCrimi, QString strAnQingSmall, QString strWeiFan,QString strTime);
    // 阅卷笔录
    void CreateCaseRead(QString strCaseName, QString strPol, QString strTime);

private:
   QString  strPrintDir;
};

#endif // LEGALDOC_H
