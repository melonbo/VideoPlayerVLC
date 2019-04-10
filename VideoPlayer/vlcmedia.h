#ifndef VLCMEDIA_H
#define VLCMEDIA_H
#include <vlc/vlc.h>
#include <QString>
#include <QtGui>
#include <QObject>

class VlcMedia
{
public:
    VlcMedia();
   ~VlcMedia();
   int changeVolume(int vol);//设置声音
   void openFile(QString);//打开文件
   void stop();//停止播放
   void play();//开始播放
   void SetPlayWindow(QWidget *PlayWindow);
   libvlc_state_t GetVlcState();
private:
    libvlc_instance_t *vlcInstance;
    libvlc_media_player_t *vlcPlayer;
    QWidget *videoWidget;
protected:
       virtual void closeEvent(QCloseEvent*);

};

#endif // VLCMEDIA_H
