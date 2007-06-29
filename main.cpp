#include <QApplication>
#include <QString>
#include <QDebug>
#include "imageviewer.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	if (argc == 1) {
		qDebug() << "usage: imageviewer image";
		return 1;
	}

	ImageViewer *i = new ImageViewer(QString(argv[1]));

	int ret = app.exec();

	delete i;

	return ret;
}
