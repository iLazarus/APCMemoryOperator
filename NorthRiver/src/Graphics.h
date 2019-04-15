#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "DXCommon.h"
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "winmm.lib")

class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	bool Init(HWND hWindow, int iWidth, int iHeight);
	void Begin();
	void End();
	void Draw();

protected:
	bool	  m_Enable4xMsaa;	 // 是否开启4倍多重采样
	UINT      m_4xMsaaQuality;   // MSAA支持的质量等级


	// 使用模板别名(C++11)简化类型名
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	// Direct3D 11
	ComPtr<ID3D11Device> m_pd3dDevice;                    // D3D11设备
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;   // D3D11设备上下文
	ComPtr<IDXGISwapChain> m_pSwapChain;                  // D3D11交换链
	// Direct3D 11.1
	ComPtr<ID3D11Device1> m_pd3dDevice1;                  // D3D11.1设备
	ComPtr<ID3D11DeviceContext1> m_pd3dImmediateContext1; // D3D11.1设备上下文
	ComPtr<IDXGISwapChain1> m_pSwapChain1;                // D3D11.1交换链

	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;   // 渲染目标视图
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;   // 深度模板视图

};

#endif // !GRAPHICS_H

