#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class PaintingPlace;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    PaintingPlace *paintingPlace;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void background();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *drawMenu;

    QAction *openAct;

    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
    QAction *backgroundAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *undoAct;
    QAction *redoAct;

};

#endif
