#pragma once
#include "../core/LightWindows.h"
#include <vector>
#include <string>
#include <cassert>

namespace DCST
{
	class ConstantLayout
	{
	public:
		class Element
		{
		public:
			enum class Type
			{
				FLOAT,
				FLOAT2,
				FLOAT3,
				FLOAT4,
				MATRIX,
				BOOL,
				PADDING,
				INVALID
			};

		private:
			std::string name;
			Type type;
			UINT offset;
			UINT size;

		public:
			Element(Type type, UINT offset, const std::string& name);

		public:
			std::string GetName() const { return name; }
			Type GetType() const { return type; }
			UINT GetOffset() const { return offset; }
			UINT GetSize() const { return size; }
			UINT GetOffsetAfter() const { return offset + size; }
			static Element& GetEmptyElement();
		};

	private:
		std::vector<Element> elements;

	public:
		size_t Size() const { return elements.size(); }
		UINT GetByteSize() const { return elements.empty() ? 0u : elements.back().GetOffsetAfter(); }
		ConstantLayout& Append(Element::Type type, const std::string& name);

		Element& operator [](const std::string& key);
	};

	class ConstantRef
	{
	private:
		ConstantLayout& layout;
		BYTE* pData;
		UINT size;

	public:
		ConstantRef(ConstantLayout& layout, BYTE* pData, UINT size);

	public:
		template<typename T>
		T& operator =(const T& val)
		{
			if (pData == nullptr) return const_cast<T&>(val);
			assert(sizeof(T) == size && "Invalid Type Assignment");
			return reinterpret_cast<T&>(*pData) = val;
		}

		operator bool() const;
	};

	class ConstantBuffer
	{
	private:
		ConstantLayout layout;
		std::vector<BYTE> buffer;

	public:
		ConstantBuffer(ConstantLayout layout_in);

	public:
		ConstantLayout& GetLayout() { return layout; }
		BYTE* GetData() { return buffer.data(); }
		size_t Size() const { return buffer.size() / layout.GetByteSize(); }
		size_t GetByteSize() const { return buffer.size(); }

		ConstantRef operator [](const std::string& key);
	};
}