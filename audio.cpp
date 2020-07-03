#include "audio.h"

#include <QDebug>

#include <QAudioBuffer>

Audio::Audio(const QString& file) :
    m_file(file),
    m_isFinished(false)
{
    m_decoder.setSourceFilename(m_file);
    m_decoder.start();

    connect(&m_decoder, &QAudioDecoder::bufferReady, this, &Audio::bufferReady);
    connect(&m_decoder, &QAudioDecoder::finished, this, &Audio::finished);
}

Audio::~Audio()
{
}

void Audio::bufferReady()
{
    QAudioBuffer buffer = m_decoder.read();
    
    qreal peak = peakValue(buffer.format());

    const qint16* data = buffer.constData<qint16>();
    int count = buffer.sampleCount() / 2;

    for (int i = 0; i < count; i++)
        m_samples << data[i] / peak;

    m_buffer = buffer;
}

void Audio::finished()
{
    emit dataFinished();

    m_channelCount = m_buffer.format().channelCount();

    m_isFinished = true;
}

qreal Audio::peakValue(const QAudioFormat& format) const
{
    qreal peak = 0;

    if (format.isValid()) {
        switch (format.sampleType()) {
            case QAudioFormat::Unknown:
                break;
            case QAudioFormat::Float: {
                peak = (format.sampleSize() != 32) ? 0 : 1.00003;
                break;
            }
            case QAudioFormat::SignedInt: {
                if (format.sampleSize() == 32) {
                    #ifdef Q_OS_WIN
                    peak = INT_MAX;
                    #endif
                    #ifdef Q_OS_UNIX
                    peak = SHRT_MAX;
                    #endif
                }
                else if (format.sampleSize() == 16)
                    peak = SHRT_MAX;
                else if (format.sampleSize() == 8)
                    peak = CHAR_MAX;
                break;
            }
            case QAudioFormat::UnSignedInt: {
                if (format.sampleSize() == 32)
                    peak = UINT_MAX;
                else if (format.sampleSize() == 16)
                    peak = USHRT_MAX;
                else if (format.sampleSize() == 8)
                    peak = UCHAR_MAX;
            }
            default:
                break;
        }
    }

    return peak;
}
