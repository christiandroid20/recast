/*
	This file is part of Flycast and is distributed under the GPLv2 or later.
 */
#include "input_mode.h"
#include <atomic>

// Input events can arrive from the Java/UI thread while the emulator thread
// draws the UI, hence the atomics.
#if defined(__ANDROID__)
static std::atomic<InputMode> currentMode{ InputMode::Gamepad };
#else
static std::atomic<InputMode> currentMode{ InputMode::Pointer };
#endif
static std::atomic<bool> modeChanged{ false };

InputMode inputModeGet() {
	return currentMode.load(std::memory_order_relaxed);
}

void inputModeReport(InputMode mode)
{
	if (currentMode.exchange(mode, std::memory_order_relaxed) != mode)
		modeChanged.store(true, std::memory_order_relaxed);
}

void inputModeSetDefault(InputMode mode) {
	inputModeReport(mode);
}

bool inputModeChanged() {
	return modeChanged.exchange(false, std::memory_order_relaxed);
}
