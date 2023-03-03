#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <map>

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
    QStringList m_imagePaths;
    int m_currentImageIndex = 0;
    const unsigned int MAX_IMAGES = 20;

    std::map<int, QPixmap> m_cache;

private:

    void drawCurrentImage();
    QPixmap * currentImage();

};
#endif // IMAGEVIEWER_H
