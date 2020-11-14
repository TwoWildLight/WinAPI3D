#include "DynamicVertex.h"

namespace DVTX
{
	VertexLayout::Element::Element(Type type, UINT offset)
		:
		type(type),
		offset(offset)
	{
		switch (type)
		{
		case Element::Type::INVALID: size = 0u; break;
		case Element::Type::POSITION2D: size = 8u; break;
		case Element::Type::POSITION3D: size = 12u; break;
		case Element::Type::POSITION4D: size = 16u; break;
		case Element::Type::NORMAL: size = 12u; break;
		case Element::Type::TANGENT: size = 12u; break;
		case Element::Type::BITANGENT: size = 12u; break;
		case Element::Type::TEXCOORD: size = 8u; break;
		case Element::Type::COLOR3: size = 12u; break;
		case Element::Type::COLOR4: size = 16u; break;
		default: assert(0 && "Bad Element Type"); break;
		}
	}

	VertexLayout::Element& VertexLayout::Element::GetEmptyElement()
	{
		static Element e(Element::Type::INVALID, 0u);
		return e;
	}

	VertexLayout& VertexLayout::Append(Element::Type type)
	{
		elements.emplace_back(type, GetByteSize());
		return *this;
	}

	VertexLayout::Element& VertexLayout::Resolve(Element::Type type)
	{
		for (auto& e : elements)
		{
			if (e.GetType() == type)
				return e;
		}
		return Element::GetEmptyElement();
	}

	Vertex::Vertex(BYTE* pData, VertexLayout& layout)
		:
		layout(layout),
		pData(pData)
	{
		assert(pData != nullptr);
	}

	VertexBuffer::VertexBuffer(VertexLayout layout_in, size_t size)
		:
		layout(std::move(layout_in))
	{
		Resize(size);
	}

	Vertex VertexBuffer::operator [](size_t index)
	{
		assert(index >= 0 && index < Size());
		return { GetData() + layout.GetByteSize() * index, layout };
	}

	void VertexBuffer::PushBack(BYTE* pValue, unsigned int iSize)
	{
		for (unsigned int i = 0; i < iSize; i++)
		{
			buffer.push_back(pValue[i]);
		}
	}
}