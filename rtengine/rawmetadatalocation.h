/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _RAWMETADATALOCATION_
#define _RAWMETADATALOCATION_

namespace rtengine
{

class RawMetaDataLocation {

public:
    int exifBase;
    int ciffBase;
    int ciffLength;

    RawMetaDataLocation () : exifBase(-1), ciffBase(-1), ciffLength(-1) {}
    explicit RawMetaDataLocation (int exifBase) : exifBase(exifBase), ciffBase(-1), ciffLength(-1) {}
    RawMetaDataLocation (int ciffBase, int ciffLength) : exifBase(-1), ciffBase(ciffBase), ciffLength(ciffLength) {}
    RawMetaDataLocation (int exifBase, int ciffBase, int ciffLength) : exifBase(exifBase), ciffBase(ciffBase), ciffLength(ciffLength) {}
};

}

#endif

