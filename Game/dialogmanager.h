#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "dialogfactory.h"

class DialogManager {
private:
  Array<DialogWindow*> dialogs_;
public:
  OnClick(LinearVector<int> coords);
  DrawDialogs();
};

#endif // DIALOGMANAGER_H
