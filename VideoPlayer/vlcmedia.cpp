#include "vlcmedia.h"
#include <QDebug>

#define qtu( i ) ((i).toUtf8().constData())
VlcMedia::VlcMedia()
{
    vlcPlayer = NULL;
    /* Initialize libVLC */
    vlcInstance = libvlc_new(0, NULL);

    /* Complain in case of broken installation */
    if (vlcInstance == NULL) {
        //qDebug()<<"set vlcInstance failed\n";
        exit(1);
    }
}
VlcMedia::~VlcMedia()
{
    /* Release libVLC instance on quit */
    if (vlcInstance)
    {
        libvlc_release(vlcInstance);
    }

}
void VlcMedia::openFile(QString fileOpen)
{

    /* The basic file-select box */
    //QString fileOpen = QFileDialog::getOpenFileName(this, tr("Load a file"), "~");

    /* Stop if something is playing */
    if (vlcPlayer && libvlc_media_player_is_playing(vlcPlayer))
        stop();

    /* Create a new Media */
    libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance, qtu(fileOpen));
    if (!vlcMedia)
    {
        return;
    }


    /* Create a new libvlc player */
    vlcPlayer = libvlc_media_player_new_from_media (vlcMedia);

    /* Release the media */
    libvlc_media_release(vlcMedia);

    /* Integrate the video in the interface */
#if defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(vlcPlayer, (void *)videoWidget->winId());
#elif defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(vlcPlayer, videoWidget->winId());
#elif defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(vlcPlayer, videoWidget->winId());
#endif

    /* And start playback */
    libvlc_media_player_play (vlcPlayer);

}

int VlcMedia::changeVolume(int vol)
{ /* Called on volume slider change */

    if (vlcPlayer)
    {
        return libvlc_audio_set_volume (vlcPlayer,vol);
    }

    return 0;
}

void VlcMedia::play()
{
    if (!vlcPlayer)
        return;

    if (!libvlc_media_player_is_playing(vlcPlayer))
    {
        /* Pause */
        //libvlc_media_player_pause(vlcPlayer);
         libvlc_media_player_play(vlcPlayer);
    }
//    else
//    {
//        /* Play again */
//

//    }
}
void VlcMedia::stop()
{
    if(vlcPlayer)
    {
        /* stop the media player */
        libvlc_media_player_stop(vlcPlayer);

        /* release the media player */
        libvlc_media_player_release(vlcPlayer);

        /* Reset application values */
        vlcPlayer = NULL;

    }
}

libvlc_state_t VlcMedia::GetVlcState()
{
    if(NULL != vlcPlayer)
    {
        return libvlc_media_player_get_state(vlcPlayer);
    }
    else
    {
        return libvlc_NothingSpecial;
    }
}
void VlcMedia::closeEvent(QCloseEvent *event)
{
    stop();
    event->accept();
}
void VlcMedia::SetPlayWindow(QWidget *PlayWindow)
{
      videoWidget = PlayWindow;
}
