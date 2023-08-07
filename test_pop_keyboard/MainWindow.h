#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FullKeyboard.h"
#include "HanCharacter.h"
#include "NumberKeyboard.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FullKeyboard *fullKeyboard;
    NumberKeyboard *numKeyboard;
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
