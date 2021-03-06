struct Video {
  Video();

  auto power() -> void;
  auto refresh() -> void;

private:
  unique_pointer<buint32[]> output;
  unique_pointer<buint32[]> paletteLiteral;
  unique_pointer<buint32[]> paletteStandard;
  unique_pointer<buint32[]> paletteEmulation;
};

extern Video video;
