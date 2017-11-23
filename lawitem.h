#ifndef LAWITEM
#define LAWITEM

class QString;

// 案件来源
// 1.举报 2.检查发现
const QString strCFOfPReport = "2016年x月x日，我局接电话举报称苍溪县x乡x村x组x被人x，望调查处理。";
const QString strCFOfPCheck = "2016年x月x日，我局在检查x处xx工作的时候，发现x有x现象。";

// 滥伐林木案件法律条文------------------------------------------------------------------------------------------------------------------
const QString strLanFaChuFa = "1、处滥伐林木价值x倍的罚款x元;\n2、责令补种5倍的树木x株。";
const QString strLanFaLinMuAnQingBig = "2016年x月x日至x月x日，未经申请办理林木采伐许可证擅自在苍溪县x乡x村x自留山砍伐柏树x株，马尾松x株，并于在2016年x月x日将砍伐的林木全部搬运出现场运到X木材加工厂销售。2016年x月x日经现场勘验地径统一标号逐一检尺共测得滥伐柏树伐桩xx个，马尾松伐桩xx个，经相似木检尺测得柏树蓄积x立方米，马尾松蓄积x立方米；折合柏树材积（x*65%）x立方米，马尾松材积（x*66%）x立方米，林木价值x元(计价方式：)。以现场勘查笔录、xxx本人供述和证人证实为据。\n";
const QString strLanFaLinMuAnQingSmall = "";
const QString strLawItemLanFaWeiFa  = "《中华人民共和国森林法》第三十二条";     // 处罚决定书生成的有问题，这里应该用一个标签来表示
const QString strLawItemLanFaYiJu   =  "《中华人民共和国森林法》第三十九条第二款";
const QString strCSILanFaLinMu = "2016年x月x日，我局接到群众举报称苍溪县x乡x村x山上林木被非法采伐林木。我局立即组织林政执法人员严畯、何宗欣、权亮、张晓敏前往现场检查，经过调查核实当事人x其所砍伐的x自留山x林木未经申请批准，属滥伐林木。\n我局林政执法人员对现场进行了勘验检查。现场勘验由苍溪县森林公安局副局长严畯统一指挥，当天天气x，执法人员何宗欣、权亮、张晓敏由x乡x村x进入现场。现场位于苍溪县x乡x村x组x旁；被采伐山林面积约x亩，坡度约x°。周边生长有柏树、马尾松等林木；现场内可见被采伐林木柏树、马尾松留下的伐桩平均高约5㎝，伐桩表面平整，可见采伐树木的工具为油锯，采伐强度轻；现场内生长林木有柏树，地下植被有黄荆、杂灌等。被砍伐的树木已全部搬运出现场，被伐树木的枝桠也已基本清除干净。勘验人员对砍伐的伐桩统一标号逐一检尺，共测得采伐树木伐桩柏树x个，马尾松x个。检尺情况详件现场检尺表，后附现场照片2张，原木检尺表1张。";
//无证收购木材案------------------------------------------------------------------------------------------------------------------------------------
const QString strWuZhengShouGouChuFa = "1、责令xxx停止违法行为；\n2、没收无证收购的x木材积x立方米。";
const QString strWuZhengShouGouAnQingBig = "2016年x月至今，苍溪县x镇x村x组村民x未经申请批准无擅自在苍溪县x镇x乡场上开办木材加工厂无证收购木材。2016年x月x日经我局执法人员现场勘验林木统一标号逐一清点共测得柏树原木x件，共计材积x立方米。以现场勘查笔录、xxx本人供述和证人证实为据。";
const QString strWuZhengShouGouAnQingSmall = "2016年x月至今，未经申请批准擅自在苍溪县x镇原x乡场上开办木材加工厂无证收购柏树原木x件，共计材积x立方米。";
const QString strWuZhengShouGouWeiFan = "《四川省绿化条例》第二十六条";
const QString strWuZhengShouGouYiJu   = "《四川省绿化条例》第四十五条";
const QString strWuZhengShouGouCSI    = "2016年x月x日x时x分苍溪县森林公安局民警权亮、任洪林、何宗欣对苍溪县x镇木材加工厂进行检查时路过x发现x乡场安装的有带锯，发现带锯旁堆放有柏原木，民警随即对此处进行检查，经询问当事人XXX确认其未办理木材经营加工许可证，厂内的木料为其无证收购，随后民警在见证人的见证下对场内木料进行检尺，本次勘验检查由案件侦查股股长权亮统一指挥，检尺当天天气x，场内院坝处有柏原木，柏原木切面呈白色，随后民警对加厂内采伐证进行检查核对，勘验采用卷尺测量，记号笔对原木进行标记，相机对现场进行照相。经勘验现场柏原木共计X件,折合材积XX立方米。检尺情况详件现场检尺表，后附现场照片2张，原木检尺表1张。";
//收购无证木材案-----------------------------------------------------------------------------------------------------------------------------
const QString strShouGouWuZhengMuCaiChuFa = "1、责令xxx停止违法行为；\n2、没收收购的无证x木材积x立方米。";
const QString strShouGouWuZhengMuCaiAnQingBig = "201x年x月x日，苍溪县x镇x村村民x在苍溪县x镇x旁开办x木材加工厂收购x运输的一车x木无证木材，木材现已加工销售，失去检尺条件。201x年x月x日经我局执法人员对xx木材加工厂收购榜单清理，发现201x年x月x日收购x运输的x木一车，共计共计x吨，林木价值x.00（x*500.00元/吨）元。以现场勘查笔录、xxx本人供述和证人证实为据。";
const QString strShouGouWuZhengMuCaiAnQingSmall = "201x年x月x日，x木材加工厂x收购x运输的一车x木木材，无木材采伐许可证，共计x立方米。";
const QString strShouGouWuZhengMuCaiWeiFan = "《四川省绿化条例》第二十六条";
const QString strShouGouWuZhengMuCaiYiJu = "《四川省绿化条例》第四十五条";
const QString strShouGouWuZhengMuCaiCSI = "201x年x月x日苍溪县森林公安局民警权亮、任洪林、何宗欣对苍溪县x乡x村xx滥伐林木案件调查时发现其将滥伐的林木全部销售到x的x木材加工厂。我局民警立即驱车前往苍溪县x镇x村x木材加工厂，通过对x木材加工厂内堆放有原木进行检查，经询问当事人陈小华厂内收购的x卖出的x木木料为提供木材采伐许可证，收购的木料全部堆放于x加工厂x处，随后民警对加厂内采伐证进行检查核对，勘验采用卷尺测量，记号笔对原木进行标记，相机对现场进行照相。经勘验现场柏原木共计X件,折合材积XX立方米。检尺情况详件现场检尺表，后附现场照片2张，原木检尺表1张。（x==叙述方法不同：现已全部加工销售了，随后民警在见证人的见证下对场内销售记录进行检查，发现有一收据显示陈xx于201x年x月x日收购了x销售的一车松柏木共计x方米，每吨500元，金额为x.00元。后附收据一张，编号：xx。)  ";

