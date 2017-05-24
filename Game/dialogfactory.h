#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

#include "dialogs.h"

static class DialogFactory {
public:
  DialogFactory() = 0;
  DialogWindow* GetDialogWindow(LinearVector<int> constraints, LinearVector<int> ref_coords);
  DialogWindow* GetMenu();
}

#endif // DIALOGFACTORY_H
