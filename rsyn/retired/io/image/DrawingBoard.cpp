/* Copyright 2014-2018 Rsyn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include <cmath>

#include "DrawingBoard.h"


namespace Rsyn {

// -----------------------------------------------------------------------------

const DrawingBoard::Rgb DrawingBoard::BLACK(0, 0, 0);
const DrawingBoard::Rgb DrawingBoard::WHITE(255, 255, 255);
const DrawingBoard::Rgb DrawingBoard::SMOOTH_RED(0xFF, 0x63, 0x84);
const DrawingBoard::Rgb DrawingBoard::SMOOTH_GREEN(0x4B, 0xC0, 0xC0);
const DrawingBoard::Rgb DrawingBoard::SMOOTH_YELLOW(0xFF, 0xCE, 0x56);
const DrawingBoard::Rgb DrawingBoard::SMOOTH_GRAY(0xE7, 0xE9, 0xED);
const DrawingBoard::Rgb DrawingBoard::SMOOTH_BLUE(0x36, 0xA2, 0xEB);

const std::uint8_t DrawingBoard::ASCII[95][13] = {
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// space :32
{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},// ! :33
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}  // :126
};

// -----------------------------------------------------------------------------

DrawingBoard::DrawingBoard() {
	clsDrawingStyle = STROKE;
	clsStrokeWidth = 1;
	clsImage.recreate(512, 512);
	boost::gil::rgb8_pixel_t white(255, 255, 255);
	boost::gil::fill_pixels(boost::gil::view(clsImage), white);
	clsOutline.resize(clsImage.height());
} // end constructor

// -----------------------------------------------------------------------------

void 
DrawingBoard::drawLine(int x0, int y0, int x1, int y1) {
	// Note: http://members.chello.at/easyfilter/bresenham.html

   int dx =  std::abs(x1-x0);
   int dy = -std::abs(y1-y0);

   int sx = x0<x1 ? 1 : -1;
   int sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2; /* error value e_xy */

   while (true) {
	  setPixel(x0, y0, clsStrokeColor);
	  if (x0==x1 && y0==y1) break;
	  e2 = 2*err;
	  if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
	  if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   } // end while
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::drawLineAntiAlias(int x0, int y0, int x1, int y1) {
	// Note: http://members.chello.at/easyfilter/bresenham.html

	float wd = clsStrokeWidth;

	int dx = abs(x1-x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0 < y1 ? 1 : -1;
	int err = dx-dy, e2, x2, y2;
	float ed = dx+dy == 0 ? 1 : std::sqrt((float)dx*dx+(float)dy*dy);

	for (wd = (wd+1)/2; ; ) {
		setPixelBlend(x0, y0, clsStrokeColor, 1.0f - std::max(0.0f, (std::abs(err-dx+dy)/ed-wd+1)));
		e2 = err; x2 = x0;
		if (2*e2 >= -dx) {
		for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx)
			setPixelBlend(x0, y2 += sy, clsStrokeColor, 1.0f - std::max(0.0f, (std::abs(e2)/ed-wd+1)));
		if (x0 == x1) break;
		e2 = err; err -= dy; x0 += sx;
		}
		if (2*e2 <= dy) {
			for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy)
				setPixelBlend(x2 += sx, y0, clsStrokeColor, 1.0f - std::max(0.0f, (std::abs(e2)/ed-wd+1)));
			if (y0 == y1) break;
			err += dx; y0 += sy;
		} // end if
	} // end for
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::drawCircle(int xm, int ym, int r) {
	const float deg2rad = 3.141592653589793f / 180.0f;

	const int x0 = (int) std::round(xm + std::cos(0)*r);
	const int y0 = (int) std::round(ym + std::sin(0)*r);
	moveTo(x0, y0);
	for (int i = 1; i < 360; i++) {
		const float alpha = i*deg2rad;
		const int x1 = xm + (int) std::round(std::cos(alpha)*r);
		const int y1 = ym + (int) std::round(std::sin(alpha)*r);
		lineTo(x1, y1);
	} // end for
	lineTo(x0, y0);

	render();
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::drawRectangle(int x, int y, int width, int height) {
	moveTo(x, y);
	lineTo(x + width, y);
	lineTo(x + width, y + height);
	lineTo(x, y + height);
	lineTo(x, y);

	render();
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::drawQuadraticCurve(
	const int x0, const int y0,
	const int x1, const int y1,
	const int x2, const int y2
) {
	const int N = 25;

	moveTo(x0, y0);
	for (int i = 0; i <= N; i++) {
		const float t1 = float(i)/float(N);
		const float t2 = t1*t1;
		const float a = 1-t1; // (1-t)^1
		const float b = a*a;  // (1-t)^2

		const int xt = (int) std::round(b*x0 + 2*a*t1*x1 + t2*x2);
		const int yt = (int) std::round(b*y0 + 2*a*t1*y1 + t2*y2);

		lineTo(xt, yt);
	} // end for

	render();
} // end for

// -----------------------------------------------------------------------------

void
DrawingBoard::drawCubicCurve(
	const int x0, const int y0,
	const int x1, const int y1,
	const int x2, const int y2,
	const int x3, const int y3
) {
	const int N = 25;

	moveTo(x0, y0);
	for (int i = 0; i <= N; i++) {
		const float t1 = float(i)/float(N);
		const float t2 = t1*t1;
		const float t3 = t2*t1;
		const float a = 1-t1; // (1-t)^1
		const float b = a*a;  // (1-t)^2
		const float c = b*a;  // (1-t)^3

		const int xt = (int) std::round(c*x0 + 3*b*t1*x1 + 3*a*t2*x2 + t3*x3);
		const int yt = (int) std::round(c*y0 + 3*b*t1*y1 + 3*a*t2*y2 + t3*y3);

		lineTo(xt, yt);
	} // end for

	render();
} // end for

// -----------------------------------------------------------------------------

void
DrawingBoard::drawCharacter(const int x, const int y, char ch) {
	const int index = ch - ' ';
	if (index < 0 || index >= 96)
		return;

	const std::uint8_t * data = ASCII[index];
	for (int row = 0; row < 13; row++) {
		const std::uint8_t line = data[row];
		for (int col = 0; col < 8; col++) {
			if (line & (1 << (7 - col))) {
				setPixel(x + col, y - row, clsStrokeColor);
			} // end if
		} // end for
	} // end for
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::drawText(const int x, const int y, const std::string &text) {
	int cx = x;
	for (std::size_t i = 0; i < text.length(); i++) {
		drawCharacter(cx, y, text[i]);
		cx += 10;
	} // end method
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::render() {
	const int numPoints = clsPath.size();

	// Fill
	if (clsDrawingStyle != STROKE) {
		clsOutlineMaxY = 0;
		clsOutlineMinY = clsImage.height() - 1;

		Direction previousDirection = NONE;
		
		for (int i = 0; i < numPoints - 1; i++) {
			const RasterPoint &p0 = clsPath[i];
			const RasterPoint &p1 = clsPath[i+1];
			const Direction currentDirection = getDirection(p0.y, p1.y);
			const bool skipFirst = currentDirection == previousDirection;
			render_createOuline(p0.x, p0.y, p1.x, p1.y, skipFirst);
			previousDirection = currentDirection;
		} // end for

		// Close the path.
		if (numPoints > 1 && (clsPath.front() != clsPath.back())) {
			const RasterPoint &p0 = clsPath.front();
			const RasterPoint &p1 = clsPath.back();
			const Direction currentDirection = getDirection(p0.y, p1.y);
			const bool skipFirst = currentDirection == previousDirection;
			render_createOuline(p0.x, p0.y, p1.x, p1.y, skipFirst);
			previousDirection = currentDirection;
		} // end if

		render_doFilling();
	} // end if

	// Stroke.
	if (clsDrawingStyle != FILL) {
		for (int i = 0; i < numPoints - 1; i++) {
			const RasterPoint &p0 = clsPath[i];
			const RasterPoint &p1 = clsPath[i+1];
			drawLine(p0.x, p0.y, p1.x, p1.y);
		} // end for
	} // end if

	// Clean-up.
	clsPath.clear();
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::render_createOuline(int x0, int y0, int x1, int y1, const bool skipFirst) {
	const int dx = +std::abs(x1-x0);
	const int dy = -std::abs(y1-y0);

	const int sx = x0<x1 ? 1 : -1;
	const int sy = y0<y1 ? 1 : -1;

	int error = dx+dy;
	bool first = true;
	int prevy = y0;

	while (true) {
		const int clipx = std::max(0, std::min(x0, (int) clsImage.width ()));
		const int clipy = std::max(0, std::min(y0, (int) clsImage.height()));
		if (clipy != prevy || (first && !skipFirst)) {
			clsOutline[clipy].push_back(clipx);
		} // end if
		clsOutlineMinY = std::min(clsOutlineMinY, clipy);
		clsOutlineMaxY = std::max(clsOutlineMaxY, clipy);
		prevy = clipy;

		if (x0==x1 && y0==y1) break;
		const int e = 2*error;
		if (e >= dy) { error += dy; x0 += sx; }
		if (e <= dx) { error += dx; y0 += sy; }

		first = false;
   } // end while
} // end method

// -----------------------------------------------------------------------------

void
DrawingBoard::render_doFilling() {
	if (clsDrawingStyle == STROKE)
		return;

	for (int y = clsOutlineMinY; y <= clsOutlineMaxY; y++) {
		std::vector<int> &xs = clsOutline[y];
		std::sort(xs.begin(), xs.end());
		const int numPoints = xs.size();
		for (int k = 0; k < numPoints - 1; k++) {
			const int x0 = xs[k] + 1;
			const int x1 = xs[k+1] - 1;
			for (int x = x0; x <= x1; x++) {
				setPixel(x, y, clsFillColor);
			} // end for
			k++;
		} // end for
		xs.clear();
	} // end for
} // end method

} // end namespace