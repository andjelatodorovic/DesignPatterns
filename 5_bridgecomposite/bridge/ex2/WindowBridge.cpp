/* primer iz knjige GoF, Gang of Four:
   Gamma, E, Helm, R, Johnson, R, Vlissides, J: Design Patterns, page 151. Addison-Wesley, 1995 */
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

typedef int Coord;

class Window;

/* View.h - neki kontejner za sadrzaj */
class View {
private:
    string m_contents;
public:
    View(string contents) : m_contents(contents) {}
    void DrawOn(Window *window) { cout << "View.DrawOn: " << m_contents << endl; }
};
/* neke komponente grafickog sistema koje necemo da definisemo */
/* Display.h */
class Display {};
/* Drawable.h */
class Drawable {};
/* GC.h */
class GC {};
/* HPS.h */
class HPS {};
/* Point.h */
class Point {
public:
    int x, y;
    int X() const { return x; }
    int Y() const { return y; }
};

typedef Point PPOINTL;

class WindowImp;
class WindowSystem;
class WindowSystemFactory;

/* Window.h - apstrakcija, ima dodeljen view ciji sadrzaj prikazuje */
class Window {
public:
    Window(View* contents) : _contents(contents) { _imp = NULL; }
    // requests handled by window
    virtual void DrawContents() { cout << "Window::DrawContents()" << endl ; }
    virtual void Open() {}
    virtual void Close() {}
    virtual void Iconify() {}
    virtual void Deiconify() {}
    // requests forwarded to implementation
    virtual void SetOrigin(const Point& at) {}
    virtual void SetExtent(const Point& extent) {}
    virtual void Raise() {}
    virtual void Lower() {}
    virtual void DrawLine(const Point&, const Point&) {}
    virtual void DrawRect(const Point&, const Point&);
    virtual void DrawPolygon(const Point[], int n) {}
    virtual void DrawText(const char*, const Point&) {}
protected:
    WindowImp* GetWindowImp();
    View* GetView() { return _contents; }
private:
    WindowImp* _imp;
    View* _contents; // the window's contents

};

/* WindowImp.h - implementor, sadrzi metode kojima mozemo da crtamo slike, linije, tekst na
   grafickom sistemu datog operativnog sistema */
class WindowImp {
public:
    virtual void ImpTop() = 0;
    virtual void ImpBottom() = 0;
    virtual void ImpSetExtent(const Point&) = 0;
    virtual void ImpSetOrigin(const Point&) = 0;
    virtual void DeviceRect(Coord, Coord, Coord, Coord) = 0;
    virtual void DeviceText(const char*, Coord, Coord) = 0;
    virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
    // lots more functions for drawing on windows...
protected:
    WindowImp() {}
};

/* Win10WindowImp.h konkretan implementor za Window 10 graficki sistem */
class Win10WindowImp : public WindowImp {
public:
    Win10WindowImp() {}
    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    virtual void ImpTop() {}
    virtual void ImpBottom() {}
    virtual void ImpSetExtent(const Point&) {}
    virtual void ImpSetOrigin(const Point&) {}
    virtual void DeviceText(const char*, Coord, Coord) {}
    virtual void DeviceBitmap(const char*, Coord, Coord) {}
    // remainder of public interface...
private:
    // lots of X window system-specific state, including:
    Display* _dpy;
    Drawable _winid; // window id
    GC _gc; // window graphic context
    void XDrawRectangle(Display *display, Drawable winid, GC gc, Coord x, Coord y, int w, int h) {
    }
};

/* XOSWindowImp.h - konkretan implementor za X OS graficki sistem */
class XOSWindowImp : public WindowImp {
public:
    enum GPI_STATUS { GPI_ERROR };
    XOSWindowImp() {}
    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    virtual void ImpTop() {}
    virtual void ImpBottom() {}
    virtual void ImpSetExtent(const Point&) {}
    virtual void ImpSetOrigin(const Point&) {}
    virtual void DeviceText(const char*, Coord, Coord) {}
    virtual void DeviceBitmap(const char*, Coord, Coord) {}
private:
    // lots of PM window system-specific state, including:
    HPS _hps;
    bool GpiBeginPath(HPS hps, long long x) {}
    bool GpiSetCurrentPosition(HPS hps, Point *point) {}
    GPI_STATUS GpiPolyLine(HPS hps, long long x, Point *point) {}
    bool GpiEndPath(HPS hps) {}
    void GpiStrokePath(HPS hps, long long x, long long y) {}
};

