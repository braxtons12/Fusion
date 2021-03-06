/**
 * Basic Vertex Array class.
 * Used to Encapsulate openGL VAOs into a local datatype
 * Header
 *
 * Version: 0.0.1
 * C 2018 Braxton Salyer
 *
 **/

#ifndef _VERTEX_ARRAY
#define _VERTEX_ARRAY

#include "graphics/buffers/buffer.h"

#include <vector>
#include <GL/glew.h>

namespace ftk { namespace core { namespace graphics {

    class VertexArray {

        private:
            GLuint m_ArrayID;
            std::vector<Buffer*> m_Buffers;

        public:
            /*
             * Constructor
             */
            VertexArray();

            /*
             * Destructor
             */
            ~VertexArray();

            /*
             * add the given buffer to the vertex array
             */
            void addBuffer(Buffer* buffer, GLuint index);

            /*
             * Bind the vertex array in openGL
             */
            inline void bind() const { glBindVertexArray(m_ArrayID); }

            /*
             * Unbind the vertex array
             */
            inline void unbind() const { glBindVertexArray(0); }
    };

}}}

#endif
