#version 330

uniform vec4 objectColor;

in vec2 TexCoord;
out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

uniform sampler2D texture1;

void main(void) {
	pixelColor=objectColor;
}
