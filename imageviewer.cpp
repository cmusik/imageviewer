#include <QDebug>
#include <QPixmap>

#include "imageviewer.h"
enum {
	NEXT = 1,
	PREV = -1
};

ImageViewer::ImageViewer(QString file, QWidget *parent) : QWidget(parent) {
	setupUi(this);

	QFileInfo info = QFileInfo(file);
	m_current_image = info.fileName();

	m_dir = new QDir(info.absolutePath());
	m_list = m_dir->entryList(QStringList() << "*.jpg" << "*.png");

	setWindowState(Qt::WindowFullScreen);
	setWindowFlags(Qt::Popup);
	setAttribute(Qt::WA_QuitOnClose);

	show();
	openImage();
}

void ImageViewer::openImage() {
	lbl_image->setCursor(Qt::WaitCursor);
	QImage img = QImage(m_dir->path()+"/"+m_current_image);

	if ((float) width()/height() < (float) img.width()/img.height()) {
		img = img.scaledToWidth(width(), Qt::SmoothTransformation);
	} else {
		img = img.scaledToHeight(height(), Qt::SmoothTransformation);
	}

	lbl_image->setPixmap(QPixmap::fromImage(img));
	lbl_image->setCursor(Qt::ArrowCursor);
}

void ImageViewer::find(int delta) {
	int next = m_list.indexOf(QRegExp("^"+m_current_image+"$")) + delta;
	if (next > m_list.count()-1)
		next = 0;

	if (next < 0)
		next = m_list.count()-1;

	m_current_image = m_list.at(next);
	openImage();
}

void ImageViewer::wheelEvent(QWheelEvent *e) {
	if (e->delta() > 0) {
		find(PREV);
	}
	else {
		find(NEXT);
	}
}

void ImageViewer::keyPressEvent(QKeyEvent *e) {
	switch(e->key()) {
		case Qt::Key_Space:
			find(NEXT);
			break;

		case Qt::Key_Backspace:
			find(PREV);
			break;

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
			find(NEXT);
			break;
		case Qt::RightButton:
			close();
			break;
		default:
			e->ignore();
	}
}
