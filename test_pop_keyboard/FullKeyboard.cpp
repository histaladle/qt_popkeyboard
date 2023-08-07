#include "FullKeyboard.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QValidator>
#include <QDebug>
#include <QSpacerItem>
#include <QPlainTextEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>
#include <QKeyEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>
FullKeyboard::FullKeyboard(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowModality(Qt::NonModal);
    initKeyboardPages();
    initKeyboard();
    for(int i=0;i<btnPages.size();i++)
    {
        updateKeyboard(i, keyboardStatus);
    }
    setWordBarVisible(false);
    langFlags[0]=1;
    langFlags[1]=1;
}

void FullKeyboard::initKeyboard()
{
    QPushButton *btn=nullptr;
    QList<QList<QPushButton*> > btnLines;

    QVBoxLayout *vlayout=nullptr, *kvlayout=nullptr;
    vlayout=new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    QWidget *w=nullptr;
    QGridLayout *glayout=nullptr;
    glayout=new QGridLayout();
    vlayout->addItem(glayout);

    int wah=30;
    spellLabel=new QLabel(this);
    spellLabel->setMaximumWidth(200);
    spellLabel->setFixedHeight(wah);
    spellLabel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    glayout->addWidget(spellLabel,0,0);

    btn=new QPushButton("<",this);
    btn->setFixedWidth(40);
    btn->setFixedHeight(wah);
    btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    leftWordAreaBtn=btn;
    connect(btn,&QPushButton::pressed,this,[this](){
        if(wordBtns.isEmpty()) {
            return;
        }
        wordArea->horizontalScrollBar()->setValue(wordArea->horizontalScrollBar()->value()-wordArea->horizontalScrollBar()->maximum()/wordBtns.size());
    });
    glayout->addWidget(btn,0,1);

    wordArea=new QScrollArea(this);
    wordArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wordArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wordArea->setFixedHeight(wah);
    wordArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    glayout->addWidget(wordArea,0,2);
    wordArea->setWidgetResizable(true);

    w=new QWidget(this);
    wordContentLayout=new QGridLayout(w);
//    w->setStyleSheet("QWidget{background-color:red;}");
    wordContentLayout->setSpacing(0);
    wordContentLayout->setMargin(0);
    wordArea->setWidget(w);
    qDebug() << "debug82" << wordArea->widget() << w
             << w->layout() << wordContentLayout;

    btn=new QPushButton(">",this);
    btn->setFixedWidth(40);
    btn->setFixedHeight(wah);
    btn->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    rightWordAreaBtn=btn;
    connect(btn,&QPushButton::pressed,this,[this](){
        if(wordBtns.isEmpty()) {
            return;
        }
        wordArea->horizontalScrollBar()->setValue(wordArea->horizontalScrollBar()->value()+wordArea->horizontalScrollBar()->maximum()/wordBtns.size());
    });
    glayout->addWidget(btn,0,3);



    int minKeyWidth=50,minKeyHeight=40;

    QWidget *kbwidget=nullptr;
    QList<QPushButton*> btnLine;
    QHBoxLayout *khlayout=nullptr;

    keyboardStack=new QStackedWidget(this);
    vlayout->addWidget(keyboardStack);

    for(int page=0;page<2;page++) {
        btnLines.clear();
        kbwidget=new QWidget();
        keyboardStack->addWidget(kbwidget);
        kvlayout=new QVBoxLayout(kbwidget);
        kvlayout->setMargin(0);
        kvlayout->setSpacing(0);
        for(int line=0;line<keyboardPages[page].size();line++) {
            khlayout=new QHBoxLayout();
            khlayout->setMargin(3);
            khlayout->setSpacing(3);
            kvlayout->addItem(khlayout);
            btnLine.clear();
            for(int n=0;n<keyboardPages[page][line].size();n++) {
                btn=new QPushButton(kbwidget);
                btn->setStyleSheet("QPushButton{font-size:8pt;font-weight:bold;}");
                btn->installEventFilter(this);
                btn->setFocusPolicy(Qt::NoFocus);
                btn->setMinimumSize(minKeyWidth,minKeyHeight);
                btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                connect(btn,&QPushButton::pressed,this,[this,page,line,n]{
                    onKeyPressed(page,line,n);
                });
                connect(btn,&QPushButton::released,this,[this,page,line,n](){
                    onKeyReleased(page,line,n);
                });
                khlayout->addWidget(btn);
                btnLine.append(btn);
            }
            btnLines.append(btnLine);
        }
        btnPages.append(btnLines);
    }

    setFixedWidth(700);
    qDebug() << "debug18" << this->width() << btnPages.size()
             << keyboardStack->count();
    connect(keyboardStack,&QStackedWidget::currentChanged,[this](int index){
        if(index==1) {
            setWordBarVisible(true);
        }
        else {
            setWordBarVisible(false);
        }
    });
    for(int l=0;l<btnLines.size();l++)
    {
        qDebug() << "key line" << l << btnLines[l].size();
    }
    QFont font;
    font=this->font();
    font.setPointSize(10);
    this->setFont(font);
}