// 无证运输木材-------------------------------------------------------------------------------------------------------------------------------
const QString strWuZhengYunShuChuFa = "1、没收其无证运输木材x立方米。";
const QString strWuZhengYunShuAnQingBig = "201x年0月0日，x雇请x承运木材，车辆为x色x车，车牌号为川Hx。从苍溪县x乡x村一组运输至县x工厂销售，在经过县x时被我局执法人员查获，经查其运输木材未办理木材运输许可证。经现场勘验核实，其无证运输x原木共计材积：x立方米。以现场勘查笔录、xxx本人供述和证人证实为据。\n";
const QString strWuZhengYunShuAnQingSmall = "201x年0月0日，苍溪县x镇x乡x，未办理木材运输许可证雇请x运输木材从苍溪县x乡x村运输至x工厂销售，车牌号为川Hx，经查证无证运输x原木共计x立方米。";
const QString strWuZhengYunShuWeiFan = "《四川省木材运输管理条例》第十一条";
const QString strWuZhengYunShuYiJu = "《四川省木材运输管理条例》第二十三条";
const QString strWuZhengYunShuCSI = "2016年x月x日x时x分苍溪县森林公安局民警权亮、任洪林、何宗欣对苍溪县x镇对x进行检查时路过x发现一辆运输木材的车辆，民警随即对该车辆进行了检查，车辆为蓝色农用车，车牌号是川Hx，检查时车辆停放于xx处。经询问当事人XXX确认其未办理木材运输许可证，随后民警在见证人的见证下对车上的木料进行检尺，本次勘验检查由案件侦查股股长权亮统一指挥，检尺当天天气x，车内运输的有x原木，柏原木切面呈白色，随后民警采用卷尺测量，记号笔对原木进行标记，相机对现场进行照相。经勘验现场柏原木共计x件,折合材积x立方米。检尺情况详件现场检尺表，后附现场照片2张，原木检尺表1张。";
// 超方运输木材-----------------------------------------------------------------------------------------------------------
const QString strChaoFangYunShuChuFa = "1.没收其超过木材运输许可证规定的数量运输的x原木，材积：x立方米";
const QString strChaoFangYunShuAnQingBig = "201x年0月0日，x雇请x承运木材，车辆为x色x车，车牌号为川Hx。从苍溪县x乡x村一组运输至县x工厂销售，在经过县x时被我局执法人员查获，经查其运输木材办理有木材运输许可证，证号：川0016XX，运输树种为x，材积：x立方米。经现场调查核实，其实际运输x原木，共计材积：x立方米。超过木材运输许可证规定的数量，运输x原木，折合材积：x立方米。以现场勘查笔录、xxx本人供述和证人证实为据。\n";
const QString strChaoFangYunShuAnQingSmall = "201x年0月0日，苍溪县x镇x乡x雇请x运输一车x原木，从x处到x处销售，经查证其超过木材运输许可证规定的数量，运输x原木折合材积x立方米。";
const QString strChaoFangYunShuWeiFan = "《四川省木材运输管理条例》第十一条";
const QString strChaoFangYunShuYiJu = "《四川省木材运输管理条例》第二十五条";
const QString strChaoFangYunShuCSI = "2016年x月x日x时x分苍溪县森林公安局民警权亮、任洪林、何宗欣对苍溪县x镇对x进行检查时路过x发现一辆运输木材的车辆，民警随即对该车辆进行了检查，车辆为蓝色农用车，车牌号是川Hx，检查时车辆停放于xx处。经询问当事人XXX确认其办理有木材运输许可证，证号：0016xx，树种为x原木，材积：x立方米。随后民警在见证人的见证下对车上的木料进行检尺，本次勘验检查由案件侦查股股长权亮统一指挥，检尺当天天气x，车内运输的有x原木，柏原木切面呈白色，随后民警采用卷尺测量，记号笔对原木进行标记，相机对现场进行照相。经勘验现场其实际运输x原木共计x件,折合材积x立方米。超过木材运输许可证规定的数量，运输x原木材积x立方米。检尺情况详件现场检尺表，后附现场照片2张，原木检尺表1张。";
// 过失失火案--------------------------------------------------------------------------------------------------------------
const QString strGuoShiShiHuoChuFa = "1.责令停止违法行为，给予警告；\n2.并处罚款2000-5000元罚款。";
const QString strGuoShiShiHuoAnQingBig = "201x年x月x日，苍溪县x镇x村x组xxx未经县林业和园林局申请批准，擅自在x镇x村自留山烧x导致发生森林火灾。201x年x月x日经我局执法人员现场勘验，共测得烧毁x树x株，经GPS测得过火面积x公顷（x亩）。以现场勘验笔录、xxx本人供述和证人证实为据。\n";
const QString strGuoShiShiHuoAnQingSmall = "201x年x月x日，苍溪县x镇x村x组xxx未经县林业和园林局申请批准，擅自在x镇x村自留山烧x导致发生森林火灾，过火面积x公顷，烧毁x树x株。";
const QString strGuoShiShiHuoWeiFan = "《四川省森林防火条例》第三十二条";
const QString strGuoShiShiHuoYiJu = "《四川省森林防火条例》第四十三条";
const QString strGuoShiShiHuoCSI = "201x年x月x日，我局接到x称苍溪县x镇x村x组xxx发生火灾。接警后我局立即民警前往现场检查，经过调查确认xx发生的森林火灾是由x未经批准在防火期内擅自在xx烧x所致，属于过失失火。\n我局民警立即对现场进行了勘验检查，现场勘验由苍溪县森林公安局副局长严畯统一指挥，当天天气晴朗，民警xxx、xxx由x路进入火灾现场。现场位于x镇x村x组x自留山，四至界限：东至x，西至x，南至x，北至x，常年x风向，土壤为山地黄壤，周边生长有x树，林下植被为茅草。现场可见被烧毁的x树，树干烧伤，个别出现枯萎，场内地下植被已全部烧毁，被烧毁的树种为x树。经过现场勘查起火点位于，x田边（现场南边），起火点内有未烧完的x，火势走向为x方向至x方向（南北向）燃烧。勘验人员使用GPS定点的方式，共测得现场面积x公顷，对过火面积内的x树统一标号，共测得烧毁x树x株。后附现场照片2张，现场示意图1张。";
// 擅自野外用火案未发生火灾-----------------------------------------------------------------------
const QString strShanZhiYeWaiYongHuoChuFa = "1.责令停止违法行为，给予警告；\n2.并处罚款200-2000元罚款。";
const QString strShanZhiYeWaiYongHuoAnQingBig = "201x年x月x日，苍溪县x镇x村x组xxx未经县林业和园林局申请批准，擅自在x镇x村自留山烧x未引发森林火灾。201x年x月x日经我局执法人员现场勘验，野外用火的地点位于x镇x村x地，四至界限：东至x，西至x，南至x，北至x，该区域为我县划定的防火区。以现场勘验笔录、xxx本人供述和证人证实为据。\n";
const QString strShanZhiYeWaiYongHuoAnQingSmall = "201x年x月x日，苍溪县x镇x村x组xxx未经县林业和园林局申请批准，擅自在x镇x村自留山（我县防火区）烧x，未引发森林火灾。";
const QString strShanZhiYeWaiYongHuoWeiFan = "《四川省森林防火条例》第三十二条";
const QString strShanZhiYeWaiYongHuoYiJu = "《四川省森林防火条例》第四十三条";
const QString strShanZhiYeWaiYongHuoCSI = "201x年x月x日，我局接到x称苍溪县x镇x村x组xxx有人未经批准在野外用火。接警后我局立即民警前往现场检查，经过调查确认当事人xxx其野外用火未经批准x。\n我局民警立即对xxx行为进行了制止并扑灭了明火，现场勘验由苍溪县森林公安局副局长严畯统一指挥，当天天气晴朗，民警xxx、xxx由x路进入违法用火现场。现场位于x镇x村x组x自留山，四至界限：东至x，西至x，南至x，北至x，常年x风向，该区域为我县划定的防火区。现场可见被点燃的x，田地内的x已全部烧毁。周边生长的有x树，林下植被为茅草，未被烧毁。后附现场照片2张，现场示意图1张。";

