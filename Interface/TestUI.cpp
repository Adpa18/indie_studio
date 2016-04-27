//
// Created by veyrie_f on 4/27/16.
//

#include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
#include "../include/IrrlichtController.hpp"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};

// Changes alpha value for all the objects
void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
    for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(SAppContext & context) : Context(context) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            {
                case EGET_SCROLL_BAR_CHANGED:
                    if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                    {
                        s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                        setSkinTransparency(pos, env->getSkin());
                    }
                    break;
                case EGET_BUTTON_CLICKED:
                    switch(id)
                    {
                        case GUI_ID_QUIT_BUTTON:
                            Context.device->closeDevice();
                            return true;

                        case GUI_ID_NEW_WINDOW_BUTTON:
                        {
                            Context.listbox->addItem(L"Window created");
                            Context.counter += 30;
                            if (Context.counter > 200)
                                Context.counter = 0;

                            IGUIWindow* window = env->addWindow(
                                    rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
                                    false, // modal?
                                    L"Test window");

                            env->addStaticText(L"Please close me",
                                               rect<s32>(35,35,140,50),
                                               true, // border?
                                               false, // wordwrap?
                                               window);
                        }
                            return true;

                        case GUI_ID_FILE_OPEN_BUTTON:
                            Context.listbox->addItem(L"File open");
                            // There are some options for the file open dialog
                            // We set the title, make it a modal window, and make sure
                            // that the working directory is restored after the dialog
                            // is finished.
                            env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
                            return true;

                        default:
                            return false;
                    }
                    break;

                case EGET_FILE_SELECTED:
                {
                    // show the model filename, selected in the file dialog
                    IGUIFileOpenDialog* dialog =
                            (IGUIFileOpenDialog*)event.GUIEvent.Caller;
                    Context.listbox->addItem(dialog->getFileName());
                }
                    break;

                default:
                    break;
            }
        }

        return false;
    }

private:
    SAppContext & Context;
};

int main()
{
    IrrlichtDevice *device = IrrlichtController::getDevice();

    if (device == nullptr)
        return 1; // could not create selected driver.

    device->setWindowCaption(L"User Interface Demo");
    device->setResizable(true);

    video::IVideoDriver* driver = device->getVideoDriver();
    IGUIEnvironment* env = device->getGUIEnvironment();
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

    env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
                   L"Quit", L"Exits Program");
    env->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
                   L"New Window", L"Launches a new Window");
    env->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
                   L"File Open", L"Opens a file");
    env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
    IGUIScrollBar* scrollbar = env->addScrollBar(true,
                                                 rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
    scrollbar->setMax(255);
    scrollbar->setPos(255);
    setSkinTransparency( scrollbar->getPos(), env->getSkin());

    // set scrollbar position to alpha value of an arbitrary element
    scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

    env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
    env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

    // Store the appropriate data in a context structure.
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = listbox;

    // Then create the event receiver, giving it that context structure.
    MyEventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);
    env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"),
                  position2d<int>(10,10));
    while(device->run() && driver)
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(0,200,200,200));

            env->drawAll();

            driver->endScene();
        }

    device->drop();

    return 0;
}