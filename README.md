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

The goal of this repository is to gather a large number of reusable Qt widgets that may be used in any application.
By doing so, we avoid having to reinvent the wheel every time we start a new project and can instead focus on adjustments and revisions rather than starting from scratch.

## Requirements

For C++ projects you will need:

* C++14
* CMake 3.10+
* Qt6

For Python projects you will need:
* Python 3.10+
* Whatever library is mentioned in the project's requirements.txt file. 

## Compilation

### Qt Creator IDE

To create the project, open the appropriate *CMakeLists.txt* file in Qt Creator.

### Terminal

Set the environment variable "*CMAKE PREFIX PATH*" to the Qt6 installation path.

Open the terminal in the project directory and use the following commands:

#### Windows:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ start ./Qt.project_name.sln

#### Linux/macOS:

    $ mkdir build
    $ cd build
    $ cmake -GNinja ..
    $ ninja ../project_name

### PyQt

The recommended approach to launch PyQT projects is to use <code>virtualenv</code>:

    $ virtualenv env
    $ source env/bin/activate
    $ pip install -r requirements.txt
    $ python main.py
    
Use the following snippet to convert *.ui* files to *.py* scripts:

    from PyQt6 import uic
  
    with open("source.ui") as ui_file:
        with open("output_ui.py","w") as py_ui_file:
            uic.compileUi(ui_file,py_ui_file)

## Content

### Core

<code>QObject</code> is perhaps the most significant class in the whole Qt ecosystem. It carries with it two enormously important mechanisms:
1. Slots and signals;
2. Parent-child relationship. 

When subclassing <code>QObject</code>, you must include the <code>Q_OBJECT</code> macro in the declaration. 

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

