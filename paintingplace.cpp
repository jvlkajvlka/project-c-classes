#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "paintingplace.h"

PaintingPlace::PaintingPlace(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    modified = false;
    scribbling = false;
    takeSnap = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
}

bool PaintingPlace::openImage(const QString &fileName)
{
    QImage loadedImage;

    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool PaintingPlace::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void PaintingPlace::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void PaintingPlace::setPenWidth(int newWidth)
{
    myPenWidth = newWidth; 
}

void PaintingPlace::setBackgroundColor(const QColor &newcolor)
{
    setImage(newcolor);
}

void PaintingPlace::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void PaintingPlace::setImage(const QColor &newcolor)
{
    image.fill(newcolor);
    modified = true;
    update();
}

void PaintingPlace::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void PaintingPlace::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void PaintingPlace::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());

        scribbling = false;
    }
    takeSnap = true;
}

void PaintingPlace::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();

    painter.drawImage(dirtyRect, image, dirtyRect);

    if(takeSnap)
        snap();
    {
        for(auto it: history)
            (*it) = (&image);
        }
        ifhistory=false;
    }


void PaintingPlace::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void PaintingPlace::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawLine(lastPoint, endPoint);

    modified = true;

    int rad = (myPenWidth / 2) + 2;

    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void PaintingPlace::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintingPlace::redo()
{
    image = history[2];
    history[1] = history[2];
    modified = true;
    update();
}

void PaintingPlace::undo()
{
    image = history[0];
    history[2]=history[1];
    history[1]=history[0];

    modified = true;
    update();
}

void PaintingPlace::snap()
{
    takeSnap = false;
    history[0] = history[1];
    history[1]= image;
}


