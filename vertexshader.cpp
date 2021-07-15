const char* vertexshaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 verticles;"
"layout (location = 1) in vec2 textCoordsInp;"
"out vec2 textCoord;"
"void main(){"
"gl_Position = vec4(vec2(verticles[0],verticles[1]),1.0,1.0);"
"textCoord = textCoordsInp;"
"}";