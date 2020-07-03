#include "waveform.h"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

Waveform::Waveform(const QString& file) :
    QWidget(),
    m_audio(file)
{
    connect(&m_audio, &Audio::dataFinished, this, qOverload<>(&Waveform::update));
}

Waveform::~Waveform()
{
}

//void Waveform::update()
//{
//    if (dynamic_cast<Audio*>(sender()) != nullptr){
//        
//   }
//    QWidget::update();
//}

void Waveform::paintEvent(QPaintEvent* event)
{
    qDebug() << "paint";

    if (m_audio.isFinished()) {
        int totalFrames = m_audio.samples().size();

        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));

        int minX = event->region().boundingRect().x();
        int maxX = event->region().boundingRect().x() + event->region().boundingRect().width();

        if (m_audio.channelCount() == 2) {
            int startIndex = 2 * minX;
            int endIndex = 2 * maxX;

            int midPt = height() / 2;
            int counter = minX;

            for (int i = startIndex; i < endIndex; i += 2) {
                qDebug() << i << " " << endIndex;
                int c1Mid = midPt - height() / 4;
                int c2Mid = midPt + height() / 4;

                painter.drawLine(counter, c1Mid, counter, c1Mid + (height() / 4) * m_audio.samples()[i]); // ver scale factor
                painter.drawLine(counter, c1Mid, counter, c1Mid - (height() / 4) * m_audio.samples()[i]); // ver scale factor

                painter.drawLine(counter, c2Mid, counter, c2Mid + (height() / 4) * m_audio.samples()[i + 1]);
                painter.drawLine(counter, c2Mid, counter, c2Mid - (height() / 4) * m_audio.samples()[i + 1]);

                counter++;
            }
        }

        // TODO: 1 channel
        qDebug() << totalFrames;
    }

    qDebug() << "finished";
}
