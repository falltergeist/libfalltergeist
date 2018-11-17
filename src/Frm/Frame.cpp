/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../Frm/Frame.h"

namespace libfalltergeist {
    namespace Frm {
        Frame::Frame(uint16_t width, uint16_t height, int16_t offsetX, int16_t offsetY) {
            _width = width;
            _height = height;
            _offsetX = offsetX;
            _offsetY = offsetY;
            _indexes = std::make_shared<std::vector<uint8_t>>();
            _indexes->resize(width * height);
        }

        uint16_t Frame::width() {
            return _width;
        }

        uint16_t Frame::height() {
            return _height;
        }

        int16_t Frame::offsetX() {
            return _offsetX;
        }

        int16_t Frame::offsetY() {
            return _offsetY;
        }

        std::shared_ptr<std::vector<uint8_t>> Frame::indexes() {
            return _indexes;
        }
    }
}
