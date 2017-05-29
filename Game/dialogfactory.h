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

  /// TODO: parameters of menu window, buttons...

  return menu;
}
#endif // DIALOGFACTORY_H
