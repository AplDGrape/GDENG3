#include "SwapChain.h"
#include "DeviceContext.h"

#include <d3dcompiler.h>
//#include "shader.fx"
#include <iostream>

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;
GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	//ID3D11DeviceContext* m_imm_context;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL,
			feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level,
			&this->m_imm_context);

		if (SUCCEEDED(res))
		{
			break;
			driver_type_index++;
		}
	}

	if (FAILED(res))
	{
		return false;
	}

	this->m_imm_device_context = new DeviceContext(this->m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	

	return true;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(Filename, nullptr, nullptr, EntryPointName, "vs_5_0", 0, 0, &this->m_blob, &errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Faied to compile vertex shader";
			errorBlob->Release();
			return false;
		}
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* Filename, const char* EntryPointName, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(Filename, nullptr, nullptr, EntryPointName, "ps_5_0", 0, 0, &this->m_blob, &errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Faied to compile pixel shader";
			errorBlob->Release();
			return false;
		}
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (this->m_blob)
	{
		this->m_blob->Release();
	}
}

//bool GraphicsEngine::createShaders()
//{
//	ID3DBlob* errblob = nullptr;
//	//D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
//	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
//	//m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
//	m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
//	
//	return true;
//}

//bool GraphicsEngine::setShaders()
//{
//	//m_imm_context->VSSetShader(m_vs, nullptr, 0);
//	m_imm_context->PSSetShader(m_ps, nullptr, 0);
//
//	return true;
//}

//void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
//{
//	*bytecode = this->m_vsblob->GetBufferPointer();
//	*size = (UINT)this->m_vsblob->GetBufferSize();
//}

bool GraphicsEngine::release()
{
	if(this->m_vs)this->m_vs->Release();
	if (this->m_ps)this->m_ps->Release();

	if(this->m_vsblob)this->m_vsblob->Release();
	if (this->m_psblob)this->m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	this->m_imm_device_context->release();
	m_d3d_device->Release();
	return true;
}

ID3D11Device* GraphicsEngine::getD3Ddevice()
{
	return this->m_d3d_device;
}

D3D_FEATURE_LEVEL GraphicsEngine::getFeatureLevel()
{
	return this->m_feature_level;
}

IDXGIFactory* GraphicsEngine::getFactory()
{
	return this->m_dxgi_factory;
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

VertexBufferTextured* GraphicsEngine::createTexturedVertexBuffer()
{
	return new VertexBufferTextured();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size)) {
		ps->release();
		return nullptr;
	}

	return ps;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	if(sharedInstance != NULL)return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if(sharedInstance != NULL)sharedInstance->release();
}

//wireframe
ID3D11Device* GraphicsEngine::getD3DDevice()
{
	return m_d3d_device;
}

ID3D11DeviceContext* GraphicsEngine::getD3DDeviceContext()
{
	return m_imm_context;
}