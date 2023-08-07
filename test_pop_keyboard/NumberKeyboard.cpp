#include "NumberKeyboard.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>
NumberKeyboard::NumberKeyboard(QWidget *parent, Qt::WindowFlags f)
    : QFrame(parent, f)
{
    initKeyboard();
    setWindowModality(Qt::NonModal);
    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::Box);
    setLineWidth(2);
    QFont font;
    font=this->font();
    font.setPointSize(12);
    this->setFont(font);
}

void NumberKeyboard::initKeyboard()
{
    setFixedWidth(500);
    setFixedHeight(400);
    QPushButton *btn=nullptr;

    QGridLayout *glayout=new QGridLayout(this);
    glayout->setMargin(5);
    glayout->setSpacing(3);

//    inputEdit=new QLineEdit(this);
//    inputEdit->setFocusPolicy(Qt::StrongFocus);
//    inputEdit->setFocus();
//    inputEdit->setReadOnly(true);
//    glayout->addWidget(inputEdit,0,0,1,4);

    //1
    btn=new QPushButton(this);
    btn->setText("1");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(100,100,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_1,Qt::NoModifier,"1");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_1,Qt::NoModifier,"1");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,1,0);

    //2
    btn=new QPushButton(this);
    btn->setText("2");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_2,Qt::NoModifier,"2");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_2,Qt::NoModifier,"2");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,1,1);

    //3
    btn=new QPushButton(this);
    btn->setText("3");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_3,Qt::NoModifier,"3");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_3,Qt::NoModifier,"3");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,1,2);

    //4
    btn=new QPushButton(this);
    btn->setText("4");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_4,Qt::NoModifier,"4");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_4,Qt::NoModifier,"4");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,2,0);

    //5
    btn=new QPushButton(this);
    btn->setText("5");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_5,Qt::NoModifier,"5");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_5,Qt::NoModifier,"5");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,2,1);

    //6
    btn=new QPushButton(this);
    btn->setText("6");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_6,Qt::NoModifier,"6");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_6,Qt::NoModifier,"6");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,2,2);

    //7
    btn=new QPushButton(this);
    btn->setText("7");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_7,Qt::NoModifier,"7");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_7,Qt::NoModifier,"7");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,3,0);

    //8
    btn=new QPushButton(this);
    btn->setText("8");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_8,Qt::NoModifier,"8");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_8,Qt::NoModifier,"8");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,3,1);

    //9
    btn=new QPushButton(this);
    btn->setText("9");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_9,Qt::NoModifier,"9");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_9,Qt::NoModifier,"9");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,3,2);

    //cancel
    btn=new QPushButton(this);
    btn->setText(tr("cancel"));
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        this->hide();
    });
    glayout->addWidget(btn,4,0);

    //0
    btn=new QPushButton(this);
    btn->setText("0");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_0,Qt::NoModifier,"0");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_0,Qt::NoModifier,"0");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,4,1);

    //.
    btn=new QPushButton(this);
    btn->setText(".");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Period,Qt::NoModifier,".");
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Period,Qt::NoModifier,".");
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,4,2);

    //<-
    btn=new QPushButton(this);
    btn->setText("<-");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(btn,&QPushButton::pressed,
            this,[=](){
        QKeyEvent *ke=nullptr;
        ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
        QCoreApplication::postEvent(atUi,ke);
        ke=new QKeyEvent(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier);
        QCoreApplication::postEvent(atUi,ke);
    });
    glayout->addWidget(btn,1,3);

    //OK
    btn=new QPushButton(this);
    btn->setText("");
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setContentsMargins(0,0,0,0);
    btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    connect(btn,SIGNAL(released()),this,SLOT(onOkReleased()));
    connect(btn,&QPushButton::pressed,this,[this](){
        moveEnabled=true;
        lastMousePos=QCursor::pos();
    });
    connect(btn,&QPushButton::released,this,[this](){
        moveEnabled=false;
    });
    glayout->addWidget(btn,4,3);
    btn->installEventFilter(this);
}

bool NumberKeyboard::eventFilter(QObject *watched, QEvent *event)
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

void NumberKeyboard::attach(QWidget *w)
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
    {}
    else {
        atUi=nullptr;
    }
}

void NumberKeyboard::onOkReleased()
{
    QString s;
    close();
    if(!atUi) return;
    if(atUi->metaObject()->className()==QString("QLineEdit"))
    {
        atUi=nullptr;
    }
}

void NumberKeyboard::showEvent(QShowEvent *event)
{
    int sx,sy;
    QRect rc;
    int h;
    Q_UNUSED(event);
    if(atUi) {
        if(atUi->metaObject()->className()==QString("QLineEdit")) {
            h=style()->pixelMetric(QStyle::PM_TitleBarHeight);
            rc=atUi->geometry();
            sx=rc.x();
            sy=rc.y()+atUi->height()+h;
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
