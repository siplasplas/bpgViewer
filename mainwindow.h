#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "qbetterportablegraphics.h"
#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printer)
#    include <QPrinter>
#  endif
#endif

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool loadFile(const QString &);
    void open();
    void saveAs();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void createActions();
    void updateActions();

    ~MainWindow();

private:
    QBetterPortableGraphics *bpgFile;

private:
    void createMenus();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printer;
#endif

    QAction *saveAsAct;
    QAction *printAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

//public slots:
    void ShowImage(QString imgFile);
    //void LoadImage(QString path);
};
#endif // MAINWINDOW_H
