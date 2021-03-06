enum class Input : uint {
  A, B, Select, Start, Right, Left, Up, Down, R, L,
};

struct BIOS : Memory {
  BIOS();
  ~BIOS();

  auto read(uint mode, buint32 addr) -> buint32 override;
  auto write(uint mode, buint32 addr, buint32 word) -> void override;

  buint8* data = nullptr;
  uint size = 0;
  buint32 mdr = 0;
};

struct System {
  auto loaded() const -> bool;

  auto init() -> void;
  auto term() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto run() -> void;
  auto runToSave() -> void;

  auto serialize() -> serializer;
  auto unserialize(serializer&) -> bool;

  auto serialize(serializer&) -> void;
  auto serializeAll(serializer&) -> void;
  auto serializeInit() -> void;

  struct Information {
    string manifest;
  } information;

  bool _loaded = false;
  uint _serializeSize = 0;
};

extern BIOS bios;
extern System system;
