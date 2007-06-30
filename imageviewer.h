#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QString>
#include <QDir>
#include <QWheelEvent>
#include "ui_imageviewer.h"

class ImageViewer : public QWidget, private Ui::ImageViewer {
	Q_OBJECT

	public:
		ImageViewer(QString, QWidget* = 0);

	private:
		void find(int);
		void openImage();
		void wheelEvent(QWheelEvent*);
		void keyPressEvent(QKeyEvent*);
		void mouseReleaseEvent(QMouseEvent*);

		QDir *m_dir;
		QStringList m_list;
		QString m_current_image;
};

#endif
