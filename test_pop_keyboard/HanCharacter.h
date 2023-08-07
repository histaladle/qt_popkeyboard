#ifndef HANCHARACTER_H
#define HANCHARACTER_H

#include <QString>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>
class HanCharacter
{
public:
    HanCharacter();
    void initDb();
    QSqlDatabase db;
};

#endif // HANCHARACTER_H
