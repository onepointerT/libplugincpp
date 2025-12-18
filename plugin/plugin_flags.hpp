/**
 * @file input_flags.hpp
 * @brief The input flag solution
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibLogC++: An intuitive and highly customizable LGPL library for logging with C++.
	Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#pragma once

#include "cppenumflag.hpp"


namespace plugin {


class PluginFlag
	:	public util::string_flag
{
public:
	PluginFlag() = default;
};


class PluginTag
	:	public util::string_flag
{
public:
	PluginTag() = default;
};


} // namespace plugin