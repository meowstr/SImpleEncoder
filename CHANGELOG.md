# Changelog

All notable changes to the SimpleEncoder library will be documented in this file.

## [1.0.0] - 2026-01-05

### Added
- Initial release of SimpleEncoder library
- Gray code finite state machine (FSM) implementation for robust rotary encoder decoding
- Polling-based approach with configurable sampling interval
- Automatic debouncing and noise rejection
- Configurable detent counting
- `RotaryEncoder` class with clean API:
  - `begin()` - Initialize encoder
  - `poll()` - Update encoder state (call in loop)
  - `getValue()` - Get current encoder value
  - `reset()` - Reset value to 0
  - `setValue(int)` - Set value to specific number
- BasicOLED example sketch demonstrating integration with SSD1306 OLED display
- Comprehensive bilingual documentation (Japanese/English)
- Arduino Library Manager compatible structure
- MIT License

### Features
- ✅ No interrupt pins required
- ✅ Works on ESP32, Arduino, and compatible boards
- ✅ Handles chattering and contact bounce
- ✅ Ignores invalid state transitions
- ✅ Educational comments explaining Gray code FSM
- ✅ Easy to integrate and configure

### Documentation
- Complete README with installation instructions
- API reference with usage examples
- Wiring diagram
- Parameter tuning guide
- Japanese and English documentation

[1.0.0]: https://github.com/Igurometsuki/SimpleEncoder/releases/tag/v1.0.0
