#include "module.h"
#include "hash.h"

//Possible injections points :
//6246f051
//1c5cbe3b

void Module::on_Present_11(void* runtime)
{
	last_runtime = runtime;
	if(!fx_done) drawfx_11(runtime);
	fx_done = false;
}

HRESULT Module::CreateVertexShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
{
	return orig->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

void Module::SetVertexShader_11(ID3D11DeviceContext* orig, ID3D11VertexShader *pVertexShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	orig->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

HRESULT Module::CreatePixelShader_11(ID3D11Device* orig, const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader)
{
	HRESULT res = orig->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
	if (injPixelShader == nullptr){
		if (SuperFastHash((char*)(pShaderBytecode), BytecodeLength) == 0x6246f051) {
			injPixelShader = *ppPixelShader;
		}
	}
	return res;
}

void Module::SetPixelShader_11(ID3D11DeviceContext* orig, ID3D11PixelShader *pPixelShader, ID3D11ClassInstance *const *ppClassInstances, UINT NumClassInstances)
{
	if (injPixelShader != nullptr && !fx_done && pPixelShader == injPixelShader) {
		drawfx_11(last_runtime);
		fx_done = true;
	}
	orig->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void  Module::RegisterDrawFxFunc(draw_fx_func_11 f) {
	drawfx_11 = f;
}