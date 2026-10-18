/*
	Input mode tracking for the game browser UI.

	Tracks which kind of input the user touched last (touchscreen, gamepad, or
	mouse/keyboard) so the UI can adapt its layout on the fly.

	This file is part of Flycast and is distributed under the GPLv2 or later.
 */
#pragma once

enum class InputMode
{
	Pointer,	// mouse / keyboard (desktop)
	Touch,		// touchscreen
	Gamepad		// physical gamepad (USB or Bluetooth) or TV remote
};

// Current mode.
InputMode inputModeGet();
// Report activity from an input source. Switches the mode immediately.
void inputModeReport(InputMode mode);
// Sets the mode used until the user produces any input.
// Android: Touch when the device has a touchscreen, Gamepad otherwise.
void inputModeSetDefault(InputMode mode);
// True exactly once after each mode change (for one-shot layout resets).
bool inputModeChanged();

static inline bool inputModeIsGamepad() {
	return inputModeGet() == InputMode::Gamepad;
}
static inline bool inputModeIsTouch() {
	return inputModeGet() == InputMode::Touch;
}
