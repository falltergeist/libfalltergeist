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

#include "../Frm/Direction.h"
#include "../Frm/Format.h"
#include "../Frm/Frame.h"
#include "../FileWrapper.h"

namespace libfalltergeist {
    namespace Frm {

        Format::Format(std::shared_ptr<IFile> file) {
            _directions = std::make_shared<std::vector<std::shared_ptr<IDirection>>>();
            FileWrapper wrapper(std::move(file));
            wrapper.seek(0);

            _version = wrapper.uint32();
            _framesPerSecond = wrapper.uint16();
            _actionFrame = wrapper.uint16();
            _framesPerDirection = wrapper.uint16();

            uint16_t shiftX[6];
            uint16_t shiftY[6];
            uint32_t dataOffset[6];
            for (unsigned int i = 0; i != 6; ++i) {
                shiftX[i] = wrapper.uint16();
            }
            for (unsigned int i = 0; i != 6; ++i) {
                shiftY[i] = wrapper.uint16();
            }
            for (unsigned int i = 0; i != 6; ++i) {
                dataOffset[i] = wrapper.uint32();
                if (i > 0 && dataOffset[i - 1] == dataOffset[i]) {
                    continue;
                }

                auto direction = std::make_shared<Direction>(shiftX[i], shiftY[i]);
                _directions->push_back(direction);
            }

            for (unsigned int i = 0; i != 6; ++i) {
                if (i > 0 && dataOffset[i - 1] == dataOffset[i]) {
                    continue;
                }

                wrapper.seek(dataOffset[i] + 62);

                // read all frames
                for (unsigned j = 0; j != _framesPerDirection; ++j) {
                    uint16_t width = wrapper.uint16();
                    uint16_t height = wrapper.uint16();
                    // Number of pixels for this frame
                    // We don't need this, because we already have width*height
                    wrapper.uint32();
                    int16_t offsetX = wrapper.int16();
                    int16_t offsetY = wrapper.int16();
                    auto frame = std::make_shared<Frame>(width, height, offsetX, offsetY);

                    // Pixels data
                    frame->indexes()->resize(width * height);
                    wrapper.readBytes(frame->indexes()->data(), width * height);
                    _directions->at(i)->frames()->push_back(frame);
                }
            }
        }

        uint32_t Format::version() {
            return _version;
        }

        uint16_t Format::framesPerSecond() {
            return _framesPerSecond;
        }

        uint16_t Format::framesPerDirection() {
            return _framesPerDirection;
        }

        uint16_t Format::actionFrame() {
            return _actionFrame;
        }

        std::shared_ptr<std::vector<std::shared_ptr<IDirection>>> Format::directions() {
            return _directions;
        }

/*
        uint16_t File::width() const {
            std::vector <uint16_t> widths;
            for (auto direction : _directions) {
                widths.push_back(direction->width());
            }
            return *std::max_element(widths.begin(), widths.end());
        }

        uint16_t File::height() const {
            uint16_t height = 0;

            for (auto direction : _directions) {
                height += direction->height();
            }
            return height;
        }

        uint32_t *File::rgba(Pal::Format *palFile) {
            if (_rgba) return _rgba;
            _rgba = new uint32_t[width() * height()]();

            uint16_t w = width();

            unsigned positionY = 0;
            for (auto direction : _directions) {
                unsigned positionX = 0;
                for (auto frame : *direction->frames()) {
                    for (unsigned y = 0; y != frame->height(); ++y) {
                        for (unsigned x = 0; x != frame->width(); ++x) {
                            _rgba[((y + positionY) * w) + x + positionX] = *palFile->color(frame->index(x, y));
                        }
                    }
                    positionX += frame->width();
                }
                positionY += direction->height();
            }
            return _rgba;
        }

        int16_t File::offsetX(unsigned int direction, unsigned int frame) const {
            if (direction >= _directions.size()) direction = 0;
            return _directions.at(direction)->frames()->at(frame)->offsetX();
        }

        int16_t File::offsetY(unsigned int direction, unsigned int frame) const {
            if (direction >= _directions.size()) direction = 0;
            return _directions.at(direction)->frames()->at(frame)->offsetY();
        }

        bool File::animatedPalette() {
            if (_animatedMasks.empty()) animatedMasks();
            return _animatedPalette;
        }

        std::map<MASK, uint8_t *> *File::animatedMasks() {
            if (!_animatedMasks.empty()) return &_animatedMasks;

            uint16_t w = width();
            uint16_t h = height();

            unsigned int positionY = 0;
            for (auto direction : _directions) {
                unsigned int positionX = 0;
                for (auto frame : *direction->frames()) {
                    for (unsigned int y = 0; y != frame->height(); ++y) {
                        for (unsigned int x = 0; x != frame->width(); ++x) {
                            uint8_t index = frame->index(x, y);

                            if (index >= 229 && index <= 232) {
                                if (!_animatedMasks[MASK::SLIME]) {
                                    _animatedMasks[MASK::SLIME] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::SLIME][((y + positionY) * w) + x + positionX] = index;
                            } else if (index >= 233 && index <= 237) {
                                if (!_animatedMasks[MASK::MONITOR]) {
                                    _animatedMasks[MASK::MONITOR] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::MONITOR][((y + positionY) * w) + x + positionX] = index;

                            } else if (index >= 238 && index <= 242) {
                                if (!_animatedMasks[MASK::FIRE_SLOW]) {
                                    _animatedMasks[MASK::FIRE_SLOW] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::FIRE_SLOW][((y + positionY) * w) + x + positionX] = index;
                            } else if (index >= 243 && index <= 247) {
                                if (!_animatedMasks[MASK::FIRE_FAST]) {
                                    _animatedMasks[MASK::FIRE_FAST] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::FIRE_FAST][((y + positionY) * w) + x + positionX] = index;
                            } else if (index >= 248 && index <= 253) {
                                if (!_animatedMasks[MASK::SHORE]) {
                                    _animatedMasks[MASK::SHORE] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::SHORE][((y + positionY) * w) + x + positionX] = index;
                            } else if (index == 254) {
                                if (!_animatedMasks[MASK::REDDOT]) {
                                    _animatedMasks[MASK::REDDOT] = new uint8_t[w * h]();
                                }
                                _animatedMasks[MASK::REDDOT][((y + positionY) * w) + x + positionX] = index;
                            }
                            if (index >= 229 && index <= 254) {
                                _animatedPalette = true;
                            }
                        }
                    }
                    positionX += direction->width();
                }
                positionY += direction->height();
            }
            return &_animatedMasks;
        }
        */
    }
}
