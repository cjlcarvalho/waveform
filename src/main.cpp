#include <QApplication>

#include "waveform.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Waveform waveform("/home/caio/Downloads/foo.wav");
    waveform.show();
    return a.exec();
}
