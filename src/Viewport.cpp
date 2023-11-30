#include "Viewport.h"
#include <QPainter>
#include <QtWidgets/QApplication>

Viewport::Viewport(QWidget* parent)
	:QWidget(parent)
{
}

void Viewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen);

    for (const auto& line : mLineVector)
    {
        painter.drawLine(line.first, line.second);
    }
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    // Create a new line
    QPoint startPoint = QWidget::mapFromGlobal(QCursor::pos());
    mLineVector.push_back({ startPoint, startPoint });

    update(); 
    
    // Call for Keyboard Events
    setFocus();
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    // Save drawing objects
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{

    QPoint mEndPoint = QWidget::mapFromGlobal(QCursor::pos());

    if (mLineVector.size())
    {
        mLineVector.back().second = mEndPoint;
    }

    update();
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "hi";

}
