# Qt-Widgets
Examples of programs that use Qt6 widgets.

## Core

<code>QObject</code> is perhaps the most significant class in the whole Qt ecosystem. It carries with it two enormously important mechanisms:
1. Slots and signals
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

## Collections And Algorithms

Qt has implemented a large number of containers and accompanying algorithms that correspond to STL containers and algorithms. Some have been deprecated, such as <code>qSort()</code>, so be careful to read the documentation before using them. This is due to the fact that it was created prior to the standardization of STL containers. Some features, like as the <code>contains()</code> function, were first added in C++20, about 30 years later.

So the obvious issue is whether you should use Qt's containers or STL. The ones from Qt are fully integrated into the Qt APIs, therefore compatibility is an important consideration. There is no obvious winner in terms of efficiency and performance, and both are viable options. The STL, on the other hand, would enable you to design logic independent of the GUI framework, making the transition to another technology much easier. 

## Widgets

<code>QWidgets</code> are used for "standard" GUI components like as buttons, checkboxes, drop down menus, and so on. Because widgets are inherited from <code>QObjects</code>, we also have signals/slots and a parent-child relationship. It is best to utilize them for standard user interface components and customize them with a subset of CSS known as QSS and so-called stylesheets. There is, however, an option of drawing them yourself using the <code>paintEvent()</code> method, however this may be difficult.

Description | Screenshot
---|---
**[QWidget Custom Painting](https://github.com/djeada/Qt-Widgets/tree/master/src/widgets/qwidget_custom_painting)** - To draw an arrow in the background, the method <code>paintEvent()</code> is overwritten. | ![](https://github.com/djeada/Qt-Widgets/blob/master/resources/qwidget_custom_painting.gif)

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

Two main classes allow us to implement custom graphics: QPainter</code> and QGraphicsView</code>.

<code>QPainter</code> is capable of allowing you to manipulate pixels on a widget. It is used when we overwrite a widget's <code>paintEvent()</code> method. It is capable of interacting with both <code>QBrush</code> and <code>QPen</code>. Fill is done using brushes, while outlines are done with pens. A brush can be styled, colored, gradiented, or textured.

With the painter you have an option to draw a:
- A Point
- A Line
- A Rectangle
- An Ellipse
- A Polygon

The graphics scene framework allows you to arrange your geometry in a tree of <code>QGraphicsItems</code> and easily manipulate its components. Whatever you do, it's always <code>QPainter</code> who does the drawing. It is just abstracted away. Because <code>QGraphicsItem</code> is not derived from <code>QObject</code>, you don't have the signals/slots and so on, however you may use <code>QGraphicsObject</code> if you require them. The standard graphics item is more lightweight and includes certain additional features not provided by the widgets API. Similar to how there are standard widgets, there are a few basic graphics elements such as lines, rectangles, and so on. For everything unique, you must implement your own painting using <code>QPainter</code>, exactly like with widgets.

If your geometry is simple and does not require interactive and hierarchical features, you should use <code>QPainter</code> directly. Use <code>QGraphicsView</code> for anything complex and interactive. 

## Files

## Networking 

## Concurrent Computing 

## Plots

## Other
