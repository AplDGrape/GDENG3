#pragma once
#include <d3d11.h>
#include <iostream>

#include "GraphicsEngine.h"

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	bool release();
	~VertexShader();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11VertexShader* m_vs;;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};