bool FullKeyboard::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    if(event->type()==QEvent::MouseMove) {
        if(moveEnabled) {
            this->move(this->pos()+(QCursor::pos()-lastMousePos));
            lastMousePos=QCursor::pos();
        }
    }
    return false;
}

void FullKeyboard::updateKeyboard(int page, int status)
{
    QList<QList<QPushButton*> > btnLines;
    QList<QPushButton*> btnLine;
    btnLines=btnPages[page];
    for(int i=0;i<btnLines.size();i++) {
        btnLine=btnLines[i];
        for(int j=0;j<btnLine.size();j++) {
            if(status==Lowered) {
                btnLine[j]->setText(keyboardPages[page][i][j].label);
            }
            else if(status==Shifted) {
                btnLine[j]->setText(keyboardPages[page][i][j].shiftedLabel);
            }
        }
    }
}

void FullKeyboard::insertKeyValue(int page, int line, int index)
{
    QString s1,s2;
    QKeyEvent *ke=nullptr;
    if(keyboardStack->currentIndex()==1) {
        QString spell;
        QStringList ss;
        spell=spellLabel->text();
        if(keyboardStatus==Lowered) {
            spell.append(keyboardPages[page][line][index].text);
        }
        else if(keyboardStatus==Shifted){
            spell.append(keyboardPages[page][line][index].shiftedText);
        }
        if(spell==spellLabel->text()) {
            return;
        }
        spellLabel->setText(spell);
//        for(int i=0;i<spell.size();i++) {
//            if(spell[i]==0x0a || spell[i]==0x0d) {
//                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,spell.mid(0,i));
//                QApplication::sendEvent(atUi,ke);
//                delete ke;
//                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,spell.mid(0,i));
//                QApplication::sendEvent(atUi,ke);
//                delete ke;

//                clearWordArea();
//                spellLabel->clear();
//                return;
//            }
//        }
        bool spellLegal=true;
        for(int i=0;i<spell.size();i++) {
            if(!spell[i].isLower()) {
                spellLegal=false;
                break;
            }
        }
        if(spellLegal) {
            ss=pin(spell);
            updateWordArea(ss);
        }
        else {
            clearWordArea();
        }
    }
    else {
        if(keyboardStatus==Lowered)
        {
            ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].text);
            QApplication::sendEvent(atUi,ke);
            delete ke;
            ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].text);
            QApplication::sendEvent(atUi,ke);
            delete ke;
        }
        else if(keyboardStatus==Shifted)
        {
            ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
            QApplication::sendEvent(atUi,ke);
            delete ke;
            ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,keyboardPages[page][line][index].shiftedText);
            QApplication::sendEvent(atUi,ke);
            delete ke;
        }
    }
}

