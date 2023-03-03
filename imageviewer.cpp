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
    m_currentImageIndex = 0;
    m_cache.clear();
    m_imagePaths.clear();

    QDir dir(dirname);

    for (auto file : dir.entryList())
    {
        if
        (
                file.endsWith(".png") ||
                file.endsWith(".jpg") ||
                file.endsWith(".jpeg")
        )
        {
            m_imagePaths.append(dir.absoluteFilePath(file));
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

    auto mapPtr = currentImage();
    if (mapPtr == nullptr)
        return;
    auto map = *mapPtr;
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

QPixmap *ImageViewer::currentImage()
{
    if (m_imagePaths.size() == 0)
        return nullptr;

    if (m_cache.count(m_currentImageIndex) == 0)
    {
        if (m_cache.size() >= MAX_IMAGES)
        {
            m_cache.erase(m_cache.begin());
        }
        m_cache[m_currentImageIndex] = QPixmap(m_imagePaths[m_currentImageIndex]);
    }

    return &m_cache[m_currentImageIndex];
}

void ImageViewer::setCounter()
{
    QString text = "Image ";
    text += QString::number(m_currentImageIndex+1);
    text += " of ";
    int length = m_imagePaths.length();
    if (length == 0)
        length = 1;
    text += QString::number(m_imagePaths.length());

    ui->counter->setText(text);
}

void ImageViewer::on_backButton_clicked()
{
    m_currentImageIndex--;
    if (m_currentImageIndex < 0)
        m_currentImageIndex = m_imagePaths.size() - 1;
    drawCurrentImage();
    setCounter();
}

void ImageViewer::on_nextButton_clicked()
{    
    m_currentImageIndex++;
    if (m_currentImageIndex >= m_imagePaths.size() - 1)
        m_currentImageIndex = 0;
    drawCurrentImage();
    setCounter();
}


void ImageViewer::on_actionOpen_Folder_triggered()
{
    QString dirName = QFileDialog::getExistingDirectory(this);
    openDir(dirName);
}