/* pomocu ovog makroa mozemo da konfigurisemo koji konkretan implementor ce biti koristen */
#define WIN_10

/* WindowSystem.h - graficki sistem, singleton fabrika implementacije grafickog sistema
   pomocu makroa WIN_10 i X_OS mozemo da kontrolisemo koju implementaciju zelimo da koristimo */
class WindowSystem {
private:
    WindowSystem() {}
    WindowSystem(const WindowSystem &winSystem) {}
    WindowSystem& operator=(const WindowSystem &winSystem) {}
public:
    friend class WindowSystemFactory;
    WindowImp* MakeWindowImp() {
        cout << "WindowSystem::MakeWindowImp()" << endl;
        #ifdef WIN_10
            static Win10WindowImp windowImp;
        #endif // WIN_10
        #ifdef X_OS
            static XOSWindowImp windowImp;
        #endif // X_OS

        return (WindowImp*) &windowImp;
    }
};

/* WindowSystemFactory.h - singleton fabrika grafickog sistema */
class WindowSystemFactory {
private:
    WindowSystemFactory() {}
    WindowSystemFactory(const WindowSystemFactory &winFactory) {}
    WindowSystemFactory& operator=(const WindowSystemFactory &winFactory) {}
public:
    static WindowSystem& Instance() {
        static WindowSystem windowSystem;
        return windowSystem;
    }
};

WindowImp* Window::GetWindowImp () {
    cout << "Window::GetWindowImp() " << endl;
    if (_imp == 0) {
        _imp = WindowSystemFactory::Instance().MakeWindowImp();
    }
    return _imp;
}


void Window::DrawRect (const Point& p1, const Point& p2) {
    cout << "DrawRect((" << p1.X() << ", " << p1.Y() << "), (" << p2.X() << ", " << p2.Y() << "))" << endl;
    WindowImp* imp = GetWindowImp();
    imp->DeviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
}
/* ApplicationWindow.h - rafinirane apstrakcije, prozor za aplikacije */
class ApplicationWindow : public Window {
public:
    // ...
    virtual void DrawContents();
};
void ApplicationWindow::DrawContents () {
    GetView()->DrawOn(this);
}
/* IconWindow.h - rafinirane apstrakcije, prozor za ikone */
class IconWindow : public Window {
public:
    IconWindow(View* view): Window(view) { _bitmapName = NULL; }
    // ...
    virtual void DrawContents();
private:
    const char* _bitmapName;
};
void IconWindow::DrawContents() {
    cout << "IconWindow::DrawContents()" << endl;
    WindowImp* imp = GetWindowImp();
    if (imp != 0) {
        imp->DeviceBitmap(_bitmapName, 0.0, 0.0);
    }
}


void Win10WindowImp::DeviceRect (Coord x0, Coord y0, Coord x1, Coord y1) {
    int x = round(min(x0, x1));
    int y = round(min(y0, y1));
    int w = round(abs(x0 - x1));
    int h = round(abs(y0 - y1));
    XDrawRectangle(_dpy, _winid, _gc, x, y, w, h);
}



void XOSWindowImp::DeviceRect (Coord x0, Coord y0, Coord x1, Coord y1) {
    Coord left = min(x0, x1);
    Coord right = max(x0, x1);
    Coord bottom = min(y0, y1);
    Coord top = max(y0, y1);
    PPOINTL point[4];
    point[0].x = left; point[0].y = top;
    point[1].x = right; point[1].y = top;
    point[2].x = right; point[2].y = bottom;
    point[3].x = left; point[3].y = bottom;
    if ((GpiBeginPath(_hps, 1L) == false) ||
        (GpiSetCurrentPosition(_hps, &point[3]) == false) ||
        (GpiPolyLine(_hps, 4L, point) == GPI_ERROR) ||
        (GpiEndPath(_hps) == false)) {
        // report error
    } else {
        GpiStrokePath(_hps, 1L, 0L);
    }
}



/* kreiramo instancu rafinirane apstrakcije i pozovemo metod da iscrta sadrzaj
   pomocu makroa kontrolisemo koju implementaciju / za koji graficki sistem zelimo da koristimo */
int main() {
    View *view = new View("Sadrzaj");
    Window *icon = new IconWindow(view);
    icon->DrawContents();

    return 0;
}
