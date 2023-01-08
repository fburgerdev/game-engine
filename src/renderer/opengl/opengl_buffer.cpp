#include "opengl_buffer.hpp"
#include <GL/glew.h>

namespace intern {
	// vertex buffer element
	VertexBufferElement::VertexBufferElement(VertexBufferElement::DType dtype, u32 count)
		: dtype(dtype), count(count) {}

	u32 VertexBufferElement::get_stride() const {
		switch (dtype)
		{
		case DType::F32:
			return 4 * count;
		case DType::U32:
			return 4 * count;
		case DType::I32:
			return 4 * count;
		case DType::U8:
			return count;
		default:
			return 0;
		}
	}
	
	// vertex buffer layout
	VertexBufferLayout::VertexBufferLayout()
		: m_elements(), m_stride(0) {}
	const List<VertexBufferElement> VertexBufferLayout::get_elements() const {
		return m_elements;
	}
	void VertexBufferLayout::push(VertexBufferElement::DType dtype, u32 count) {
		m_elements.emplace_back(dtype, count);
		m_stride += m_elements.back().get_stride();
	}
	u32 VertexBufferLayout::get_stride() const {
		return m_stride;
	}

	// vertex buffer
	VertexBuffer_OPENGL::VertexBuffer_OPENGL(const void* vertices, adress size, bool is_static)
		: m_id(0), m_is_static(is_static)
	{
		glGenBuffers(1, &m_id);
		bind();
		if (m_is_static)
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		else
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}
	VertexBuffer_OPENGL::~VertexBuffer_OPENGL() {
		if (m_id != 0) {
			glDeleteBuffers(1, &m_id);
		}
	}
	VertexBuffer_OPENGL::VertexBuffer_OPENGL(VertexBuffer_OPENGL&& other) 
		: m_id(other.m_id), m_is_static(other.m_is_static) {
		other.m_id = 0;
	}
	
	void VertexBuffer_OPENGL::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	void VertexBuffer_OPENGL::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer_OPENGL::overwrite_data(const void* vertices, adress size, adress offset)
	{
		if (m_is_static)
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		else
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}

	// index buffer
	IndexBuffer_OPENGL::IndexBuffer_OPENGL(const List<u32>& indices, bool is_static)
		: m_id(0), m_is_static(is_static)
	{
		glGenBuffers(1, &m_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}
	IndexBuffer_OPENGL::~IndexBuffer_OPENGL()
	{
		glDeleteBuffers(1, &m_id);
	}

	void IndexBuffer_OPENGL::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}
	void IndexBuffer_OPENGL::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer_OPENGL::overwrite_data(const List<u32>& indices, u32 offset)
	{
		if (m_is_static)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);
		else
			glBufferSubData(GL_ARRAY_BUFFER, offset, indices.size() * sizeof(u32), indices.data());
	}

	// vertex array
	VertexArray_OPENGL::VertexArray_OPENGL(const VertexBuffer_OPENGL& vb, const VertexBufferLayout& layout)
	{
		glGenVertexArrays(1, &m_id);
		bind();
		vb.bind();
		
		auto& elements = layout.get_elements();
		u64 offset = 0;
		for (u32 i = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			if (element.dtype == VertexBufferElement::DType::I32 || element.dtype == VertexBufferElement::DType::U32) {
				glVertexAttribIPointer(i, element.count, (i32)element.dtype, layout.get_stride(), (const void*)offset);
			}
			else {
				glVertexAttribPointer(i, element.count, (i32)element.dtype, GL_FALSE, layout.get_stride(), (const void*)offset);
			}
			offset += element.get_stride();
		}
	}

	VertexArray_OPENGL::~VertexArray_OPENGL()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray_OPENGL::bind() const
	{
		glBindVertexArray(m_id);
	}
	void VertexArray_OPENGL::unbind() const
	{
		glBindVertexArray(0);
	}
}