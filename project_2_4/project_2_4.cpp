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
  int remaining_time; // in my_state
  std::string printOutput(LightOutputs output);
  void changeState(std::string new_state, int new_rem_time);
  LightOutputs translateMyState();
};

LightController::LightController() {
  my_state = "red";
  remaining_time = 1;
  // changeState("red", 1);
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
    // no other my_state options
}

LightOutputs LightController::update(LightInputs input) {
  if (remaining_time == 0) {
    if (my_state == "red") {
      if (input.car_sensor_n || input.car_sensor_s) {
        changeState("ns_green", 5);
      } else {
        changeState("ew_green", 5);
      }
    } else if (my_state == "ew_green") {
      changeState("ew_yellow", 2);
    } else if (my_state == "ns_green") {
      changeState("ns_yellow", 2);
    } else if (my_state == "ew_yellow" || my_state == "ns_yellow") {
      changeState("red", 1);
    }
  }

  remaining_time--;
  return translateMyState();
}

void LightController::changeState(std::string new_state, int new_rem_time) {
  my_state = new_state;
  remaining_time = new_rem_time;
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
