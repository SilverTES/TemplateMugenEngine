//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED


#include "Window.h"
#include <SFML/Window.hpp>

#define DEAD_ZONE 50

int const MAX_JOYSTICK(16);

class PlayerManager;

enum SNESButton
{
    PAD_UNDEFINED = 0,
    PAD_START,
    PAD_SELECT,
    PAD_UP,
    PAD_DOWN,
    PAD_LEFT,
    PAD_RIGHT,
    PAD_A,PAD_B,PAD_X,PAD_Y,
    PAD_L,PAD_R,
    MAX_BUTTONS
};


struct Button
{
    Button(int id = 0, int idKey = 0, int idJoy = 0, int idStick = 0, int idAxis = 0, float idDirection = 0, int idButton = 0):
    _id(id),
    _idKey(idKey),
    _idJoy(idJoy),
    _idStick(idStick),
    _idAxis(idAxis),
    _idDirection(idDirection),
    _idButton(idButton),
    _isPressed(false)
    {
        //log("+++ Button \n");
    }
    virtual ~Button()
    {
        //log("--- Button \n");
    }

    int _id;      // SNESButton enum !
    int _idKey;     // Keyboard Id
    int _idJoy;     // Gamepad Id
    int _idStick;   // Stick of Gamepad Id
    int _idAxis;   // Axis of Stick Id
    float _idDirection; // Direction of the Axis Id
    int _idButton;  // Button of Gamepad Id
    bool _isPressed; // if button is pressed !

};

extern std::vector<std::string> SNESButtonDico; // Extern variable return string "PAD_XXXX" by id
std::string getSNESButtonDico(unsigned id);

extern int scanKey();

extern std::shared_ptr<Button> getButton(int id);
extern void assignButton (PlayerManager &playerManager, int player, int id, std::function<void(int, int)> run); // Fonction bloquante , wait KEY or JOY inputs

extern void showGamePadInfo (int index);

class Controller
{
    public:
        Controller();

        virtual ~Controller();

        void showController();

        void addButton(int id, int idKey, int idJoy, int id_stick, int idAxis, float idDirection, int idButton);
        void addButton(int id, std::shared_ptr<Button> button);
        void setButton(int id, bool pressed);
        int getButton(int id);

        bool getKey(int keyCode);
        int getNumJoystick();

        void pollJoystick();

    protected:
    private:

        ALLEGRO_KEYBOARD_STATE _keyState;
        //ALLEGRO_JOYSTICK_STATE _joyState;
        std::shared_ptr<Button> _arrayButton[MAX_BUTTONS] = {};

        //ALLEGRO_JOYSTICK * _arrayJoystick[MAX_JOYSTICK] = {NULL};
        int _joystickCount;
};


#endif // CONTROLLER_H_INCLUDED
