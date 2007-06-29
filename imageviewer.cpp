#include <QDebug>

#include "imageviewer.h"

ImageViewer::ImageViewer(QString file, QWidget *parent) : QWidget(parent) {
	setupUi(this);

	setWindowState(Qt::WindowFullScreen);
	setWindowFlags(Qt::Popup);
	setAttribute(Qt::WA_QuitOnClose);

	QImage img = QImage(file);

	//img = img.scaledToWidth(width(), Qt::SmoothTransformation);


	if (img.width()/width() < 0) {
		img = img.scaledToWidth(width(), Qt::SmoothTransformation);
	}
	else /*if (img.height() > height())*/ {
		img = img.scaledToHeight(height(), Qt::SmoothTransformation);
	}




	lbl_image->setPixmap(QPixmap::fromImage(img));

	show();
}
