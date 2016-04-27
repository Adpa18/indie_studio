//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP

#include "../Irrlicht/irrlicht-1.8.3/include/IEventReceiver.h"

// Event receiver for ui
class UIEventReceiver : public irr::IEventReceiver
{
public:
    UIEventReceiver(SAppContext& context) : Context(context) {}

    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment *env = Context.device->getGUIEnvironment();

            switch (event.GUIEvent.EventType)
            {
                case EGET_SCROLL_BAR_CHANGED:
                    if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                    {
                        s32 pos = ((IGUIScrollBar *) event.GUIEvent.Caller)->getPos();
                        setSkinTransparency(pos, env->getSkin());
                    }
                    break;
                case EGET_BUTTON_CLICKED:
                    switch (id)
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

                            IGUIWindow *window = env->addWindow(
                                    rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter,
                                              200 + Context.counter),
                                    false, // modal?
                                    L"Test window");

                            env->addStaticText(L"Please close me",
                                               rect<s32>(35, 35, 140, 50),
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
                    IGUIFileOpenDialog *dialog =
                            (IGUIFileOpenDialog *) event.GUIEvent.Caller;
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
    SAppContext &Context;
};


#endif //CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
