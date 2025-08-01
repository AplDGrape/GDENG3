struct VS_INPUT 
{
	float4 position : POSITION;
	//float4 position1 : POSITION1;
	float3 color : COLOR;
	float3 color1 : COLOR1;

	//float4x4 instanceTransform : INSTANCE_TRANSFORM;
};

struct VS_OUTPUT 
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	unsigned int time;
	//float m_time;
	//float3 padding;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//float4 worldPos = mul(float4(input.position, 1.0f), input.instanceTransform);

	//output.position = lerp(input.position, input.position1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
	//WORLD SPACE
	output.position = mul(input.position, m_world);
	//VIEW SPACE
	output.position = mul(output.position, m_view);
	//SCREEN SPACE
	output.position = mul(output.position, m_proj);

	output.color = input.color;
	output.color1 = input.color1;

	/*if (position.y > 0 && position.y < 1)
	{
		position.x += 0.25f;
	}

	if (position.y > 0 && position.y < 1 && position.x > -1 && position.x < 0)
	{
		position.y -= 0.25f;
	}*/

	return output;
}

//float psmain(float4 pos : SV_Position) : SV_Target
//{
//    return float4(0.8f, 0.9f, 0.4f, 1.0f);
//}