void FullKeyboard::onKeyPressed(int page, int line, int index)
{
    QString s;
    QStringList ss;
    insertKeyValue(page,line,index);
    qDebug() << "keyboard pressed" << page << line << index;
    if(line==2 && index==0) //shift
    {
        keyboardStatus=(keyboardStatus+1)%2;
        updateKeyboard(page,keyboardStatus);
    }
    else if(line==2 && index==12) {
        if(page==0) {
            QKeyEvent *ke=nullptr;
            ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
            QApplication::postEvent(atUi,ke);
            ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Return,Qt::NoModifier);
            QApplication::postEvent(atUi,ke);
        }
        else if(page==1) {
            if(spellLabel->text().isEmpty()) {
                QKeyEvent *ke=nullptr;
                ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
                QApplication::postEvent(atUi,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Return,Qt::NoModifier);
                QApplication::postEvent(atUi,ke);
            }
            else {
                QKeyEvent *ke=nullptr;
                ke=new QKeyEvent(QEvent::KeyPress,0,Qt::NoModifier,spellLabel->text());
                QApplication::postEvent(atUi,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,0,Qt::NoModifier,spellLabel->text());
                QApplication::postEvent(atUi,ke);
                clearWordArea();
                spellLabel->clear();
            }
        }
    }
    else if(line==3 && index==11) //EN/ZH
    {
        if(page==0)
        {
            if(langFlags[1]) {
                keyboardStack->setCurrentIndex(1);
            }
        }
        else if(page==1)
        {
            keyboardStack->setCurrentIndex(0);
        }
        updateKeyboard(keyboardStack->currentIndex(),keyboardStatus);
    }
    else if(line==3 && index==12) //ok
    {
        moveEnabled=true;
        lastMousePos=QCursor::pos();
        qDebug() << "start move" << lastMousePos;
//        if(atUi)
//        {
//            atUi=nullptr;
//        }
//        close();
//        clearWordArea();
//        spellLabel->clear();
    }
    else if(line==0 && index==13) //<-
    {
        QKeyEvent *ke=nullptr;
        if(page==0) {
            ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(atUi,ke);
            ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
            QApplication::postEvent(atUi,ke);
        }
        else if(page==1) {
            if(spellLabel->text().isEmpty()) {
                ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(atUi,ke);
                ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
                QApplication::postEvent(atUi,ke);
            }
            else {
                s=spellLabel->text();
                s.remove(s.size()-1,1);
                spellLabel->setText(s);
                ss=pin(s);
                updateWordArea(ss);
            }
        }
    }
    else if(line==3 && index==0) //exit
    {
        atUi=nullptr;
        close();
        clearWordArea();
        spellLabel->clear();
    }
}

void FullKeyboard::onKeyReleased(int page,int line,int index)
{
    Q_UNUSED(page);
    if(line==3 && index==12) //ok
    {
        moveEnabled=false;
    }
}

void FullKeyboard::attach(QWidget *w)
{
    atUi=w;
//    QValidator *v=nullptr;
//    const QDoubleValidator *cdv=nullptr;
//    const QIntValidator *civ=nullptr;
//    const QRegExpValidator *crv=nullptr;
    if(atUi==nullptr)
    {
        return;
    }
    if(QString(atUi->metaObject()->className())=="QLineEdit")
    {
        setFixedHeight(250);
    }
    else if(QString(atUi->metaObject()->className())=="QPlainTextEdit")
    {
        setFixedHeight(250);
    }
}

