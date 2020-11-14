#pragma once
#include "../core/LightWindows.h"
#include <vector>
#include <string>
#include <cassert>

namespace DVTX
{
	class VertexLayout
	{
	public:
		class Element
		{
		public:
			enum class Type
			{
				POSITION2D,
				POSITION3D,
				POSITION4D,
				NORMAL,
				TANGENT,
				BITANGENT,
				COLOR3,
				COLOR4,
				TEXCOORD,
				INVALID
			};
		private:
			Type type;
			UINT offset;
			UINT size;

		public:
			Element(Type type, UINT offset);

		public:
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
		VertexLayout& Append(Element::Type type);
		Element& Resolve(Element::Type type);
		Element& operator [](size_t index) { return elements[index]; }
	};

	class Vertex
	{
	private:
		VertexLayout& layout;
		BYTE* pData;

	public:
		Vertex(BYTE* pData, VertexLayout& layout);

	public:
		template<typename T>
		void SetAttributeByIndex(size_t i, T&& val) noexcept
		{
			const auto& element = layout[i];
			auto pAttribute = reinterpret_cast<T*>(pData + element.GetOffset());
			*pAttribute = val;
		}
		template<typename First, typename ...Rest>
		void SetAttributeByIndex(size_t i, First&& first, Rest&&... rest) noexcept
		{
			SetAttributeByIndex(i, std::forward<First>(first));
			SetAttributeByIndex(i + 1, std::forward<Rest>(rest)...);
		}

		template <typename Systype>
		Systype& Attr(VertexLayout::Element::Type type)
		{
			size_t offset = layout.Resolve(type).GetOffset();
			assert(offset >= 0 && offset < layout.GetByteSize());
			return *reinterpret_cast<Systype*>(pData + offset);
		}
		template <typename Systype>
		const Systype& Attr(VertexLayout::Element::Type type) const
		{
			size_t offset = layout.Resolve(type).GetOffset();
			assert(offset >= 0 && offset < layout.GetByteSize());
			return *reinterpret_cast<Systype*>(pData + offset);
		}
	};

	class VertexBuffer
	{
	private:
		VertexLayout layout;
		std::vector<BYTE> buffer;

	public:
		VertexBuffer(VertexLayout layout_in, size_t size = 0u);

	public:
		VertexLayout& GetLayout() { return layout; }
		BYTE* GetData() { return buffer.data(); }
		size_t Size() const { return buffer.size() / layout.GetByteSize(); }
		size_t GetByteSize() const { return buffer.size(); }
		void Resize(size_t size) { buffer.resize(size * layout.GetByteSize()); }

		Vertex Front() { return { GetData(), layout }; }
		Vertex Back() { return { GetData() + buffer.size() - layout.GetByteSize(), layout }; }
		Vertex operator [](size_t index);

		void PushBack(BYTE* pValue, unsigned int iSize);
		template<typename ...Params>
		void EmplaceBack(Params&&... params) noexcept
		{
			assert( sizeof...(params) == layout.Size() );
			buffer.resize(buffer.size() + layout.GetByteSize());
			Back().SetAttributeByIndex(0u, std::forward<Params>(params)...);
		}
	};
}