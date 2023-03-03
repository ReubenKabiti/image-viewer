#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QFileDialog>
#include <QDir>

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    openDir(QDir::currentPath());
}

void ImageViewer::openDir(QString dirname)
{
    auto dir = QDir(dirname);
    m_images.clear();
    for (auto file : dir.entryList())
    {
        if (file.endsWith(".png") || file.endsWith(".jpg"))
        {
            m_images.append(dir.absoluteFilePath(file));
        }
    }
    drawCurrentImage();
    setCounter();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::drawCurrentImage()
{
    if (m_images.length() == 0)
        return;
    auto filename = m_images[m_currentImage];
    QPixmap map(filename);

    /*
     * Clamp the image to fit the screen if its size is bigger than that of the screen
     * The extra calculations are there to make sure the aspect ratio of the image stays the same so that the
     * image does not look stretched
    */

    if (map.size().width() > size().width())
    {
        float W = size().width();
        float w = map.size().width();
        float h = map.size().height();
        float H = W/w * h;

        map = map.scaled(W, H);
    }
    if (map.size().height() > size().height())
    {
        float w = map.size().width();
        float h = map.size().height();
        float H = size().height();
        float W = H / h * w;

        map = map.scaled(W, H);
    }

    ui->label->setPixmap(map);
}

void ImageViewer::setCounter()
{
    QString text = "Image ";
    text += QString::number(m_currentImage+1);
    text += "/";
    text += QString::number(m_images.length());

    ui->counter->setText(text);
}

void ImageViewer::on_backButton_clicked()
{
    if (m_currentImage == 0)
        m_currentImage = m_images.length() - 1;
    else
        m_currentImage--;
    drawCurrentImage();
    setCounter();
}


void ImageViewer::on_nextButton_clicked()
{
    if (m_currentImage == m_images.length() - 1)
        m_currentImage = 0;
    else
        m_currentImage++;
    drawCurrentImage();
    setCounter();
}


void ImageViewer::on_actionOpen_Folder_triggered()
{
    QString dirName = QFileDialog::getExistingDirectory(this);
    openDir(dirName);
}

