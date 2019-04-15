#ifndef DXCOMMON_H
#define DXCOMMON_H

#include <d3d11_1.h>
#include <DirectXCollision.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <d3dcompiler.h>
#include <filesystem>
#include <vector>
#include <string>

#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

#endif
