#ifndef PAINTINGPLACE_H
#define PAINTINGPLACE_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>

template <class Type>
struct Node
{
    Type item_;
    Node* next_;
};



template <class Type>
class iterator
{
private:
    Node<Type>* ptr_;

public:
    iterator(): ptr_(0) {}
    iterator( Node<Type>* n ): ptr_(n) {}

    /* operator wyluskania wartosci, na ktora wskazuje iterator */
    Type operator* () { return ptr_->item_; }

    /* preinkrementacja - ++iter */
    /* odwiedza nastepny element w kontenerze */
    iterator& operator++()
    {
        ptr_ = ptr_->next_;

        return *this;
    }

    /* postinkrementacja - iter++ */
    iterator& operator++(int)
    {
        iterator tmp = *this;
        ptr_ = ptr_->next_;

        return tmp;
    }

    /* operator porownania == */
    /* zwraca true jesli iteratory wskazuja na ten sam element */
    bool operator== ( const iterator& i )
    {
        if ( ptr_ == i.ptr_ )
            return true;

        return false;
    }

    /* operator nierownosci != */
    bool operator!= ( const iterator& i )
    {
        return !( *this == i );
    }

    /* operator przypisania = */
    iterator& operator= ( const iterator& i )
    {
        ptr_ = i.ptr_;

        return *this;
    }
    iterator begin(){
        return ptr_[0];
    }
    iterator end(){
        return iterator();
    }
};



class PaintingPlace : public QWidget
{
    Q_OBJECT

public:
    PaintingPlace(QWidget *parent = nullptr);
    
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool openImage(const QString &fileName);
    
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setBackgroundColor(const QColor &newcolor);

    bool isModified() const {return modified;}
    int penWidth() const {return myPenWidth;}
    QColor penColor() const {return myPenColor;}
    QColor backgroundColor() const {return myBackgroundColor;}
    QImage restore() const;
    QImage image;
    QColor myBackgroundColor;
    QColor myPenColor;
    int myPenWidth;

    iterator<QImage>* it;



public slots:
    void clearImage();
    void print();
    void setImage(const QColor &newcolor);
    void redo();
    void undo();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void snap();
    bool modified;
    bool scribbling;
    bool takeSnap;
    bool ifhistory=true;
    int history_pos;

    QPoint lastPoint;
    QPoint mousePos;

    static const int historySize = 3;
    QImage history[historySize];

};


#endif
