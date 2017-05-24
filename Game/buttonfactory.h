#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H

#include "buttons.h"

static class ButtonFactory {
public:
  ButtonFactory() = 0;
  Button* GetButton(LinearVector<int> constraints, LinearVector<int> ref_coords);
  Button* GetExitButton();
}

#endif // BUTTONFACTORY_H
