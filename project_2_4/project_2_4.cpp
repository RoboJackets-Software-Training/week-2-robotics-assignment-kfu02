#include <iostream>  // Gives us access to std::cin and std::cout
#include <string>  // Gives us access to std::string and std::getline()

struct LightOutputs {
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs {
  int time;
  bool car_sensor_n;
  bool car_sensor_s;
};

// TODO Define your light controller state machine class here
class LightController {
public:
  LightController();

  LightOutputs update(LightInputs input);

private:
  std::string my_state;
  int remaining_time; // before my_state changes

  void changeState(std::string new_state);
  LightOutputs translateMyState();
};

LightController::LightController() {
  my_state = "red";
  remaining_time = 1;
  // equivalent to changeState("red");
}

LightOutputs LightController::update(LightInputs input) {
  if (remaining_time == 0) { // when no time remaining, change to proper next state
    if (my_state == "red") {
      if (input.car_sensor_n || input.car_sensor_s) {
        changeState("ns_green");
      } else {
        changeState("ew_green");
      }
    } else if (my_state == "ew_green") {
      changeState("ew_yellow");
    } else if (my_state == "ns_green") {
      changeState("ns_yellow");
    } else if (my_state == "ew_yellow" || my_state == "ns_yellow") {
      changeState("red");
    }
  }
  // decrement time, return current state in LightOutput form
  remaining_time--;
  return translateMyState();
}

//update state, remaining time
void LightController::changeState(std::string new_state) {
  my_state = new_state;
  remaining_time = 1; // assume "red"
  if (new_state == "ew_green" || new_state == "ns_green") {
    remaining_time = 5;
  } else if (my_state == "ew_yellow" || my_state == "ns_yellow") {
    remaining_time = 2;
  }
}

LightOutputs LightController::translateMyState() {
    if (my_state == "red") {
        return {true, false, false, true, false, false};
    } else if (my_state == "ew_green") {
        return {true, false, false, false, false, true};
    } else if (my_state == "ew_yellow") {
        return {true, false, false, false, true, false};
    } else if (my_state == "ns_green") {
        return {false, false, true, true, false, false};
    } else if (my_state == "ns_yellow") {
        return {false, true, false, true, false, false};
    }
    // no other my_state options, ignore compiler warning
}

int main()
{
    // TODO Initialize your state machine class here
    LightController controller;

    while(true)
    {
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;

        // TODO Parse the input digits
        LightInputs inputs{
            0,
            input[0] == '1',
            input[1] == '1'
        };

        // TODO Update your state machine based on input
        LightOutputs outputs = controller.update(inputs);

        // TODO Output your state machine's light controls to std::cout
        std::cout << outputs.red_ns << outputs.yellow_ns << outputs.green_ns << outputs.red_ew << outputs.yellow_ew << outputs.green_ew << std::endl;
    }
    return 0;
}
