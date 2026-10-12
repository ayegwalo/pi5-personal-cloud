#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Style the push button in code
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #28a745;" // green color
        "   color: white;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #218838;"
        "}"
        );
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OnOpen()
{
    // Open a save file dialog so a user can choose the file name and location
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        "",
        tr("Text Files (*.txt);;All Files (*)")
        );


    // If a user clicked cancel or didn't select a file, stop here
    if (fileName.isEmpty())
        return;

    // Initialize a QFile object with the chosen file path
    QFile file(fileName);

    // Try to open the file for writing; show a warning popup if it fails
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file for writing."));
        return;
    }

    // Use QTextStream to take text from the text box and write it into the file
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();

    // Close the file to safely save the data to disk
    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    // Triggered automatically when the button is clicked; calls the save function above
    OnOpen();
}