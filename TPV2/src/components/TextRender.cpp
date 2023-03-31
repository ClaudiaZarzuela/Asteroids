#include "../checkML.h"
#include "TextRender.h"

 //renderiza el texto
void TextRender::render() {
	text->render(x, y);
	if (text != nullptr) {
		text->render(x, 100);
	}
}