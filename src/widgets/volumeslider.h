#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <DSlider>
#include <DToolButton>
#include <QPoint>
#include <DArrowRectangle>
#include <DUtil>

#include "utils.h"
#include "volumemonitoring.h"
#include "threadpool.h"
#include "mainwindow.h"
#include "compositing_manager.h"
#include "dmr_settings.h"
#include "dbus_adpator.h"
#include "../accessibility/ac-deepin-movie-define.h"

DWIDGET_USE_NAMESPACE

namespace dmr {

class VolumeSlider: public DArrowRectangle
{
    Q_OBJECT

    enum State {
        Open,
        Close
    };

signals:
    void sigVolumeChanged(int nValue);
    void sigMuteStateChanged(bool bMute);

public:
    VolumeSlider(MainWindow *mw, QWidget *parent);
    ~VolumeSlider();

    void initVolume();   //初始化音量
    void initBgImage();
    void stopTimer();
    void popup();        //弹起音量条
    void updatePoint(QPoint point);
    bool getsliderstate();

public slots:
    void volumeUp();                   //滚轮加音量
    void volumeDown();                 //滚轮减音量
    void changeMuteState(bool bMute);  //改变静音状态
    void volumeChanged(int nVolume);   //控件音量变化后的后续处理
    void muteButtnClicked();
    void setThemeType(int type);
    void delayedHide();

protected:
    void enterEvent(QEvent *e);
    void showEvent(QShowEvent *se);
    void leaveEvent(QEvent *e);
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *obj, QEvent *e);

    void refreshIcon();                //刷新图标
    void changeVolume(int nVolume);    //改变控件音量

private:
    QString readSinkInputPath();       //获取dbus接口的地址
    void setAudioVolume(int volume);   //回设dock栏应用音量
    void setMute(bool muted);          //回设dock栏应用静音状态

private:
    DToolButton *m_pBtnChangeMute {nullptr};
    QLabel *m_pLabShowVolume {nullptr};
    DSlider *m_slider;
    MainWindow *_mw;
    QTimer m_autoHideTimer;
    bool m_bIsMute {false};
    bool m_bFinished {false};
    QPropertyAnimation *pVolAnimation {nullptr};
    State state {Close};
    QPoint m_point {0, 0};
    QPixmap m_bgImage;
    bool m_mouseIn {false};
    int m_nVolume;                      //记录实际音量(实际音量最大值为200,显示最大到100)
    VolumeMonitoring volumeMonitoring;  //监听dock栏应用音量变化
};
}


#endif // VOLUMESLIDER_H
