#include "../checkML.h"
#include "TextRender.h"

// renderiza el texto
void TextRender::render() {
	text1->render(x, y);
	if (text2 != nullptr) {
		text2->render(x, 100);
	}
}