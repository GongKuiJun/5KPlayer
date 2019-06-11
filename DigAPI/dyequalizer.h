#ifndef DYEQUALIZER_H
#define DYEQUALIZER_H

#include <QObject>


class DYMediaPlayer;

struct libvlc_equalizer_t;

class DYEqualizer : public QObject
{
    Q_OBJECT
public:
    explicit DYEqualizer(DYMediaPlayer *vlcMediaPlayer);
    ~DYEqualizer();


    /*!
        \brief Get the amplification value for a particular equalizer frequency band.
        \param bandIndex index, counting from zero, of the frequency band to get
        \return amplification value (Hz); -1.0 if there is no such frequency band
     */
    float amplificationForBandAt(uint bandIndex) const;

    /*!
        \brief Get the number of distinct frequency bands for an equalizer.
        \return number of frequency bands
     */
    uint bandCount() const;

    /*!
        \brief Get a particular equalizer band frequency.

        This value can be used, for example, to create a label for an equalizer band control in a user interface.

        \param bandIndex index of the band, counting from zero
        \return equalizer band frequency (Hz), or -1 if there is no such band
     */
    float bandFrequency(uint bandIndex) const;

    /*!
        \brief Get the current pre-amplification value from an equalizer.
        \return preamp value (Hz)
     */
    float preamplification() const;

    /*!
        \brief Get the number of equalizer presets.
        \return number of presets
     */
    uint presetCount() const;

    /*!
        \brief Get the name of a particular equalizer preset.

        This name can be used, for example, to prepare a preset label or menu in a user interface.

        \param index index of the preset, counting from zero
        \return preset name, or an empty string if there is no such preset
     */
    QString presetNameAt(int index) const;

public slots:
    /*!
        \brief Load from preset
        \param index index of the preset, counting from zero
     */
    void loadFromPreset(int index);

    /*!
        \brief Set a new amplification value for a particular equalizer frequency band.

        The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
        The supplied amplification value will be clamped to the -20.0 to +20.0 range.

        \param amp amplification value (-20.0 to 20.0 Hz)
        \param bandIndex counting from zero, of the frequency band to set
     */
    void setAmplificationForBandAt(float amp, uint bandIndex);

    /*!
        \brief Enable or disable equalizer
        \param enabled toggle flag
     */
    void setEnabled(bool enabled);

    /*!
        \brief Set a new pre-amplification value for an equalizer.

        The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
        The supplied amplification value will be clamped to the -20.0 to +20.0 range.

        \param value preamp value in (-20.0 to 20.0 Hz)
     */
    void setPreamplification(float value);

signals:
    /*!
        \brief Emitted when preset is loaded
     */
    void presetLoaded();

private:
    DYMediaPlayer *m_pParent;
    libvlc_equalizer_t *_vlcEqualizer;
};

#endif // DYEQUALIZER_H
