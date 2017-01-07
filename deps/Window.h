//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------

#ifndef WINDOW_H
#define WINDOW_H

#define WINSYSTEM // for Windows specific platform

#include "MugenEngine.h"

//------------------------------------------------------------------------------ Class Window
class Window
{
    public:
    // Setup
        Window();
        virtual ~Window();
        int init(const char* name, int screenW, int screenH, int scaleWin, int scaleFull, bool fullScreen, bool vsync);
        int done();

    // Render
        void beginRender();
        void endRender();

    // Manager
        void toggleFullScreen(int scale); // Toggle windowed to FullScreen : 0 = Max Zoom , -1 = Default Zoom
        void switchMonitor(int scale); // Switch monitor : 0 = Max Zoom, -1 Default Zoom
        void setMonitor(int monitor, int scale); // Select the Monitor : O = Max Zoom, -1 Default Zoom
        void setScale(int scale); // set Scale : 0 = Max Zoom, -1 Default Zoom
        void setWindow(ALLEGRO_DISPLAY * display, int adapter,bool isFullScreen, int scale);

        void setViewAtCenter(int scale); // Place the View in the center of Monitor by scale !
        int getMaxScale(); // Calculate max scaling factor !
        void pollMonitor(int adapter);

    // Accessor
        bool isFullScreen() const;
        ALLEGRO_DISPLAY * display();
        ALLEGRO_BITMAP * buffer();


        int screenW() const;
        int screenH() const;
        int centerX() const;
        int centerY() const;

        int scaleWin() const;
        int scaleFull() const;
        int viewX() const;
        int viewY() const;
        int viewW() const;
        int viewH() const;

        int currentMonitor(ALLEGRO_DISPLAY * display); // Find the current monitor where the window is !
        int currentMonitor() const; // return the current Monitor selected !
        int currentMonitorX() const;
        int currentMonitorY() const;
        int currentMonitorW() const;
        int currentMonitorH() const;

        // Mouse
        void getMouse(ALLEGRO_MOUSE_STATE * mouseState, float &xMouse, float &yMouse);


    // Debug
        int x() const;
        int y() const;

    protected:
        const char* _name;

        // Screen of Game
        int _screenW;
        int _screenH;

        // Windowed
        int _scaleWin;
        int _x;
        int _y;

        // FullScreen
        int _scaleFull;
        int _viewW;
        int _viewH;
        int _viewX;
        int _viewY;

        // Monitor
        int _currentMonitor;
        int _currentMonitorX;
        int _currentMonitorY;
        int _currentMonitorW;
        int _currentMonitorH;

        // View state
        bool _isFullScreen;
        bool _isMaxScale;
        bool _isVsync;

    private:
        ALLEGRO_DISPLAY *_windowDisplay = NULL;
        ALLEGRO_BITMAP *_windowBuffer = NULL;
};


#endif // WINDOW_H
