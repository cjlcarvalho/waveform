#ifndef WAVEFORM_H
#define WAVEFORM_H

#include "audio.h"

#include <QWidget>

class Waveform : public QWidget
{
    Q_OBJECT

public:
    Waveform(const QString& file);
    ~Waveform();

    void paintEvent(QPaintEvent* event);

private:
    Audio m_audio;
};

#endif // WAVEFORM_H
