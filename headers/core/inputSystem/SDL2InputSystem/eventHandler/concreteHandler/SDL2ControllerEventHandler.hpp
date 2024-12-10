#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractControllerManager.hpp"
#include "../headers/core/inputSystem/enums/ControllerButton.hpp"
#include "../headers/core/inputSystem/enums/ControllerAxis.hpp"

#define MIN_AXIS_VAL -32768.0f
#define MAX_AXIS_VAL 32767.0f

class SDL2ControllerEventHandler : public SDL2AbstractEventHandler
{

private:
  /**
   * NOTE: maybe there is some floating point error issue?
   */
  const float scaling_factor = 1.0f / (MAX_AXIS_VAL - MIN_AXIS_VAL);
  const float translation_factor = MIN_AXIS_VAL / (MAX_AXIS_VAL - MIN_AXIS_VAL);

  SDL_JoystickID controller_id;

  std::shared_ptr<AbstractControllerManager> abstractControllerManager;

  ControllerButton convertSDLtoControllerButton(SDL_Keycode sdlButton) const;
  ControllerAxis convertSDLAxistoControllerButton(SDL_Keycode sdlAxis) const;

  inline float normalize_SDL2_axis(int value) const;

protected:
  bool can_handle(SDL_Event event) const override;
  void concrete_handle(SDL_Event event) const override;

public:
  SDL2ControllerEventHandler(std::shared_ptr<AbstractControllerManager> abstractControllerManager, int controller_id)
      : abstractControllerManager(abstractControllerManager),
        controller_id(controller_id)
  {
  }

  bool can_handle(SDL_Event event) const override;
  void concrete_handle(SDL_Event event) const override;
};