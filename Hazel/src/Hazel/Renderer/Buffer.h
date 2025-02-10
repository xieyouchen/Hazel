#pragma once

namespace Hazel {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Hazel::ShaderDataType::Float:	  return 4;
		case Hazel::ShaderDataType::Float2:	  return 4 * 2;
		case Hazel::ShaderDataType::Float3:	  return 4 * 3;
		case Hazel::ShaderDataType::Float4:	  return 4 * 4;
		case Hazel::ShaderDataType::Mat3: 	  return 4 * 3 * 3;
		case Hazel::ShaderDataType::Mat4: 	  return 4 * 4 * 4;
		case Hazel::ShaderDataType::Int:  	  return 4;
		case Hazel::ShaderDataType::Int2: 	  return 4 * 2;
		case Hazel::ShaderDataType::Int3: 	  return 4 * 3;
		case Hazel::ShaderDataType::Int4:	  return 4 * 4;
		case Hazel::ShaderDataType::Bool:	  return 1;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;

		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		uint32_t GetComponentCount() const {
			switch (Type)
			{
			case ShaderDataType::Bool:   return 1;
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> layout)
			: m_Elements(layout)
		{
			CalculateOffsetAndStride();
		}

		void CalculateOffsetAndStride() {
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }


	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		static VertexBuffer* Create(float* vertices, uint32_t size);

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);

		virtual inline uint32_t GetCount() const = 0;
	};


}
