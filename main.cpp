#include <QApplication>
#include <QString>
#include <iostream>
#include <iomanip>
#include "imageviewer.h"


void usage(QString name) {
    using namespace std;
    int w = 25;
    cout << "Usage: " << name.toStdString() << " [ -r ] file" << endl;
    cout << left;
    cout << endl;
    cout << setw(w) << " -r, --recursive" << "Search subdirectories for images" << endl;
    cout << setw(w) << " -h, --help" << "This message" << endl;
    cout << endl;
    exit(0);
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (argc == 1) {
        usage(args.first());
    }

    bool recursive = false;

    foreach (QString a, args) {
        if (a == "-r" || a == "--recursive")
            recursive = true;
        if (a == "-h" || a == "--help")
            usage(args.first());
    }

    ImageViewer *i = new ImageViewer(args.last(), recursive);

    if (i->haveImages()) {
        int ret = app.exec();

        delete i;

        return ret;
    }
}
