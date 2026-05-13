#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Textura.h"
#include <iostream>

Textura::~Textura() {
    if (id != 0)
        glDeleteTextures(1, &id);
}

bool Textura::cargar(const char* archivo) {
    int ancho, alto, canales;

    unsigned char* data = stbi_load(archivo, &ancho, &alto, &canales, 4);
    if (!data) {
        std::cout << "Error cargando textura: " << archivo << "\n";
        return false;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA,
        ancho, alto, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data
    );

    stbi_image_free(data);
    return true;
}

void Textura::activar() const {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
}
