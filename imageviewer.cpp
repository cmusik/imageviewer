#include <QDebug>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDirIterator>

#include "imageviewer.h"
enum {
	Next = 1,
	Previous = -1
};

ImageViewer::ImageViewer(QString file, QWidget *parent) : QWidget(parent) {
	setupUi(this);

    QFileInfo info = QFileInfo(file);
    QString dir;

    if (info.isFile())
        dir = info.absolutePath();
    else
        dir = file;

    QDirIterator it(dir, QStringList() << "*.JPG" << "*.jpg" << "*.png" << "*.gif" << "*.bmp", QDir::NoFilter, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        m_list.append(it.next());
    }
    m_list.sort();

    if (info.isFile())
        m_current_image = m_list.at(m_list.indexOf(QRegExp("^"+info.absoluteFilePath()+"$")));
    else
        m_current_image = m_list.at(0);

	if (m_list.count() > 0) {
		setWindowState(Qt::WindowFullScreen);
		setWindowFlags(Qt::SplashScreen);
		setAttribute(Qt::WA_QuitOnClose);

		m_scene = new QGraphicsScene(this);
		graphicsView->setScene(m_scene);

		showMaximized();
        activateWindow();
		layout()->update();
		graphicsView->update();
		openImage();
	}
}

void ImageViewer::openImage() {
	setCursor(Qt::WaitCursor);
	QImage img = QImage(m_current_image);

	if ((float) width()/height() < (float) img.width()/img.height()) {
		img = img.scaledToWidth(width(), Qt::SmoothTransformation);
	} else {
		img = img.scaledToHeight(height(), Qt::SmoothTransformation);
	}

	foreach (QGraphicsItem *i, m_scene->items()) {
		m_scene->removeItem(i);
		delete i;
	}

	QGraphicsPixmapItem *item = m_scene->addPixmap(QPixmap::fromImage(img));

	if (img.width() == width())
		item->setPos(0, (height()-img.height())/2);
	else
		item->setPos((width()-img.width())/2, 0);

	setCursor(Qt::ArrowCursor);
}

void ImageViewer::find(int delta) {
	int next;
	if (m_current_image.isEmpty()) {
		next = 0;
	}
	else {
		next = m_list.indexOf(QRegExp("^"+m_current_image+"$")) + delta;
	}
	if (next > m_list.count()-1)
		next = 0;

	if (next < 0)
		next = m_list.count()-1;

	m_current_image = m_list.at(next);
	openImage();
}

void ImageViewer::wheelEvent(QWheelEvent *e) {
	if (e->delta() > 0) {
		find(Previous);
	}
	else {
		find(Next);
	}
}

void ImageViewer::keyPressEvent(QKeyEvent *e) {
	switch(e->key()) {
		case Qt::Key_Space:
			find(Next);
			break;

		case Qt::Key_Backspace:
			find(Previous);
			break;

		case Qt::Key_Q:
		case Qt::Key_Escape:
			close();
			break;

		default:
			e->ignore();
	}
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *e) {
	switch (e->button()) {
		case Qt::LeftButton:
			find(Next);
			break;
		case Qt::RightButton:
			close();
			break;
		default:
			e->ignore();
	}
}

bool ImageViewer::haveImages() {
	return m_list.count() > 0;
}
