#include "keyboard/carbon.cpp"

struct InputCarbon : Input {
  InputKeyboardCarbon carbonKeyboard;
  InputCarbon() : carbonKeyboard(*this) {}
  ~InputCarbon() { term(); }

  auto cap(const string& name) -> bool {
    if(name == Input::KeyboardSupport) return true;
    return false;
  }

  auto get(const string& name) -> any {
    return {};
  }

  auto set(const string& name, const any& value) -> bool {
    return false;
  }

  auto acquire() -> bool { return false; }
  auto release() -> bool { return false; }
  auto acquired() -> bool { return false; }

  auto poll() -> vector<shared_pointer<HID::Device>> {
    vector<shared_pointer<HID::Device>> devices;
    carbonKeyboard.poll(devices);
    return devices;
  }

  auto rumble(buint64 id, bool enable) -> bool {
    return false;
  }

  auto init() -> bool {
    if(!carbonKeyboard.init()) return false;
    return true;
  }

  auto term() -> void {
    carbonKeyboard.term();
  }
};
