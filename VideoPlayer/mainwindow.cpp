#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pVlcPlayer = new VlcMedia();//创建vlc对象
    pVlcPlayer->SetPlayWindow(ui->label_video);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
                                            tr("选择视频"),
                                            "",
                                            tr("Images (*.mp4 *.avi *.mkv *.flv *.wmv)")); //选择路径
    playLocalFile(filename.toLatin1().data());
    ui->label_filename->setText(filename);
}

void MainWindow::playLocalFile(char *path)
{

}

void MainWindow::on_pushButton_play_clicked()
{
    QString filename = ui->label_filename->text();
    printf("filename : %s\n", filename.toLatin1().data());
    pVlcPlayer->openFile(filename.toLatin1().data());
}

void MainWindow::on_pushButton_stop_clicked()
{
    pVlcPlayer->stop();
}
