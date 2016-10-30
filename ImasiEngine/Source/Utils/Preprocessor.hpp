#pragma once

#define safeDelete(pointer) { delete pointer; pointer = nullptr; }
#define safeDeleteArray(pointer) { delete[] pointer; pointer = nullptr; }
