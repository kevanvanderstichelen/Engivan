#pragma once

#pragma region UTILITIES

#define SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }
#define UNREFERENCED_PARAMETER(x) (x)

#pragma endregion UTILITIES