#include "HanCharacter.h"
HanCharacter::HanCharacter()
{}
/*
han_character_frequency.txt来源:https://lingua.mtsu.edu/chinese-computing/statistics/char/list.php?Which=TO
Column 1: Serial number; 第一列：序号
Column 2: Character; 第二列：汉字
Column 3: Individual raw frequency; 第三列：频率
Column 4: Cumulative frequency in percentile; 第四列：累计频率(%)
Column 5: Pinyin. 请注意：拼音取自于CEDICT: Chinese-English Dictionary (http://www.mandarintools.com/cedict.html), the online HSK word list (http://www.chinese-forums.com/vocabulary/)和汉语拼音与输入法论坛(http://sh.netsh.com/bbs/1951/)的GBK汉字列表。数字代表声调。如果没有声调则表示轻声。该信息只是提供给用户以参考。其准确性没有校对过。
Column 6: English translation; 英文翻译。请注意：英文翻译来源于CEDICT: Chinese-English Dictionary (http://www.mandarintools.com/cedict.html)。目前使用的数据是21 December 2005发布的版本。该信息只是提供给用户以参考。其准确性没有校对过。
 */
void HanCharacter::initDb()
{
    db=QSqlDatabase::addDatabase("QSQLITE","qt");
    db.setDatabaseName(QApplication::applicationDirPath()+"/han_character_frequency.db");
    bool ok=false;
    ok=db.open();
    qDebug() << "debug92" << ok;
    if(!ok) return;
    QSqlQuery query(db);
    ok=query.exec("drop table if exists `character_frequency`");
    qDebug() << "debug75" << ok;
    ok=query.exec("create table character_frequency(serial_number int, karacter varchar(2) not null, individual_raw_frequency int, cumulative_frequency float, pinyin varchar(16), english_translation varchar(1024));");
    qDebug() << "debug77" << ok;
    QString filename=QApplication::applicationDirPath()+"/han_character_frequency.txt";
    QString line;
    QStringList ss;
    QByteArray ba;
    QFile file(filename);
    ok=file.open(QFile::ReadOnly);
    qDebug() << "debug93" << ok;
    if(!ok) return;
    int l=0;
    QString trans,s;
    QStringList pinyins;
    while(!file.atEnd()) {
        ba=file.readLine();
        line=QString::fromUtf8(ba);
        line=line.trimmed();
        ss=line.split('\t');
        qDebug() << "debug98-9" << l << line << ss.size();
        s.clear();
        if(ss.size()>4) {
            s=ss[4];
            for(int n=0;n<s.size();n++) {
                if(!s[n].isLetter() && s[n]!='/') {
                    s.remove(n,1);
                    n--;
                }
            }
            s=s.toLower();
            pinyins=s.split('/');
        }
        trans.clear();
        if(ss.size()>5) {
            trans=ss[5];
        }
        for(int i=0;i<pinyins.size();i++) {
            s=pinyins[i];
            ok=query.exec(QString("insert into character_frequency values(%1,\'%2\',%3,%4,\'%5\',\'%6\')").arg(ss[0]).arg(ss[1]).arg(ss[2]).arg(ss[3]).arg(s).arg(trans));
            qDebug() << "debug54" << l << ok << s;
        }
        l++;
    }
    db.close();
    file.close();
}
