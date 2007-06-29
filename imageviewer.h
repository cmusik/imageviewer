#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QPalette>
#include "ui_imageviewer.h"

class ImageViewer : public QWidget, private Ui::ImageViewer {
	Q_OBJECT

	public:
		ImageViewer(QString, QWidget* = 0);
};

#endif
