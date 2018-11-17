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

#pragma once

#include "../IFile.h"
#include "../Frm/IFormat.h"

namespace libfalltergeist {
    namespace Frm {
        class Format : public IFormat {
        public:
            explicit Format(std::shared_ptr<IFile> file);
            ~Format() override = default;
            uint32_t version() override;
            uint16_t framesPerSecond() override;
            uint16_t framesPerDirection() override;
            uint16_t actionFrame() override;
            std::shared_ptr<std::vector<std::shared_ptr<IDirection>>> directions() override;
        private:
            uint32_t _version;
            uint16_t _framesPerSecond;
            uint16_t _framesPerDirection;
            uint16_t _actionFrame;
            std::shared_ptr<std::vector<std::shared_ptr<IDirection>>> _directions;
        };
    }
}
