#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

#include "dialogs.h"

class DialogFactory {
public:
  DialogFactory(){}
  static DialogWindow* GetDialogWindow(LinearVector<int> constraints, LinearVector<int> coords);
  static DialogWindow* GetMenu();
};

DialogWindow* DialogFactory::GetDialogWindow(LinearVector<int> constraints, LinearVector<int> coords)
{
  return new DialogWindow(constraints, coords);
}

DialogWindow* DialogFactory::GetMenu()
{
  DialogWindow* menu = new DialogWindow(kMenuConstraints, kMenuCoords);
  menu->AddText(18, LinearVector<int>(20, 20), "Game over!");
  Button* continueButton = menu->AddButton(LinearVector<int>(100, 50), LinearVector<int>(50, 100), "Continue");
  Button* exitButton = menu->AddButton(LinearVector<int>(100, 50), LinearVector<int>(200, 100), "Exit");
  /// TODO: parameters of menu window, buttons...

  return menu;
}
#endif // DIALOGFACTORY_H