void FullKeyboard::initKeyboardPages()
{
    QList<QList<QList<KeyButtonInfo> > > keyboardPages = {
        //page 0
        {
            //line 0
            {
                {          "`",      "`",          "~",      "~"},
                {          "1",      "1",          "!",      "!"},
                {          "2",      "2",          "@",      "@"},
                {          "3",      "3",          "#",      "#"},
                {          "4",      "4",          "$",      "$"},
                {          "5",      "5",          "%",      "%"},
                {          "6",      "6",          "^",      "^"},
                {          "7",      "7",          "&",      "&"},
                {          "8",      "8",          "*",      "*"},
                {          "9",      "9",          "(",      "("},
                {          "0",      "0",          ")",      ")"},
                {          "-",      "-",          "_",      "_"},
                {          "=",      "=",          "+",      "+"},
                {         "<-",       "",         "<-",       ""},
            },
            //line 1
            {
                {        "Tab",     "\t",        "Tab",     "\t"},
                {          "q",      "q",          "Q",      "Q"},
                {          "w",      "w",          "W",      "W"},
                {          "e",      "e",          "E",      "E"},
                {          "r",      "r",          "R",      "R"},
                {          "t",      "t",          "T",      "T"},
                {          "y",      "y",          "Y",      "Y"},
                {          "u",      "u",          "U",      "U"},
                {          "i",      "i",          "I",      "I"},
                {          "o",      "o",          "O",      "O"},
                {          "p",      "p",          "P",      "P"},
                {          "[",      "[",          "{",      "{"},
                {          "]",      "]",          "}",      "}"},
                {         "\\",     "\\",          "|",      "|"},
                {        "[ ]",      " ",        "[ ]",      " "},
            },
            //line 2
            {
                {      "Shift",       "",      "Shift",       ""},
                {          "a",      "a",          "A",      "A"},
                {          "s",      "s",          "S",      "S"},
                {          "d",      "d",          "D",      "D"},
                {          "f",      "f",          "F",      "F"},
                {          "g",      "g",          "G",      "G"},
                {          "h",      "h",          "H",      "H"},
                {          "j",      "j",          "J",      "J"},
                {          "k",      "k",          "K",      "K"},
                {          "l",      "l",          "L",      "L"},
                {          ";",      ";",          ":",      ":"},
                {         "\'",     "\'",         "\"",     "\""},
                {      "Enter",       "",      "Enter",       ""},
            },
            //line 3
            {
                {        "Esc",       "",        "Esc",       ""},
                {          "z",      "z",          "Z",      "Z"},
                {          "x",      "x",          "X",      "X"},
                {          "c",      "c",          "C",      "C"},
                {          "v",      "v",          "V",      "V"},
                {          "b",      "b",          "B",      "B"},
                {          "n",      "n",          "N",      "N"},
                {          "m",      "m",          "M",      "M"},
                {          ",",      ",",          "<",      "<"},
                {          ".",      ".",          ">",      ">"},
                {          "/",      "/",          "?",      "?"},
                {      "en_US",       "",      "en_US",       ""},
                {           "",       "",           "",       ""},
            },
        },
        //page 1
        {
            //line 0
            {
                {          "`",      "`",          "~",      "~"},
                {          "1",      "1",          "!",      "!"},
                {          "2",      "2",          "@",      "@"},
                {          "3",      "3",          "#",      "#"},
                {          "4",      "4",          "$",      "$"},
                {          "5",      "5",          "%",      "%"},
                {          "6",      "6",          "^",      "^"},
                {          "7",      "7",          "&",      "&"},
                {          "8",      "8",          "*",      "*"},
                {          "9",      "9",          "(",      "("},
                {          "0",      "0",          ")",      ")"},
                {          "-",      "-",          "_",      "_"},
                {          "=",      "=",          "+",      "+"},
                {         "<-",       "",         "<-",       ""},
            },
            //line 1
            {
                {        "Tab",     "\t",        "Tab",     "\t"},
                {          "q",      "q",          "Q",      "Q"},
                {          "w",      "w",          "W",      "W"},
                {          "e",      "e",          "E",      "E"},
                {          "r",      "r",          "R",      "R"},
                {          "t",      "t",          "T",      "T"},
                {          "y",      "y",          "Y",      "Y"},
                {          "u",      "u",          "U",      "U"},
                {          "i",      "i",          "I",      "I"},
                {          "o",      "o",          "O",      "O"},
                {          "p",      "p",          "P",      "P"},
                {          "[",      "[",          "{",      "{"},
                {          "]",      "]",          "}",      "}"},
                {         "\\",     "\\",          "|",      "|"},
                {        "[ ]",      " ",        "[ ]",      " "},
            },
            //line 2
            {
                {      "Shift",       "",      "Shift",       ""},
                {          "a",      "a",          "A",      "A"},
                {          "s",      "s",          "S",      "S"},
                {          "d",      "d",          "D",      "D"},
                {          "f",      "f",          "F",      "F"},
                {          "g",      "g",          "G",      "G"},
                {          "h",      "h",          "H",      "H"},
                {          "j",      "j",          "J",      "J"},
                {          "k",      "k",          "K",      "K"},
                {          "l",      "l",          "L",      "L"},
                {          ";",      ";",          ":",      ":"},
                {         "\'",     "\'",         "\"",     "\""},
                {      "Enter",       "",      "Enter",       ""},
            },
            //line 3
            {
                {        "Esc",       "",        "Esc",       ""},
                {          "z",      "z",          "Z",      "Z"},
                {          "x",      "x",          "X",      "X"},
                {          "c",      "c",          "C",      "C"},
                {          "v",      "v",          "V",      "V"},
                {          "b",      "b",          "B",      "B"},
                {          "n",      "n",          "N",      "N"},
                {          "m",      "m",          "M",      "M"},
                {          ",",      ",",          "<",      "<"},
                {          ".",      ".",          ">",      ">"},
                {          "/",      "/",          "?",      "?"},
                {      "zh_CN",       "",      "zh_CN",       ""},
                {           "",       "",           "",       ""},
            },
        },
    };
    this->keyboardPages=keyboardPages;
}

void FullKeyboard::setWordBarVisible(bool f)
{
    spellLabel->setVisible(f);
    leftWordAreaBtn->setVisible(f);
    wordArea->setVisible(f);
    rightWordAreaBtn->setVisible(f);
}

