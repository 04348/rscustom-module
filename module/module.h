#pragma once

#include <d3d9.h>
#include <d3d11.h>
#include <iostream>
#include <string>
#include <Windows.h>

using draw_fx_func = void(IDirect3DSurface9* surface);

using draw_fx_func_9 = void(void);
using draw_fx_func_10 = void(void);

typedef void(*draw_fx_func_11)(void*);

class IModule {
public:
	virtual ~IModule() = default;

	/*
	 * DX9 NOT IMPLEMENTED YET !
	 */
	virtual void on_Present_9() = 0;
	virtual HRESULT CreateVertexShader_9(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader) = 0;
	virtual HRESULT SetVertexShader_9(IDirect3DVertexShader9 *pShader) = 0;
	virtual HRESULT CreatePixelShader_9(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader) = 0;
	virtual HRESULT SetPixelShader_9(IDirect3DPixelShader9 *pShader) = 0;

	/*
	 * DX10 NOT IMPLEMENTED YET !
	 */
	virtual void on_Present_10() = 0;
	virtual HRESULT CreateVertexShader_10(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader) = 0;
	virtual HRESULT SetVertexShader_10(IDirect3DVertexShader9 *pShader) = 0;
	virtual HRESULT CreatePixelShader_10(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader) = 0;
	virtual HRESULT SetPixelShader_10(IDirect3DPixelShader9 *pShader) = 0;

	/*
	 * DX11 methods
	 */
	virtual void on_Present_11(void* runtime) = 0;
	virtual HRESULT CreateVertexShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader) = 0;
	virtual void SetVertexShader_11(ID3D11DeviceContext* orig, ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances) = 0;
	virtual HRESULT CreatePixelShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader) = 0;
	virtual void SetPixelShader_11(ID3D11DeviceContext* orig, ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances) = 0;
	virtual void RegisterDrawFxFunc(draw_fx_func_11) = 0;
};

class Module : public IModule {
public:
	Module();

	virtual void on_Present_9();
	virtual HRESULT CreateVertexShader_9(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader);
	virtual HRESULT SetVertexShader_9(IDirect3DVertexShader9 *pShader);
	virtual HRESULT CreatePixelShader_9(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader);
	virtual HRESULT SetPixelShader_9(IDirect3DPixelShader9 *pShader);

	virtual void on_Present_10();
	virtual HRESULT CreateVertexShader_10(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader);
	virtual HRESULT SetVertexShader_10(IDirect3DVertexShader9 *pShader);
	virtual HRESULT CreatePixelShader_10(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader);
	virtual HRESULT SetPixelShader_10(IDirect3DPixelShader9 *pShader);

	virtual void on_Present_11(void* runtime);
	virtual HRESULT CreateVertexShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader);
	virtual void SetVertexShader_11(ID3D11DeviceContext* orig, ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances);
	virtual HRESULT CreatePixelShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader);
	virtual void SetPixelShader_11(ID3D11DeviceContext* orig, ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances);
	virtual void RegisterDrawFxFunc(draw_fx_func_11);
private:
	int version;
	int version_target;
	std::string name;
	std::string author;

	bool fx_done = false;
	void* last_runtime = nullptr;
	ID3D11PixelShader * injPixelShader = nullptr;

	draw_fx_func_11 drawfx_11 = nullptr;
};

extern "C"
{
	__declspec (dllexport) IModule* CreateModule();
}