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
	bool	  m_Enable4xMsaa;	 // �Ƿ���4�����ز���
	UINT      m_4xMsaaQuality;   // MSAA֧�ֵ������ȼ�


	// ʹ��ģ�����(C++11)��������
	template <class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	// Direct3D 11
	ComPtr<ID3D11Device> m_pd3dDevice;                    // D3D11�豸
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;   // D3D11�豸������
	ComPtr<IDXGISwapChain> m_pSwapChain;                  // D3D11������
	// Direct3D 11.1
	ComPtr<ID3D11Device1> m_pd3dDevice1;                  // D3D11.1�豸
	ComPtr<ID3D11DeviceContext1> m_pd3dImmediateContext1; // D3D11.1�豸������
	ComPtr<IDXGISwapChain1> m_pSwapChain1;                // D3D11.1������

	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;   // ��ȾĿ����ͼ
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;   // ���ģ����ͼ

};

#endif // !GRAPHICS_H

