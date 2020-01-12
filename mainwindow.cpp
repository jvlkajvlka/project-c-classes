#include <QtWidgets>
#include <QCursor>

#include "mainwindow.h"
#include "paintingplace.h"

MainWindow::MainWindow()
{
    paintingPlace = new PaintingPlace;
    setCentralWidget(paintingPlace);
    createActions();
    createMenus();
    setWindowTitle(tr("PAINTING PLACE"));
    resize(1500, 750);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::open()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open File"), QDir::currentPath());
        if(!fileName.isEmpty()){
            paintingPlace->openImage(fileName);
        }
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(paintingPlace->penColor());
    if(newColor.isValid()){
        paintingPlace->setPenColor(newColor);
    }
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("PaintingPlace"),
                                        tr("Select pen width : "),
                                        paintingPlace->penWidth(),
                                        1, 50, 1, &ok);
    if(ok){
        paintingPlace->setPenWidth(newWidth);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About PaintingPlace"),
                       tr("<p>The <b>PaintingPlace</b> created by Ania and Julia</p>"));
}

void MainWindow::background()
{
    QColor newColor = QColorDialog::getColor(paintingPlace->backgroundColor());
    if(newColor.isValid()){
        paintingPlace->setBackgroundColor(newColor);
    }
}

void MainWindow::createActions(){
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    foreach(QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            paintingPlace, SLOT(clearImage()));

    backgroundAct = new QAction((tr("&Backgroundcolor")),this);
    connect(backgroundAct,SIGNAL(triggered()),this,SLOT(background()));


    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    redoAct = new QAction( tr("&Redo"),this);
    redoAct->setShortcut(tr("Ctrl+R"));
    connect(redoAct, SIGNAL(triggered()),paintingPlace,SLOT(redo()));

    undoAct = new QAction( tr("&Undo"),this);
    undoAct->setShortcut(tr("Ctrl+Z"));
    connect(undoAct, SIGNAL(triggered()),paintingPlace,SLOT(undo()));



}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addAction(backgroundAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);
    optionMenu->addAction(redoAct);
    optionMenu->addAction(undoAct);


    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);





    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave()
{
    if (paintingPlace->isModified()) {
       QMessageBox::StandardButton ret;

        ret = QMessageBox::warning(this, tr("Scribble"),
                           tr("The image has been modified.\n"
                              "Do you want to save your changes?"),
                           QMessageBox::Save | QMessageBox::Discard
                           | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return saveFile("png");

        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
   }
   return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                initialPath,
                                tr("%1 Files (*.%2);;All Files (*)")
                                .arg(QString::fromLatin1(fileFormat.toUpper()))
                                .arg(QString::fromLatin1(fileFormat)));

    if (fileName.isEmpty()) {
        return false;
    } else {
        return paintingPlace->saveImage(fileName, fileFormat.constData());
    }
}


