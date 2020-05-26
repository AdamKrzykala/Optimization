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
    QLabel *pix1;

    QStringList listPic;

    void addFunctions(QListWidget*);
    void fillPicList();

signals:
    void ok_clicked(QString,
                    QString,
                    int,
                    QVector<double>,
                    QVector<double>);

public slots:
    void sendFunctionToMain();

private slots:
    void on_ItemF1Selected(int);
};

#endif // LIBRARYWINDOW_H
