/*
 * File: qgwindow.h
 * ----------------
 *
 * @version 2018/06/25
 * - initial version
 */

#ifndef _qgwindow_h
#define _qgwindow_h

#include <string>
#include <QLayout>
#include <QApplication>
#include <QMainWindow>
#include <QRect>
#include "gtypes.h"
#include "point.h"
#include "qgborderlayout.h"
#include "qgcanvas.h"
#include "qginteractor.h"

// set up Qt for gui stuff
void initializeQt();

// global function for starting the app
void startEventLoop();

// forward declaration
class QGWindow;

// Internal class; not to be used by clients.
class _Q_Internal_Window : public QMainWindow {
    Q_OBJECT

public:
    _Q_Internal_Window(QGWindow* window, QWidget* parent = nullptr);

private:
    QHBoxLayout _northLayout;
    QHBoxLayout _southLayout;
    QHBoxLayout _centerLayout;
    QHBoxLayout _middleLayout;
    QVBoxLayout _eastLayout;
    QVBoxLayout _westLayout;
    QVBoxLayout _overallLayout;
    QGWindow* _qgwindow;

    friend class QGWindow;
};

/*
 * ...
 */
class QGWindow {
public:
    QGWindow(double width = 0, double height = 0, bool visible = true);
    virtual ~QGWindow();
    void add(QGInteractor* interactor);
    void addToRegion(QGInteractor* interactor, const std::string& region = "Center");

    /*
~   clear
    compareToImage
    draw***
    fill***
    getColor
    getGObjectAt
    setColor
    */

    void clear();
    void clearCanvas();
    void center();
    void close();
    void draw(QGObject* obj);
    void draw(QGObject& obj, double x, double y);
    void draw(QGObject* obj, double x, double y);
    void drawImage(const std::string& filename, double x = 0, double y = 0);
    void drawLine(const GPoint& p0, const GPoint& p1);
    void drawLine(double x0, double y0, double x1, double y1);
    void drawOval(const GRectangle& bounds);
    void drawOval(double x, double y, double width, double height);
    GPoint drawPolarLine(const GPoint& p0, double r, double theta);
    GPoint drawPolarLine(double x0, double y0, double r, double theta);
    void drawPixel(double x, double y);
    void drawPixel(double x, double y, int color);
    void drawPixel(double x, double y, const std::string& color);
    void drawPolygon(std::initializer_list<double> coords);
    void drawPolygon(std::initializer_list<GPoint> points);
    void drawRect(const GRectangle& bounds);
    void drawRect(double x, double y, double width, double height);
    void drawString(const std::string& text, double x, double y);
    void fillOval(const GRectangle& bounds);
    void fillOval(double x, double y, double width, double height);
    void fillPolygon(std::initializer_list<double> coords);
    void fillRect(const GRectangle& bounds);
    void fillRect(double x, double y, double width, double height);

    // TODO: get/setCanvasSize,width,height
    // TODO: get/setColor, background, linewidth, font

    double getCanvasHeight() const;
    GDimension getCanvasSize() const;
    double getCanvasWidth() const;
    std::string getColor() const;
    int getColorInt() const;
    std::string getFillColor() const;
    int getFillColorInt() const;
    QGObject* getQGObject(int index) const;
    QGObject* getQGObjectAt(double x, double y) const;
    int getQGObjectCount() const;
    Point getLocation() const;
    double getHeight() const;
    double getLineWidth() const;
    static double getScreenHeight();
    static GDimension getScreenSize();
    static double getScreenWidth();
    GDimension getSize() const;
    std::string getTitle() const;
    double getWidth() const;
    double getX() const;
    double getY() const;
    bool inBounds(double x, double y) const;
    bool inCanvasBounds(double x, double y) const;
    bool isOpen() const;
    bool isResizable() const;
    bool isVisible() const;
    void pack();
    void remove(QGObject* obj);
    void remove(QGObject& obj);
    void remove(QGInteractor* interactor);
    void removeFromRegion(QGInteractor* interactor, const std::string& region);
    void repaint();
    void requestFocus();
    void setCanvasHeight(double height);
    void setCanvasSize(double width, double height);
    void setCanvasSize(const GDimension& size);
    void setCanvasWidth(double width);
    void setColor(int color);
    void setColor(const std::string& color);
    void setFillColor(int color);
    void setFillColor(const std::string& color);
    void setFont(const std::string& font);
    void setLineWidth(double lineWidth);
    void setLocation(double x, double y);
    void setLocation(const GPoint& p);
    void setLocation(const Point& p);
    void setResizable(bool resizable);
    void setSize(double width, double height);
    void setSize(const GDimension& size);
    void setTitle(const std::string& title);
    void setVisible(bool visible);
    void setWindowTitle(const std::string& title);
    void setX(double x);
    void setY(double y);
    void toBack();
    void toFront();

    // not to be called by students
    static QMainWindow* getLastWindow();

    // TODO: pause

private:
    static QApplication* _app;
    static _Q_Internal_Window* _lastWindow;

    void ensureCanvas();
    void initializeQGObject(QGObject* obj, bool filled = false);

    _Q_Internal_Window _qwindow;
    QGCanvas* _canvas;
    std::string _color;
    std::string _fillColor;
    std::string _font;
    int _colorInt;
    int _fillColorInt;
    double _lineWidth;
    bool _resizable;

    friend class QGInteractor;
    friend class _Q_Internal_Window;
    friend void initializeQt();
    friend void startEventLoop();
};

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#endif // _qgwindow_h