QStringList FullKeyboard::pin(QString pinyin)
{
    QList<int> ids;
    QStringList ss;
    QString s;
    if(pinyin.isEmpty()) {
        return ss;
    }
//    for(int i=0;i<15;i++) {
//        s=pinyin+QString::number(i);
//        ss.append(s);
//    }
    if(!chineseDb.isOpen()) {
        chineseDb=QSqlDatabase::addDatabase("QSQLITE","fullkeyboard");
        chineseDb.setDatabaseName(QApplication::applicationDirPath()+"/han_character_frequency.db");
        if(!chineseDb.open()) {
            return ss;
        }
    }
    QSqlQuery query(chineseDb);
    query.exec(QString("select serial_number, karacter from character_frequency where pinyin=\'%1\';").arg(pinyin));
    while(query.next()) {
        if(!ids.contains(query.value(0).toInt())) {
            ids.append(query.value(0).toInt());
            ss.append(query.value(1).toString());
        }
    }
    return ss;
}

void FullKeyboard::clearWordArea()
{
    for(int i=0;i<wordBtns.size();i++) {
        disconnect(wordBtns[i]);
        wordContentLayout->removeWidget(wordBtns[i]);
        wordBtns[i]->deleteLater();
    }
    wordBtns.clear();
}

void FullKeyboard::updateWordArea(QStringList words)
{
    QPushButton *btn=nullptr;
    clearWordArea();
    for(int i=0;i<words.size();i++) {
        btn=new QPushButton(words[i],this);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(btn,&QPushButton::pressed,this,[this,btn](){
            QString s1,s2;
            QKeyEvent *ke=nullptr;
            ke=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier, btn->text());
            QApplication::sendEvent(atUi,ke);
            delete ke;
            ke=new QKeyEvent(QEvent::KeyRelease, 0, Qt::NoModifier, btn->text());
            QApplication::sendEvent(atUi,ke);
            delete ke;
            clearWordArea();
            spellLabel->clear();
        });
        wordContentLayout->addWidget(btn, 0, i);
        wordBtns.append(btn);
    }
}

void FullKeyboard::setLanguageEnabled(int page,bool f)
{
    if(f) {
        langFlags[page]=1;
    }
    else {
        langFlags[page]=0;
    }
}

void FullKeyboard::showEvent(QShowEvent *event)
{
    int sx,sy;
    QRect rc;
    int h;
    Q_UNUSED(event);
    if(atUi) {
        if(atUi->metaObject()->className()==QString("QLineEdit")) {
            h=style()->pixelMetric(QStyle::PM_TitleBarHeight);
            rc=atUi->geometry();
            sx=atUi->mapToGlobal(QPoint(0,0)).x();
            sy=atUi->mapToGlobal(QPoint(0,0)).y()+atUi->height()+h;
            QDesktopWidget* desktopWidget = QApplication::desktop();
            rc=desktopWidget->availableGeometry();
            sx=sx<0?0:sx;
            sy=sy<0?0:sy;
            sx-=sx+width()-rc.width()>0?sx+width()-rc.width():0;
            sy-=sy+height()-rc.height()>0?sy+height()-rc.height():0;
            setGeometry(sx,sy,width(),height());
//            setGeometry(0,0,width(),height());
        }
        else if(atUi->metaObject()->className()==QString("QPlainTextEdit") || atUi->metaObject()->className()==QString("QTextEdit")) {
            h=style()->pixelMetric(QStyle::PM_TitleBarHeight);
            rc=atUi->geometry();
            sx=atUi->mapToGlobal(QPoint(0,0)).x();
            sy=atUi->mapToGlobal(QPoint(0,0)).y()+atUi->height()/2+h;
            QDesktopWidget* desktopWidget = QApplication::desktop();
            rc=desktopWidget->availableGeometry();
            sx=sx<0?0:sx;
            sy=sy<0?0:sy;
            sx-=sx+width()-rc.width()>0?sx+width()-rc.width():0;
            sy-=sy+height()-rc.height()>0?sy+height()-rc.height():0;
            setGeometry(sx,sy,width(),height());
        }
    }
    else {
        if(parentWidget()) {
            rc=parentWidget()->geometry();
        }
        else {
            QDesktopWidget* desktopWidget = QApplication::desktop();
            rc=desktopWidget->availableGeometry();
        }
        sx=rc.center().x()-size().width()/2;
        sy=rc.center().y()-size().height()/2;
        setGeometry(sx,sy,width(),height());
    }
}
