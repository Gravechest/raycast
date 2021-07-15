const char* fragshaderSource = "#version 330 core\n"
"out vec4 FragColor;"
"in vec2 textCoord;"
"uniform sampler2D ourTexture;"
"void main(){"
"FragColor = texture(ourTexture,textCoord);"
"}";