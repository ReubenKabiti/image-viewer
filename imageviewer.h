#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();


private slots:

    void on_backButton_clicked();

    void on_nextButton_clicked();
    void setCounter();
    void openDir(QString dirname);

    void on_actionOpen_Folder_triggered();

private:
    Ui::ImageViewer *ui;
    int m_currentImage = 0;
    QStringList m_images;

    void drawCurrentImage();
};
#endif // IMAGEVIEWER_H
