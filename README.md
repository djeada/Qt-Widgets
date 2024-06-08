# Qt-Widgets
A collection of examples and reusable elements created with Qt6 widgets.

![Capture](https://user-images.githubusercontent.com/37275728/185923826-67a8472a-4216-4062-bb65-5dd9efbb2a3b.PNG)

## Table of Contents
<!--ts-->
- [Requirements](#Requirements)
- [Compilation](#Compilation)
  - [Qt-Creator-IDE](#Qt-Creator-IDE)
  - [Terminal](#Terminal)
    - [Windows](#Windows)
    - [Linux/macOS](#Linux/macOS)
  - [PyQt](#PyQt)
- [Content](#Content)
  - [Core](#Core)
  - [Collections-And-Algorithms](#Collections-And-Algorithms)
  - [Widgets](#Widgets)
  - [MVC](#MVC)
  - [Graphics](#Graphics)
  - [Files](#Files)
  - [Network](#Network)
  - [Concurrent-Computing](#Concurrent-Computing)
  - [Plots](#Plots)
  - [Other](#Other)
<!--te-->

## Purpose

The objective of this repository is to compile a comprehensive collection of reusable Qt widgets suitable for integration into any application. This approach eliminates the need to develop common components from scratch for each new project, allowing developers to concentrate on customization and enhancement.

## Requirements

### For C++ Projects:
* C++14
* CMake 3.10+
* Qt6

### For Python Projects:
* Python 3.10+
* Dependencies specified in the project's `requirements.txt` file

## Compilation Instructions

### Using Qt Creator IDE

To initiate the project, open the relevant `CMakeLists.txt` file in Qt Creator.

### Using Terminal

1. Set the environment variable `CMAKE_PREFIX_PATH` to the Qt6 installation path.
2. Open the terminal in the project directory and execute the following commands:

#### For Windows:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ start ./Qt.project_name.sln
```

For Linux/macOS:

```sh
$ mkdir build
$ cd build
$ cmake -GNinja ..
$ ninja ../project_name
```

### PyQt Projects

The recommended method for running PyQt projects is to use virtualenv:

1. Create and activate a virtual environment:

```sh
$ virtualenv env
$ source env/bin/activate
```

2. Install the required dependencies:

```sh
$ pip install -r requirements.txt
```

3. Run the application:

```sh
$ python main.py
```

To convert .ui files to .py scripts, use the following Python snippet:

```python
from PyQt6 import uic

with open("source.ui") as ui_file:
    with open("output_ui.py", "w") as py_ui_file:
        uic.compileUi(ui_file, py_ui_file)
```

## Content

### Core

**QObject** is perhaps the most significant class in the entire Qt ecosystem. It encompasses two crucial mechanisms:

1. **Slots and Signals**:
   - Signals and slots are used for communication between objects.
   - A signal is emitted when a particular event occurs.
   - Slots are functions that are called in response to a signal.
   - This mechanism is central to Qt and allows for a flexible and reusable object-oriented code.

2. **Parent-Child Relationship**:
   - The parent-child relationship ensures that child objects are automatically deleted when their parent is deleted.
   - This is crucial for managing the lifecycle of objects and preventing memory leaks.

When subclassing **QObject**, it is necessary to include the `Q_OBJECT` macro in the declaration to enable these mechanisms. Below is an example of how to subclass `QObject`:

```cpp
class SubClass : public QObject {
  Q_OBJECT

public:
  SubClass(QObject *parent = nullptr);
  ~SubClass();

signals:
  void someSignal();

public slots:
  void someSlot();
};
```

Examples and Demonstrations

Description | Screenshot
---|---
**[Children Generator](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/children_generator)** - Demonstrates the parent-child relationship in Qt. This generator can create and delete children dynamically. When the generator instance is destroyed, all of its children are also destroyed.| <img width="2000"/>![children_generator](https://user-images.githubusercontent.com/37275728/174343131-44e1644d-2188-42c0-9b86-d6d6ae9e9818.gif)
**[Custom Signal and Slots](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/custom_signal_slots)** - A slot is a standard method that can be connected to a signal. Multiple slots can be connected to a single signal. A signal is a value that can be emitted by any function, and when emitted, the value is passed as a parameter to all associated slots. <br><br> **Python Implementation**: [Custom Signal and Slots in Python](https://github.com/djeada/Qt-Widgets/tree/master/src/core/python/custom_signal_slots)| <img width="2000"/>![custom_signal_slots](https://user-images.githubusercontent.com/37275728/174352043-88d09439-d504-4ffe-802b-555a5fe669d8.gif)
**[Smart Pointers](https://github.com/djeada/Qt-Widgets/tree/master/src/core/smart_pointers)** - A smart pointer is an abstract data type that has all the properties of a raw pointer along with automated garbage collection. Qt provided smart pointers before they were included in the C++ standard. They are used in some projects, but raw pointers are typically used for `QObjects` because they utilize a parent-child model for managing object lifecycles.| <img width="2000"/>![smart_pointers](https://user-images.githubusercontent.com/37275728/174352307-5e5a7333-6cb3-4d16-87d7-ffe48cac5bcf.gif)
**[QVariant and QMetaType](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/qvariant_and_qmetatype)** - The `QVariant` class acts as a union for the most commonly used Qt data types. Because C++ prohibits unions from containing types with non-default constructors or destructors, most useful Qt classes cannot be used in raw unions. The type is registered using the `Q_DECLARE_METATYPE(Type)` macro, enabling `QMetaType` to recognize the type. `Q_DECLARE_METATYPE` requires the class or struct to have a default constructor, copy constructor, and public destructor.| <img width="2000"/>![qvariant_and_qmetatype](https://user-images.githubusercontent.com/37275728/174352447-56258e05-1edf-4073-918b-20afa8784f42.gif)

### Collections And Algorithms

Qt has implemented a large number of containers and accompanying algorithms that correspond to STL containers and algorithms. Some have been deprecated, such as `qSort()`, so be careful to read the documentation before using them. This is due to the fact that they were created prior to the standardization of STL containers. Some features, like the `contains()` function, were first added in C++20, about 30 years later.

So the obvious question is whether you should use Qt's containers or STL. The ones from Qt are fully integrated into the Qt APIs, so compatibility is an important consideration. There is no clear winner in terms of efficiency and performance, and both are viable options. However, using the STL would enable you to design logic independent of the GUI framework, making the transition to another technology much easier.

Description | Screenshot 
---|---
**[QList](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist)** - `QList` is a generic container class in Qt. It maintains a list of values and allows for rapid index-based access as well as quick insertions and deletions. Despite being implemented as an array-list, it has very fast prepends and appends. `QList` is the ideal type to use for most purposes. This example shows how to initialize, display, and find and delete the list's elements.<br><br> A quick note for Python programmers: Python lists cannot be serialized using `QDataStream`, whereas `QList` can be serialized using C++. When porting the C++ code, `QList` cannot always be replaced with a Python list.| <img width="2000"/>![qlist](https://user-images.githubusercontent.com/37275728/174391054-adbe0a88-456d-4ed3-9ee6-9ef6db12b0f0.gif)
**[QList vs QVector](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist_vs_qvector)** - `QVector` is very similar in use to `QList`. One distinction is that items of `QVector` are always stored in a contiguous way in memory, whereas `QList` does not guarantee this.| ![qlist_vs_qvector](https://user-images.githubusercontent.com/37275728/174391027-7851c137-8462-4ba3-81cb-8eb313e2fb0a.gif)
**[QSet](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qset)** - `QSet` ensures the uniqueness of its elements, although the order in which the elements are inserted is lost.| <img width="2000"/>![qset](https://user-images.githubusercontent.com/37275728/174390876-de5497cb-77b1-43a6-a7d1-b0f6c966acad.gif)
**[QMap](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qmap)** - The `QMap` class is a template class that offers a dictionary based on a red-black tree. `QMap<Key, T>` is a generic container class in Qt. It holds (key, value) pairs and allows for quick access to the value associated with a key. Use it anytime you don't want numeric (or ordered) indices.| <img width="2000"/>![qmap](https://user-images.githubusercontent.com/37275728/174390916-7f6786b2-ef60-4075-af4c-0a977f2a1be0.gif)

### Widgets

`QWidgets` are used for "standard" GUI components such as buttons, checkboxes, drop-down menus, and more. Since widgets inherit from `QObjects`, they also have signals/slots and a parent-child relationship. It is best to use them for standard user interface components and customize them with a subset of CSS known as QSS and stylesheets. There is also the option of drawing them yourself using the `paintEvent()` method, although this can be challenging.

Description | Screenshot
---|---
**[Message Box](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/message_box)** - The `QMessageBox` class provides a modal dialog for informing the user or asking for and receiving an answer from the user. A message box displays a primary message to notify the user of an issue, an informative explanation to clarify the message, or a query to the user. The message box can also display an icon and standard buttons for receiving user responses.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/message_box) as well. | <img width="2000"/>![message_box](https://user-images.githubusercontent.com/37275728/174391108-b9f9a7fe-c43c-4571-83bf-91148c276ca3.gif)
**[Custom Tooltip](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/custom_tooltip)** - When you hover your cursor over a widget, a tooltip will appear. Besides conventional text, the tooltip can be styled with a subset of HTML.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/custom_tooltip) as well. | <img width="2000"/>![custom_tooltip](https://user-images.githubusercontent.com/37275728/174391265-8c4dc1db-4583-44f3-8057-b6c9a088deae.gif)
**[QWidget Custom Painting](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/custom_painting)** - To draw an arrow in the background, the `paintEvent()` method is overridden. Most drawing tasks required by GUI programs are handled by highly efficient algorithms in `QPainter`. It can draw anything from basic graphical primitives like points, lines, rectangles, ellipses, and polygons to more complex shapes like vector paths.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/custom_painting) as well. | <img width="2000"/>![qwidget_custom_painting](https://user-images.githubusercontent.com/37275728/174391245-3f98c4e9-68db-4ced-9cc7-498c004ea945.gif)
**[Status Bar](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/status_bar)** - The `QStatusBar` class implements a horizontal bar for displaying status information. A timer is used to control how long it takes the bar to reach 100%. Three buttons are used to control the bar: start, stop, and reset.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar) as well. | <img width="2000"/>![status_bar](https://user-images.githubusercontent.com/37275728/174391150-776450f1-e6f2-4170-b5fe-ae10eaea830a.gif)
**[Switch](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/switch_button)** - The `QSwitch` class is used to create switch buttons, providing a way to toggle between two states. This example shows how to create and customize switch buttons.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/switch_button) as well. | ![switch](https://user-images.githubusercontent.com/37275728/181903593-ae6d136b-086c-49ce-8d67-1fa14ce5b3c3.gif)
**[Double Range Slider](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/double_range_slider)** - The `QDoubleRangeSlider` class implements a slider that allows for selecting a range between two values. This example shows how to create and customize double range sliders.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/double_range_slider) as well. | <img width="2000"/>![double_range_slider](https://user-images.githubusercontent.com/37275728/181903584-a58a4afc-85f3-4f3c-a05d-8f5067635d41.gif)

### MVC

**What is Model-View-Controller (MVC)?**

It is a common method of separating concerns regarding the presentation and modification of dynamic content in graphical applications:

* **Model**: Responsible for connecting to the data source. The data may already be in memory, requested from a database, or read from a file. After receiving the necessary information, it organizes it into cells with potentially numerous rows and columns. It determines what should and should not be displayed and provides an API for accessing, modifying, inserting, and removing cells. The model also decides what data interactions are permitted and how they are carried out.
* **View**: Receives the model's data, which already has a suitable structure. The view is aware of the cells, rows, and columns that the model has prepared and is concerned with how those elements will be displayed. It handles the appropriate fonts, colors, spacing between elements, slider bars, and so forth.
* **Controller**: Allows the user to interact with the data displayed in the view. It collects user events such as keystrokes and mouse clicks and then calls the relevant function from the model API.

**How to implement it using the Qt framework?**

1. **`QStandardItemModel`**: A simple implementation that is not suitable for large or complex models. It is designed for ease of use rather than high performance and has a shallow learning curve.
2. **`QAbstractItemModel`**: Provides the separation of real data storage and organization (which must occur in the model and the related proxy models) from the presentation. This allows for complete customization but requires a thorough understanding of its inner workings.

Description | Screenshot 
---|---
**[String List Model](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/string_list_model)** - The `QStringListModel` class provides a simple model that stores a list of strings. It is suitable for use with a `QListView` or `QComboBox`.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/string_list_model) as well. | <img width="2000"/>![string_list_model](https://user-images.githubusercontent.com/37275728/174391715-d60c2382-ec92-490d-9084-03aa65315632.gif)
**[Tree Model](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/tree_model)** - Simple implementation of a tree model. The items are stored using hierarchical relationships. It is suitable for use with a `QTreeView`.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/tree_model) as well. | ![tree_model](https://user-images.githubusercontent.com/37275728/174391748-bf6efd6b-3bec-4aea-89c8-66bade3f62f6.gif)
**[Reorderable Tree View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/reorderable_treeview)** - Extends the tree model to allow reordering of items. Reordering is triggered through drag-and-drop mechanisms in `QTreeView`. The selected item is moved with all its children to the new position.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/reorderable_treeview) as well. | <img width="2000"/>![reorderable_tree_view](https://user-images.githubusercontent.com/37275728/174391785-9b95cd28-19ea-40c5-a5c6-de90440b612c.gif)
**[Custom Item Delegate](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/item_delegate)** - Custom item delegate for `QListView`/`QTableView`. The item delegate is responsible for painting the items in the view. It can paint the items in various ways depending on their current role. For instance, when a user clicks on an item, you can change the role from display to edit and render a completely different widget. This example shows how to position the text and style it, as well as how to paint custom shapes and render custom widgets instead of text.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/item_delegate) as well. | ![custom_delegate](https://user-images.githubusercontent.com/37275728/174391798-1e9971bf-91df-42d6-88d1-30f6ba526fe5.gif)
**[Matrix View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/matrix_view)** - Displays an array of arrays in the form of a table. Allows the user to define the precision of the floating point numbers.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/matrix_view) as well. | ![matrix_view](https://user-images.githubusercontent.com/37275728/182579831-a277a892-cc9c-43e5-90f1-28def863b4c4.gif)
**[File Directory Tree View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/file_directory_treeview)** - A tree model implementation for displaying file directories. It supports reordering of items through drag-and-drop mechanisms in `QTreeView`. The selected item is moved with all its children to the new position.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/file_directory_treeview) as well. | <img width="2000"/>![file_dir_treeview](https://user-images.githubusercontent.com/37275728/174501389-3d9c8bef-79a7-4401-9011-91875fa74ab0.gif)
**[Crypto Ranking](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/crypto_ranking)** - A tree model for displaying cryptocurrency rankings. It allows for reordering of items through drag-and-drop mechanisms in `QTreeView`. The selected item is moved with all its children to the new position.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/crypto_ranking) as well. | <img width="2000"/>![crypto_ranking](https://user-images.githubusercontent.com/37275728/174501398-a7f470c7-76ca-4e49-818c-d559bc3e50c6.gif)
**[Emoji Picker](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/emoji_picker)** - A tree model for displaying emojis. It allows for reordering of items through drag-and-drop mechanisms in `QTreeView`. The selected item is moved with all its children to the new position.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/emoji_picker) as well. | <img width="2000"/>![emoji_picker](https://user-images.githubusercontent.com/37275728/174501411-13046047-afcf-4910-a0bc-832c24cae30f.gif)
  
### Graphics

Two main classes allow us to implement custom graphics: `QPainter` and `QGraphicsView`.

`QPainter` allows you to manipulate pixels on a widget. It is used when we overwrite a widget's `paintEvent()` method. It can interact with both `QBrush` and `QPen`. Filling is done using brushes, while outlines are created with pens. A brush can be styled, colored, gradiented, or textured.

With `QPainter`, you have the option to draw:
- A Point;
- A Line;
- A Rectangle;
- An Ellipse;
- A Polygon.

The graphics scene framework allows you to arrange your geometry in a tree of `QGraphicsItems` and easily manipulate its components. Regardless of the complexity, `QPainter` handles the drawing, which is abstracted away. Since `QGraphicsItem` is not derived from `QObject`, it lacks signals/slots; however, you can use `QGraphicsObject` if you need those features. The standard graphics item is more lightweight and includes additional features not provided by the widgets API. Like standard widgets, there are basic graphics elements such as lines and rectangles. For unique elements, you must implement your own painting using `QPainter`, similar to custom widgets.

If your geometry is simple and does not require interactive and hierarchical features, use `QPainter` directly. For anything complex and interactive, use `QGraphicsView`.

Description | Screenshot 
---|---
**[Movable Image](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/movable_image)** - Create a scene and display it with elements added. The `QGraphicsView` object is a widget created in Designer to display the contents of a `QGraphicsScene`. A movable object can be easily spawned on a graphics scene. Since the scene keeps track of its items, deletion is not an issue. You can change the item's appearance using the paint event.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/movable_image) as well. | <img width="2000"/>![movable_image](https://user-images.githubusercontent.com/37275728/174391871-c78ae82c-7982-4d2d-8a35-5ae565cfdde1.gif)
**[Image Cropper](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/image_cropper)** - `QWidget` has been subclassed to receive image drops and display them with an elliptical crop. When the widget's width and height are equal, the crop has a circular shape.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/image_cropper) as well. | <img width="2000"/>![image_cropper](https://user-images.githubusercontent.com/37275728/174391888-f4338633-402b-4298-9bf4-9adfea5869f5.gif)
**[Transformations](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/transformations)** - The `scale()` function scales the coordinate system by a specified offset, the `rotate()` function rotates it clockwise, and the `translate()` function translates it (i.e., adds a given offset to the points). Note that any transformation is a matrix multiplication, so the order in the code should be inverted relative to the order in which the transformations should be applied.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/transformations) as well. | <img width="2000"/>![transformations](https://user-images.githubusercontent.com/37275728/174391909-bd03d417-b0c3-4297-adea-1adf624bf41f.gif)
**[Moving Balls](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/moving_balls)** - `QGraphicView` acts like a camera in Qt's universe, while `QGraphicScene` is a movie scene. The camera and the scene have separate coordinate systems, connected by a transformation. As actors move in the film, their size on the scene may change while their real size remains constant. This example uses colored balls to demonstrate how to control the position of an item on the scene.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/moving_balls) as well. | <img width="2000"/>![moving_balls](https://user-images.githubusercontent.com/37275728/174391947-8f427876-7c9e-43fb-98a2-bae13eefc10f.gif)

### Files

File handling is a fundamental aspect of many applications, and Qt provides a comprehensive set of classes to facilitate reading from and writing to files. The primary class for file handling in Qt is `QFile`, which is an I/O device that allows you to manipulate text and binary files and resources.

`QFile` can operate in several modes, including read-only, write-only, and read-write. It supports both synchronous and asynchronous operations, providing flexibility depending on the needs of your application. For easier and more efficient file manipulation, `QFile` is often used in conjunction with other classes such as `QTextStream`, `QDataStream`, and `QFileInfo`.

- **`QFile`**: The basic class for file handling, allowing opening, closing, reading, and writing files. It can work with text or binary data.
- **`QTextStream`**: Used with `QFile` to handle text file operations more conveniently. It provides functions for reading and writing text, including support for different encodings.
- **`QDataStream`**: Facilitates reading and writing binary data to and from a `QFile`. It ensures that the data is read and written in a consistent format across different platforms.
- **`QFileInfo`**: Provides information about files and directories. It can be used to retrieve file names, sizes, last modified times, and other attributes.

Description | Screenshot 
---|---
**[File Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/file_info)** - Displays information about files. Get a list of files in a given directory and all its subdirectories. Use `QFileInfo` to get the file's name, size, and other data. Unfortunately, `QFileInfo` does not use many static methods, and you must create an object to access most of its features. This results in generating a large number of temporary objects that are destroyed immediately after usage.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/file_info) as well. | <img width="2000"/>![file_info](https://user-images.githubusercontent.com/37275728/174392052-f02d2d46-14aa-4d80-a255-6dbe5cef93b3.gif)
**[File Operations](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/file_operations)** - Manipulates files by copying, moving, or deleting them. Creates a temporary directory and fills it with text files. If any error occurs, it is displayed on the console.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/file_operations) as well. | <img width="2000"/>![file_operations](https://user-images.githubusercontent.com/37275728/174392152-ffb056b4-857a-4dd4-a788-c5317d101cea.gif)
**[Storage Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/storage_info)** - Displays information about storage, such as free space, total space, and used space. Shows mounted volumes and their names.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/storage_info) as well. | <img width="2000"/>![storage_info](https://user-images.githubusercontent.com/37275728/174392119-78714676-d6b6-4510-846c-783e6ce44947.gif)
**[JSON Serialization](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/json_serialization)** - Serializes an object of a custom class to a JSON file. Deserializes a JSON file to an object of a custom class. Checks if the objects are the same.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/json_serialization) as well. | <img width="2000"/>![json_serialization](https://user-images.githubusercontent.com/37275728/174392103-9f5c0775-fc94-4865-a337-eed7283ddc40.gif)
 
### Network

Qt provides powerful classes for network programming, allowing you to create both client and server applications. The main classes for handling network operations in Qt are `QNetworkAccessManager`, `QTcpSocket`, and `QUdpSocket`.

- **`QNetworkAccessManager`**: Manages the network operations, such as sending network requests and receiving replies. It supports HTTP and FTP protocols and can be used to download files or communicate with REST APIs.
- **`QTcpSocket`**: Allows you to create TCP clients that can connect to TCP servers, send and receive data.
- **`QUdpSocket`**: Provides an interface for UDP socket communication, enabling you to send and receive UDP datagrams.

These classes provide a robust framework for implementing various network functionalities, from simple data transfers to complex network protocols.

### Concurrent Computing

Qt's concurrent programming module provides classes to help you manage threads and asynchronous operations easily. It includes classes like `QThread`, `QtConcurrent`, and `QProcess`, which allow for spawning threads, running tasks concurrently, and handling external processes.

- **`QThread`**: Represents a thread and allows you to manage its execution.
- **`QtConcurrent`**: Offers high-level APIs for running functions in parallel, making it simpler to utilize multiple cores.
- **`QProcess`**: Enables the execution of external programs and facilitates interaction with their input/output streams.

Description | Screenshot 
---|---
**[Spawn Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_thread)** - Spawns a thread and runs a function in it using the internal Qt framework for managing threads.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar) as well. | <img width="2000"/>![spawn_thread](https://user-images.githubusercontent.com/37275728/174501495-8c326dad-939a-4269-b212-85023a292c80.gif)
**[Gui Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/gui_thread.cpp)** - Ensures the GUI's responsiveness while the threads perform their tasks. When worker threads finish their work, the view is updated to show the results. `QFutureWatcher` emits the `finished()` signal when the worker thread completes its task. There is no direct support for clearing the watcher, so a common solution is to spawn the watchers along with the threads dynamically.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar) as well. | <img width="2000"/>![gui_thread](https://user-images.githubusercontent.com/37275728/174501505-fad1d705-4ea5-488e-8432-4af6383bd05b.gif)
**[Spawn Process](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_process)** - `QProcess` allows you to spawn new processes, connect to their input/output/error pipes, and obtain their return codes. This example spawns a single process and waits for it to finish.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar) as well. |
**[CMD Interface](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/cmd_interface)** - A simple command line interface that allows you to execute commands as if they were typed in the console.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar) as well. | <img width="2000"/>![cmd_interface](https://user-images.githubusercontent.com/37275728/174501513-8103dd52-7310-448d-89c6-cdee96b4141d.gif)

### Plots

Qt applications can display simple static plots as well as build visually appealing, interactive dashboards. In addition to the native QtCharts library, Qt also supports the widely used Matplotlib. However, any modern plotting library can be integrated with minimal effort.

Description | Screenshot 
---|---
**[Simple plot](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/plot_widget)** - Embeds a Matplotlib canvas into a Qt widget. Matplotlib offers several options for constructing useful, personalized, and beautiful plots to display data in the simplest and most effective way possible. All standard plotting options are accessible, and a toolbar with dynamic functionality is included.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/plot_widget) as well. | <img width="2000"/>![plot](https://user-images.githubusercontent.com/37275728/182579732-a0a52499-6400-4fa0-9f22-a8e65c9f55f3.gif)
**[Lasso selection](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/lasso_scatter_plot)** - The lasso tool is used to select and deselect points on a graph.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/lasso_scatter_plot) as well. | <img width="2000"/>![lasso_scatter](https://user-images.githubusercontent.com/37275728/182579749-83b1d6c5-e943-4068-bb1d-51b1b8c5ff40.gif)
**[Histogram filtering](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/filter_histogram)** - Allows selection or deselection of bins on the histogram by moving one of the slider handles.<br><br> Check out the [Python implementation](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/filter_histogram) as well. | <img width="2000"/>![histogram](https://user-images.githubusercontent.com/37275728/182579743-b68b169f-d24b-470d-8a12-2f9fc3e2783d.gif)
    
## How to Contribute

We encourage contributions that enhance the repository's value. To contribute:

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

## License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=djeada/Qt-Widgets&type=Date)](https://star-history.com/#djeada/Qt-Widgets&Date)