// 擅自改变林地用途 编号5
const QString strChangeLindiChuFa       =  "1.责令于x年x月x日前恢复原状；\n2.处非法改变林地用途每平方米10-30元罚款。";
const QString strChangeLindiAnQingBig   =  "201x年x月x日至x月x日，苍溪县xx镇xx村的xxx未经苍溪县林业和园林局审批，擅自在苍溪县xx镇xx村xx地占用林地修建xx。201x年x月x日，经我局执法人员对现场进行了勘验检查，查证xxx占用林地属于xxx林地，经GPS（皮尺）测得占用林地面积x公顷(x平方米)。以现场勘查笔录、xxx本人供述和证人证实为据。";
const QString strChangeLindiAnQingSmall =  "201x年x月x日至x月x日，未经苍溪县林业和园林局申请批准，擅自在xx镇xx村xx地xxx处占用林地修xx，经查证占用林地为xx林地，共计占用x公顷（x平方米）。";
const QString strChangeLindiWeiFan      =  "《中华人民共和国森林法实施条例》第十七条";
const QString strChangeLindiYiJu        =  "《中华人民共和国森林法实施条例》第四十三条";
const QString strChangeLindiCSI         =  "201x年x月x日，我局接到xx举报称xx有人占用林地修xx。接警后我局民警立即前往现场检查，经过调查确认当事人xxx其非法改变林地用途修xx未经林业和园林局审批。\n我局民警立即对现场进行了勘验检查，现场勘验由苍溪县森林公安局副局长严畯统一指挥，当天天气晴朗，民警权亮、何宗欣由xx路进入占用林地现场，现场位于苍溪县xx镇xx村x组小地名xx处，现场周边生长的有生长良好的XX树，林地所有权人为xxx，被占用的林地属于xx树林，中心现场内是一块被平整的土地，有未完工的xx房，堆放的有修建房屋用的水泥、石料等，经过GPS（或皮卷尺）测得已占用林地面积为x公顷（x平方米）。后附现场照片2张，现场示意图1张。";


#endif // LAWITEM


//  参考code
/*  QAxWidget *word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
   // word->setProperty("Visible", true);
   // 获取所有的工作文档
   QAxObject * documents = word->querySubObject("Documents");
   // 以文件template.doc为模版新建一个文档
   documents->dynamicCall("Add(QString)",QString::fromLocal8Bit("D:/temple/cover.doc"));
   // 获取当前激活的文档
   QAxObject *document=word->querySubObject("ActiveDocument");

   // 获取文档中名字为text的标签
   QAxObject*bookmark_text=document->querySubObject("Bookmarks(QVariant)","nameOfCase");
   // 选中标签，将字符InsertText插入到标签位置
   if(!bookmark_text->isNull()){
   bookmark_text->dynamicCall("Select(void)");
   bookmark_text->querySubObject("Range")->setProperty("Text","敬正帅滥伐林木案");
  }
   // 将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
   document->dynamicCall("SaveAs (const QString&)", QString("D:/封面.doc"));
   document->dynamicCall("Close (boolean)", false);
   word->dynamicCall("Quit()");

*/


