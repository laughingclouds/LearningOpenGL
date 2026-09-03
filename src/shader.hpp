#pragma once
#include <utility>

std::pair<unsigned int, unsigned int> createShaderPrograms();

// Return True if error detected during shader compilation
bool isError();