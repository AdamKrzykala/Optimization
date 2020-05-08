#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QList>
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>

class LibraryWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LibraryWindow(QWidget *parent = nullptr);

private:
    QListWidget *f1List;
    QListWidget *f2List;
    QLabel *pix1;
    QLabel *pix2;

    QStringList listPic;

    void addFunctions(QListWidget*);
    void fillPicList();

signals:
    void ok_clicked(QString, QString);

public slots:
    void sendFunctionToMain();

private slots:
    void on_ItemF1Selected(int);
    void on_ItemF2Selected(int);
};

#endif // LIBRARYWINDOW_H
