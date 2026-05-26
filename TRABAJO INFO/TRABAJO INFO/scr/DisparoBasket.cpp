#include "DisparoBasket.h"
#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include "ETSIDI.h" 

DisparoBasket::DisparoBasket(float x, float y, float z,
    float velX, float velY, float velZ, bool conEstela)
    : pelota(x, y, z, velX, velY, velZ), conEstela(conEstela) {
    texID = ETSIDI::getTexture("elementos/bola_baloncesto.png").id;
}

void DisparoBasket  ::actualizar(float dt) {
    if (!pelota.estaActiva()) return;

    if (conEstela)
        puntosEstela.push_back({ pelota.getPosX(), pelota.getPosY(), pelota.getPosZ() });

    pelota.mueve(dt);
}
void DisparoBasket::dibujar(bool dibujarEstela) const {
    if (!pelota.estaActiva()) return;

    float px = pelota.getPosX();
    float py = pelota.getPosY();
    float pz = pelota.getPosZ();
    float r = 1.0f;

    // estela
    if (dibujarEstela && !puntosEstela.empty()) {
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i < puntosEstela.size(); i++) {
            float alpha = (float)i / (float)puntosEstela.size();
            glColor4f(1.0f, 0.6f, 0.0f, alpha);
            glVertex3f(puntosEstela[i].x, puntosEstela[i].y, puntosEstela[i].z);
        }
        glEnd();
        glDisable(GL_BLEND);
    }

    // pelota con textura
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1); glVertex3f(px - r, py - r, pz);
    glTexCoord2d(1, 1); glVertex3f(px + r, py - r, pz);
    glTexCoord2d(1, 0); glVertex3f(px + r, py + r, pz);
    glTexCoord2d(0, 0); glVertex3f(px - r, py + r, pz);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
void DisparoBasket::desactivar() {
    pelota.desactivar();
}

bool DisparoBasket::estaActivo() const {
    return pelota.estaActiva();
}

bool DisparoBasket::colisionaConAro(float aroX, float aroY, float aroZ, float radio) const {
    float dx = pelota.getPosX() - aroX;
    float dy = pelota.getPosY() - aroY;
    float dz = pelota.getPosZ() - aroZ;
    return std::sqrt(dx * dx + dy * dy + dz * dz) <= radio;
}