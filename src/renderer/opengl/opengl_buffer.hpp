#pragma once
#include "common.hpp"

namespace intern {
	struct VertexBufferElement {
		enum class DType : i32 {
			F32 = 0x1406, U32 = 0x1405, I32 = 0x1404, U8 = 0x1401
		};

		VertexBufferElement(DType dtype, u32 count);
		u32 get_stride() const;

		DType dtype;
		u32 count;
	};

	class VertexBufferLayout {
	public:
		VertexBufferLayout();

		void push(VertexBufferElement::DType dtype, u32 count);
		const List<VertexBufferElement> get_elements() const;
		u32 get_stride() const;
	private:
		List<VertexBufferElement> m_elements;
		u32 m_stride;
	};

	class VertexBuffer_OPENGL {
	public:
		VertexBuffer_OPENGL() = default;
		VertexBuffer_OPENGL(const void* vertices, adress size, bool is_static = false);
		VertexBuffer_OPENGL(VertexBuffer_OPENGL&& other);
		~VertexBuffer_OPENGL();

		void bind() const ;
		void unbind() const ;

		void overwrite_data(const void* vertices, adress size, adress offset = 0) ;
	private:
		u32 m_id = 0;
		bool m_is_static;
	};

	class IndexBuffer_OPENGL
	{
	public:
		IndexBuffer_OPENGL() = default;
		IndexBuffer_OPENGL(const List<u32>& indices, bool is_static = false);
		~IndexBuffer_OPENGL();

		void bind() const ;
		void unbind() const ;

		void overwrite_data(const List<u32>& indices, u32 offset = 0);
	private:
		u32 m_id;
		bool m_is_static;
	};

	class VertexArray_OPENGL
	{
	public:
		VertexArray_OPENGL(const VertexBuffer_OPENGL& vb, const VertexBufferLayout& layout);
		~VertexArray_OPENGL();

		void bind() const;
		void unbind() const;
	private:
		u32 m_id;
	};
}