//******************
//
// scls_foundation_random.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Foundation "Leonhard" part represents the foundation of SCLS.
// It is named after the "Father of modern mathematics", Leonhard Euler.
//
// This file contains the source code of scls_foundation_random.h.
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

// Include the needed header
#include "../scls_foundation_directory/scls_foundation_random.h"

// The namespace "scls" is used to simplify the all.
namespace scls {

    // Random engine
    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Returns a random int between two included numbers
    int random_int_between_included(int min_number, int max_number){double d = dis(gen);if(d == 1){return max_number;}return min_number + std::floor(static_cast<double>((max_number - min_number) + 1) * d);}
}
