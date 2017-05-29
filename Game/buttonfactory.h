#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H

#include "buttons.h"

class ButtonFactory {
public:
  ButtonFactory(){}
  static Button* GetButton(LinearVector<int> constraints, LinearVector<int> coords, std::string caption);
  static Button* GetExitButton(LinearVector<int> window_constraints, LinearVector<int> window_coords);
};

Button* ButtonFactory::GetButton(LinearVector<int> constraints, LinearVector<int> coords, std::string caption)
{
  return new Button(constraints, coords, caption);
}

Button* ButtonFactory::GetExitButton(LinearVector<int> window_constraints, LinearVector<int> window_coords)
{
  LinearVector<int> exit_coords;
  exit_coords.x_ = window_coords.x_ + window_constraints.x_ - 30;
  exit_coords.y_ = window_coords.y_ + 5;
  return new Button(LinearVector<int>(20,20), exit_coords, std::string("X"));
}
#endif // BUTTONFACTORY_H
