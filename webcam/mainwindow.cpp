#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QUrl>

MainWindow::MainWindow(QMainWindow *parent) :
      QMainWindow(parent),
      ui(new Ui::MainWindow),
      connected(true),
      recording(true),
      camera(nullptr),
      recorder(nullptr)
 {
    ui->setupUi(this);

    for (auto& cameraInfo : QCameraInfo::availableCameras())
        ui->devices->addItem(cameraInfo.description());

    toggleConnected();
    toggleRecording();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_devices_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_connectButton_released()
{
    if (!connected) {
        for (auto& cameraInfo : QCameraInfo::availableCameras()) {

            if (cameraInfo.description() == ui->devices->currentText())
            {
                camera = new QCamera(cameraInfo);
                QCameraViewfinder* viewFinder = new QCameraViewfinder(this);
                camera->setViewfinder(viewFinder);
                ui->webcam->layout()->addWidget(viewFinder);
                camera->start();
                toggleConnected();
            }
        }
    }

    else if (camera) {
        camera->stop();
        toggleConnected();
    }

}

void MainWindow::on_recordButton_released()
{
    if (connected)
    {
        if (!recording && camera)
        {
            recorder = new QMediaRecorder(camera);
            camera->setCaptureMode(QCamera::CaptureVideo);
            recorder->setOutputLocation(QUrl(qApp->applicationDirPath()));
            recorder->record();
            toggleRecording();
        }
        else if (recorder)
        {
            recorder->stop();
            toggleRecording();
        }
    }
}

void MainWindow::toggleConnected()
{
    connected = !connected;
    const QString text = connected ? "Disconnect" : "Connect";
    ui->connectButton->setText(text);
}

void MainWindow::toggleRecording()
{
    recording = !recording;
    const QString text = recording ? "Stop" : "Record";
    ui->recordButton->setText(text);
}