Description | Screenshot
---|---
**[Children Generator](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/children_generator)** - Example of parent-child relationship in Qt. The generator may be used to create and delete children on the fly. When the generator instance is destroyed, all of its children are also destroyed.| <img width="2000"/>![](https://user-images.githubusercontent.com/37275728/174343131-44e1644d-2188-42c0-9b86-d6d6ae9e9818.gif)
**[Custom Signal and Slots](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/custom_signal_slots)** - A slot is just a standard method that may be connected to a signal. Many slots can be connected to a single signal. A signal is just a value that may be emitted by any function. When the signal is emitted, the value emitted by the signal is passed as a parameter to all associated slots.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/core/python/custom_signal_slots">Python</a> implementation as well.|![custom_signal_slots](https://user-images.githubusercontent.com/37275728/174352043-88d09439-d504-4ffe-802b-555a5fe669d8.gif)
**[Smart Pointers](https://github.com/djeada/Qt-Widgets/tree/master/src/core/smart_pointers)** - A smart pointer is an abstract data type that has all of the properties of a raw pointer plus automated garbage collection. Qt featured smart pointers long before they were included in C++ standard. These are also used in some of the projects. However, raw pointers are typically used for <code>QObjects</code> since they utilise a parent-child model to manage all issues related to the objects life cycle.|![smart_pointers](https://user-images.githubusercontent.com/37275728/174352307-5e5a7333-6cb3-4d16-87d7-ffe48cac5bcf.gif)
**[QVariant and QMetaType](https://github.com/djeada/Qt-Widgets/tree/master/src/core/cpp/qvariant_and_qmetatype)** - The <code>QVariant</code> class serves as a union for the most commonly used Qt data types. Because C++ prohibits unions from containing types with non-default constructors or destructors, the majority of useful Qt classes cannot be used in raw unions. The type is registered via the <code>Q_DECLARE_METATYPE(Type)</code> macro, so that <code>QMetaType</code> can recognize this type. <code>Q_DECLARE_METATYPE</code> expects a class or struct to contain a default constructor, a copy constructor, and a public destructor.|![qvariant_and_qmetatype](https://user-images.githubusercontent.com/37275728/174352447-56258e05-1edf-4073-918b-20afa8784f42.gif)

### Collections And Algorithms

Qt has implemented a large number of containers and accompanying algorithms that correspond to STL containers and algorithms. Some have been deprecated, such as <code>qSort()</code>, so be careful to read the documentation before using them. This is due to the fact that it was created prior to the standardization of STL containers. Some features, like as the <code>contains()</code> function, were first added in C++20, about 30 years later.

So the obvious issue is whether you should use Qt's containers or STL. The ones from Qt are fully integrated into the Qt APIs, therefore compatibility is an important consideration. There is no obvious winner in terms of efficiency and performance, and both are viable options. The STL, on the other hand, would enable you to design logic independent of the GUI framework, making the transition to another technology much easier. 

Description | Screenshot 
---|---
**[QList](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist)** - <code>QList</code> is a generic container class in Qt. It keeps a list of values and allows for rapid index-based access as well as quick insertions and deletions. Despite the fact that it is implemented as an array-list, it has very fast prepends and appends. <code>QList</code> is the ideal type to utilize for most purposes. This example shows how to initialize, display, and find and delete the list's elements.<br><br> A quick remark for Python programmers: Python lists cannot be serialized using <code>QDataStream</code>, whereas <code>QList</code> can be serialized using C++. When porting the C++ code, <code>QList</code> cannot always be replaced with Python list.| <img width="2000"/>![qlist](https://user-images.githubusercontent.com/37275728/174391054-adbe0a88-456d-4ed3-9ee6-9ef6db12b0f0.gif)
**[QList vs QVector](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist_vs_qvector)** - <code>QVector</code> is very similar in use to <code>QList</code>. One distinction is that items of <code>QVector</code> are always stored in a contignous way in memory, whereas <code>QList</code> does not. | ![qlist_vs_qvector](https://user-images.githubusercontent.com/37275728/174391027-7851c137-8462-4ba3-81cb-8eb313e2fb0a.gif)
**[QSet](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qset)** - <code>QSet</code> assures the uniquness of it's elements. Although the order in which the elements are inserted is lost. | ![qset](https://user-images.githubusercontent.com/37275728/174390876-de5497cb-77b1-43a6-a7d1-b0f6c966acad.gif)
**[QMap](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qmap)** - The <code>QMap</code> class is a template class that offers a dictionary based on a red-black tree. <code>QMap<Key, T></code> is a generic container class in Qt. It holds (key, value) pairs and allows for quick access to the value associated with a key. Use it anytime you don't want numeric (or ordered) indices. | ![qmap](https://user-images.githubusercontent.com/37275728/174390916-7f6786b2-ef60-4075-af4c-0a977f2a1be0.gif)

### Widgets

<code>QWidgets</code> are used for "standard" GUI components like as buttons, checkboxes, drop down menus, and so on. Because widgets are inherited from <code>QObjects</code>, we also have signals/slots and a parent-child relationship. It is best to utilize them for standard user interface components and customize them with a subset of CSS known as QSS and so-called stylesheets. There is, however, an option of drawing them yourself using the <code>paintEvent()</code> method, however this may be difficult.

Description | Screenshot
---|---
 **[Message Box](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/message_box)** - The <code>QMessageBox</code> class provides a modal dialog for informing the user or asking for and receiving an answer from the user. A message box displays a primary message to notify the user to an issue, an informative explanation to better clarify the message, or a query to the user. Furthermore, the message box can display an icon as well as ordinary buttons for receiving user answers.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/message_box">Python</a> implementation as well. | <img width="2000"/>![message_box](https://user-images.githubusercontent.com/37275728/174391108-b9f9a7fe-c43c-4571-83bf-91148c276ca3.gif)
**[Custom Tooltip](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/custom_tooltip)** - When you hover your cursor over a widget, a tooltip will appear. Aside from conventional text, the tooltip may be styled with a subset of HTML.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/custom_tooltip">Python</a> implementation as well. | ![custom_tooltip](https://user-images.githubusercontent.com/37275728/174391265-8c4dc1db-4583-44f3-8057-b6c9a088deae.gif)
**[QWidget Custom Painting](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/custom_painting)** - To draw an arrow in the background, the method <code>paintEvent()</code> is overwritten. The majority of the drawing tasks required by GUI programs are handled by very efficient algorithms in <code>QPainter</code>. It can draw anything from fundamental graphical primitives like point, line, rectangle, ellipse, and polygon to more complex forms like vector routes.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/custom_painting">Python</a> implementation as well. | ![qwidget_custom_painting](https://user-images.githubusercontent.com/37275728/174391245-3f98c4e9-68db-4ced-9cc7-498c004ea945.gif)
**[Status Bar](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/status_bar)** - The <code>QStatusBar</code> class implements a horizontal bar for displaying status information. We use a timer to regulate how long it takes the bar to reach 100%. We use three buttons to control the bar: start, stop, and reset.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar">Python</a> implementation as well. | ![status_bar](https://user-images.githubusercontent.com/37275728/174391150-776450f1-e6f2-4170-b5fe-ae10eaea830a.gif)
**[Switch](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/switch_button)** - The <code>QStatusBar</code> class implements a horizontal bar for displaying status information. We use a timer to regulate how long it takes the bar to reach 100%. We use three buttons to control the bar: start, stop, and reset.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/switch_button">Python</a> implementation as well. | ![switch](https://user-images.githubusercontent.com/37275728/181903593-ae6d136b-086c-49ce-8d67-1fa14ce5b3c3.gif)
**[Double range slider](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/cpp/double_range_slider)** - The <code>QStatusBar</code> class implements a horizontal bar for displaying status information. We use a timer to regulate how long it takes the bar to reach 100%. We use three buttons to control the bar: start, stop, and reset.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/double_range_slider">Python</a> implementation as well. | ![double_range_slider](https://user-images.githubusercontent.com/37275728/181903584-a58a4afc-85f3-4f3c-a05d-8f5067635d41.gif)

### MVC

What is Model-View-Controler?

It is a common method of separating concerns about the presentation and modification of dynamic content in graphical applications:
  
* Model: It is concerned with connecting us to the data source. The data may already be in memory, or it may be requested from a database or read from a file. After receiving the necessary information, it organizes it into cells with potentially numerous rows and columns. It chooses what should and should not be displayed. Finally, the model provides an API for accessing, modifying, inserting, and removing cells. It determines what data interactions are permitted and how they are carried out.
* View: It receives the model's data. The data already has a suitable structure, and the view is aware of the cells, rows, and columns that model has prepared. It is simply concerned with how those elements will be displayed. It selects the appropriate font, colors, spacing between elements, slider bars, and so forth.
* Controller: The controller allows the user to interact with the data displayed in the view. The standard method is to collect user events such as keystrokes and mouse clicks and then call the relevant function from the model API. 

How to implement it using Qt framework?

1. <code>QStandardItemModel</code> is a simple implementation that is not suitable for large or complex models. It is designed for simplicity of use rather than high performance. It is distinguished by a shallow learning curve.

2. The separation of real data storage and organization (which must occur in the model and the related proxy models) and presentation is an obvious benefit of <code>QAbstractItemModel</code> abstraction. Allows for complete customisation. It requires a thorough understanding of its inner workings.

Description | Screenshot 
---|---
**[String List Model](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/string_list_model)** - The <code>QStringListModel</code> class provides a simple model that stores a list of strings. It is suitable for use with a <code>QListView</code> or <code>QComboBox</code>.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/string_list_model">Python</a> implementation as well. | <img width="2000"/>![string_list_model](https://user-images.githubusercontent.com/37275728/174391715-d60c2382-ec92-490d-9084-03aa65315632.gif)
**[Tree Model](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/tree_model)** - Simple implementation of a tree model. The items are stored using hierarchical relationships. It is suitable for use with a <code>QTreeView</code>.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/tree_model">Python</a> implementation as well. | ![tree_model](https://user-images.githubusercontent.com/37275728/174391748-bf6efd6b-3bec-4aea-89c8-66bade3f62f6.gif)
**[Reorderable Tree View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/reorderable_treeview)** - Extending tree model to allow reordering of items. Reordering is triggered trough drag and drop mechanis in <code>QTreeView</code>. Selected item is moved with all its children to the new position.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/reorderable_treeview">Python</a> implementation as well. | ![reorderable_tree_view](https://user-images.githubusercontent.com/37275728/174391785-9b95cd28-19ea-40c5-a5c6-de90440b612c.gif)
**[Custom Item Delegate](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/item_delegate)** - Custom item delegate for qListView/qListView. The item delegate is in charge of painting the items in the view. It is important to note that it can paint the items in all sorts of ways depending on their current role. So, everytime a user clicks on an item, you may change the role from display to edit and render a whole different widget. The examples show how to position the text and style it, as well as how to paint custom shapes and render custom widgets instead of text.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/item_delegate">Python</a> implementation as well. | ![custom_delegate](https://user-images.githubusercontent.com/37275728/174391798-1e9971bf-91df-42d6-88d1-30f6ba526fe5.gif)
**[Matrix View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/matrix_view)** - Display an array of arrays in a form of a table. Allow the user to define the precision of the floating point numbers. <br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/matrix_view">Python</a> implementation as well. | ![custom_delegate](https://user-images.githubusercontent.com/37275728/182579831-a277a892-cc9c-43e5-90f1-28def863b4c4.gif)
**[File Directory Tree View](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/file_directory_treeview)** - Extending tree model to allow reordering of items. Reordering is triggered trough drag and drop mechanis in <code>QTreeView</code>. Selected item is moved with all its children to the new position.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/file_directory_treeview">Python</a> implementation as well. | ![file_dir_treeview](https://user-images.githubusercontent.com/37275728/174501389-3d9c8bef-79a7-4401-9011-91875fa74ab0.gif)
**[Crypto Ranking](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/crypto_ranking)** - Extending tree model to allow reordering of items. Reordering is triggered trough drag and drop mechanis in <code>QTreeView</code>. Selected item is moved with all its children to the new position.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/crypto_ranking">Python</a> implementation as well. | ![crypto_ranking](https://user-images.githubusercontent.com/37275728/174501398-a7f470c7-76ca-4e49-818c-d559bc3e50c6.gif)
**[Emoji Picker](https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/cpp/emoji_picker)** - Extending tree model to allow reordering of items. Reordering is triggered trough drag and drop mechanis in <code>QTreeView</code>. Selected item is moved with all its children to the new position.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/mvc/python/emoji_picker">Python</a> implementation as well. | ![emoji_picker](https://user-images.githubusercontent.com/37275728/174501411-13046047-afcf-4910-a0bc-832c24cae30f.gif)
  
### Graphics

Two main classes allow us to implement custom graphics: <code>QPainter</code> and <code>QGraphicsView</code>.

<code>QPainter</code> is capable of allowing you to manipulate pixels on a widget. It is used when we overwrite a widget's <code>paintEvent()</code> method. It is capable of interacting with both <code>QBrush</code> and <code>QPen</code>. Fill is done using brushes, while outlines are done with pens. A brush can be styled, colored, gradiented, or textured.

With the painter you have an option to draw a:
- A Point;
- A Line;
- A Rectangle;
- An Ellipse;
- A Polygon.

The graphics scene framework allows you to arrange your geometry in a tree of <code>QGraphicsItems</code> and easily manipulate its components. Whatever you do, it's always <code>QPainter</code> who does the drawing. It is just abstracted away. Because <code>QGraphicsItem</code> is not derived from <code>QObject</code>, you don't have the signals/slots and so on, however you may use <code>QGraphicsObject</code> if you require them. The standard graphics item is more lightweight and includes certain additional features not provided by the widgets API. Similar to how there are standard widgets, there are a few basic graphics elements such as lines, rectangles, and so on. For everything unique, you must implement your own painting using <code>QPainter</code>, exactly like with widgets.

If your geometry is simple and does not require interactive and hierarchical features, you should use <code>QPainter</code> directly. Use <code>QGraphicsView</code> for anything complex and interactive. 

Description | Screenshot 
---|---
**[Movable Image](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/movable_image)** - We'll make a scene, and the scene will be shown with the elements we'll be adding. The <code>QGraphicsView</code> object is a widget created in designer that is used to display the contents of a <code>QGraphicsScene</code>. A moveable object may be readily spawned on a graphics scene. Because the scene retains track of its items, deletion is not an issue. You can change the item's appearance by using the paint event.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/movable_image">Python</a> implementation as well. | <img width="2000"/>![movable_image](https://user-images.githubusercontent.com/37275728/174391871-c78ae82c-7982-4d2d-8a35-5ae565cfdde1.gif)
**[Image Cropper](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/image_cropper)** - <code>QWidget</code> has been subclassed in order to receive image drops and show them with an elipsoidal crop. When the widget's width and height are equal, the crop has a circular form.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/image_cropper">Python</a> implementation as well. | ![image_cropper](https://user-images.githubusercontent.com/37275728/174391888-f4338633-402b-4298-9bf4-9adfea5869f5.gif)
**[Transformations](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/transformations)** - The <code>scale()</code> function may scale the coordinate system by a specified offset, the <code>rotate()</code> function can rotate it clockwise, and the <code>translate()</code> function can translate it (i.e. add a given offset to the points). It is important to note that any transformation is a matrix multiplication. As a result, the order in the code should be inverted to the order in which the transformations should be applied.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/transformations">Python</a> implementation as well. | ![transformations](https://user-images.githubusercontent.com/37275728/174391909-bd03d417-b0c3-4297-adea-1adf624bf41f.gif)
**[Moving balls](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/moving_balls)** - <code>QGraphicView</code> is a camera in Qt's universe, while <code>QGraphicScene</code> is a movie scene. In the actual world, the camera has one coordinate system and the scene has another; they do not match, but there is a transformation that connects them. When actors move in the film, their size on the scene may change while their real size stays constant. In the example, we use coloured balls to demonstrate how to control the position of an item on the scene.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/python/moving_balls">Python</a> implementation as well. | ![moving_balls](https://user-images.githubusercontent.com/37275728/174391947-8f427876-7c9e-43fb-98a2-bae13eefc10f.gif)

### Files
    
<code>QFile</code> is an I/O device that allows you to read and write text and binary files and resources. A <code>QFile</code> can be used alone or, more easily, in conjunction with a <code>QTextStream</code> or <code>QDataStream</code>.

Description | Screenshot 
---|---
**[File Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/file_info)** - Display informations about files. Get list of files in a given directory and all its subdirectories. Use <code>QFileInfo</code> to get the file's name, size, and other data. Unfortunately, <code>QFileInfo</code> does not use many static methods, and you must create an object to access most of its features. We generate a large number of temporary objects that are destroyed immediately after usage.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/file_info">Python</a> implementation as well. | <img width="2000"/>![file_info](https://user-images.githubusercontent.com/37275728/174392052-f02d2d46-14aa-4d80-a255-6dbe5cef93b3.gif)
**[File Operations](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/file_operations)** - Manipulate files, by copying, moving, or deleting them. Create a temporary directory, and fill it with text files. If any error occurs, display it in on the console.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/file_operations">Python</a> implementation as well. | ![file_operations](https://user-images.githubusercontent.com/37275728/174392152-ffb056b4-857a-4dd4-a788-c5317d101cea.gif)
**[Storage Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/storage_info)** - Display informations about storage, like free space, total space, and used space. Show mounted volumes, and their names.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/storage_info">Python</a> implementation as well. | ![storage_info](https://user-images.githubusercontent.com/37275728/174392119-78714676-d6b6-4510-846c-783e6ce44947.gif)
**[JSON Serialization](https://github.com/djeada/Qt-Widgets/tree/master/src/files/cpp/json_serialization)** - Serialize an object of a custom class to a JSON file. Deserialize a JSON file to an object of a custom class. Check if the objects are the same.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/files/python/json_serialization">Python</a> implementation as well. | ![json_serialization](https://user-images.githubusercontent.com/37275728/174392103-9f5c0775-fc94-4865-a337-eed7283ddc40.gif)
  
 
### Network

### Concurrent Computing 

Description | Screenshot 
---|---
**[Spawn Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_thread)** - Spawn a thread and run a function in it. Use internal Qt framework for managing threads.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar">Python</a> implementation as well. | <img width="2000"/>![spawn_thread](https://user-images.githubusercontent.com/37275728/174501495-8c326dad-939a-4269-b212-85023a292c80.gif)
**[Gui Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/gui_thread.cpp)** - Ensure the GUI's responsiveness while the threads perform their tasks. When worker threads finish their work, the view is updated to show the results of their work. When the worker thread completes its task, <code>QFutureWatcher</code> emits the <code>finished()</code> signal. Regrettably, there is currently no support for clearing the watcher. One solution is to spawn the watchers along with the threads on the fly.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar">Python</a> implementation as well. | ![gui_thread](https://user-images.githubusercontent.com/37275728/174501505-fad1d705-4ea5-488e-8432-4af6383bd05b.gif)
**[Spawn Process](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_process)** - The <code>QProcess</code> allows you to spawn new processes, connect to their input/output/error pipes, and obtain their return codes. Spawn a single process and wait for it to finish.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar">Python</a> implementation as well. | 
**[CMD Interface](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/cmd_interface)** - A simple command line interface that allows you to execute commands as if they were typed in the console.<br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/python/status_bar">Python</a> implementation as well. | ![cmd_interface](https://user-images.githubusercontent.com/37275728/174501513-8103dd52-7310-448d-89c6-cdee96b4141d.gif)

### Plots

Qt applications may be used to display simple static plots as well as build visually appealing, interactive dashboards. Aside from the native QtCharts library, Qt offers also support for the widely used Matplotlib. Any modern plotting library may, however, be used (with little effort).
  
Description | Screenshot 
---|---
**[Simple plot](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/plot_widget)** - Embed Matplotlib canvas into a Qt widget. Matplotlib provides several options for constructing useful, personalized, and beautiful plots to show data in the simplest and most effective way possible. All of the standard plotting options are accessible. A tool bar with dynamic functionality is also included. <br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/plot_widget">Python</a> implementation as well. | <img width="2000"/>![plot](https://user-images.githubusercontent.com/37275728/182579732-a0a52499-6400-4fa0-9f22-a8e65c9f55f3.gif)
**[Lasso selection](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/lasso_scatter_plot)** - The lasso tool is used to select and deselect points on a graph. <br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/lasso_scatter_plot">Python</a> implementation as well. | ![lasso_scatter](https://user-images.githubusercontent.com/37275728/182579749-83b1d6c5-e943-4068-bb1d-51b1b8c5ff40.gif)
**[Histogram filtering](https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/filter_histogram)** - To select or deselect bins on the histogram, move one of the slider handles. <br><br> Check out the <a href="https://github.com/djeada/Qt-Widgets/tree/master/src/plots/matplotlib/filter_histogram">Python</a> implementation as well. | ![histogram](https://user-images.githubusercontent.com/37275728/182579743-b68b169f-d24b-470d-8a12-2f9fc3e2783d.gif)
    
### Other

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
