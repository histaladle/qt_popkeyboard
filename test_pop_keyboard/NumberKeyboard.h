#ifndef NUMBERKEYBOARD_H
#define NUMBERKEYBOARD_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QStyle>
class NumberKeyboard : public QFrame
{
    Q_OBJECT
public:
    explicit NumberKeyboard(QWidget *parent = nullptr,
                            Qt::WindowFlags f=Qt::Dialog);

    void attach(QWidget *w);
private:
    QWidget *atUi=nullptr;
//    QLineEdit *inputEdit=nullptr;
    void initKeyboard();
    QList<QWidget*> targets;
    QPoint lastMousePos;
    bool moveEnabled=false;
protected:
    bool eventFilter(QObject *watched,QEvent *event);
    void showEvent(QShowEvent *event);
signals:

private slots:
    void onOkReleased();
};

#endif // NUMBERKEYBOARD_H
