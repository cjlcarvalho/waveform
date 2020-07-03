#ifndef AUDIO_H
#define AUDIO_H

#include <QAudioDecoder>
#include <QString>

class Audio : public QObject
{
    Q_OBJECT

public:
    Audio(const QString& file);
    ~Audio();

    QVector<double> samples() const { return m_samples; }

    int channelCount() const { return m_channelCount; }

    double maxPeak() const { return m_maxPeak; }

    void clear() { m_samples.clear(); }

    bool isFinished() const { return m_isFinished; }

signals:

    void dataFinished();

private slots:
    
    void bufferReady();
    void finished();

private:

    qreal peakValue(const QAudioFormat& format) const;

private:
    QString m_file;
    QAudioDecoder m_decoder;
    QAudioBuffer m_buffer;
    QVector<double> m_samples;
    int m_channelCount;
    double m_maxPeak;
    bool m_isFinished;
};

#endif // AUDIO_H
