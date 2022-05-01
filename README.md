# Qt-Widgets
Examples of programs that use Qt6 widgets.

## Core

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
**[Children Generator](https://github.com/djeada/Qt-Widgets/tree/master/src/core/children_generator)** - Example of parent-child relationship in Qt. The generator may be used to create and delete children on the fly. When the generator instance is destroyed, all of its children are also destroyed. | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/children_generator.gif)
**[Custom Signal and Slots](https://github.com/djeada/Qt-Widgets/tree/master/src/core/custom_signal_slots)** - A slot is just a standard method that may be connected to a signal. Many slots can be connected to a single signal. A signal is just a value that may be emitted by any function. When the signal is emitted, the value emitted by the signal is passed as a parameter to all associated slots. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/custom_signal_slots.gif)
**[Smart Pointers](https://github.com/djeada/Qt-Widgets/tree/master/src/core/smart_pointers)** - A smart pointer is an abstract data type that has all of the properties of a raw pointer plus automated garbage collection. Qt featured smart pointers long before they were included in C++ standard. These are also used in some of the projects. However, raw pointers are typically used for <code>QObjects</code> since they utilise a parent-child model to manage all issues related to the objects life cycle. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/smart_pointers.gif)
**[QVariant and QMetaType](https://github.com/djeada/Qt-Widgets/tree/master/src/core/qvariant_and_qmetatype)** - The <code>QVariant</code> class serves as a union for the most commonly used Qt data types. Because C++ prohibits unions from containing types with non-default constructors or destructors, the majority of useful Qt classes cannot be used in raw unions. The type is registered via the <code>Q_DECLARE_METATYPE(Type)</code> macro, so that <code>QMetaType</code> can recognize this type. <code>Q_DECLARE_METATYPE</code> expects a class or struct to contain a default constructor, a copy constructor, and a public destructor.  | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qvariant_and_qmetatype.gif)

## Collections And Algorithms

Qt has implemented a large number of containers and accompanying algorithms that correspond to STL containers and algorithms. Some have been deprecated, such as <code>qSort()</code>, so be careful to read the documentation before using them. This is due to the fact that it was created prior to the standardization of STL containers. Some features, like as the <code>contains()</code> function, were first added in C++20, about 30 years later.

So the obvious issue is whether you should use Qt's containers or STL. The ones from Qt are fully integrated into the Qt APIs, therefore compatibility is an important consideration. There is no obvious winner in terms of efficiency and performance, and both are viable options. The STL, on the other hand, would enable you to design logic independent of the GUI framework, making the transition to another technology much easier. 

Description | Screenshot 
---|---
**[QList](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist)** - <code>QList</code> is a generic container class in Qt. It keeps a list of values and allows for rapid index-based access as well as quick insertions and deletions. Despite the fact that it is implemented as an array-list, it has very fast prepends and appends. <code>QList</code> is the ideal type to utilize for most purposes. Learn how to initialize, display, and find and delete the list's elements. | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qlist.gif)
**[QList vs QVector](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qlist_vs_qvector)** - <code>QVector</code> is very similar in use to <code>QList</code>. One distinction is that items of <code>QVector</code> are always stored in a contignous way in memory, whereas <code>QList</code> does not. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qlist_vs_qvector.gif)
**[QSet](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qset)** - <code>QSet</code> assures the uniquness of it's elements. Although the order in which the elements are inserted is lost. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qset.gif)
**[QMap](https://github.com/djeada/Qt-Widgets/tree/master/src/collections_and_algorithms/qmap)** - The <code>QMap</code> class is a template class that offers a dictionary based on a red-black tree. <code>QMap<Key, T></code> is a generic container class in Qt. It holds (key, value) pairs and allows for quick access to the value associated with a key. Use it anytime you don't want numeric (or ordered) indices. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qmap.gif)

## Widgets

<code>QWidgets</code> are used for "standard" GUI components like as buttons, checkboxes, drop down menus, and so on. Because widgets are inherited from <code>QObjects</code>, we also have signals/slots and a parent-child relationship. It is best to utilize them for standard user interface components and customize them with a subset of CSS known as QSS and so-called stylesheets. There is, however, an option of drawing them yourself using the <code>paintEvent()</code> method, however this may be difficult.

Description | Screenshot
---|---
 **[Message Box](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/message_box)** - The <code>QMessageBox</code> class provides a modal dialog for informing the user or asking for and receiving an answer from the user. A message box displays a primary message to notify the user to an issue, an informative explanation to better clarify the message, or a query to the user. Furthermore, the message box can display an icon as well as ordinary buttons for receiving user answers. | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/message_box.gif)
**[Custom Tooltip](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/custom_tooltip)** - When you hover your cursor over a widget, a tooltip will appear. Aside from conventional text, the tooltip may be styled with a subset of HTML.  | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/custom_tooltip.gif)
**[QWidget Custom Painting](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/qwidget_custom_painting)** - To draw an arrow in the background, the method <code>paintEvent()</code> is overwritten. The majority of the drawing tasks required by GUI programs are handled by very efficient algorithms in <code>QPainter</code>. It can draw anything from fundamental graphical primitives like point, line, rectangle, ellipse, and polygon to more complex forms like vector routes. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qwidget_custom_painting.gif)
**[Status Bar](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/qwidget_custom_painting)** - The <code>QStatusBar</code> class implements a horizontal bar for displaying status information. We use a timer to regulate how long it takes the bar to reach 100%. We use three buttons to control the bar: start, stop, and reset. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/status_bar.gif)

