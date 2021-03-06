struct Sequencer {
  auto run() -> void;
  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  auto serialize(serializer&) -> void;

  bool leftEnable;
  uint3 leftVolume;
  bool rightEnable;
  uint3 rightVolume;

  struct Channel {
    bool leftEnable;
    bool rightEnable;
  } square1, square2, wave, noise;

  bool enable;

  int16 center;
  int16 left;
  int16 right;

  int64 centerBias;
  int64 leftBias;
  int64 rightBias;
};
