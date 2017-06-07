// -*- mode: c++; coding: utf-8 -*-

module SmartObject {

  interface Observable {
    void setObserver(string observer);
  };

  // Global Position of Sensors/Actuators
  struct Position {
    float latitude;    // GPS coordinates (ie. 42.361020)
    float longitude;   // GPS coordinates (ie. 0.160056)
    float altitude;    // GPS coordinates (ie. 1852.25)
    string place;      // Human readable coarse position description
  };

  sequence <Position> PositionOpt;

  struct MeasureMetadata {
    int timestamp;         // Unix time
    byte quality;          // 0:unknown, 1:poor, 255:best
    short expiration;      // seconds
  };

  sequence <MeasureMetadata> MeasureMetadataOpt;

  // G-Force sensed on each axis (m/s² or Gs)
  struct Acceleration {
    float x;
    float y;
    float z;
  };

  interface DigitalSink {
    void update(string id, bool value,
		MeasureMetadataOpt meta, PositionOpt position);
  };

  interface AnalogSink {
    void update(string id, float value,
		MeasureMetadataOpt meta, PositionOpt position);
  };

  interface AccelerometerSensorListener {
    void update(string id, Acceleration value,
		MeasureMetadataOpt meta, PositionOpt position);
  };
};
