namespace hiro {

Settings::Settings() {
  geometry.append(geometry.frameX = 4, "FrameX");
  geometry.append(geometry.frameY = 24, "FrameY");
  geometry.append(geometry.frameWidth = 8, "FrameWidth");
  geometry.append(geometry.frameHeight = 28, "FrameHeight");
  geometry.append(geometry.menuHeight = 20, "MenuHeight");
  geometry.append(geometry.statusHeight = 20, "StatusHeight");
  append(geometry, "Geometry");
  window.append(window.backgroundColor = 0xedeceb, "BackgroundColor");
  append(window, "Window");
}

auto Settings::load() -> void {
  string path = {configpath(), "hiro/"};
  Configuration::Document::load({path, "gtk.bml"});
}

auto Settings::save() -> void {
  string path = {configpath(), "hiro/"};
  directory::create(path, 0755);
  Configuration::Document::save({path, "gtk.bml"});
}

}
