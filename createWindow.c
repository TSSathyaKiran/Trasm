#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

typedef struct {
    int X;
    int Y;
    int Width;
    int Height;
} entity;

int main()
{
    Display* MainDisplay = XOpenDisplay(0);
    Window RootWindow = XDefaultRootWindow(MainDisplay);

    int DefaultScreen = DefaultScreen(MainDisplay);
    GC Context = XDefaultGC(MainDisplay, DefaultScreen);
    
    int WindowX = 0;
    int WindowY = 0;
    int WindowWidth = 800;
    int WindowHeight = 600;
    int BorderWidth = 0;
    int WindowDepth = CopyFromParent;
    int WindowClass = CopyFromParent;
    Visual* WindowVisual = CopyFromParent;

    int AttributeValueMask = CWBackPixel | CWEventMask;
    XSetWindowAttributes WindowAttributes = {};
    WindowAttributes.background_pixel = 0x0C1D33;
    WindowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;

    Window MainWindow = XCreateWindow(MainDisplay, RootWindow, 
            WindowX, WindowY, WindowWidth, WindowHeight,
            BorderWidth, WindowDepth, WindowClass, WindowVisual,
            AttributeValueMask, &WindowAttributes);

    XSizeHints *hints = XAllocSizeHints();
  
    hints->flags = PMinSize | PMaxSize;
    hints->min_width = 800;
    hints->min_height = 600;
    hints->max_width = 800;
    hints->max_height = 600;
    
    XSetWMNormalHints(MainDisplay, MainWindow, hints);
    XFree(hints);

    XMapWindow(MainDisplay, MainWindow);

    XStoreName(MainDisplay, MainWindow, "TRASM");

    Atom WM_DELETE_WINDOW = XInternAtom(MainDisplay, "WM_DELETE_WINDOW", False);
    if(!XSetWMProtocols(MainDisplay, MainWindow, &WM_DELETE_WINDOW, 1)) {
        printf("Couldn't register WM_DELETE_WINDOW property \n");
    }


    entity Box = {};
    Box.Width = 15;
    Box.Height = 45;
    Box.X = WindowWidth/2 - Box.Width/2;
    Box.Y = WindowHeight/2 - Box.Height/2;
    XSetForeground(MainDisplay, Context, 0xffa60d); 
    XFillRectangle(MainDisplay, MainWindow, Context, Box.X, Box.Y, Box.Width, Box.Height);

    int StepSize = 5;

    int IsWindowOpen = 1;
    while(IsWindowOpen) {
        XEvent GeneralEvent = {};


        XNextEvent(MainDisplay, &GeneralEvent);

        switch(GeneralEvent.type) {
            case KeyPress:
            case KeyRelease:
            {
                XKeyPressedEvent *Event = (XKeyPressedEvent *)&GeneralEvent;
                if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_S))
                {
                    Box.Y += StepSize;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_W))
                {
                    Box.Y -= StepSize;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_D))
                {
                    Box.X += StepSize;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_A))
                {
                    Box.X -= StepSize;
                }
            } break;
        }

        XClearWindow(MainDisplay, MainWindow);
        XFillRectangle(MainDisplay, MainWindow, Context, Box.X, Box.Y, Box.Width, Box.Height);
    }
}