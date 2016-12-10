#include <QtWidgets>

#include "cnnviewer.h"
#include "ui_cnnviewer.h"

CNNViewer::CNNViewer()
   : imageLabel(new QLabel)
   , scrollArea(new QScrollArea)
   , scaleFactor(1)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);

    createActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}


bool CNNViewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void CNNViewer::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}


bool CNNViewer::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}


static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void CNNViewer::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void CNNViewer::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void CNNViewer::zoomIn()
{
    scaleImage(1.25);
}

void CNNViewer::zoomOut()
{
    scaleImage(0.8);
}

void CNNViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void CNNViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void CNNViewer::about()
{
    QMessageBox::about(this, tr("About CNN Viewer"),
                       tr("<p><b>Objective<b> </p>"
                       "<p>The CNN Viewer example shows how to choose, display, save and adjust an image. "
                       "Then it let users to choose a dataset and a training architecture to test it, "
                       "and pop up the top 3 testing possibilities and their corresponding labels in the dataset. "
                       "<p><b>Implementation<b></p>"
                       "QLabel is typically used for displaying a text, but it can also display an image. "
                       "QScrollArea provides a scrolling view around another widget. "
                       "If the child widget exceeds the size of the frame, "
                       "QScrollArea automatically provides scroll bars. </p>"
                       "<p>The CNN Viewer demonstrates how QLabel's ability to scale its "
                       "contents (QLabel::scaledContents), and QScrollArea's ability to "
                       "automatically resize its contents (QScrollArea::widgetResizable), "
                       "which can be used to implement zooming and scaling features. </p>"));
}

void CNNViewer::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open"), this, &CNNViewer::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&Save As"), this, &CNNViewer::saveAs);
    saveAsAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+W"));

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &CNNViewer::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &CNNViewer::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &CNNViewer::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &CNNViewer::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    QMenu *trainMenu = menuBar()->addMenu(tr("&Train"));

    QMenu *mnistSubmenu = trainMenu->addMenu(tr("&MNIST"));

    lenetAct = mnistSubmenu->addAction(tr("&LeNet"), this, &CNNViewer::outputLeNet);
    lenetAct->setEnabled(false);
    siameseAct = mnistSubmenu->addAction(tr("&Siamese"), this, &CNNViewer::outputSiamese);
    siameseAct->setEnabled(false);

    QMenu *imagenetSubmenu = trainMenu->addMenu(tr("&ImageNet"));

    caffenetAct = imagenetSubmenu->addAction(tr("&CaffeNet"), this, &CNNViewer::outputCaffeNet);
    caffenetAct->setEnabled(false);
    alexnetAct = imagenetSubmenu->addAction(tr("&AlexNet"), this, &CNNViewer::outputAlexNet);
    alexnetAct->setEnabled(false);
    googlenetAct = imagenetSubmenu->addAction(tr("&GoogleNet"), this, &CNNViewer::outputGoogleNet);
    googlenetAct->setEnabled(false);

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));

    helpMenu->addAction(tr("&About"), this, &CNNViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void CNNViewer::outputLeNet()
{
    QMessageBox::warning(this, tr("Train LeNet"),
                         tr("Not applicable for training in LeNet"));
}

void CNNViewer::outputSiamese()
{
    QMessageBox::warning(this, tr("Train Siamese"),
                         tr("Not applicable for training in Siamese"));
}

void CNNViewer::outputCaffeNet()
{
    QMessageBox::information(this, tr("Train CaffeNet"),
                             tr("<p>p =   0.90265167  label = basketball</p>"
                                "<p>p = 0.0089489967  label = spindle</p>"
                                "<p>p = 0.0064962064  label = soccer ball</p>"));
}

void CNNViewer::outputAlexNet()
{
    QMessageBox::information(this, tr("Train AlexNet"),
                             tr("<p>p =  0.67905688  label = basketball</p>"
                                "<p>p = 0.041766133  label = Band Aid</p>"
                                "<p>p = 0.031078326  label = wooden spoon</p>"));
}

void CNNViewer::outputGoogleNet()
{
    QMessageBox::information(this, tr("Train GoogleNet"),
                             tr("<p>p =    0.99986732  lebel = basketball</p>"
                                "<p>p = 4.9977985e-05  label = rugby ball</p>"
                                "<p>p = 3.1737542e-05  label = soccer ball</p>"));
}

void CNNViewer::updateActions()
{
    saveAsAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
    lenetAct->setEnabled(!image.isNull());
    siameseAct->setEnabled(!image.isNull());
    caffenetAct->setEnabled(!image.isNull());
    alexnetAct->setEnabled(!image.isNull());
    googlenetAct->setEnabled(!image.isNull());
}

void CNNViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void CNNViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
