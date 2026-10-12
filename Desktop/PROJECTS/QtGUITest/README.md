# 🔬 Qt Data & Parameter Exporter (MSc Physics Task)

A lightweight, cross-platform graphical user interface (GUI) application built using **C++ and the Qt Framework**. This tool serves as a foundational desktop utility designed for physics laboratory data acquisition (DAQ) environments, simulation staging, or experimental log management, allowing researchers to quickly output metadata, parameters, or log entries into flat text files (`.txt`).

This project satisfies a core computational physics task: handling asynchronous event loops and streaming data safely to localized hardware disks.

---

## 🎯 Task Objective & Implementation

The core assignment requirement was to implement the file-writing sequence using Qt's native file handling and dialog classes:

### The Assignment Prompt:
```cpp
void QtGUITest::OnOpen()
{
    // implement the OnOpen function
    // it should use QFileDialog to select a new file name
    // and write the data from the text edit to the file using QFile
}
```

### Technical Solution Provided:
The logic was successfully fulfilled in `mainwindow.cpp` via the following steps:
1. **Dynamic File Selection:** Utilizes `QFileDialog::getSaveFileName` to open a native operating system window, prompting the user for a destination file path and filtering specifically for text entries.
2. **Safety Gates:** Implements conditional checking (`fileName.isEmpty()`) to prevent crashes or empty outputs if a user hits "Cancel".
3. **I/O Error Trapping:** Attempts a safe stream sequence via `QFile::open`. If a file is write-locked by another active physical process or directory permissions fail, it raises a native graphical `QMessageBox` warning.
4. **Data Stream Piping:** Bridges the interface layout and system layer by funneling plain text buffers from the `QTextEdit` widget straight into `QTextStream`, cleanly flushing and closing the file object afterward.

---

## 🛠️ Architecture & Core Logic Explained

### 1. Dynamic UI Component Styling (`mainwindow.cpp`)
To ensure presentation layouts remain perfectly clear across various lab workstation operating systems (Linux, Windows, macOS), the interface updates button states natively using Qt Style Sheets (QSS) inside the initialization constructor:

```cpp
ui->pushButton->setStyleSheet(
    "QPushButton { background-color: #28a745; color: white; border-radius: 4px; font-weight: bold; }"
    "QPushButton:hover { background-color: #218838; }"
);
```

### 2. Event Slot Mapping
The application ties user actions to physical hardware operations using Qt's Signal and Slot architecture. The automated slot pattern `on_pushButton_clicked()` listens for clicks on the interface button and seamlessly reroutes execution down to the implemented `OnOpen()` method.

---

## 📋 Prerequisites & Project Blueprint

### Directory Layout
* 📄 **`mainwindow.h`**: Class declaration mapping framework slot macros (`slots:`) to automate visual signal listening handlers.
* 📄 **`mainwindow.cpp`**: Concrete implementation containing widget styles, local memory lifecycle hooks, and safe file writing streams.
* 📄 **`mainwindow.ui`**: Core layout definitions mapping screen spatial positions for the text canvas (`textEdit`) and execution button (`pushButton`).

### System Requirements
* **C++ Compiler** Supporting C++17 or higher (GCC, Clang, or MSVC)
* **Qt 5 / Qt 6 SDK** (Core, GUI, and Widgets modules)
* **Build tool configuration** (`CMake` or `qmake`)

---

## 🔨 Compilation and Execution Steps

### Option B: Terminal Command Line (`qmake`)
Navigate to your project root workspace folder and execute the following commands:

```bash
# Generate localized build makefiles
qmake -makefile

# Build the binary application file
make

# Boot up the graphical desktop tool
./QtTextExporter
```

---

## 📝 Academic Use Notice
This toolkit was constructed as an assignment task under an **MSc in Physics** academic module curriculum. Feel free to copy, modify, or extend this application baseline for laboratory data pipeline handling or automated equipment monitoring routines.
