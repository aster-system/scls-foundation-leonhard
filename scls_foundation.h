//******************
//
// scls_foundation.h
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
// This file contains the includes to all the others SCLS Foundation files.
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

#ifndef SCLS_FOUNDATION
#define SCLS_FOUNDATION

// Include every needed SLCS Foundation files
#include "scls_foundation_directory/scls_foundation_binary.h"
#include "scls_foundation_directory/scls_foundation_core.h"
#include "scls_foundation_directory/scls_foundation_file.h"
#include "scls_foundation_directory/scls_foundation_math.h"
#include "scls_foundation_directory/scls_foundation_string.h"
// Include every needed SLCS Foundation files (indev)
#ifdef __ASTER_DEV
#include "scls_foundation_directory/scls_foundation_compression.h"
#endif // __ASTER_DEV

// Define SCLS_INIT
#ifndef SCLS_FOUNDATION_INIT
#define SCLS_FOUNDATION_INIT SCLS_FOUNDATION_CORE_INIT SCLS_FOUNDATION_BINARY_INIT
#endif // SCLS_FOUNDATION_INIT
#ifndef SCLS_INIT
#define SCLS_INIT SCLS_FOUNDATION_INIT
#endif // SCLS_INIT

#endif // SCLS_FOUNDATION