## MVC

What is Model-View-Controler?

It is a common method of separating concerns about the presentation and modification of dynamic content in graphical applications:

* Model: It is concerned with connecting to the data source. The data may already be in memory, or it may be requested from a database or read from a file. After receiving the necessary information, it organizes it into cells with potentially numerous rows and columns. It chooses what should and should not be displayed. Finally, the model provides an API for accessing, modifying, inserting, and removing cells. It determines what is allowed and how it is carried out. 
* View: It receives the model's data. The data already has a suitable structure, and the view is aware of the cells, rows, and columns that model has prepared. It is simply concerned with how those elements will be displayed. It selects the appropriate font, colors, spacing between elements, slider bars, and so forth.
* Controller: The controller allows the user to interact with the data displayed in the view. The standard method is to collect user events such as keystrokes and mouse clicks and then call the relevant function from the model API. 

How to implement it using Qt framework?

1. <code>QStandardItemModel</code> is a simple implementation that is not suitable for large or complex models. It is designed for simplicity of use rather than high performance. It is distinguished by a shallow learning curve.

2. The separation of real data storage and organization (which must occur in the model and the related proxy models) and presentation is an obvious benefit of <code>QAbstractItemModel</code> abstraction. Allows for complete customisation. It requires a thorough understanding of its inner workings.

## Graphics

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
**[Movable Image](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/movable_image)** - We'll make a scene, and the scene will be shown with the elements we'll be adding. The <code>QGraphicsView</code> object is a widget created in designer that is used to display the contents of a <code>QGraphicsScene</code>. A moveable object may be readily spawned on a graphics scene. Because the scene retains track of its items, deletion is not an issue. You can change the item's appearance by using the paint event. | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/movable_image.gif)
**[Image Cropper](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/image_cropper)** - <code>QWidget</code> has been subclassed in order to receive image drops and show them with an elipsoidal crop. When the widget's width and height are equal, the crop has a circular form.  | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/image_cropper.gif)
**[Transformations](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/transformations)** - The <code>scale()</code> function may scale the coordinate system by a specified offset, the <code>rotate()</code> function can rotate it clockwise, and the <code>translate()</code> function can translate it (i.e. add a given offset to the points). It is important to note that any transformation is a matrix multiplication. As a result, the order in the code should be inverted to the order in which the transformations should be applied. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/transformations.gif)
**[Moving balls](https://github.com/djeada/Qt-Widgets/tree/master/src/graphics/moving_balls)** - <code>QGraphicView</code> is a camera in Qt's universe, while <code>QGraphicScene</code> is a movie scene. In the actual world, the camera has one coordinate system and the scene has another; they do not match, but there is a transformation that connects them. When actors move in the film, their size on the scene may change while their real size stays constant. In the example, we use coloured balls to demonstrate how to control the position of an item on the scene. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/moving_balls.gif)

## Files
    
<code>QFile</code> is an I/O device that allows you to read and write text and binary files and resources. A <code>QFile</code> can be used alone or, more easily, in conjunction with a <code>QTextStream</code> or <code>QDataStream</code>.

Description | Screenshot 
---|---
**[File Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/file_info)** - ... | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/file_info.gif)
**[File Operations](https://github.com/djeada/Qt-Widgets/tree/master/src/files/file_operations)** - ... | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/file_operations.gif)
**[Storage Info](https://github.com/djeada/Qt-Widgets/tree/master/src/files/storage_info)** - ... | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/storage_info.gif)
**[JSON Serialization](https://github.com/djeada/Qt-Widgets/tree/master/src/files/json_serialization)** - ...  | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/json_serialization.gif)    
## Networking 

## Concurrent Computing 

Description | Screenshot 
---|---
**[Spawn Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_thread)** - ... | <img width=1000/>![](https://github.com/djeada/Qt-Widgets/blob/master/resources/spawn_thread.gif)
**[Gui Thread](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/gui_thread.cpp)** - Ensure the GUI's responsiveness while the threads perform their tasks. When worker threads finish their work, the view is updated to show the results of their work. When the worker thread completes its task, <code>QFutureWatcher</code> emits the <code>finished() </code>signal. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/gui_thread.gif)
**[Spawn Process](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/spawn_process)** - ... | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/spawn_process.gif)
**[CMD Interface](https://github.com/djeada/Qt-Widgets/tree/master/src/concurrent_computing/cmd_interface)** - ...  | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/cmd_interface.gif)
    
## Plots

Qt applications may be used to build visually appealing, interactive dashboards. Aside from the native QtCharts library, there is also support for the widely used Matplotlib. Any modern plotting library may, however, be used (with little effort).
    
## Other
