#include "DynamicConstant.h"

namespace DCST
{
	ConstantLayout::Element::Element(Type type, UINT offset, const std::string& name)
		:
		type(type),
		offset(offset),
		name(name)
	{
		switch (type)
		{
		case Type::FLOAT: size = sizeof(float); break;
		case Type::FLOAT2: size = sizeof(8u); break;
		case Type::FLOAT3: size = sizeof(12u); break;
		case Type::FLOAT4: size = sizeof(16u); break;
		case Type::MATRIX: size = sizeof(64u); break;
		case Type::BOOL: size = sizeof(bool); break;
		case Type::PADDING: size = 1u; break;
		default: size = 0u; break;
		}
	}

	ConstantLayout::Element& ConstantLayout::Element::GetEmptyElement()
	{
		static Element e(Type::INVALID, -1, "INVALID");
		return e;
	}

	ConstantLayout& ConstantLayout::Append(Element::Type type, const std::string& name)
	{
		elements.emplace_back(type, GetByteSize(), name);
		return *this;
	}

	ConstantLayout::Element& ConstantLayout::operator[](const std::string& key)
	{
		for (auto& e : elements)
		{
			if (e.GetName() == key)
			{
				return e;
			}
		}
		return Element::GetEmptyElement();
	}

	ConstantRef::ConstantRef(ConstantLayout& layout, BYTE* pData, UINT size)
		:
		layout(layout),
		pData(pData),
		size(size)
	{}

	ConstantRef::operator bool() const
	{
		return pData != nullptr;
	}

	ConstantBuffer::ConstantBuffer(ConstantLayout layout_in)
		:
		layout(std::move(layout_in))
	{
		buffer.resize(this->layout.GetByteSize());
	}

	ConstantRef ConstantBuffer::operator[](const std::string& key)
	{
		auto e = layout[key];
		if (e.GetType() == ConstantLayout::Element::Type::INVALID)
		{
			return { layout, nullptr, 0u };
		}
		auto offset = e.GetOffset();
		assert(offset < buffer.size());
		return { layout, buffer.data() + offset, e.GetSize() };
	}
}